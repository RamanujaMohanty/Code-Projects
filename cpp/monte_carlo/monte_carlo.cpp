#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

double urn() { return double(rand()) / double(RAND_MAX); }

void run_test(int test_num) {
    int N = 1000000;    int count = 0;
    int n = 2; // Default number of variables [cite: 2002, 2526, 3916]
    string name;

    for (int i = 0; i < N; i++) {
        double x1 = urn(), x2 = urn(), x3 = urn(), x4 = urn();
        double z = urn(); // Height [cite: 3627, 3631, 3863]
        double y = 0;

        switch(test_num) {
            case 1: name = "Arithmetic Mean (n=2)"; y = (x1 + x2) / 2.0; n = 2; break; // [cite: 2003, 2537]
            case 2: name = "Geometric Mean (n=2)"; y = sqrt(x1 * x2); n = 2; break; // [cite: 2011, 3911, 3915]
            case 3: name = "Min (n=2)"; y = min(x1, x2); n = 2; break; // [cite: 2011, 2219, 2663]
            case 4: name = "Product (n=2)"; y = x1 * x2; n = 2; break; // [cite: 2012, 2710, 2788]
            case 5: name = "Product (n=4)"; y = x1 * x2 * x3 * x4; n = 4; break; // [cite: 2012]
        }
        if (z <= y) count++; // [cite: 3707, 3714, 3845]
    }

    double V = (double)count / N; // [cite: 3845, 3866, 3991]
    double alpha = (n - (n + 1.0) * V) / (n - 1.0); // Andness formula [cite: 2002, 2123, 2526]
    double omega = (1.0 - alpha);
    cout << name << "\t-> V: " << V << " | Alpha: " << alpha << " | Omega: " << omega << endl;
}

int main() {
    srand(time(NULL)); // [cite: 3194, 3259, 3855]
    cout << fixed << setprecision(4);
    for(int i = 1; i <= 5; i++) run_test(i);
    return 0;
}
