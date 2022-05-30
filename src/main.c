/** Main function of the TweenGen project. */
#include "events.h"

/*#undef main*/

int main(int argc, char * argv[]) {
	printf(">>> Program starts.\n");

	unsigned int windowWidth, windowHeight;

	unsigned int n = 7; /* number of frames */
	int i;
	int res;

	/* creating window */
	createWindow(&windowWidth, &windowHeight);
	State state = initState();

	/* loading frames */
	char src[] = "files/sample/frame_";
	char tmp[255];
	char buffer[255];

	FrameSeq frames = loadFrame("files/sample/frame_1.png", 1);
	resizeFrame(&frames, windowWidth, windowHeight);

	for(i = 2; i < n + 1; i++) {
		strncpy(tmp, src, sizeof(tmp));
		sprintf(buffer, "%d", i);
		strcat(tmp, buffer);
		strcat(tmp, ".png");
		printf("loading %s...\n", tmp);
		addFrameToSequence(tmp, &frames);
		resizeFrame(&frames, windowWidth, windowHeight);

	}

	drawFrame(frames, windowWidth, windowHeight);


	MLV_actualise_window();

	/* events */
    while(1) {
    	res = getAndApplyEvent(windowWidth, windowHeight, &frames, &state);
    	if(res == 1)
    		MLV_actualise_window();

	    if ( res == -1)
	    	break;
    }

	closeWindow();

	printf(">>> End.\n");

	return 0;
}