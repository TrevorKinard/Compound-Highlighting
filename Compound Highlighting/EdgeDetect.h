#ifndef _Edge_Detect_
#define _Edge_Detect_
#include "Cluster.h"

//Line in a 3D space (point on line, radians rotation on xy, radians rotation on z)
struct Line { Location A{ 0, 0, 0 }; double hRot{ 0 }, vRot{ 0 }; };

//Find outer lines in an array of points
Line* edgeDetect(Location* points)
{
	
}
#endif