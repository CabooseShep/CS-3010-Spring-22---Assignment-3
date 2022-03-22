/* Nicholas Hortua
   Prof. Edwin Rodriguez, CS 3010 - Spring 2022
   Assignment 3, Exercise 4

   main.cpp - Driver file for the program, includes argument options for the different methods and iteration count
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "fileManagement.hpp"
#include "polynomial.hpp"

int main(int argc, char *argv[])
{
	cout << "== Welcome to the Polynomial Root Computation Program ==  \n \n";
	
	int func_degree = 0, initial_point = 0, initial_point2 = 0, iteration_count = 10000;
	double root = 0.0;
	char* file_name = NULL;
	vector<int> polynomial_func{};

	file_name = argv[argc - 1]; // storing the name of the file to be opened

	// calling the file input function

	func_degree = file_Reading(polynomial_func, file_name);

	// checks how many argument parameters the program is running with in order to properly select the mode the program will run in
	// as visual studio uses the filepath as the first command line parameter arg[0], the checks are added by 1 to account for this
	// - 4 arguments is considered the defaults for bisection and newton methods, with a check to see if the second argument is -newt flag
	// - 5 arguments is considered the defaults for secant and hybrid
	// - 6 arguments is considered the size for modified bisection or newton
	// - 7 arguments is considered the size for modified secant and hybrid

	switch (argc)
	{
		case 4:
			if (strcmp(argv[1], "-newt") == 0)
			{
				initial_point = atoi(argv[2]);
				root = newton_method(func_degree, polynomial_func, initial_point, iteration_count);
			}

			else
			{
				initial_point = atoi(argv[1]);
				initial_point2 = atoi(argv[2]);
				root = bisection_method(func_degree, polynomial_func, initial_point, initial_point2, iteration_count);
			}
			break;

		case 5:
			if ((strcmp(argv[1], "-sec") == 0))
			{
				initial_point = atoi(argv[2]);
				initial_point2 = atoi(argv[3]);
				root = secant_method(func_degree, polynomial_func, initial_point, initial_point2, iteration_count);
			}

			else if ((strcmp(argv[1], "-hybrid") == 0))
			{
				initial_point = atoi(argv[2]);
				initial_point2 = atoi(argv[3]);
				root = hybrid_method(func_degree, polynomial_func, initial_point, initial_point2, iteration_count);
			}
			break;

		case 6:
			if ((strcmp(argv[1], "-newt") == 0))
			{

				if ((strcmp(argv[2], "-maxIter") == 0))
				{
					iteration_count = atoi(argv[3]);
				}

				initial_point = atoi(argv[4]);
				root = newton_method(func_degree, polynomial_func, initial_point, iteration_count);
			}

			else
			{
				if ((strcmp(argv[1], "-maxIter") == 0))
				{
					iteration_count = atoi(argv[2]);
				}

				initial_point = atoi(argv[3]);
				initial_point2 = atoi(argv[4]);
				root = bisection_method(func_degree, polynomial_func, initial_point, initial_point2, iteration_count);
			}
			break;

		case 7:
			if ((strcmp(argv[1], "-sec") == 0))
			{
				if ((strcmp(argv[2], "-maxIter") == 0))
				{
					iteration_count = atoi(argv[3]);
				}

				initial_point = atoi(argv[4]);
				initial_point2 = atoi(argv[5]);
				root = secant_method(func_degree, polynomial_func, initial_point, initial_point2, iteration_count);
			}

			else if ((strcmp(argv[1], "-hybrid") == 0))
			{
				if ((strcmp(argv[2], "-maxIter") == 0))
				{
					iteration_count = atoi(argv[3]);
				}

				initial_point = atoi(argv[4]);
				initial_point2 = atoi(argv[5]);
				root = hybrid_method(func_degree, polynomial_func, initial_point, initial_point2, iteration_count);
			}
			break;

		default:
			cout << "Error in reading execution parameters, exiting. \n";
			return -1;
			break;
	}



	cout << "\n";

}
