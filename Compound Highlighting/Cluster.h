#ifndef _Cluster_
#define _Cluster_
#include <math.h>

// 3D coordinate point
struct Location { double x{ 0 }, y{ 0 }, z{ 0 }; };

//Cluster position data based on proximity to eachother and return center points of each cluster
Location* cluster(Location* data, double radius)
{
	//Clusters of points
	Location* groups[1];

	//Loop through each point to cluster
	for (unsigned int c = 1; c < 1000; ++c)
	{
		//Nearest point to current point
		Location nearest;
		Location* nearCluster;
		//Loop through current groups
		for (unsigned int n = 0; n < (sizeof(groups) / sizeof(groups[0])); ++n)
			//Loop through each position in group
			for (unsigned int x = 0; x < (sizeof(groups[n]) / sizeof(groups[n][0])); ++x)
			{
				//Point closer than the last becomes the new nearest
				if (distance(data[c], groups[n][x]) <= radius && distance(data[c], groups[n][x]) < distance(data[c], nearest))
				{
					//Set nearest location to new point
					nearest = groups[n][x];
					//save group of nearest location
					nearCluster = groups[n];
				}
			}
		//Check to see nearest is within radius
		if (distance(data[c], nearest) <= radius)
		{
			//Temporary array to resize the near cluster for new point
			Location temp[(sizeof(nearCluster) / sizeof(nearCluster[0])) + 1];
			//Loop through each cluster
			for (unsigned int c = 0; c < (sizeof(nearCluster) / sizeof(nearCluster[0])); ++c)
			{
				//Add each cluster to temp array
				temp[c] = nearCluster[c];
			}
			//Add new cluster to array
			temp[(sizeof(nearCluster) / sizeof(nearCluster[0]))] = data[c];
			//Remake group to size and store new temp data
			Location nearCluster[(sizeof(temp) / sizeof(temp[0])) + 1];
			//Save temp to nearcluster
			for (unsigned int c = 0; c < ((sizeof(temp) / sizeof(temp[0])) + 1); ++c)
				nearCluster[c] = temp[c];
			//Delete temp array
			delete temp;
		}
		else
		{
			//Temporary array to resize groups
			Location* temp[(sizeof(groups) / sizeof(groups[0])) + 1];
			//Loop through each cluster
			for (unsigned int c = 0; c < (sizeof(groups) / sizeof(groups[0])); ++c)
			{
				//Add each cluster to temp array
				temp[c] = groups[c];
			}
			//Add new cluster to array
			temp[(sizeof(groups) / sizeof(groups[0]))][0] = data[c];
			//Remake group to size and store new temp data
			Location* groups[(sizeof(temp) / sizeof(temp[0])) + 1];
			//Save temp to groups
			for (unsigned int c = 0; c < ((sizeof(temp) / sizeof(temp[0])) + 1); ++c)
				groups[c] = temp[c];
			//delete temp array
			delete temp;
		}
	}
}

//Distance between two points
double distance(Location a, Location b)
{
	return sqrt(a.x - b.x * a.x - b.x) + (a.y - b.y * a.y - b.y);
}
#endif