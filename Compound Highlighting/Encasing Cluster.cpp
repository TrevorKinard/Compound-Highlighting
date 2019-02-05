#include "Encasing Cluster.h"

///Clustering
//Cluster locations into groups returning center of groups and locations in cluster (K-means)
std::vector<Cluster> clustering(std::vector<Location> locations, double radius, unsigned int iterations)
{
	// 3D coordinate point
	std::vector<Cluster> centroids;

	//Loop through all location points & create needed centroids
	for (unsigned int c = 0; c < locations.size(); ++c)
	{
		//Pointer to closest centroid to point
		Cluster* closest = nullptr;

		//Check if any centroids exist
		if (centroids.size() > 0)
		{
			//Loop through centroids
			for (unsigned int n = 0; n < centroids.size(); ++n)
			{
				//Find closest centroid
				if ((closest != nullptr && distance(locations[c], centroids[n].center) < distance(locations[c], closest->center)) || distance(locations[c], centroids[n].center) <= distance(locations[c], { locations[c].x + radius, locations[c].y, locations[c].z }))
				{
					closest = &centroids[n];
				}
			}
		}

		//Location has a centroid, add it to the group and recalculate center
		if (closest != nullptr)
		{
			closest->groups.push_back(locations[c]);
			double xAverage = NULL;
			double yAverage = NULL;
			//Recalculate Center
			for (unsigned int n = 0; n < closest->groups.size(); ++n)
			{
				xAverage += closest->groups[n].x;
				yAverage += closest->groups[n].y;
			}
			closest->center.x = xAverage / closest->groups.size();
			closest->center.y = yAverage / closest->groups.size();
		}
		//Location has no centroid, make it a centroid
		else
		{
			centroids.push_back(Cluster{ Location(locations[c]) });
		}
	}

	//Loop through all points and recalculate cluster for n number of iterations
	for (unsigned int i = 0; i <= iterations; ++i)
	{
		//Remove associated locations to be reassociated
		for (unsigned int c = 0; c < centroids.size(); ++c)
		{
			centroids[c].groups.clear();
		}

		//Loop through all locations in each centroid and move to closest cluster
		for (unsigned int c = 0; c < locations.size(); ++c)
		{
			//Pointer to closest centroid to point
			Cluster* closest = &centroids[0];

			//Loop through centroids
			for (unsigned int t = 0; t < centroids.size(); ++t)
			{
				//Find closest centroid
				if (distance(locations[c], centroids[t].center) < distance(locations[c], closest->center))
				{
					closest = &centroids[t];
				}
			}

			//Move location to closest cluster
			closest->groups.push_back(locations[c]);
		}

		//Recalculate center of the clusters
		for (unsigned int c = 0; c < centroids.size(); ++c)
		{
			//Position Averages
			double xAverage = NULL;
			double yAverage = NULL;
			//Recalculate Center
			for (unsigned int n = 0; n < centroids[c].groups.size(); ++n)
			{
				xAverage += centroids[c].groups[n].x;
				yAverage += centroids[c].groups[n].y;
			}
			centroids[c].center.x = xAverage / centroids[c].groups.size();
			centroids[c].center.y = yAverage / centroids[c].groups.size();
		}
	}

	return centroids;
}

///Find Outer points and edges
// Global variable used in qsort() 
Location A;
// Returns of a set of n Locations. (Graham scan)
std::vector<Line> shell(std::vector<Cluster> Locations)
{
	//Vector of connecting corners.
	std::vector<Line> edges;

	//Loop through each clusters lcoations
	for (unsigned int c = 0; c < Locations.size(); ++c)
	{
		//Vector to store the edge vertices of the clusters
		std::vector<Location> corners;

		// Default the minimum y to the first point in the cluster & default min to 0
		int ymin = Locations[c].groups[0].y, min = 0;
		/*Loop through to find the lowest left corner point*/
		for (int i = 1; i < Locations[c].groups.size(); i++)
		{
			//Save the y location of looped through point
			int y = Locations[c].groups[i].y;

			//Compare to see if looped through point's y is lesser than the ymin or if the same make sure its x is lower
			if ((y < ymin) || (ymin == y && Locations[c].groups[i].x < Locations[c].groups[min].x))
				//Set the ymin to the new location and the min to the new index
				ymin = Locations[c].groups[i].y, min = i;
		}

		//Set the lowest left corner point to first in the cluster points 
		swap(Locations[c].groups[0], Locations[c].groups[min]);

		//Set global variable to first point in cluster points
		A = Locations[c].groups[0];
		//Sort n-1 locations based on first point in vector
		qsort(&Locations[c].groups[1], Locations[c].groups.size() - 1, sizeof(Location), compare);
 
		//Size of modified cluster locations
		int m = 1;
		/*Find non linear points from the bottom left corner*/
		for (int i = 1; i < Locations[c].groups.size(); i++)
		{
			// Loop until points are not the same angle
			while (i < Locations[c].groups.size() - 1 && concavity(A, Locations[c].groups[i], Locations[c].groups[i + 1]) == 0)
				//increase index of points in cluster
				i++;

			//Change cluster location at index m to the next angled location
			Locations[c].groups[m] = Locations[c].groups[i];
			//Increase index of modified cluster locations 
			m++;
		}

		//Return null if cluster has less than three points
		if (m < 3) return { {0,0,0},{0,0,0} };

		//Push first 3 points to corners vector 
		corners.push_back(Locations[c].groups[0]);
		corners.push_back(Locations[c].groups[1]);
		corners.push_back(Locations[c].groups[2]);

		/*Find the shortest edges that surround the clusters*/
		for (int i = 3; i < m; i++)
		{
			// While the corners aren't convex
			while (concavity(corners[corners.size() - 2], corners.back(), Locations[c].groups[i]) != 2)
				//Remove the non-convex corners
				corners.pop_back();
			//Add corners that are convex to the corners vector
			corners.push_back(Locations[c].groups[i]);
		}

		//Loop through corners to create edges
		for (unsigned int c = 0; c < corners.size(); ++c)
		{
			//if not last element
			if (c != corners.size() - 1)
				//Create edge from current corner to the next in the vector
				edges.push_back({ corners[c],corners[c + 1] });
			//otherwise is the last element
			else
				//Create edge from last corner to the first corner
				edges.push_back({ corners[c],corners[0] });
		}
	}
	//Return the cumalitve edges of all the cluster
	return edges;
}
// Swap value of locations
void swap(Location &A, Location &B)
{
	//Save location A
	Location temp = A;
	//Set A to location B
	A = B;
	//Set B to original location A
	B = temp;
}
// Function for qsort() to sort Locations with respect to the first Location 
int compare(const void *vp1, const void *vp2)
{
	//Location B of passed in first variable
	Location *B = (Location *)vp1;
	//Location C oof passed in second variable
	Location *C = (Location *)vp2;

	// Grab concavity of points
	int direction = concavity(A, *B, *C);
	//If the concavity is zero compare distances of C and B compared to A
	if (direction == 0)
		//If the distance is greater or equal return -1 otherwise return 1
		return (distance(A, *C) >= distance(A, *B)) ? -1 : 1;
	//Return -1 if direction is 2 otherwise 1
	return (direction == 2) ? -1 : 1;
}
// Concavity of points to center (0,flat)(1,concave)(2,convex)
int concavity(Location A, Location B, Location C)
{
	//Calculate numerical concavity
	int val = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);

	//return 0 for flat concavity
	if (val == 0) return 0;
	//return 1 for greater than 0 and 2 for less than
	return (val > 0) ? 1 : 2; 
}

//Distance between two points
double distance(Location a, Location b)
{
	//Return the square of the distance
	return (((b.x - a.x)*(b.x - a.x)) + ((b.y - a.y)*(b.y - a.y)) + ((b.z - a.z)*(b.z - a.z)));
}

//Cluster, find edges, and display
void display(std::vector<Location> points, double radius)
{
	//Cluster: find clusters in array
	std::vector<Cluster> clusters = clustering(points, 100, 100);
	//EdgeDetect: Group exterior points of Clusters to find corners
	std::vector<Line> edges = shell(clusters);

	std::cout << "Clusters:\n";

	//Display Cluster locations
	for (unsigned int c = 0; c < clusters.size(); ++c)
		std::cout << "(" << clusters[c].center.x << ", " << clusters[c].center.y << ")\n";

	std::cout << "\n\nEdges:\n";

	//Display area
	for (unsigned int c = 0; c < edges.size(); ++c)
		std::cout << "(" << edges[c].A.x << edges[c].A.y << ") - (" << edges[c].B.x << edges[c].B.y << ")\n";

	system("pause");
}