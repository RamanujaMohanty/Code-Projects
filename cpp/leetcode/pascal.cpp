#include <iostream>

using namespace std;

int main() {
    int rows;
    cout << "Enter the number of rows for Pascal's Triangle: ";
    cin >> rows;

    for (int i = 0; i < rows; i++) {
        int coef = 1;
        for (int j = 0; j <= i; j++) {
            cout << coef << " ";
            coef = coef * (i - j) / (j + 1);
        }
        cout << endl;
    }

    return 0;
}
