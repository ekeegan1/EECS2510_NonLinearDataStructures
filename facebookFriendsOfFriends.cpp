
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

//main method contains similar code to previous assignment
int main()
{
	ifstream inFS;
	int firstUser;
	int secondUser;
	string unused;
	int totalVerticies = 0;
	int largeVerticies = 0;
	double avgSizeEdges = 0;
	
	int totalNumberOfEdges = 0;


	//create a vector (verticies) of sets (edges)
	vector<unordered_set<int>> unorderedSet;

	//opens the file
	inFS.open("facebook-links.txt");

	//if the file doesn't open
	if (!inFS.is_open())
	{
		cout << "The input file facebook-links.txt could not be opened." << endl;
		return EXIT_FAILURE;
	}

	while (!inFS.eof())
	{
		//take in row a values
		inFS >> firstUser;
		inFS >> secondUser;
		inFS >> unused;			//take value to remove from file


		//increase the vector size to match the needed space
		if ((firstUser + 1) > unorderedSet.size() || (secondUser + 1) > unorderedSet.size())
		{
			int maxsize = max(firstUser, secondUser);
			unorderedSet.resize(maxsize + 1);
		}


		//add the edges to the needed verticies
		if (unorderedSet.at(firstUser).count(secondUser) == 0)
			unorderedSet.at(firstUser).insert(secondUser);

		if (unorderedSet.at(secondUser).count(firstUser) == 0)
			unorderedSet.at(secondUser).insert(firstUser);

	}


	double runningAverage = 0.0;
	//check to see if each vertex has any edges
	//if it does, increase the vertext size
	for (int i = 0; i < unorderedSet.size(); i++)
	{
		cout << "loading..." << endl;

		//number of verticies
		if (!unorderedSet.at(i).empty())
			totalVerticies++;

		//average number of edges (adding for computation later)
		if (!unorderedSet.at(i).empty())
			avgSizeEdges += unorderedSet.at(i).size();

		//number of verticies over 100
		if (unorderedSet.at(i).size() >= 100)
			largeVerticies++;

		//average number of edges of the edges (friendsOfFriends)
		if (!unorderedSet.at(i).empty())
		{
			double avgSizeEdgesOfEdges = 0;
			//create a temp vector for this iteration
			vector<int> friendsOfFriend  = vector<int>();

			// since the user has friends, put each friend in a vector
			for (auto itr = unorderedSet.at(i).begin(); itr != unorderedSet.at(i).end(); ++itr)
			{
				friendsOfFriend.push_back(*itr);
				totalNumberOfEdges++;
			}

			
			for (int j = 0; j < friendsOfFriend.size(); j++)
				avgSizeEdgesOfEdges += unorderedSet.at(friendsOfFriend.at(j)).size();

			avgSizeEdgesOfEdges /= friendsOfFriend.size();

			runningAverage += avgSizeEdgesOfEdges;			
		}
	}

	//average edge size computation
	avgSizeEdges /= unorderedSet.size();

	//average edges of edges computation
	runningAverage /= unorderedSet.size();


	cout << "Total number of verticies: " << totalVerticies << endl;
	cout << "Average degree over all vertices: " << avgSizeEdges << endl;
	cout << "The number of Vertices with degree >= 100: " << largeVerticies << endl;

	cout << "\nHomework 10 Solution: " << endl;
	cout << "Total number of edges: " << totalNumberOfEdges << endl;
	cout << "Average degree over all vertices' edges: " << runningAverage << endl;

	return 0;

}




