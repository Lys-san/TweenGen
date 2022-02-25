/** Main function of the TweenGen project. */
#include "armature.h"
#include "interface.h"

#undef main

int main(int argc, char * argv[]) {
	printf(">>> Program starts.\n");

	unsigned int windowWidth, windowHeight;
	unsigned int frameNo = 1;

	createWindow(&windowWidth, &windowHeight);
	ctrlPoint test = createCtrlPoint("test", windowWidth/2, windowHeight/2, 1);
	printCtrlPoint(test);
	drawCtrlPoint(test, PVS_FRAME);
	MLV_actualise_window();
	MLV_wait_seconds( 30 );
	closeWindow();
	printf(">>> End.\n");
	return 0;
}