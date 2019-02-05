#ifndef _EncasingCasing_
#define _EncasingCasing_
#include <iostream>
#include <vector>

//3D point in space
struct Location { double x, y, z; };
//Group of points with a center location
struct Cluster { Location center; std::vector<Location> groups; };
//Line connecting the edge points
struct Line { Location A, B; };

///Clustering (K-Means)
//Cluster locations into groups returning center of groups and locations in cluster
std::vector<Cluster> clustering(std::vector<Location> locations, double radius, unsigned int iterations);

///Encasing Corners (Graham Scan)
// Prints convex hull of a set of n Locations.
std::vector<Line> shell(std::vector<Cluster> Locations);
// A utility function to swap two Locations 
void swap(Location &p1, Location &p2);
// Function for qsort() to sort Locations with respect to the first Location 
int compare(const void *vp1, const void *vp2);
// Concavity of points to center (0,flat)(1,concave)(2,convex)
int concavity(Location A, Location B, Location C);

//Distance between two points
double distance(Location a, Location b);

//Cluster, find edges, and display
void display(std::vector<Location> points, double radius);
#endif
