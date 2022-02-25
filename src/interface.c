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

	drawInterface(*windowWidth, *windowHeight);

	MLV_actualise_window();
}

void drawInterface(unsigned int windowWidth, unsigned int windowHeight) {
	MLV_draw_filled_rectangle(
		0,
		0,
		MARGIN_RATIO * windowWidth,
		windowHeight,
		TOOLBAR_COLOR
	);

	MLV_draw_filled_rectangle(
		0,
		0,
		windowWidth,
		MENU_RATIO * windowHeight,
		MENU_COLOR
	);

	MLV_draw_text(
		MARGIN_RATIO * windowWidth + 10,
		windowHeight - 20,
		"TweenGen v.0.0.1 - 2022 Lysandre Macke",
		TEXT_COLOR_2
	);
}

void closeWindow() {
	MLV_free_window();
}

void drawCtrlPoint() {

}