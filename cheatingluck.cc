/* This is an example solution to the "Cheating Luck" problem from the
 * Spotify Programming Challenge, held on May 29, 2010.
 *
 * The solution is provided as-is, is not documented, and may be
 * generally difficult to read.
 *
 * This work by Scrool (http://scrool.se/) is licensed under a
 * Creative Commons Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You
 * are free to redistribute it as you like as long as this license
 * information is not removed.
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

int tot;
int bet[2001][51][51];
int val[2001][51][51];

int Val(int m, int n, int k);

int Bet(int m, int n, int k) {
  if (!k || !n || !m) return m;
  
  Val(m, n, k);
  
  return bet[m][n][k];
}

int Val(int m, int n, int k) {
  if (m >= tot) return tot;		//If Donald's amount is greater or equal to the total coins, then the game ends and he has max coins
  
  if (!k || !n || !m) return min((ll)tot, m*(1LL << n));	// 1LL << n conversion of int to Long; Why multiply m*n?;
															// ll is small LL, not 11 (eleven} and is custom type casting ...
															// ...see the typedef at the top
  int &res = val[m][n][k];		//Instantiation of a reference variable?? denoting the array of parameters
								//Perhaps it also points to the first value in the arrat, that is, 'm'
  
  if (res == 0) {
    res = m;
    int mlo = Bet(m-1, n, k), mhi = min(m, tot-m); 	//Comma operator used to update the stuff before the comma, then evaluate what
													//is after the comma and assign to the variable on the left

    if (mlo > mhi) mlo = mhi;
		bet[m][n][k] = mlo;
    
	// this may look bad, but an amortized analysis shows that
    // this loop is O(1) amortized time
    for (int b = mlo; b <= mhi; ++b) {
      int v = min(Val(m-b, n-1, k-1), Val(m+b, n-1, k));
      if (v < res) break;
      bet[m][n][k] = b;
      res = v;
    }
  }
  return res;
}

int main(void) {
  int md, mg, n, k;		//Donald's coins, Gladstone's coins, total number of rounds to play, number of rounds Donald will win
  
  scanf("%d%d%d%d", &md, &mg, &n, &k);
  
  tot = md + mg;	//Total amount of coins in the game, i.e. what Donald has abd what Gladstone has
  
  memset(val, 0, sizeof(val));
  
  printf("%d\n", Val(md, n, n-k));
  
  return 0;
}

