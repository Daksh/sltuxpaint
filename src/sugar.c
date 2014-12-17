/*
  sugar.c

  Sugar DE integration

  Copyright (C) 2010, Aleksey Lim

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  (See COPYING.txt)
*/

#include <sys/stat.h>
#include <unistd.h>
#include <SDL/SDL_syswm.h>

#include <polyol/env.h>
#include <polyol/ds.h>
#include <polyol/shell.h>

#include "sugar.h"

static void chooser_response_cb(GObject*, const gchar*);

static SugarShell *shell;
static SugarJournal *journal;
static SugarJobject *jobject;
static gboolean new_jobject;
static GMainLoop *chooser_loop;
static char *chosen_object_id;

void sugar_setup(int * argc, char *** argv)
{
  g_type_init();

  if (!sugar_init(argv, argc))
    return;

  g_debug("Use sugar mode");

  sugar_environ_set_sync_dbus(TRUE);

  if (sugar_environ_get_object_id() != NULL)
    jobject = sugar_jobject_find(sugar_environ_get_object_id());

  if (jobject != NULL)
    g_debug("Journal entry %s was found", sugar_environ_get_object_id());
  else
  {
    jobject = sugar_jobject_create();
    g_debug("Create new Journal entry");
  }

  shell = sugar_shell_new();

  journal = sugar_journal_new();
  g_signal_connect(journal, "chooser-response",
          G_CALLBACK(chooser_response_cb), NULL);

  chooser_loop = g_main_loop_new (NULL, FALSE);
}

int sugar_detected()
{
  return sugar_environ_get_initialized();
}

void sugar_cleanup()
{
  if (!sugar_detected())
    return;

  g_debug("Cleanup sugar mode");

  if (new_jobject)
    sugar_journal_show_object(journal, sugar_jobject_get_uid(jobject));

  g_object_unref(G_OBJECT(jobject));
  jobject = NULL;

  g_object_unref(G_OBJECT(shell));
  shell = NULL;

  g_object_unref(G_OBJECT(journal));
  journal = NULL;

  g_main_loop_unref(chooser_loop);
  chooser_loop = NULL;
}

void sugar_setup_x11(int * window_width, int * window_height)
{
  if (!sugar_detected())
    return;

  SDL_SysWMinfo wminfo;
  SDL_VERSION(&wminfo.version);

  if (SDL_GetWMInfo(&wminfo))
  {
    Display * display = wminfo.info.x11.display;
    Window window = wminfo.info.x11.wmwindow;

    wminfo.info.x11.lock_func();

    sugar_environ_set_window(display, window);
    *window_width = DisplayWidth(display, DefaultScreen(display));
    *window_height = DisplayHeight(display, DefaultScreen(display));

    wminfo.info.x11.unlock_func();
  }
  else
  {
      g_warning ("Cannot get WMInfo to setup X11 properties");
  }
}

const char *sugar_get_savedir(void)
{
  return sugar_environ_get_activity_root();
}

char *sugar_get_image_file()
{
  if (!sugar_detected())
    return NULL;

  const char * file_path = sugar_jobject_get_file_path(jobject);

  if (file_path != NULL)
    g_debug("Load image from journal entry %s", sugar_jobject_get_uid(jobject));

  return g_strdup(file_path);
}

void sugar_save_image(char *path)
{
  if (!sugar_detected())
    return;

  if (sugar_jobject_get_uid(jobject) == NULL)
      new_jobject |= TRUE;

  sugar_jobject_set_mime_type(jobject, "image/png");
  sugar_jobject_write_file(jobject, path, TRUE);

  g_debug("Saved %s image to journal entry %s", path,
          sugar_jobject_get_uid(jobject));
}

void sugar_save_thumb(char *path)
{
  struct stat fstat;
  g_return_if_fail(stat(path, &fstat) == 0);

  FILE *fp = fopen(path, "rb");
  g_return_if_fail(fp);

  GArray *preview = g_array_new(FALSE, FALSE, 1);
  g_array_set_size(preview, fstat.st_size);

  if (fread(preview->data, 1, fstat.st_size, fp) == (size_t) fstat.st_size)
  {
    sugar_jobject_set_preview(jobject, preview);
    sugar_jobject_write(jobject);
  }

  fclose(fp);
  unlink(path);
}

const char *sugar_open()
{
  sugar_journal_choose_object(journal, SUGAR_MIME_IMAGE);
  g_main_loop_run(chooser_loop);

  if (chosen_object_id == NULL)
    return NULL;

  SugarJobject *image_jobject = sugar_jobject_find(chosen_object_id);
  g_free(chosen_object_id);
  chosen_object_id = NULL;
  g_return_val_if_fail(image_jobject, NULL);

  const char *image_path = sugar_jobject_get_file_path(image_jobject);
  g_return_val_if_fail(image_path, NULL);

  return g_strdup(image_path);
}

static void chooser_response_cb(GObject *sender, const gchar *object_id)
{
  g_debug("SugarShell.chooser_response_cb=%s", object_id);
  chosen_object_id = g_strdup(object_id);
  g_main_loop_quit(chooser_loop);
}
