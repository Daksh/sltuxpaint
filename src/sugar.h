/*
  sugar.h

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

#ifndef SUGAR_H
#define SUGAR_H

#ifdef SUGAR
  void sugar_setup(int * argc, char *** argv);
  void sugar_cleanup(void);
  void sugar_setup_x11(int * window_width, int * window_height);
  int sugar_detected(void);
  const char *sugar_get_savedir(void);
  char *sugar_get_image_file(void);
  void sugar_save_image(char *path);
  void sugar_save_thumb(char *path);
  const char *sugar_open(void);
#else
  void sugar_setup(int * argc, char *** argv) { }
  void sugar_cleanup(void) { }
  void sugar_setup_x11(int * window_width, int * window_height) { }
  int sugar_detected(void) { return 0; }
  const char *sugar_get_savedir(void) { return NULL; }
  char *sugar_get_image_file(void) { return NULL; }
  void sugar_save_image(char *path) { }
  void sugar_save_thumb(char *path) { }
  const char *sugar_open(void) { return NULL; }
#endif

#endif
