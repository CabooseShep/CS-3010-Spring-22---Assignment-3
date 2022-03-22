/* Nicholas Hortua
   Prof. Edwin Rodriguez, CS 3010 - Spring 2022
   Assignment 3, Exercise 4

   polynomial.hpp - Handles all the root finding methods along with functions to evaluate linear functions.
*/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

using std::vector;

const double epsilon_value = pow(2.0, -23.0);
int iteration_final = 0;
bool outcome;

double function_evaluation(int exp, vector<int>& func, double value);
void derivative_func(int exp, vector<int>& func, vector<int>& d_func); // responsible for creating a vector containing the derivative form of the function to be passed in function_evaluation for newton's method

double bisection_method(int exp, vector<int>& func, int i1, int i2, int iterations)
{
	// casting our two initial positions as floating point numbers
	int i_counter = 0;
	double a = (double)i1;
	double b = (double)i2;
	double f_a = function_evaluation(exp, func, a); // we input a into the function to obtain the first evaluated function value

	// obtain c,  f(c) and the error value 

	double c = (a + b) / 2.0;
	double f_c = function_evaluation(exp, func, c);
	double error_value = b - a;

	// now we begin the loop, if the root is found; we append +1 to the iteration counter to account for us starting at 0
	
	for (int i = 0; i < iterations; i++)
	{

		if (((abs((error_value)) < epsilon_value)) || (f_c == 0.0))
		{
			iteration_final = i + 1;
			cout << "Root: [" << c << "] successfully found using Bisection method with " << iteration_final << " iterations." << endl;
			outcome = true;

			file_Writing(c, iteration_final, outcome);
			return c;
		}

		else 
		{
			
			if ((f_a * f_c) < 0.0)
			{
				b = c;
			}

			else
			{
				a = c;
			}

			// repeating the process if root is not found

			f_a = function_evaluation(exp, func, a);
			c = (a + b) / 2.0;
			f_c = function_evaluation(exp, func, c);
			error_value = b - a;
			i_counter++;
		}
	}



	cout << "Max Iterations reached with no root found, Bisection converging was unsuccessful. \n";
	outcome = false;
	file_Writing(c, i_counter, outcome);
}

double newton_method(int exp, vector<int>& func, int x_i, int iterations)
{
	int i_counter = 0;
	vector<int> derivative_function{};	derivative_func(exp, func, derivative_function);

	double x_0 = (double)x_i, x = 0.0;
	double f_x = function_evaluation(exp, func, x_0);
	double f_x_d = function_evaluation(exp - 1, derivative_function, x_0);

	double f_x_n = (f_x / f_x_d);
	x = x_0 - f_x_n;

	for (int i = 0; i < iterations; i++)
	{
		if (abs(f_x_n) < epsilon_value)
		{
			iteration_final = i + 1;
			cout << "Root: [" << x << "] successfully found using Newton's Method with " << iteration_final << " iterations." << endl;
			outcome = true;
			file_Writing(x, iteration_final, outcome);

			return x;
		}

		x_0 = x;
		f_x = function_evaluation(exp, func, x_0);
		f_x_d = function_evaluation(exp - 1, derivative_function, x_0);
		f_x_n = (f_x / f_x_d);

		x = x_0 - (f_x_n);
		i_counter++;

	}

	cout << "Max Iterations reached with no root found, Newton's Method converging was unsuccessful. \n";
	outcome = false;
	file_Writing(x, i_counter, outcome);

}

double secant_method(int exp, vector<int>& func, int x1, int x2, int iterations)
{
	int i_counter = 0;
	double x_1 = (double)x1;
	double x_2 = (double)x2;
	double x = 0.0;

	double f_x_1 = function_evaluation(exp, func, x_1);
	double f_x_2 = function_evaluation(exp, func, x_2);

	double f_x_n = (((x_1 - x_2) * f_x_1) / (f_x_1 - f_x_2)); // f'(x_1): will be used to check for convergence to epsilon
	x = x_1 - f_x_n;

	for (int i = 0; i < iterations; i++)
	{
		if (abs(f_x_n) < epsilon_value)
		{
			iteration_final = i + 1;
			cout << "Root [" << x << "] successfully found using Secant Method with " << iteration_final << " iterations." << endl;
			outcome = true;
			file_Writing(x, iteration_final, outcome);

			return x;
		}

		// repeating the process again

		x_2 = x_1;
		x_1 = x;
		f_x_1 = function_evaluation(exp, func, x_1);
		f_x_2 = function_evaluation(exp, func, x_2);

		f_x_n = (((x_1 - x_2) * f_x_1) / (f_x_1 - f_x_2));
		x = x_1 - f_x_n;
		i_counter++;
	}

	cout << "Max Iterations reached with no root found, Secant Method converging was unsuccessful. \n";
	outcome = false;
	file_Writing(x, i_counter, outcome);
}

// combines both bisection and newton method together

double hybrid_method(int exp, vector<int>& func, int x1, int x2, int iterations)
{
	// casting our two initial positions as floating point numbers
	int i_counter = 0;
	double a = (double)x1;
	double b = (double)x2;
	double f_a = function_evaluation(exp, func, a);

	// obtain c, the function evaluation of c and the error value 

	double c = (a + b) / 2.0;
	double f_c = function_evaluation(exp, func, c);
	double error_value = b - a;

	// performs bisection method for the first 5 iterations, and then switches over to newton

	for (int i = 0; i < 5; i++)
	{
		if (((abs((error_value)) < epsilon_value)) || (f_c == 0.0))
		{
			iteration_final = i + 1;
			cout << "Root: [" << c << "] successfully found using the Bisection portion of Hybrid Method with " << i + 1 << " iterations." << endl;
			outcome = true;
			file_Writing(c, iteration_final, outcome);

			return c;
		}

		else
		{
			if ((f_a * f_c) < 0.0)
			{
				b = c;
			}

			else
			{
				a = c;
			}

			f_a = function_evaluation(exp, func, a);
			c = (a + b) / 2.0;
			f_c = function_evaluation(exp, func, c);
			error_value = b - a;
		}
	}

	// now moving over to newton, works the same as the standalone newton function

	vector<int> derivative_function{};
	derivative_func(exp, func, derivative_function);

	double x_0 = c;
	double f_x = f_c;
	double f_x_d = function_evaluation(exp - 1, derivative_function, c);
	double f_x_n = (f_x / f_x_d);

	double x = x_0 - (f_x_n);

	for (int j = 5; j < iterations; j++)
	{
		if (abs(f_x / f_x_d) < epsilon_value)
		{
			iteration_final = j + 1;
			cout << "Root: [" << x << "] successfully found using Newton portion of Hybrid Method with " << j + 1 << " iterations." << endl;
			outcome = true;
			file_Writing(x, iteration_final, outcome);
			return x;
		}

		x_0 = x;
		f_x = function_evaluation(exp, func, x_0);
		f_x_d = function_evaluation(exp - 1, derivative_function, x_0);
		f_x_n = (f_x / f_x_d);

		x = x_0 - (f_x_n);
	}

	cout << "Max Iterations reached with no root found, Hybrid Method converging was unsuccessful. \n";
	outcome = false;
	file_Writing(x, i_counter, outcome);

}

// handles the plugging in of f(n), and returns the final result

double function_evaluation(int d_value, vector<int>& func, double value)
{
	double exponent = (double) d_value;
	double result = 0.0;

	for (int i = 0; i < func.size(); i++)
	{
		if (exponent > 0.0)
		{
			result += (double)func[i] * pow(value, exponent);
			exponent--;
		}

		else
		{
			result += (double)func[i];
		}
	}

	return result;
}

// we create a new vector and use a for loop to obtain the coefficients for the derivative values

void derivative_func(int exp, vector<int>& func, vector<int>& d_func)
{
	int exponent = exp; 

	for (int i = 0; i < func.size(); i++)
	{
		if (exponent > 0.0)
		{
			d_func.push_back(func[i] * exponent);
			exponent--;
		}

		else
		{
			d_func.push_back(func[i] * 0);
		}
	}
}


#endif

