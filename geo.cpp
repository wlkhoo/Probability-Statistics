/*
 *	Written by : Wai Khoo
 * 	A small program to compute the probability of success for geometric distribution using (1-p)^(k-1) * p
 * 	Have to change some bound for each player.
 * 	Need to give the cumulative number to the program to find the probability.
 */
#include <cstdlib>
#include <iostream>

using namespace std;

// MAXSCORE is the total number of trials which is the maximum number of score each player can scores.
#define MAXSCORE	30

// Since raising to a power is "expensive", i'm storing it in an array.
double oneminusprob[MAXSCORE+1];

double geo(double p)
{
     unsigned long i;
     double sum;

     /*
      * oneminusprob[i] gives us (1-p) to the i power
      */

     oneminusprob[0] = 1.0;

     for (i = 1; i <= MAXSCORE; i++)
	  	oneminusprob[i] = oneminusprob[i-1] * (1 - p);

     sum = p / (1.0-p);

     // have to change the bound for each player. (11, 9, or 17)
     for (i = 1; i <= 17; i++) {
	  sum += oneminusprob[i-1] * p;

     }
     return sum;
}

inline int signum(double x)
{
     if (x == 0)
	  return 0;
     else if (x < 0)
	  return -1;
     else
	  return 1;
}

main(int argc, char *argv[])
{
     unsigned long i;

     double p, cum;

     double left, right;
     int sgnleft, sgnright;

     cum = atof(argv[1]); // need to input different argument for each player (the cumulative).

     left = 0.0;
     right = 1.0;
     sgnleft  = signum((geo(left)-cum));
     sgnright = signum((geo(right)-cum));

	// doing binary search with 0.000001 precision for the right probability.
     while ((right - left) > 0.000001) {
	  p = (right + left) / 2;
	  if (signum(geo(p)-cum) == sgnright)
	       right = p;
	  else
	       left = p;
     }

	cout<<"Prob of success = "<<p<<"\t Cumulative = "<<geo(p)<<endl;
}
