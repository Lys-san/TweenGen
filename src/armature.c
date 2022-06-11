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

int areSamePoints(CtrlPoint p1, CtrlPoint p2) {
	if (
		strcmp(p1.name, p2.name) == 0
		&& p1.x == p2.x
		&& p1.y == p2.y
		) 
		return 1;
	
	return 0;
}

void printCtrlPoint(CtrlPoint cp) {
	fprintf(stderr, "**********************************\n");
	fprintf(stderr, "[DEBUG] Control point : %s\n", cp.name);
	fprintf(stderr, "[DEBUG] Coordinates   : (%d, %d)\n", cp.x, cp.y);

	fprintf(stderr, "**********************************\n");
}

int areSameBones(Bone bone_1, Bone bone_2) {
	if (areSamePoints(bone_1.a, bone_2.a) && areSamePoints(bone_1.b, bone_2.b))
		return 0;
	if (areSamePoints(bone_1.a, bone_2.b) && areSamePoints(bone_1.b, bone_2.a))
		return 1;
	return -1;
}

int length(Bone bone) {
	return sqrt(SQUARE(bone.b.x - bone.a.x) + SQUARE(bone.b.y - bone.a.y));
}

int dist(CtrlPoint a, CtrlPoint b) {
	return sqrt(SQUARE(b.x - a.x) + SQUARE(b.y - a.y));
}

void printArmature(Armature a) {
	int i;
	CtrlPoint cp;

	fprintf(stderr, "**********************************\n");

	for(i = 0; i < a.nPoints; i++) {
		cp = a.points[i];
		fprintf(stderr, "[DEBUG] Control point : %s (%d, %d)\n", cp.name, cp.x, cp.y);
	}
	fprintf(stderr, "**********************************\n");

}


Armature createArmature(char *name) {
	Armature new;

	new.name = (char *)malloc(strlen(name) * sizeof(char));
	strcpy(new.name, name);

	new.nPoints = 0;
	new.nBones = 0;

	return new;
}

int isContained(Armature armature, CtrlPoint p) {
	int i;

	for (i = 0; i < armature.nPoints; i++) {
		if (areSamePoints(armature.points[i], p))
			return 1; /* found */
	}
	return 0; /* not found */
}

void addCtrlPointToArmature(Armature *armature, CtrlPoint p) {
	if (!isContained(*armature, p)) {
		armature->points[armature->nPoints] = p;
		armature->nPoints++;

	}
}
