/* Nicholas Hortua
   Prof. Edwin Rodriguez, CS 3010 - Spring 2022
   Assignment 3, Exercise 4

   fileManagement.hpp - Handles the file processing required for input the functions for usage
   in all of the root finding methods.
*/

#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <errno.h>

using std::cout;
using std::cerr;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::vector;

int file_Reading(vector<int>& func, char* file)
{
	ifstream my_File;
	my_File.open(file);

	int exponent_val = 0, coeff = 0;
	string line;

	// reads the first line containing the degree, inserting it into the variable

	if (my_File)
	{
		my_File >> exponent_val;

		// skips the first line in order to read the line containing the function coefficients

		my_File.ignore(1000, '\n');

		while (getline(my_File, line))
		{
			istringstream fp(line); // string stream which is used to navigate through the line

			while (fp >> coeff) // will read in values until it reaches '\0'
			{
				func.push_back(coeff);
			}

		}
	}

	else
	{
		cerr << "Error: File could not be processed correctly! \n";
	}

	my_File.close();
	return exponent_val;
}

void file_Writing(double root, int iteration, bool result)
{
	ofstream solutions_file;
	solutions_file.open("fun1.sol", ofstream::out | ofstream::app);

	if (solutions_file.is_open())
	{
		solutions_file << root << " " << iteration << " ";

		if (result == true)
		{
			solutions_file << "Successful";
		}

		else
		{
			solutions_file << "Failed";
		}
	}

	solutions_file.close();

	cout << "Solutions file written. \n \n";
}

#endif