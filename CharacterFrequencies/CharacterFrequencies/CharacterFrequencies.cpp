/*
    Name: Ethan Keegan
    Class: Non-Linear Data Structures
    Date: 2/10/23
    
    Assignment 2

    In this project, I demostrate my understanding of the use of separate class files. Additionally,
    I use new functions such as pairs, for example. The code takes a string and counts the frequency of each
    character and puts them into a vector. There are many funciton that can be called to manipulate this vector
    as well as print it. More details are given thoughtout the code.
*/

#include <iostream>
#include <string>
#include <utility>
#include "CharacterFreqencies.h"



//no arg
CharacterFrequencies::CharacterFrequencies()
{
}

CharacterFrequencies::CharacterFrequencies(string line)
{
    
    //add the first character to make the vector have a size
    if (frequencies.empty())
    {
        frequencies.push_back(make_pair(line[0], 1));
    }

    //start with the second charcter since the first one is added already
    for (int i = 1; i < line.size(); i++)
    {
        for (int j = 0; j < frequencies.size(); j++)
        {
            //if the character is found in the vector, then increase the pair's count
            if (line[i] == frequencies[j].first)
            {
                frequencies[j].second += 1;
                break;
            }

            //if it reaches the end of the vector with no match, add the pair to the list
            if (j == (frequencies.size()-1))
            {
                frequencies.push_back(make_pair(line[i], 1));
                break;
            }
        }
        
    }
}


//adds characters to initialized characters
void CharacterFrequencies::readString(string line)
{
    //this is the same as the initailization without the creation of the pairs
    for (int i = 0; i < line.size(); i++)
    {
        for (int j = 0; j < frequencies.size(); j++)
        {
            if (line[i] == frequencies[j].first)
            {
                frequencies[j].second += 1;
                break;
            }
        }
    }
}

//clears the frequenies vector (sets the values to 0)
void CharacterFrequencies::reset()
{
    for (int i = 0; i < frequencies.size(); i++)
    {
        frequencies[i].second = 0;
    }
}

//calls for a specific character's frequency
int CharacterFrequencies::getFrequency(char c)
{
    for (int i = 0; i < frequencies.size(); i++)
    {
        //if the character is found, output the second value (the frequency) of the pair
        if (frequencies[i].first == c)
            return frequencies[i].second;
 
        //if it not found, then return a 0 (meaning it has no frequency)
        if (i == (frequencies.size() - 1))
            return 0;
    }
}


//print the frequencies vector
void CharacterFrequencies::printFrequencies()
{
    for(int i = 0; i < frequencies.size(); i++)
        cout << frequencies[i].first << ": " << frequencies[i].second << endl; 
}


//main class has been left as is in the sample code from the assignment
int main()
{

    //This is the line to analyize
    string line2 = "Twinkle twinkle little star, how I wonder what you are.";
    //print this line
    cout << line2 << endl;

    //create a new object for the frequency of characters in this line
    CharacterFrequencies line2CharFreq(line2);

    //print the frequencies of the characters
    line2CharFreq.printFrequencies(); //(initialized charcters and prints them)

    //add to the characters from initilaized string
    line2CharFreq.readString(line2);

    //print again (should have x2 frequency b/c of readString
    line2CharFreq.printFrequencies();
    
}