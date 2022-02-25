/** Main function of the TweenGen project. */
#include "armature.h"
#include "interface.h"

#undef main

int main(int argc, char * argv[]) {
	printf(">>> Program starts.\n");

	unsigned int windowWidth, windowHeight;
	
	
	createWindow(&windowWidth, &windowHeight);
	MLV_wait_seconds( 30 );
	closeWindow();
	printf(">>> End.\n");
	return 0;
}