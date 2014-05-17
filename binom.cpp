/*
 *	Written by : Wai Khoo
 * 	A small program to compute the probability of success for binomial distribution
 * 	Have to change some bound for each player.
 * 	Need to give the cumulative number to the program to find the probability.
 */
#include <cstdlib>
#include <iostream>

using namespace std;

// MAXSCORE is the total number of trials which is the maximum number of score each player can scores.
#define MAXSCORE	30

// Since raising to a power is "expensive", i'm storing it in an array.
double prob[MAXSCORE+1];
double oneminusprob[MAXSCORE+1];

double
binom(double p)
{
     unsigned long i;
     unsigned long long comb;
     double sum;

     /*
      * Prob[i] gives us p-to-the-i power
      * oneminusprob[i] gives us (1-p) to the i power
      */

     prob[0] = 1.0;
     oneminusprob[0] = 1.0;

     for (i = 1; i <= MAXSCORE; i++) {
	  prob[i] = prob[i-1] * p;
	  oneminusprob[i] = oneminusprob[i-1] * (1 - p);

    }

     sum = 0;
     comb = 1;
     // have to change the bound for each player. (11, 9, or 17)
     for (i = 0; i <= 11; i++) {
	  sum += comb*prob[i]*oneminusprob[MAXSCORE - i];
	  comb /= (i + 1);
	  comb *= (MAXSCORE - i);
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

     cum = atof(argv[1]); // need to input different argument for each player.

     left = 0;
     right = 1.0;
     sgnleft  = signum((binom(left)-cum));
     sgnright = signum((binom(right)-cum));

	// doing binary search with 0.000001 precision for the right probability.
     while ((right - left) > 0.000001) {
	  p = (right + left) / 2;
	  if (signum(binom(p)-cum) == sgnright)
	       right = p;
	  else
	       left = p;
     }

	cout<<"Prob of success = "<<p<<"\t Cumulative = "<<binom(p)<<endl;



}

