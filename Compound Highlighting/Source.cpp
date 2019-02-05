#include "Encasing Cluster.h"

void main()
{
	//user input
	int input;
	//Create vector of 3D points
	std::vector<Location> points;

	//Loop through menu until user exit
	while (true)
	{
		//Clear screen
		system("cls");
		std::cout << "Compound Clustering:\n     Compound clustering takes an array of 3D locations that are\n"
			<< "     clustered based on a chosen radius and displays the cluster points\n"
			<< "     and its vertices that create a shell around it\n\n";

		std::cout << "0) Exit program\n"
			<< "1) Add 3D location\n"
			<< "2) Run with Test Locations\n"
			<< "3) Cluster added locations\n\n"
			<< "Input: ";

		std::cin >> input;

		switch (input)
		{
		case 0:
			//Exit program
			return;
			break;
		case 1:
			//Clear screen
			system("cls");
			//location variables
			double x, y, z;
			std::cout << "X: ";
			//Users desired x coordinate
			std::cin >> x;
			//Clear screen
			system("cls");
			std::cout << "Y: ";
			//Users desired y coordinate
			std::cin >> y;
			system("cls");
			std::cout << "Z: ";
			//Users desired z coordinate
			std::cin >> z;
			system("cls");
			//Add desired location to position vector
			points.push_back({ x,y,z });
			break;
		case 2:
			std::cout << "Clustering radius: ";
			//Grab radius desire from user
			std::cin >> input;
			//Cluster, find edges of clusters, and display the test locations based on user's radius
			display({{1023.8,2008.22,0},{1017.05,2015.06,0},{1024.6,2001.85,0},{1010.59,2016.17,0},{1015.75,2006.42,1.37024},{1017.53,2001.92,0},{1011.63,2008.22,0},{1025.37,1992.06,0},{1000.95,2015.63,0},{1017.79,1996.34,0},{1006.12,2008.04,6.66489},{1024.08,1985.59,0},{1018.06,1990.74,0},{1000.57,2007.84,0},{995.288,2011.87,0},{997.561,2007.52,0},{1016.33,1986.6,1.37175},{994.578,2004.75,0},{1011.78,1984.75,2.1658},{1017.31,1978.69,0},{990.518,2006.9,0},{994.536,2001.84,0},{994.801,1996.3,0},{1010.86,1978.14,0},{987.453,2001.2,0},{1000.88,1984.54,0},{994.973,1990.69,0},{996.823,1986.16,0},{1002.24,1977.85,0},{988.33,1991.78,0},{989.288,1985.25,0},{996.052,1977.97,0},{1334.46,1233.04,0},{1319.01,1247.2,0},{1336.3,1224.87,0},{1313.47,1247.07,0},{1336.18,1219.23,0},{1311.46,1243.42,0},{1318.1,1226.32,0},{1302.28,1235.34,0},{1303.72,1230.16,0},{1310.76,1210.41,0},{1312.3,1205.36,0},{1297.06,1214.84,0},{1303.05,1197.56,0},{1278.76,1221.23,0},{1300.91,1194.01,0},{1278.54,1215.58,0},{1295.37,1194.08,0},{1280.53,1208.48,0}}, input);
			break;
		case 3:
			std::cout << "Clustering radius: ";
			//Grab radius desire from user
			std::cin >> input;

			//Cluster, find edges of clusters, and display the user's locations based on user's radius
			display(points, input);
			break;
		}
	}
}