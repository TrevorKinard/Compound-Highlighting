#include "Cluster.h"
#include "EdgeDetect.h"
#include "Fill.h"
#include <iostream>

void main()
{
	//Create array of 3D points
	Location points[] = { (1023.8,2008.22,0),(1017.05,2015.06,0),(1024.6,2001.85,0),(1010.59,2016.17,0),(1015.75,2006.42,1.37024),(1017.53,2001.92,0),(1011.63,2008.22,0),(1025.37,1992.06,0),(1000.95,2015.63,0),(1017.79,1996.34,0),(1006.12,2008.04,6.66489),(1024.08,1985.59,0),(1018.06,1990.74,0),(1000.57,2007.84,0),(995.288,2011.87,0),(997.561,2007.52,0),(1016.33,1986.6,1.37175),(994.578,2004.75,0),(1011.78,1984.75,2.1658),(1017.31,1978.69,0),(990.518,2006.9,0),(994.536,2001.84,0),(994.801,1996.3,0),(1010.86,1978.14,0),(987.453,2001.2,0),(1000.88,1984.54,0),(994.973,1990.69,0),(996.823,1986.16,0),(1002.24,1977.85,0),(988.33,1991.78,0),(989.288,1985.25,0),(996.052,1977.97,0),(1334.46,1233.04,0),(1319.01,1247.2,0),(1336.3,1224.87,0),(1313.47,1247.07,0),(1336.18,1219.23,0),(1311.46,1243.42,0),(1318.1,1226.32,0),(1302.28,1235.34,0),(1303.72,1230.16,0),(1310.76,1210.41,0),(1312.3,1205.36,0),(1297.06,1214.84,0),(1303.05,1197.56,0),(1278.76,1221.23,0),(1300.91,1194.01,0),(1278.54,1215.58,0),(1295.37,1194.08,0),(1280.53,1208.48,0) };
	//Cluster: find clusters in array
	Location* clusters = cluster(points, 100);
	//EdgeDetect: Group exterior points of Clusters to find edges
	Line* edges = edgeDetect(clusters);
	//Fill: find intersect points of edges in clusters
	Location* area = fill(edges);

	//Display edges
	for (unsigned int c = 0; c < sizeof edges / sizeof edges[0]; ++c)
		std::cout << "X: " << edges[c].A.x << " Y: " << edges[c].A.y << " Z: " << edges[c].A.z << "\nHorizontal Rotation: " << edges[c].hRot << "\nVertical Rotation: " << edges[c].vRot << "\n\n";
	
	std::cout << "\n\n";
	
	//Display area
	for (unsigned int c = 0; c < sizeof area / sizeof area[0]; ++c)
		std::cout << "X: " << area[c].x << " Y: " << area[c].y << " Z: " << area[c].z << "\n\n";
}