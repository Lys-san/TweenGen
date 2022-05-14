/** Graphic interface for TweenGen program using MLV library. */

#include <stdio.h>

#include "armature.h"
#include "frame.h"

#ifndef __INTERFACE__
#define __INTERFACE__
	
	#define BACKGROUND_COLOR  MLV_COLOR_GREY25
	#define TEXT_COLOR_1      MLV_COLOR_WHITE
	#define TEXT_COLOR_2      MLV_COLOR_GREY1
	#define FRAME_NUM_COLOR   MLV_COLOR_RED
	#define TOOLBAR_COLOR     MLV_COLOR_GREY10
	#define MENU_COLOR        MLV_COLOR_GREY90

	/* Control points color */
	#define CRT_FRAME_PT_COLOR MLV_COLOR_BLACK
	#define PVS_FRAME_PT_COLOR MLV_COLOR_DARK_SLATE_BLUE
	#define NXT_FRAME_PT_COLOR MLV_COLOR_GREEN

	/* Bones color */
	#define CRT_FRAME_LN_COLOR MLV_COLOR_BLACK
	#define PVS_FRAME_LN_COLOR MLV_COLOR_PURPLE4
	#define NXT_FRAME_LN_COLOR MLV_COLOR_DARK_GREEN
	
	/* Dimensions */
	#define CTRL_POINT_RADIUS  5
	#define MARGIN_RATIO       (1.0/20.0) /* window-margin ratio */
	#define MENU_RATIO         (1.0/40.0) /* window-menu height ratio */

	typedef enum {
		CRT_FRAME, /* current frame */
		PVS_FRAME, /* previous frame */
		NXT_FRAME  /* next frame */
	} FramePos;

	/** Opens the TweenGen window and stores the dimensions of the created
	 *  window. */
	void createWindow(unsigned int *windowWidth, unsigned int *windowHeight);

	/** Draws the side toolbar. */
	void drawToolbar(unsigned int windowWidth, unsigned int windowHeight);

	/** Drawing of the interface (buttons etc...) */
	void drawInterface(unsigned int windowWidth, unsigned int windowHeight);

	/** Draws the top menu. */
	void drawTopMenu(unsigned int windowWidth, unsigned int windowHeight);

	/** Resizes the current frame for it to fit in the workspace. */
	void resizeFrame(FrameSeq *frame, unsigned int windowWidth, unsigned int windowHeight);

	/** Draw the current frame in the workspace. */
	void drawFrame(FrameSeq frame, unsigned int windowWidth, unsigned int windowHeight);

	/** Closes the current window. */
	void closeWindow();

	/** Draws a given control point on the canvas. */
	void drawCtrlPoint(CtrlPoint cp, FramePos framePos);

	/** Draws a given armature on the canvas. */
	void drawArmature();

#endif