#include "armature.h"

CtrlPoint createCtrlPoint(char *name, unsigned int x, unsigned int y) {
	CtrlPoint newCtrlPoint;

	/* copy of the name */
	newCtrlPoint.name = (char *)malloc(strlen(name) * sizeof(char));
	strcpy(newCtrlPoint.name, name);

	/* storing coordinates */
	newCtrlPoint.x = x;
	newCtrlPoint.y = y;

	return newCtrlPoint;
}

void printCtrlPoint(CtrlPoint cp) {
	fprintf(stderr, "**********************************\n");
	fprintf(stderr, "[DEBUG] Control point : %s\n", cp.name);
	fprintf(stderr, "[DEBUG] Coordinates   : (%d, %d)\n", cp.x, cp.y);

	fprintf(stderr, "**********************************\n");
}