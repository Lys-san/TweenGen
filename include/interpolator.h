/** Frames/points interpolation module */
#include "frame.h"

#ifndef __INTERPOL__
#define __INTERPOL__
	#define ABS(a) ((a) > 0 ? (a) : -(a))

	#ifndef M_PI
	#define M_PI 3.14159265359
	#endif
	#define INTERPOL_FUNC cosineInterpol /* default interpolation function */

	/** Absolute value */
	int abs(int a);

	/** Linear interpolation given two known points : the returned point
	 * is the point located in the middle of the line formed by the two points.*/
	CtrlPoint linearInterpol(CtrlPoint a, CtrlPoint b);

	/** Cosine interpolation given two points. The created curve is smoothed. */
	CtrlPoint cosineInterpol(CtrlPoint a, CtrlPoint b);

	/** Ameliorated interpolation considering bone length. */
	Bone boneInterpol(Bone bone_1, Bone bone_2);

	/** Average of two images */
	MLV_Image avgImages(MLV_Image a, MLV_Image b);

	/** Use a certain interpolation method once on a given Frame sequence. */
	void interpolateSeq(FrameSeq *seq, CtrlPoint (*interpolFunction)(CtrlPoint, CtrlPoint));

	void interpolateSeqFromBones(FrameSeq *seq, Bone (*interpolFunction)(Bone, Bone));

	/** Creates the inbetweens from the average of the frames. */
	void averageSeq(FrameSeq *seq);

#endif