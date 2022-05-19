/** Frame object (image) */
#include "armature.h"

#include "colors.h"

#ifndef __FRAME__
#define __FRAME__
	/** A Frame object contains informations about its pixels, its armature and about
	its neighbor frames (linked list). */
	typedef struct Frame {
		unsigned int index; /* index of the frame */
		MLV_Image *img;     /* 2D array of pixels */
		Armature armature;  /* set of bones and points */
		struct Frame *next; /* next frame */
		struct Frame *prev; /* previous frame */
	} Frames, *FrameSeq;

	/** Creates and returns a Frame object according to a given file. */
	FrameSeq loadFrame(const char *fileName, int frameIndex);

	/** adds a new Frame created from a given file to a given frame sequence. */
	void addFrameToSequence(const char *fileName, FrameSeq *seq);

	/** Goes to frame of given index in the given frame sequence. */
	void goToFrame(int index, FrameSeq *seq);


	/** (DEBUG) Prints the informations about a given FramSeq. */
	void printFrameSeq(FrameSeq seq);

#endif