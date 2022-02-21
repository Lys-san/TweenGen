/** Bones and armature of an object */

#ifndef __ARMATURE__
#define __ARMATURE__

	/** A control point represents a moving point on a frame. */
	typedef struct {
		char *name;                /* name */
		unsigned int x;            /* x coordinate on the frame */
		unsigned int y;            /* y coordinate on the frame */
		struct Neighbor *neighbor; /* linked point */
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

	

#endif