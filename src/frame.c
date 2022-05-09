#include "frame.h"

FrameSeq loadFrame(const char *fileName, int frameIndex) {
	FrameSeq new;

	new = (Frames *)malloc(sizeof(Frames));

	if (new != NULL) {
		/* initialising the new Frame */
		new->index = frameIndex;
		new->img   = MLV_load_image(fileName);
		new->next  = NULL;
		new->prev  = NULL;

		return new;
	}
	fprintf(stderr, "Error while creating the Frame object.");
	return NULL;
}


void addFrameToSequence(const char *fileName, FrameSeq *seq) {
	FrameSeq new = loadFrame(fileName, (*seq)->index + 1);
	new->prev = *seq;
	(*seq)->next = new;
	*seq = (*seq)->next; /* upadting the position */
}