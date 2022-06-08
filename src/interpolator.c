#include "interpolator.h"

CtrlPoint linearInterpol(CtrlPoint a, CtrlPoint b) {
	int x, y;
	x = (a.x + b.x) / 2;
	y = (a.y + b.y) / 2;
	return createCtrlPoint("GenPoint", x, y);
}

CtrlPoint cosineInterpol(CtrlPoint a, CtrlPoint b) {
	float x, y;
	float mu_1, mu_2;
	x = (a.x + b.x) / 2.0;
	mu_1 = a.y > b.y ? 0.3 : 0.7;
	mu_2 = (1 - cos(mu_1*M_PI)) / 2.0;
	y = a.y * (1 - mu_2) + b.y * mu_2;
	return createCtrlPoint("GenPoint", (int)x, (int)y);

}

void interpolateSeq(FrameSeq *seq, CtrlPoint (*interpolFunction)(CtrlPoint, CtrlPoint)) {
	/* moving to the first frame */
	goToFrame(1, seq);
	int i;
	int nPoints = (*seq)->armature.nPoints; /* should be constant for each frames */
	CtrlPoint genPoint;
	FrameSeq tmp; /* generated frames */

	/* going forward in the linked list until reaching the last frame */
	while ((*seq)->next != NULL) {
		printFrameSeq(*seq);
		tmp = createEmptyFrame();

		/* generating points */
		for (i = 0; i < nPoints; i++) {
			genPoint = (*interpolFunction)(
				(*seq)->armature.points[i],
				(*seq)->next->armature.points[i]
				);
			addCtrlPointToArmature(&(tmp->armature), genPoint);
			
		}
		insertFrameHere(tmp, seq);
		*seq = (*seq)->next;
	}
	printf("[DEBUG] End of interpolate function.\n");
}

void averageSeq(FrameSeq *seq) {
	int width, height;
	MLV_Image *img_A, *img_B;
	int r1, g1, b1, a1;           /* img A */
	int r2, g2, b2, a2;           /* img B */
	MLV_Color clr1, clr2, genClr; /* colors of pixels */
	MLV_Image *genImg;            /* generated image */
	FrameSeq genFrame;            /* generated frame */
	int x, y;

	/* moving to the first frame */
	goToFrame(1, seq);
	MLV_get_image_size((*seq)->img, &width, &height);



	/* going forward in the linked list until reaching the last frame */
	while ((*seq)->next != NULL) {
		img_A = (*seq)->img;
		img_B = (*seq)->next->img;

		/* creating an empty image */
		genImg = MLV_create_image(width, height);

		/* filling with the average of each pixels */
		for (x = 0; x < width; x ++) {
			for (y = 0; y < height; y++) {
				MLV_get_pixel_on_image(img_A, x, y, &r1, &g1, &b1, &a1);
				MLV_get_pixel_on_image(img_B, x, y, &r2, &g2, &b2, &a2);

				clr1 = MLV_convert_rgba_to_color(r1, g1, b1, a1);
				clr2 = MLV_convert_rgba_to_color(r2, g2, b2, a2);
				genClr = avgOfColors(clr1, clr2);

				MLV_set_pixel_on_image(x, y, genClr, genImg);
			}
		}
		genFrame = createEmptyFrame();
		genFrame->img = genImg;

		
		insertFrameHere(genFrame, seq);
		*seq = (*seq)->next;
	}
	printf("[DEBUG] End of interpolate function.\n");
}