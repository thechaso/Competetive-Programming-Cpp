#include <bits/stdc++.h>
using namespace std;
#define ll long long

//return number of ways you can sum
//positive integers to achieve a sum of n
int numWaysSum(int n)
{
    //there is 1 way to reach sum of 0 --> base case
    //f(n) = f(o) + f(1) + ... + f(n - 1)
    //because we can jump to f(n) straight from f(0) or f(1) ... or f(n - 1)
    //ex. f(0) = 0, f(1) = 1, f(2) = 2 --> 0 + 2 or 1 + 1
    //f(3) = 0 + 3 = 1 + 2 = 0  + 2 + 1 = 1 + 1 + 1
    if (n == 0) return 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += numWaysSum(i);
    }
    return ans;
    //f(n) = pow(2, n - 1);
}

int factorial(int n)
{
    if (n == 0) return 1;
    if (n == 1 || n == 2) return n;
    return n * factorial(n - 1);
}

int choose(int n, int k)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}

vector<int> binomialCoefficient(int n)
{
    vector<int> ans;
    for (int k = 0; k <= n; k++) {
        ans.push_back(choose(n, k));
    }
    return ans;
}

//based on pascal's triangle
int chooseRecursive(int n, int k)
{
    if (k == 0 || k == n) return 1;
    return chooseRecursive(n - 1, k - 1) + chooseRecursive(n - 1, k);
}

//in how many ways can we place k balls in n boxes
int starsAndBars(int k, int n)
{
    int bars = n - 1;
    int stars = k;
    return choose(stars + bars, stars);
}

//in how many ways can we divide n into subsets of sizes k[i]
//where sum of all k[i] = n
int multinomialCoefficient(int n, vector<int> k)
{
    int den = 1;
    for (int i : k) {
        den *= factorial(i);
    }
    return factorial(n) / den;
}

//return nth Catalan number
int catalan(int n)
{
    return factorial(2 * n) / (factorial(n) * factorial(n + 1));
}

//calculate number of permutations of a set of size n
//S.T. none of the elements are at their original position
int numDearrangementsRecursive(int n)
{
    if (n == 1) return 0;
    if (n == 2) return 1;
    return (n - 1) * (numDearrangementsRecursive(n - 2) + numDearrangementsRecursive(n - 1));
}

int main()
{

}

