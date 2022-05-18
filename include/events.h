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

	/* modes */
	typedef struct {
		int onionSkin;
		int editMode;
	} State;

	/** Returns a state with modes set to 0 or 1. */
	State initState();

	/** Does an action according to a given event. 
	 *  Returns 1 if an action was performed, 0 othewise and
	 *  -1 if the user quits the program. */
	int getAndApplyEvent(unsigned int windowWidth, unsigned int windowHeight, FrameSeq *frame, State *s);

#endif