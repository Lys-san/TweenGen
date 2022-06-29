/** Graphic interface for TweenGen program using MLV library. */

#include <stdio.h>

#include "armature.h"
#include "frame.h"

#ifndef __INTERFACE__
#define __INTERFACE__
	
	#define BACKGROUND_COLOR   MLV_COLOR_GREY25
	#define TEXT_COLOR_1       MLV_COLOR_WHITE
	#define TEXT_COLOR_2       MLV_COLOR_GREY1
	#define FRAME_NUM_COLOR    MLV_COLOR_RED
	#define TOOLBAR_COLOR      MLV_COLOR_GREY10
	#define MENU_COLOR         MLV_COLOR_GREY90

	/* Control points color */
	#define CRT_FRAME_PT_COLOR MLV_COLOR_BLACK
	#define PVS_FRAME_PT_COLOR MLV_COLOR_LIGHT_BLUE
	#define NXT_FRAME_PT_COLOR MLV_COLOR_LIGHT_GREEN

	#define SELECT_PT_COLOR    MLV_COLOR_ORANGE


	/* Bones color */
	#define CRT_FRAME_LN_COLOR MLV_COLOR_BLACK
	#define PVS_FRAME_LN_COLOR MLV_COLOR_PURPLE4
	#define NXT_FRAME_LN_COLOR MLV_COLOR_DARK_GREEN

	#define SELECT_LN_COLOR    MLV_COLOR_DARK_ORANGE


	/* Other colors... */
	
	/* Dimensions */
	#define CTRL_POINT_RADIUS  4
	#define MARGIN_RATIO       (1.0/20.0) /* window-margin ratio */
	#define MENU_RATIO         (1.0/40.0) /* window-menu height ratio */

	/* other constants */
	#define MAX_ONIONSKIN_LEVEL 5

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

	/** Draws a white rectangle on the workspace */
	void drawWhiteFrame(unsigned int windowWidth, unsigned int windowHeight);

	/** Draw the current frame on the workspace. */
	void drawFrame(FrameSeq frame, unsigned int windowWidth, unsigned int windowHeight);

	/** Closes the current window. */
	void closeWindow();

	/** Draws a given control point on the canvas. */
	void drawCtrlPoint(CtrlPoint cp, FramePos framePos, Uint8 opacity);

	/** Highlights a given point. */
	void drawPointSelection(CtrlPoint cp);

	/** Draws a given bone o, the canvas. */
	void drawBone(Bone b, FramePos framePos, Uint8 opacity);

	/** Draws a given armature on the canvas. */
	void drawArmature(Armature a, FramePos framePos, Uint8 opacity);

	/** Displays control points from neighbor frames. 
	* level parameter indicates how many neighbor frames are shown. */
	void onionSkin(FrameSeq seq, unsigned int level);

#endif