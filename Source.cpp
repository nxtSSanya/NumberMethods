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
//#define _DEBUG
using namespace std;
map <int, long long> inversions;
vector<int> Si;
const int INF = 1 << 30;
const ll LINF = 1ll << 62;
const int MAXN = 1050;

double F(double x) {
	return 1 - 0.5*x*x*log(x) + 0.3*sqrt(x);
}
double GetAns(double(*f)(double), double a, double b, double eps, int accuracy) {
	double c;
	int it = 0;
	vector<long double> cn;
	double pred;
	while (1) {
		pred = a;
		c = a - f(a)*(b-a) / (f(b)-f(a));
		if ((f(a)*f(c)) < 0) b = c;
		else a = c;
		cn.push_back(c);
		cout.precision(accuracy);
		cout << fixed << "Iteration: " << it << "|\t";
		cout << fixed << "Xn: " << c << "\t";
		cout << fixed << "f(Xn): " << f(c) << "\t";
		if(it != 0)
		cout << fixed << "|Xn - Xn-1|: " << abs(c-pred) << endl;
		cout << endl;
		it++;
		if (abs(c-pred) <= eps) break;
	}
#ifndef _DEBUG
	for (int i = 0; i < cn.size() - 1; ++i) {
		cout <<"RAZNOST X: " << abs(cn[i] - cn[i + 1]) << " ";
	}
#endif
	return c;
}
int GetNumbersAfterDot(long double eps) {
	string s = to_string(eps);
	string res;
	int ind = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '.') {
			ind = i;
		}
	}
	for (int i = ind + 1; i < s.size(); ++i) {
		res += s[ind];
	}
	return res.size();
}

int main()
{
	//#ifndef ONLINE_JUDGE	
	//	freopen("input.txt", "r", stdin); freope	n("output.txt", "w", stdout);
	//#endif
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
	cout << GetAns(F, a, b, epsilon, GetNumbersAfterDot(epsilon));
	return 0;
}
