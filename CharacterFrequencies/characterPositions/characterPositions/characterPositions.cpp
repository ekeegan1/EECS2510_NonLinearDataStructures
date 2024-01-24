/*
	Assignment 1
	Writer: Ethan Keegan
	Date: 2/3/23
	Class: EECS 2510

	This program reads a .txt file. The user may input a disired value, and the program will find the number of occurrences of that character as well as their indecies and output them.
*/



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream inFS;
	char userChar;
	int charFreq = 0;
	char currChar;
	int index = 0;
	int openSpace = 0;
	int array[1000];

	//opens the file
	inFS.open("input.txt");

	//if the file doesn't open
	if (!inFS.is_open())
	{
		cout << "The input file input.txt could not be opened." << endl;
		return EXIT_FAILURE;
	}
	
	//char to be found
	cout << "Enter the character to search for: ";
	cin >> userChar;

	//c++ string directory

	//while the file has more characters
	while (!inFS.eof())
	{
		//take the next character
		inFS >> currChar;

		//as long as there is an accepted character
		if (!inFS.fail())
		{
			//increase the index of the file location
			index++;

			//if the desired character is found
			if (currChar == userChar)
			{
				++charFreq;					//increase that charcter count
				array[openSpace] = index;	//save that index location
				openSpace++;				//and move the array variable to an open space

			}
		}
	}
	
	//standard output...exicutes no matter the character occurances
	cout << "The number of occurrences of the character " << userChar << " is " << charFreq << endl;


	//if the character count is more than 0, then output the saved index values
	if (charFreq > 0)
	{
		cout << "The indces of the character positions are : ";
		for (int i = 0; i < openSpace; i++)
		{
			cout << array[i] << " ";
		}
	}
		
	
	//Close the file
	inFS.close();

	return 0;
	


}
