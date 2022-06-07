/** Frames/points interpolation module */
#include "frame.h"
#include <math.h>

#ifndef __INTERPOL__
#define __INTERPOL__
	#ifndef M_PI
	#define M_PI 3.14159265359
	#endif
	#define INTERPOL_FUNC cosineInterpol /* default interpolation function */

	/** Linear interpolation given two known points : the returned point
	 * is the point located in the middle of the line formed by the two points.*/
	CtrlPoint linearInterpol(CtrlPoint a, CtrlPoint b);

	/** Cosine interpolation given two points. The created curve is smoothed. */
	CtrlPoint cosineInterpol(CtrlPoint a, CtrlPoint b);

	/** Average of two images */
	MLV_Image avgImages(MLV_Image a, MLV_Image b);

	/** Use a certain interpolation method once on a given Frame sequence. */
	void interpolateSeq(FrameSeq *seq, CtrlPoint (*interpolFunction)(CtrlPoint, CtrlPoint));

#endif