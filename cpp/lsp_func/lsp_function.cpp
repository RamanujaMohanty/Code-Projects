#include <cstddef>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double LARGE(double a, double A, double B)
{
    return 100.0 * min(1.0, max(0.0, (a - A) / (B - A)));
}

double SMALL(double a, double C, double D)
{
    return 100.0 * min(1.0, max(0.0, (D - a) / (D - C)));
}

double RANGE(double a, double A, double B, double C, double D)
{
    return 100.0 * min(1.0, max({0.0, (a - A) / (B - A), (D - a) / (D - C)}));
}

double GCD(const vector<double>& x, const vector<double>& w, double r)
{
    double sum = 0.0;

    for (size_t ii = 0; ii < x.size(); ++ii)
    {
        double norm_x = x[ii] / 100.0;
        sum += w[ii] * pow(norm_x, r);
    }
    return 100.0 * pow(sum, 1.0 / r);
}

int main()
{
    double weight_score = SMALL(5.5, 3.0, 7.0);
    double ram_score = LARGE(32.0, 8.0, 64.0);
    vector<double> scores = {weight_score, ram_score};
    vector<double> weights = {0.5, 0.5};
    double overall_suitability = GCD(scores, weights, 1.0);
    cout << "Weight Suitability: " << weight_score << "%" << endl;
    cout << "RAM Suitability: " << ram_score << "%" << endl;
    cout << "Overall Suitability: " << overall_suitability << "%" << endl;
    return 0;
}
