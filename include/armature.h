/** Bones and armature of an object */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#ifndef __ARMATURE__
#define __ARMATURE__
	#define MAX_POINTS 255
	#define MAX_BONES  255

	#define SQUARE(a)     ((a)*(a))

	/** A control point represents a moving point on a frame. */
	typedef struct {
		char *name;                /* name */
		unsigned int x;            /* x coordinate on the frame */
		unsigned int y;            /* y coordinate on the frame */
	} CtrlPoint;

	/** A bone is a connexion between two control points. */
	typedef struct {
		CtrlPoint a;               /* first point */
		CtrlPoint b;               /* secnd point */
	} Bone;

	/** An armature is a set of linked control points. */
	typedef struct {
		char *name;                   /* name */
		CtrlPoint points[MAX_POINTS]; /* point list */
		Bone bones[MAX_BONES];        /* bone list */
		unsigned int nPoints;         /* number of points */
		unsigned int nBones;          /* number od bones */
	} Armature;

	/** Creates and returns a control point of given name and coordinates. */
	CtrlPoint createCtrlPoint(char *name, unsigned int x, unsigned int y);

	/** Updates the point's coordinate. */
	void updatePointWithNewCoords(CtrlPoint *cp, unsigned int new_x, unsigned int new_y);

	/** Returns 1 if the given control points are the same
	 *  and 0 otherwise. */
	int areSamePoints(CtrlPoint p1, CtrlPoint p2);

	/** Creates and returns a bone formed with the given points. */
	Bone createBone(CtrlPoint a, CtrlPoint b);

	/** (DEBUG) Prints the informations about a given control point. */
	void printCtrlPoint(CtrlPoint cp);

	/** Returns 0 if the given bones are the same exactly the same,
	 *  1 if they are the same but flipped and 0 otherwise. */
	int areSameBones(Bone bone_1, Bone bone_2);

	/** Returns the euclidian norm between the two control points forming 
	 *  the bone. */
	int length(Bone bone);

	/** Returns the euclidian norm between a and b. */
	float dist(CtrlPoint a, CtrlPoint b);

	/** (DEBUG) Prints all the control points stored in the given armature. */
	void printArmature(Armature a);

	/** Creates and returns a new Armature object. */
	Armature createArmature(char *name);

	/** Returns -1 if a given control point isn't stored in the armature object
	 *  and its index otherwise. */
	int isContained(Armature armature, CtrlPoint p);

	int isContainedBone(Armature armature, Bone bone);

	/** Adds a given control point to the armature (if it isn't already in it) */
	void addCtrlPointToArmature(Armature *armature, CtrlPoint p);

	/** Adds a given bone to the armature (if it isn't already in it) */
	void addBoneToArmature(Armature *armature, Bone b);

#endif