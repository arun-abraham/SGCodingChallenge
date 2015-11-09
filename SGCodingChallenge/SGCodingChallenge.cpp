/* 
SGCodingChallenge.cpp : Defines the entry point for the console application.
Given a list of people with their birth and end years (all between 1900 and 2000), find the year with the most number of people alive.

PSEUDO CODE: (Input size: n, Input range m)
1. Create buckets for the given range m (Example 0-100 for 1900-2000.)
2. For each Input, calculate newPeopleBorn that year
	 add 1 to the bucket where the person was born
	 subtract 1 from the bucket+1 where the person died (Assumption: Person still counts as +1 in the year he/she died)
	 (At the end of the loop, this value will effectively represent number of people born - number of people died in a year)
	 O(n) time complexity to store data
3. For each bucket, calculate the number of people alive in that year:
	 peopleAlive = peopleAliveLastYear + newPeopleBorn
	 O(n) time complexity to calculate this
4. Find the largest number of people alive in any year
	 O(n) time to calculate max
5. Print all years that had max number of people
	 O(n) time

** Overall space complexity: O(m) (Hash tables can be used instead. That will reduce space complexity, but increase time complexity)
** Overall time complexity: O(n)
*/

#include "stdafx.h"
#include "RandomListGenerator.h"

//Macros
#define MIN 1900
#define MAX 2000
#define YEAR_GAP MAX-MIN
#define OUTPUT_FILE "Result and Bar Graph.txt"
#define INPUT_LIST "Input List.txt"

//Function Declarations:
Node* RandomizeInputList();
void SaveResultToFile(int (&peopleAlive)[YEAR_GAP+2], int maxPeople, string fileName);

//Main
int _tmain(int argc, _TCHAR* argv[])
{
	//101 years including 1900 & 2000. Buffer 2001 (if person was born and died in 2000)
	int newPeopleInYear[YEAR_GAP+2];		//Effectively the new borns - people passed away
	int peopleAlive[YEAR_GAP+2];			//people alive in that year (summation)
	Node* first;
	Node* current;

	//Initialize to zeroes
	for (int i=0; i< YEAR_GAP+2; i++)
	{
		newPeopleInYear[i] = 0;
		peopleAlive[i] = 0;
	}

	//Randomize input data
	first = RandomizeInputList(); 
	current = first;
	SaveListToFile(first, INPUT_LIST);

	//Store input into Array
	do 
	{
		newPeopleInYear[current->birthYear - MIN]++;
		//Assumption: The person counts towards the population of the year he/she died in
		//Thus, he is subtracted from the system one year after that
		newPeopleInYear[current->deathYear - MIN + 1]--;
		//Next node
		current = current->next;
	}
	while (current->next != NULL);
	
	//Calculate number of people Alive in the years
	peopleAlive[0] = newPeopleInYear[0];
	int maxPeople = peopleAlive[0];

	//Calculate the largest number in the array
	for (int i=1; i < YEAR_GAP+1; i++)
	{
		peopleAlive[i] = peopleAlive[i-1] + newPeopleInYear[i];
		if (peopleAlive[i] > maxPeople)
			maxPeople = peopleAlive[i];
	}

	//Output into files:
	SaveResultToFile(peopleAlive, maxPeople, OUTPUT_FILE);

	return 0;
}

//Takes in a random size and creates a list of that many nodes
Node* RandomizeInputList()
{	
	Node* first = new Node(MIN, MAX);
	Node* current = first;
	Node* next;

	//Get a random size for input
	random_device rd;
	default_random_engine gen;
	std::uniform_int_distribution<int> dist(500, 1000);
	int inputSize = dist(gen);

	//Create nodes
	for (int i = 0; i < inputSize-1; i++)
	{
		next = new Node(MIN, MAX);
		current->next = next;
		current = next;
	}

	return first;
}

void SaveResultToFile(int (&peopleAlive)[YEAR_GAP+2], int maxPeople, string fileName)
{
	ofstream ofs;
	//Automatically clear file when the code is run
	ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);

	//Print all years that had highest number of people alive
	for (int i=0; i < YEAR_GAP+1; i++)
	{
		if (peopleAlive[i] == maxPeople)
		{
			ofs<<MIN+i<<" ("<<maxPeople<<"), ";
		}
	}

	//Graph:
	ofs<<"\n\nDistribution Graph:"<<endl;
	for (int i=0; i < YEAR_GAP+1; i++)
	{
		ofs<<MIN+i<<" ("<<peopleAlive[i]<<") : ";

		if (peopleAlive[i] > 0)
			for (int j=0; j<peopleAlive[i]; j+=4)
			{
				if(peopleAlive[i] == maxPeople)
					ofs<<"*";
				else
					ofs<<"-";
			}

		ofs<<endl;
	}
	ofs.close();
}

