//#pragma GCC optimize("O3")
#pragma comment(linker, "/STACK:36777216")
#define _CRT_SECURE_NO_WARNINGS
#define all(x) begin(x), end(x)
#include <iostream>
#include <functional>
#include <cstdio>
#include <climits>
#include <cmath>
#include <map>
#include <set>
#include <thread>
#include <chrono>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
//#include <bitset>
#define ll long long
#define ull unsigned long long
#define endl "\n"
#define rt(x) return(x)
using namespace std;	
map <int, long long> inversions;
vector<int> Si;
const int INF = 1 << 30;
const ll LINF = 1ll << 62;	
const int MAXN = 1050;

double F(double x) {
	return 1 - 0.5*x*x*log(x) + 0.3*sqrt(x);
	//return 2 * x*x - x * x*x - exp(x);
}
double GetAns(double(*f)(double), double a, double b, double eps) {
	double c;
	int it = 0;
	while (1) {
		c = a - f(a)*(b-a) / (f(b)-f(a));
		if ((f(a)*f(c)) < 0) b = c;
		else a = c;
		cout << "Iteration: " << it << "|\t";
		cout << "Xn: " << c << "\t";
		cout << "f(Xn): " << f(c) << "\t";
		cout << "|Xn - Xn-1|: " << abs(f(b) - f(a)) << endl;
		cout << endl;
		it++;
		if (f(c) < eps) break;
	}
	return c;
}

int main()
{
	//#ifndef ONLINE_JUDGE	
	//	freopen("input.txt", "r", stdin); freope	n("output.txt", "w", stdout);
	//#endif
	//vector<ll> st(57);
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	double a, b, epsilon, x;
	cout << "Interval: ";
	cin >> a >> b;
	if (F(a)*F(b) > 0) {
		cout << "Wrong interval!" << endl;
		return 0;
	}
	cout << "error: ";
	cin >> epsilon;
	cout << GetAns(F, a, b, epsilon);
	return 0;
}
//c - (f(c)/(f(a) - f(c))*(a-c)
