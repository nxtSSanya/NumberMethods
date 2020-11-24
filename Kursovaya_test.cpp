#include <iomanip> 
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
double f(double x, double y)
{
    return (3*(x*x)*cos(y*y - x*x*x))/(2*sqrt(1+x*x*x)*cos(1));
}
using namespace std;

int GetNumbersAfterDot(double eps) {
    return -1*log10(eps);
}

void method_RK(double eps) {
    double x_1, y_1, xn, h, y0, x0, k1, k2, k3, k4, y1, y2, y3, y4;
    int n = 10;
    x_1 = 0;
    y_1 = 1;
    xn = 1;
    y0 = y_1;
    x0 = 0;
    h = (xn - x_1) / n;
    for (int i = 0; i < n; i++)
    {
        y1 = y_1;
        k1 = f(x_1, y1);
        x_1 = x_1 + 0.5 * h;
        y2 = y1 + 0.5 * h * k1;
        k2 = f(x_1, y2);
        y3 = y1 + 0.5 * h * k2;
        k3 = f(x_1, y3);
        x_1 = x_1 + 0.5 * h;
        y4 = y1 + h * k3;
        k4 = f(x_1, y4);
        y_1 = y1 + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        cout.precision(GetNumbersAfterDot(eps));
        cout << fixed << "x: " << x_1 << " " << "y: " << y_1 << "\t" << "f(x,y): " << f(x_1, y_1) << endl;
    }
}
int main()
{
    double a = 0.0, b = 1.0, k1, k2, k3, k4;
    double ypr[22], ykor[22], x[22], y[22];
   // vector<double> ypr, ykor, x, y;

    double eps, abs_pogr, h;
    cout << "eps: ";
    cin >> eps;
    int i = 0;
    x[0] = a;
    y[0] = 1;

   // x.push_back(a);
   // y.push_back(1);
    h = 0.1;
    while (i <= 3)
    {
        k1 = h * f(x[i], y[i]);
    
        k2 = h * f(x[i] + h / 2, y[i] + k1 / 2);
       
        k3 = h * f(x[i] + h / 2, y[i] + k2 / 2);
       
        k4 = h * f(x[i] + h, y[i] + k3);
       

        y[i + 1] = y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;

        x[i + 1] = x[i] + h;
        ++i;
    }
    i = 4;
    while (x[i] <= b + h)
    {
        ypr[i] = y[i - 4] + ((4 * h) / 3) * (2 * f(x[i - 3], y[i - 3]) - f(x[i - 2], y[i - 2]) + 2 * f(x[i - 1], y[i - 1]));
        ykor[i] = y[i - 2] + (h / 3) * (f(x[i - 2], y[i - 2]) + 4 * f(x[i - 1], y[i - 1]) + f(x[i], ypr[i]));

        abs_pogr = abs(ykor[i] - ypr[i]) / 29;
        if (abs_pogr > eps) y[i] = ykor[i];
        else y[i] = ypr[i];
        x[i + 1] = x[i] + h;
        ++i;
    }
    cout << "numbers: " << GetNumbersAfterDot(eps) << endl;
    cout << "---------------------------------------TEST(metod Milna)-----------------------------------" << endl;
    for (int i = 1; i <= 10; ++i) {
        cout.precision(GetNumbersAfterDot(eps));
        cout << fixed << "x: " << x[i] << " " << "y: " << y[i] << "\t" << "[DEBUG]:f(x,y): " << f(x[i], y[i]) << endl;
    }
    cout << "------------------------------SUPER TEST(metod Runge-Kutta)--------------------------------" << endl;
    method_RK(eps);
    return 0;
}
