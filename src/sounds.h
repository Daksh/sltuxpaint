/*
  sounds.h

  For Tux Paint
  List of sound effects.

  Copyright (c) 2002-2007 by Bill Kendrick and others
  bill@newbreedsoftware.com
  http://www.tuxpaint.org/

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

  June 15, 2002 - July 5, 2007
  $Id: sounds.h,v 1.14 2007/07/17 18:41:22 wkendrick Exp $
*/

#ifndef SOUNDS_H
#define SOUNDS_H


/* Sounds available: */

#define SND_NONE -1

enum
{
  SND_HARP,			/* Begin / New */
  SND_CLICK,			/* Tool selections */
  SND_BLEEP,			/* Selector selection */
  SND_BUBBLE,			/* Color selection */
  SND_STAMP,			/* Using stamp tool */
  SND_LINE_START,		/* Using line tool */
  SND_LINE_END,
  SND_SCROLL,			/* Selector scroll buttons */
  SND_PAINT1,			/* Sound while painting */
  SND_PAINT2,
  SND_PAINT3,
  SND_PAINT4,
  SND_ERASER1,			/* Sound while erasing */
  SND_ERASER2,
  SND_SAVE,			/* Save sound effect */
  SND_PROMPT,			/* Prompt animation sound effect */
  SND_FLIP,			/* Magic flip */
  SND_MIRROR,			/* Magic mirror */
  SND_KEYCLICK,			/* Text tool keyboard click feedback */
  SND_KEYCLICKRING,		/* Text tool keyboard click feedback with bell ring */
  SND_RETURN,			/* Text tool carriage return sound */
  SND_SHRINK,			/* Stamp shrink */
  SND_GROW,			/* Stamp grow */
  SND_ITALIC_ON,		/* Italic on */
  SND_ITALIC_OFF,		/* Italic off */
  SND_AREYOUSURE,		/* "Are you sure?" */
  SND_YOUCANNOT,		/* "No no no!" */
  SND_TUXOK,			/* "Ok" */
  SND_THICK,
  SND_THIN,
  NUM_SOUNDS
};


/* Sound file filenames: */

/* FIXME: These should be moved to a .c file (sounds.c?) and extern'd here, to
   avoid being stored multiple times, and to avoid compiler warning
   -bjk 2007.07.17 */

static const char *sound_fnames[NUM_SOUNDS] = {
  "sounds/harp.wav",
  "sounds/click.wav",
  "sounds/bleep.wav",
  "sounds/bubble.wav",
  "sounds/stamp.wav",
  "sounds/line_start.wav",
  "sounds/line_end.wav",
  "sounds/scroll.wav",
  "sounds/paint1.wav",
  "sounds/paint2.wav",
  "sounds/paint3.wav",
  "sounds/paint4.wav",
  "sounds/eraser1.wav",
  "sounds/eraser2.wav",
  "sounds/save.wav",
  "sounds/prompt.wav",
  "sounds/flip.wav",
  "sounds/mirror.wav",
  "sounds/keyclick.wav",
  "sounds/typewriterbell.wav",
  "sounds/return.wav",
  "sounds/shrink.wav",
  "sounds/grow.wav",
  "sounds/italic_on.wav",
  "sounds/italic_off.wav",
  "sounds/areyousure.wav",
  "sounds/youcannot.wav",
  "sounds/tuxok.wav",
  "sounds/thick.wav",
  "sounds/thin.wav"
};

#endif
