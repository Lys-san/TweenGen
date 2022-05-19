#include "colors.h"

int isSameRGBA(int color1[4], Uint8 color2[4]) {
	int i;
	for(i = 0; i < 3; i++) {
		if(color1[i] != color2[i]) {
			return 0;
		}
	}
	/*printf("%d %d %d | %d %d %d\n", color1[0], color1[1], color1[2], 
				color2[0], color2[1], color2[2]);*/
	return 1;
}


MLV_Color addOpacity(MLV_Color color, Uint8 alpha) {
	Uint8 rgba[4];

	/*store the informations of the given color so we can modify it*/
	MLV_convert_color_to_rgba(color, &rgba[0], &rgba[1], &rgba[2], &rgba[3]);

	return MLV_convert_rgba_to_color(rgba[0], rgba[1], rgba[2], rgba[3] + alpha);
}


MLV_Color avgOfColors(MLV_Color color1, MLV_Color color2) {
	Uint8 rgbaColor1[4], rgbaColor2[4];

	MLV_convert_color_to_rgba(color1, &rgbaColor1[0], &rgbaColor1[1], &rgbaColor1[2], &rgbaColor1[3]);
	MLV_convert_color_to_rgba(color2, &rgbaColor2[0], &rgbaColor2[1], &rgbaColor2[2], &rgbaColor2[3]);

	return MLV_convert_rgba_to_color(
		AVG(rgbaColor1[0], rgbaColor2[0]),
		AVG(rgbaColor1[1], rgbaColor2[1]),
		AVG(rgbaColor1[2], rgbaColor2[2]),
		AVG(rgbaColor1[3], rgbaColor2[3])
		);
}


/* CHECK LATER */
void boundaryFill(int x, int y, MLV_Color fillColor, MLV_Color borderColor) {
	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);

	int pixelRGBA[4];
	Uint8 borderRGBA[4];
	Uint8 fillRGBA[4];

	MLV_convert_color_to_rgba(borderColor, &borderRGBA[0], &borderRGBA[1], &borderRGBA[2], &borderRGBA[3]);
	MLV_convert_color_to_rgba(fillColor, &fillRGBA[0], &fillRGBA[1], &fillRGBA[2], &fillRGBA[3]);

	MLV_get_pixel(x, y, &pixelRGBA[0], &pixelRGBA[1], &pixelRGBA[2], &pixelRGBA[3]);

	/* checking the color of the (x, y) pixel */
	if( !isSameRGBA(pixelRGBA, borderRGBA)
		&& !isSameRGBA(pixelRGBA, fillRGBA)
		&& x > 0 && x < windowWidth - 1
		&& y > 0 && y < windowHeight - 1) {

		MLV_draw_pixel(x, y, fillColor);
		/*MLV_actualise_window();
		MLV_wait_milliseconds( 50 );*/

		/* recursive calls */
		boundaryFill(x + 1, y, fillColor, borderColor);
		boundaryFill(x, y + 1, fillColor, borderColor);
		boundaryFill(x - 1, y, fillColor, borderColor);
		boundaryFill(x, y - 1, fillColor, borderColor);
	}
}