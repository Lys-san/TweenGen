/** Main function of the TweenGen project. */
#include "armature.h"
#include "interface.h"
#include "frame.h"

#undef main

int main(int argc, char * argv[]) {
	printf(">>> Program starts.\n");

	unsigned int windowWidth, windowHeight;
	int workspace_x = MARGIN_RATIO * windowWidth;
	int workspace_y = MENU_RATIO * windowHeight;

	unsigned int n = 3; /* number of frames */
	int i;

	/* creating window */
	createWindow(&windowWidth, &windowHeight);

	/* loading frames */
	FrameSeq frames = loadFrame("files/sample/frame_1.png", 0);

	addFrameToSequence("files/sample/frame_2.png", &frames);
	addFrameToSequence("files/sample/frame_3.png", &frames);
	for(i = 0; i < n; i++) {
		goToFrame(i, &frames);
		resizeFrame(&frames, windowWidth, windowHeight);
		printFrameSeq(frames);
	}

	drawFrame(frames, windowWidth, windowHeight);

	/* creating control points */
	CtrlPoint test = createCtrlPoint("test", windowWidth/2, windowHeight/2, 1);

	printCtrlPoint(test);
	drawCtrlPoint(test, PVS_FRAME);

	MLV_actualise_window();
	MLV_wait_seconds( 5 );
	closeWindow();

	printf(">>> End.\n");

	return 0;
}