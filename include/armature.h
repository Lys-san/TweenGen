/** Bones and armature of an object */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __ARMATURE__
#define __ARMATURE__

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
		char *name;                /* name */
		CtrlPoint *CtrlPoints;     /* point list (linked list) */
	} Armature;

	/** Creates and returns a control point of given name and coordinates. */
	CtrlPoint createCtrlPoint(char *name, unsigned int x, unsigned int y);

	/** (DEBUG) Prints the informations about a given control point. */
	void printCtrlPoint(CtrlPoint cp);


#endif