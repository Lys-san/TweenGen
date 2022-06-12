#include "interpolator.h"

int abs(int a) {
	if (a > 0)
		return a;
	return -a;
}


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
	mu_1 = a.y < b.y ? 0.3 : 0.7;
	mu_2 = (1 - cos(mu_1*M_PI)) / 2.0;
	y = a.y * (1 - mu_2) + b.y * mu_2;
	return createCtrlPoint("GenPoint", (int)x, (int)y);
}

Bone boneInterpol(Bone bone_1, Bone bone_2) {
	CtrlPoint p1, p2;       /* generated control points */
	int len1, len2, genLen; /* length of the 2 bones and generated length */
	float cosTheta;         /* cos of the angle formed by the generated bone and the x axis */
	CtrlPoint base, mv;     /* base point and moving point */
	int x, y;               /* adjusted coordinates of the moving point */
	
	len1 = length(bone_1);
	len2 = length(bone_2);
	genLen = AVG(len1, len2);
	printf("[DEBUG] lengths : %d %d %d\n", len1, len2, genLen);

	/* getting informations based on the linear interpolation */
	p1 = linearInterpol(bone_1.a, bone_2.a);
	p2 = linearInterpol(bone_1.b, bone_2.b);

	if (dist(bone_1.a, bone_2.a) < dist(bone_1.b, bone_2.b)) {
		base = p1;
		mv = p2;
	}
	else {
		base = p2;
		mv = p1;
	}
	

	/* adjusting the interpolation of the moving point */
	cosTheta = abs(mv.x - base.x)/((dist(base, mv)));
	printf("----%d %d\n", mv.x, base.x);
	printf("cos(theta) : %d / %f = %f\n", (mv.x - base.x), dist(base, mv), cosTheta);
	printf("[DEBUG] BASE POINT : \n");
	printCtrlPoint(base);
	x = - genLen*cosTheta + base.x;
	printf("[DEBUG] %d * %f + %d = %d\n", -genLen, cosTheta, base.x, x);
	y = - sqrt(SQUARE(genLen) + SQUARE((x - base.x))) + base.y;

	CtrlPoint genMvPoint = createCtrlPoint("GenPoint", x, y);

	printCtrlPoint(genMvPoint);
	Bone genBone = {base, genMvPoint};
	printf("[DEBUG] final length : %d\n", length(genBone));
	return genBone;
}

void interpolateSeq(FrameSeq *seq, CtrlPoint (*interpolFunction)(CtrlPoint, CtrlPoint)) {
	/* moving to the first frame */
	goToFrame(1, seq);
	int i;
	int nPoints = (*seq)->armature.nPoints; /* should be constant for each frames */
	int nBones = (*seq)->armature.nBones;
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
		/* recreating the bones */

		/* TODO */
		/*for (i = 0; i < nPoints; i++) {
			genPoint = (*interpolFunction)(
				(*seq)->armature.points[i],
				(*seq)->next->armature.points[i]
				);
			addCtrlPointToArmature(&(tmp->armature), genPoint);
			
		}*/

		insertFrameHere(tmp, seq);
		*seq = (*seq)->next;
	}
	printf("[DEBUG] End of interpolate function.\n");
}

void interpolateSeqFromBones(FrameSeq *seq, Bone (*interpolFunction)(Bone, Bone)) {
	/* moving to the first frame */
	goToFrame(1, seq);
	int i;
	int nBones = (*seq)->armature.nBones; /* should be constant for each frames */
	Bone genBone;
	FrameSeq tmp; /* generated frames */

	/* going forward in the linked list until reaching the last frame */
	while ((*seq)->next != NULL) {
		tmp = createEmptyFrame();

		/* generating bones */
		for (i = 0; i < nBones; i++) {
			genBone = (*interpolFunction)(
				(*seq)->armature.bones[i],
				(*seq)->next->armature.bones[i]
				);
			addBoneToArmature(&(tmp->armature), genBone);
			addCtrlPointToArmature(&(tmp->armature), genBone.a);
			addCtrlPointToArmature(&(tmp->armature), genBone.b);

			
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