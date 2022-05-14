/** Bones and armature of an object */
#include "interface.h"

#ifndef __EVENTS__
#define __EVENTS__
	#define EDIT_MODE 1 /* control points edition */

	typedef enum {
		NONE,
		TOOLBAR,
		MENU,
		NEXT_FRAME,
		PREV_FRAME,
		SAVE,
		QUIT
	} Event;

	typedef enum {
		EDIT_CTRL_POINTS
	} Toolbar;

	/** Does an action according to a given event. 
	 *  Returns 1 if an action was performed, 0 othewise and
	 *  -1 if the user quits the program. */
	int getAndApplyEvent(unsigned int windowWidth, unsigned int windowHeight, FrameSeq *frame);

#endif