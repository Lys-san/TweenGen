/** Bones and armature of an object */
#include "interface.h"

#ifndef __EVENTS__
#define __EVENTS__

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

	/** Returns an event done by the user. */
	Event getEvent(unsigned int windowWidth, unsigned int windowHeight);

	/** Does an action according to a given event. 
	 *  Returns 1 if an action was performed, 0 othewise and
	 *  -1 if the user quits the program. */
	int doAction(Event ev, FrameSeq *frame, unsigned int windowWidth, unsigned int windowHeight);
#endif