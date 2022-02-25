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
		struct Neighbor *neighbor; /* linked point */
		unsigned int frame;        /* num of the frame */
	} ctrlPoint;

	/** A bone is a connexion between two control points. */
	typedef struct {
		ctrlPoint a;               /* first point */
		ctrlPoint b;               /* secnd point */
	} bone;

	/** An armature is a set of linked control points. */
	typedef struct {
		char *name;                /* name */
		ctrlPoint *ctrlPoints;     /* point list (linked list) */
	} armature;

	/** Creates and returns a control point of given name and coordinates. */
	ctrlPoint createCtrlPoint(char *name, unsigned int x, unsigned int y, unsigned int frame);

	/** (DEBUG) Prints the informations about a given control point. */
	void printCtrlPoint(ctrlPoint cp);


#endif