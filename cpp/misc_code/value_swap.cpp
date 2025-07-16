#include <iostream>
using namespace std;

inline void swap(int& ii, int& jj)
{
	int temp = ii;
	ii = jj;
	jj = temp;
}

inline void swap(double& ii, double& jj)
{
	double temp = ii;
	ii = jj;
	jj = temp;
}

int main()
{
	int m = 5, n = 10;
	double x = 5.3, y = 10.6;
	cout << "int inputs: " << m << "," << n << endl;
	swap(m,n);
	cout << "int outputs: " << m << "," << n << endl;
	cout << "double inputs: " << x << "," << y << endl;
	swap(x,y);
	cout << "double outputs: " << x << "," << y << endl;
	return 0;
}
