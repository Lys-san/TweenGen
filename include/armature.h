/** Bones and armature of an object */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __ARMATURE__
#define __ARMATURE__
	#define MAX_POINTS 255
	#define MAX_BONES  255

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

	/** Returns 1 if the given control points are the same
	 * and 0 otherwise. */
	int areSamePoints(CtrlPoint p1, CtrlPoint p2);

	/** (DEBUG) Prints the informations about a given control point. */
	void printCtrlPoint(CtrlPoint cp);

	/** (DEBUG) Prints all the control points stored in the given armature. */
	void printArmature(Armature a);

	/** Creates and returns a new Armature object. */
	Armature createArmature(char *name);

	/** Returns 0 if a given control point isn't stored in the armature object
	 * and 1 otherwise. */
	int isContained(Armature armature, CtrlPoint p);

	/** Adds a given control point to the armature (if it isn't already in it) */
	void addCtrlPointToArmature(Armature *armature, CtrlPoint p);


#endif