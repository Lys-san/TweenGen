#include "interface.h"

void createWindow(unsigned int *windowWidth, unsigned int *windowHeight) {
	MLV_get_desktop_size(windowWidth, windowHeight);
	float ratio = 0.7; /* 1 for full-size window */
	*windowWidth  *= ratio;
	*windowHeight *= ratio;

	MLV_create_window_with_default_font(
		"TweenGen",
		"TweenGen 0.0.1",
		*windowWidth,
		*windowHeight,
		"files/geo_1.ttf",
		12
	);

	MLV_draw_filled_rectangle(
		0,
		0,
		*windowWidth,
		*windowHeight,
		BACKGROUND_COLOR
	);

	drawInterface(*windowWidth, *windowHeight); /* set pos to first frame at first */

	MLV_actualise_window();
}

void drawToolbar(unsigned int windowWidth, unsigned int windowHeight) {
	MLV_draw_filled_rectangle(
		0,
		0,
		MARGIN_RATIO * windowWidth,
		windowHeight,
		TOOLBAR_COLOR
	);
}

void drawTopMenu(unsigned int windowWidth, unsigned int windowHeight) {
	MLV_draw_filled_rectangle(
		0,
		0,
		windowWidth,
		MENU_RATIO * windowHeight,
		MENU_COLOR
	);
}

void drawInterface(unsigned int windowWidth, unsigned int windowHeight) {
	/* toolbar and menu */
	drawToolbar(windowWidth, windowHeight);	
	drawTopMenu(windowWidth, windowHeight);

	/* workspace */
	MLV_draw_text(
		MARGIN_RATIO * windowWidth + 10,
		windowHeight - 20,
		"TweenGen v.0.0.2 - 2022 Lysandre Macke",
		TEXT_COLOR_2
	);
}

void resizeFrame(FrameSeq *frame, unsigned int windowWidth, unsigned int windowHeight) {
	int width, height;
	int workspaceWidth = windowWidth - (MARGIN_RATIO * windowWidth);
	int workspaceHeight = windowHeight - (MENU_RATIO * windowHeight);

	MLV_get_image_size((*frame)->img, &width, &height);

	float ratio = (float)workspaceWidth/(float)width;

	if (ratio*height > workspaceHeight)
		ratio = workspaceHeight/height;

	width *= ratio;
	height *= ratio;

	MLV_resize_image((*frame)->img, width, height);
}

void drawFrame(FrameSeq frame, unsigned int windowWidth, unsigned int windowHeight) {
	int workspace_x = MARGIN_RATIO * windowWidth;
	int workspace_y = MENU_RATIO * windowHeight;

	/* frame */
	MLV_draw_image(frame->img, workspace_x, workspace_y);

	/* frame number */
	MLV_change_default_font(
		"files/geo_1.ttf",
		30);

	MLV_draw_text(
		windowWidth - (2 * MENU_RATIO * windowHeight),
		2 * MENU_RATIO * windowHeight,
		"%d",
		FRAME_NUM_COLOR,
		frame->index
	);

	MLV_change_default_font(
		"files/geo_1.ttf",
		12);

	MLV_actualise_window();
}

void closeWindow() {
	MLV_free_window();
}

void drawCtrlPoint(CtrlPoint cp, FramePos framePos) {
	MLV_Color fillColor, lineColor;

	/* selecting color according to the frame position */
	switch(framePos) {
		case CRT_FRAME :
			fillColor = CRT_FRAME_PT_COLOR;
			lineColor = CRT_FRAME_LN_COLOR;
			break;
		case PVS_FRAME :
			fillColor = PVS_FRAME_PT_COLOR;
			lineColor = PVS_FRAME_LN_COLOR;
			break;
		case NXT_FRAME :
			fillColor = NXT_FRAME_PT_COLOR;
			lineColor = NXT_FRAME_LN_COLOR;
			break;
		default:
			break;
	}

	MLV_draw_filled_circle(
		cp.x,
		cp.y,
		CTRL_POINT_RADIUS,
		fillColor
	);

	MLV_draw_circle(
		cp.x,
		cp.y,
		CTRL_POINT_RADIUS,
		lineColor
	);
}

void drawArmature(Armature a, FramePos framePos) {
	int i;

	for (i = 0; i < a.nPoints; i++) {
		drawCtrlPoint(a.points[i], framePos);
	}
}

void onionSkin(FrameSeq seq) {
	if (seq->prev != NULL)
		drawArmature(seq->prev->armature, PVS_FRAME);
	if (seq->next != NULL)
		drawArmature(seq->next->armature, NXT_FRAME);
}
