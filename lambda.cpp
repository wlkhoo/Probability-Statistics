/*
 *	Written by : Wai Khoo
 *	A small program to compute the lambda for poisson distribution.
 *	Have to change the boundary manually (hard coded)
 *	Pass a number from the command prompt to this program (presumably lambda)
 */
#include <iostream>
#include <cmath>

using namespace std;

int main (int argc, char *argv[])
{
	double lambdai = 1.0;
	double ifact = 1.0;
	double result = 0.0;
	double lambda = atof(argv[1]);

	result = lambdai / ifact;

	/*
	 *	the bound can be changed accordingly...12 for the forwards, 10 for the guards, and 18 for the center.
	 *	need to find result that matches close to the probability given.
	 *	(e.g. for forward, input the number (lambda) until the result is close to 0.300)
	 */
	for (int i = 1; i <= 18; i++)
	{
		lambdai *= lambda;
		ifact *= i;
		result += lambdai / ifact;
	}

	result /= exp (lambda);

	cout<<result<<endl;

	return 0;
}
