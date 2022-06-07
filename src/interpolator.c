#include "interpolator.h"

CtrlPoint linearInterpol(CtrlPoint a, CtrlPoint b) {
	int x, y;
	x = (a.x + b.x) / 2;
	y = (a.y + b.y) / 2;
	return createCtrlPoint("GenPoint", x, y);
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