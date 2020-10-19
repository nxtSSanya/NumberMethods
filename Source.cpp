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
#include <fstream>
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

bool shodimost(vector<vector<long double> > A) {
	vector<long double> sum(4, 0.0);
	vector<long double> Equal(4);
	bool flag = 0;
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			if (i != j) sum[i] += abs(A[i][j]);
			else Equal[i] = abs(A[i][j]);
		}
	}
#ifdef _DEBUG
	for (int i = 0; i < 4; ++i) {
		cout << "EQ " << Equal[i] << " ";
		cout << endl;
		cout << "SUM " << sum[i] << endl;
	}
#endif
	for (int i = 0; i < 4; ++i) {
		if (Equal[i] < sum[i]) {
			flag = 1;
		}
		else {
			cout << Equal[i] << " > " << sum[i];
			cout << endl << endl;
		}
	}
	if (flag) rt(false);
	else rt(true);
}
vector<vector<long double> > GetMatrixFromFile(int size) {
	vector<vector<long double> > A;
	A.resize(size);
	ifstream str("file.txt");
	for (int i = 0; i < size; i++)
	{
		A[i].resize(size + 1);

		for (int j = 0; j < size + 1; j++)
		{
			str >> A[i][j];
		}
	}
	rt(A);
}
void GetMatrix(vector<vector<long double> > A) {
	cout << "Matrix A is: " << endl << endl;
	for (int i = 0; i < A.size(); ++i) {
		for (int j = 0; j < A.size(); ++j) {
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;
}
void GetAnswer(vector<long double> ans, long double epsilon) {
	int It = 1;
	cout << "Answer is: " << endl;

	for (auto&i : ans) {
		cout.precision(3);
		cout << fixed << "x" << It << ": " << i << endl;
		It++;
	}
	cout << "With error: " << epsilon << endl;
}
int main()
{
	//#ifndef ONLINE_JUDGE	
	//	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	//#endif
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int size;		
	long double epsilon;
	vector <vector <long double> > matrix;
	cout << "Size: ";
	cin >> size;
	matrix = GetMatrixFromFile(size);
	cout << "Epsilon: ";
	cin >> epsilon;
	GetMatrix(matrix);
	cout << "Proverka shodimosti." << endl;

	if (shodimost(matrix)) { cout << "Vse horosho, metod shoditsya." << endl << endl; }
	else { cout << "Metod ne shoditsya." << endl; rt(0); }

	vector <long double> previousVariableValues(size, 0.0); //pred shag
	int it = 0, xIT = 1;
	while (true)
	{     
		vector <long double> currentVariableValues(size); //tekushiy shag
		for (int i = 0; i < size; i++)
		{
			currentVariableValues[i] = matrix[i][size];
			for (int j = 0; j < size; j++)
			{
				if (j < i)
				{
					currentVariableValues[i] -= matrix[i][j] * currentVariableValues[j];
				}
				if (j > i)
				{
					currentVariableValues[i] -= matrix[i][j] * previousVariableValues[j];
				}
			}
			currentVariableValues[i] /= matrix[i][i];
		}
		long double error = 0.0;

		for (int i = 0; i < size; i++)
		{
			error += abs(currentVariableValues[i] - previousVariableValues[i]);
		}

		if (error < epsilon)
		{
			break;
		}
		xIT = 1;//Xi
		for (auto&i : currentVariableValues) {
			
			cout << "iteraciya " << it << " ";
			cout << " x" << xIT << ":";
			cout << i << " ";
			cout << endl;
			xIT++;
		}
		it++;//iteracia
		cout << endl;
		previousVariableValues = currentVariableValues;
	}
	GetAnswer(previousVariableValues, epsilon);
	
	return 0;
}
