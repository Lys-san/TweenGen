/** Main function of the TweenGen project. */
#include "armature.h"
#include "interface.h"
#include "frame.h"

#undef main

int main(int argc, char * argv[]) {
	printf(">>> Program starts.\n");

	unsigned int windowWidth, windowHeight;
	unsigned int frameNo = 1;

	createWindow(&windowWidth, &windowHeight);
	CtrlPoint test = createCtrlPoint("test", windowWidth/2, windowHeight/2, 1);

	/* loading frames */
	FrameSeq frames = loadFrame("files/sample/frame_1.png", frameNo);
	addFrameToSequence("files/sample/frame_2.png", &frames);
	addFrameToSequence("files/sample/frame_3.png", &frames);
	printFrameSeq(frames);

	/* creating control points */
	printCtrlPoint(test);
	drawCtrlPoint(test, PVS_FRAME);

	MLV_actualise_window();
	MLV_wait_seconds( 2 );
	closeWindow();

	printf(">>> End.\n");

	return 0;
}