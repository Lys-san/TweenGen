#include "interface.h"

void createWindow(unsigned int *windowWidth, unsigned int *windowHeight) {
	MLV_get_desktop_size(windowWidth, windowHeight);
	*windowWidth  /= 1.5;
	*windowHeight /= 1.5;

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

	drawInterface(*windowWidth, *windowHeight, 1); /* set pos to first frame at first */

	MLV_actualise_window();
}

void drawInterface(unsigned int windowWidth, unsigned int windowHeight, unsigned int frame) {
	/* toolbar */
	MLV_draw_filled_rectangle(
		0,
		0,
		MARGIN_RATIO * windowWidth,
		windowHeight,
		TOOLBAR_COLOR
	);

	/* menu */
	MLV_draw_filled_rectangle(
		0,
		0,
		windowWidth,
		MENU_RATIO * windowHeight,
		MENU_COLOR
	);

	/* text */
	MLV_draw_text(
		MARGIN_RATIO * windowWidth + 10,
		windowHeight - 20,
		"TweenGen v.0.0.1 - 2022 Lysandre Macke",
		TEXT_COLOR_2
	);

	/* frame number */
	MLV_change_default_font(
		"files/geo_1.ttf",
		30);

	MLV_draw_text(
		windowWidth - (2 * MENU_RATIO * windowHeight),
		2 * MENU_RATIO * windowHeight,
		"%d",
		TEXT_COLOR_1,
		frame
	);

	MLV_change_default_font(
		"files/geo_1.ttf",
		12);
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

CtrlPoint createCtrlPointByClick() {
	/* TODO */;
}