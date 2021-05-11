#include <bits/stdc++.h>
using namespace std;
#define ll long long

//returns weather n is prime or not
bool isPrime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i <= floor(sqrt(n)); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

//returns map of {prime, power} pairs
map<int, int> primeFactorization(int n)
{
    map<int, int> mp;
    for (int i = 2; i <= floor(sqrt(n)); i++) {
        while (n % i == 0) {
            mp[i]++;
            n /= i;
        }
    }
    if (n > 1) mp[n]++;
    return mp;
}

//uses the above function to print prime factorization of n
void printPrimeFactorization(int n)
{
    string s = "";
    for (pair<int, int> p : primeFactorization(n)) {
        s += to_string(p.first) + "^" + to_string(p.second) + " * ";
    }
    s.pop_back();
    s.pop_back();
    cout << s << endl;
}

//returns number of factors of n
int numberFactors(int n)
{
    map<int, int> mp = primeFactorization(n);
    int ans = 1;
    for (pair<int, int> p : mp) {
        ans *= (p.second + 1);
    }
    return ans;
}

//returns sum of all factors of number
int sumFactors(int n)
{
    map<int, int> mp = primeFactorization(n);
    int ans = 1;
    for (pair<int, int> p : mp) {
        int prime = p.first, power = p.second;
        int geometricSeqSum = (1 - pow(prime, power + 1)) / (1 - prime);
        ans *= geometricSeqSum;
    }
    return ans;
}

ll productFactors(int n)
{
    ll numFact = (ll)numberFactors(n);
    return (ll)pow(n, numFact / 2);
}

//create an array sieve of size n + 1
//S.T. sieve[i] = 0 if i is prime (i >= 2)
//sieve[i] = k if i is not prime but k is prime, and k|i (i >= 2)
//O(n * log(n)) time
vector<int> sieveEratosthenes(int n)
{
    vector<int> sieve(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (sieve[i] != 0) continue;
        //i is prime
        for (int j = 2*i ; j <= n; j += i) {
            sieve[j] = i;
        }
    }
    return sieve;
}

//find kth prime number
//constraint: k < 10^6
//2nd prime is 3 {2, 3, 5, 7, 11, ...}
int kth_prime(int k)
{
    int maxN = pow(10, 6);
    vector<int> sieve = sieveEratosthenes(maxN);
    vector<int> primes;
    for (int i = 2; i <= maxN; i++) {
        if (sieve[i] == 0) primes.push_back(i);
    }
    return primes[k - 1];
}


//calculate gcd of pair of numbers
//O(log(n)) time
int euclideanAlgorithm(int a, int b)
{
    if (a == b) return a;
    if (a > b) swap(a, b);
    int rem = b % a;
    if (rem == 0) return a;
    return euclideanAlgorithm(a, rem);
}

//calculate gcd of vector of numbers
//O(n * log(n)) time
int gcd(vector<int> arr)
{
    if (arr.size() == 1) return arr[0];
    int sol = euclideanAlgorithm(arr[0], arr[1]);
    arr.erase(arr.begin() + 0);
    arr[0] = sol;
    return gcd(arr);
}

int lcm(int a, int b)
{
    return a*b / euclideanAlgorithm(a, b);
}

//return number of numbers from [1, n]
//which are relatively prime to n
//i.e. gcd(i, n) = 1 for some int i = [1, n]
int eulerTotientFunction(int n)
{
    map<int, int> mp = primeFactorization(n);
    int ans = 1;
    for (pair<int, int> p : mp) {
        int prime = p.first, power = p.second;
        ans *= (pow(prime, power - 1) * (prime - 1));
    }
    return ans;
}

//calculate x^n(mod m)
//O(log(n)) time
int modpow(int x, int n, int m)
{
    if (n == 0) return 1%m;
    long long u = modpow(x,n/2,m);
    u = (u*u)%m;
    if (n%2 == 1) u = (u*x)%m;
    return u;

}

//calculate x^n(mod m) only when m is prime
//O(log(n)) time
int fermatLittleTheorem(int x, int n, int m)
{
    if (n < m) return (int)pow(x, n) % m;
    return fermatLittleTheorem(x, n % (m - 1), m);
}

//return pair of int {x, y}
//S.T. ax + by = gcd(a, b)
//util is recursive helper function storing ans inside
//reference arguments x, y
//also returns gcd(a, b)
int util(int a, int b, int& x, int& y)
{
    if (a > b) swap(a, b);
    if (a == 0) {
      //if a=0, gcd(a, b) = 0
      //ax + by = by = b
      //therefore y = 1 and x = 0
      x = 0;
      y = 1;
      return b;//b is gcd
   }
   int x1, y1;
   int gcd = util(b%a, a, x1, y1);
   x = y1 - (b/a) * x1;
   y = x1;
   return gcd;
}

//return pair of int {x, y} S.T. ax + by = gcd(a, b)
//O(log(n))
pair<int, int> extended_ea(int a, int b)
{
    int x, y;
    util(a, b, x, y);
    return {x, y};
}

//brute force approach to extended e.a.
pair<int, int> extended_ea_bruteForce(int a, int b)
{

    int g = euclideanAlgorithm(a, b);
    if (a > b) swap(a, b);
    vector<vector<int>> backTrack;
    int rem = -1;
    while (true) {
        if (rem == g) {
            break;
        }
        vector<int> v;
        if (rem == -1) {
            v = {b, floor(b / a), a, b % a};
            rem = b % a;
        }
        else {
            int tb = backTrack[backTrack.size() - 1][2], ta = backTrack[backTrack.size() - 1][3];
            v = {tb, floor(tb / ta), ta, tb % ta};
            rem = tb % ta;
        }
        backTrack.push_back(v);
    }

    vector<vector<int>> sol;
    sol.push_back({1, backTrack[backTrack.size() - 1][0], -backTrack[backTrack.size() - 1][1], backTrack[backTrack.size() - 1][2]});
    for (int i = backTrack.size() - 2; i >= 0; i--) {
        vector<int> sub = {backTrack[i][0], -backTrack[i][1], backTrack[i][2]};
        vector<int> prev = sol[sol.size() - 1];
        vector<int> v;
        v = {prev[2], sub[0], prev[0] + prev[2] * sub[1], sub[2]};
        sol.push_back(v);
    }
    int y = sol[sol.size() - 1][0], x = sol[sol.size() - 1][2];
    return {x, y};
}


//return x S.T. a * x = 1(mod b)
int modInverse(int a, int b)
{
    //rearranging --> ax = bk + 1 for some int k
    //ax - bk = 1
    //gcd(a, b) must equal to 1 from Beizhout's identity
    //use extended e.a to find x
    int g = euclideanAlgorithm(a, b);
    if (g != 1) {
        cout << "No solutions to mod inverse";
        return -1;
    }
    pair<int, int> p = extended_ea(a, b);
    int x = p.first;
    return x;
}

//return a particular solution to the diophantine equation
//S.T. ax + by = c
//return pair of {x, y}
pair<int, int> linearDiophantine(int a, int b, int d)
{
    //From beizhout's identity, we must check that gcd(a, b) | d
    int g = euclideanAlgorithm(a, b);
    if (d % g != 0) {
        cout << "No Solutions";
        return {-1, -1};
    }
    //generate particular solutions with extended E.A. for when ax + by = gcd(a, b)
    pair<int, int> p = extended_ea(a, b);
    //get scale factor
    int scale = d / g;
    return {p.first * scale, p.second * scale};
}

//return x S.T. ax = b(mod m)
int linearCongruence(int a, int b, int m)
{
    //rewrite equation as ax = mk + b
    //ax - mk = b
    //from beizhout's identity gcd(a, m) | b
    int g = euclideanAlgorithm(a, m);
    if (b % g != 0){
        cout << "No Solutions";
        return -1;
    }
    //solve the linear diophantine equations
    pair<int, int> p = linearDiophantine(a, m, b);
    return p.first;
}

//return x, S.T. for every pair {a, b} in equations parameter
//x = a(mod b)
int chineseRemainderTheorem(vector<pair<int, int>> equations)
{
    int N = 1;
    vector<int> n, b, y, a;
    for (pair<int, int> p : equations) {
        N *= p.second;
        a.push_back(p.first);
        b.push_back(p.second);
    }
    for (pair<int, int> p : equations) {
        n.push_back(N / p.second);
    }
    int len = equations.size();
    for (int i = 0; i < len; i++) {
        y.push_back(modInverse(n[i], b[i]));
    }
    int x;
    for (int i = 0; i < len; i++) {
        x += ((a[i] * n[i] * y[i]) % N);
        x %= N;
    }
    return x;
}

//figure out if n is prime in O(n) time
bool isPrimeWilsonTheorem(int n)
{
    //n is prime exactly when (n - 1)! = n-1(mod n)
    ll fact = 1;
    for (ll i = 1; i < n; i++) {
        fact *= (i % (ll)n);
        fact %= n;
    }
    return fact == ((ll)n - 1);
}

int run()
{

}

