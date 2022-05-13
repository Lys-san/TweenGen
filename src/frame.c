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

void goToFrame(int index, FrameSeq *seq) {
	while (index > seq->index) {
		if (seq->next != NULL)
			seq = seq->next;
		else
			fprintf(stderr, "Frame %d does not exist", index);
	}
}

void printFrameSeq(FrameSeq seq) {
	fprintf(stderr, "**********************************\n");
	fprintf(stderr, "[DEBUG] actual frame : %d\n", seq->index);
	fprintf(stderr, "[DEBUG] prev frame   : %d\n", seq->prev != NULL ? seq->prev->index : -1);
	fprintf(stderr, "[DEBUG] next frame   : %d\n", seq->next != NULL ? seq->next->index : -1);
	fprintf(stderr, "**********************************\n");
}