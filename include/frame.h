/** Frame object (image) */
#include <MLV/MLV_all.h> /* http://www-igm.univ-mlv.fr/~boussica/mlv/index.html */
#include <armature.h>


#ifndef __FRAME__
#define __FRAME__
	/** A Frame object contains informations about its pixels, its armature and about
	its neighbor frames (linked list). */
	typedef struct Frame {
		unsigned int index; /* index of the frame */
		MLV_Image *img;     /* 2D array of pixels */
		Armature armature;  /* set of bones */
		struct Frame *next; /* next frame */
		struct Frame *prev; /* previous frame */
	} Frames, *FrameSeq;

	/** Creates and returns a Frame object according to a given file. */
	FrameSeq loadFrame(const char *fileName, int frameIndex);

	/** adds a new Frame created from a given file to a given frame sequence. */
	void addFrameToSequence(const char *fileName, FrameSeq *seq);


#endif