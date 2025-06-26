#include <iostream>
#include <stack>

using namespace std;

int main()
{
        string test = "This is a test!";
        stack<char> testStack;
        for (int ii = 0, ulimit = test.length(); ii < ulimit; ++ii)
        {
                if (test[ii] != ' ')
                {
                        testStack.push(test[ii]);
                }
        }
        int size = testStack.size();
        cout << size << endl;
        return 0;
}
