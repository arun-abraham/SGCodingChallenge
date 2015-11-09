#ifndef _RANDOMLISTGENERATOR_H_
#define _RANDOMLISTGENERATOR_H_

/*
1. Creates a list of random Nodes containing birth, end dates between years min, max
2. Prints them to the file Input List.txt (code in main)
*/

#include <iostream>
#include <fstream>
#include <random>

using namespace std;

struct Node
{

	int birthYear;
	int deathYear;
	Node* next;

	Node(int min, int max);
	void RandomizeValues(int min, int max);
	void SaveListToFile(string fileName);
};

Node::Node(int min, int max)
	{
		RandomizeValues(min,max);
		next = NULL;
	}

void Node::RandomizeValues(int min, int max)
	{
		//C++ 11 RNG
		random_device rd;
		std::uniform_int_distribution<int> dist(min, max);

		//Assuming min = 1900 & max = 2000
		birthYear = dist(rd);		//results in 1900-2000
		deathYear = 2000;
		if (birthYear == max)
			deathYear = max;									//capping values at max
		else													//example, birth = 1950, death results in 1950-2000
		{
			std::uniform_int_distribution<int> dist(birthYear, max);
			deathYear = dist(rd);	
		}
	}

void SaveListToFile(Node* current, string fileName)
{
	ofstream ofs;
	ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
	
	int count = 0;

	do
	{
		ofs<<count+1<<". "<<current->birthYear<<" to "<<current->deathYear<<endl;
		count++;
		current = current->next;
	}
	while(current != NULL);
}

#endif