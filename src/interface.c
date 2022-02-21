#include "interface.h"

void createWindow() {
	unsigned int windowWidth, windowHeight;
	MLV_get_desktop_size(&windowWidth, &windowHeight);

	MLV_create_window_with_default_font(
		"TweenGen",
		"TweenGen 0.0.1",
		windowWidth,
		windowHeight,
		"files/geo_1.ttf",
		30
	);
}

void closeWindow() {
	MLV_free_window();
}