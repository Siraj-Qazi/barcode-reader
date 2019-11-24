#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int decodeBinary(vector<int>);

long decode39(vector<int>);

long decode48(vector<int>);

long factorial(long);

long nCr(long n, long r);

int main() {
    cout << "\n Input numbers.\n Press Enter Key when done.\n> ";
    string input;
    getline(cin, input);
    istringstream ss(input);
    vector<int> inputs;
    while (ss) {
        int inp;
        ss >> inp;
        inputs.push_back(inp);
    }

    inputs.pop_back();

    /*  DEBUG
     *
     *
    cout <<"\n Number of input items: "<<inputs.size()<<"\n";


    for (auto i : inputs)
        cout << "  "<< i;

    */

    if (inputs.size() != 8 && inputs.size() != 9 && inputs.size() != 10) {
        cout << "\n Error: Input can only be in Code 39 (9 digits), Code 48 (8 digits) or in Binary Code(10 digits)!";
        exit(1);
    }

    if (inputs.size() == 8)
        cout << "\n Code 48: " << decode48(inputs) <<"\n";

    else if (inputs.size() == 9)
        cout << "\n Code 39: " << decode39(inputs) <<"\n";

    else if (inputs.size() == 10)
        cout << "\n Binary Code: " << decodeBinary(inputs) <<"\n";

}

int decodeBinary(vector<int> input) {
    int m = (3 * input[0]) / 2;
    int answer = 0;
    for (int i = 0; i <= 9; ++i) {
        answer = answer * 2;
        if (input[i] > m)
            answer = answer + 1;
    }

    return answer;
}

long decode39(vector<int> input) {
    int total = 0;
    for (int i = 0; i <= 8; ++i) {
        total = total + input[i];
    }

    int mid = total / 8;

    long answer = 0;
    int k = 3;

    for (int i = 8; i >= 0; --i) {
        if (input[8 - i] > mid) {
            if (k == 0) {
                cout << "\n Error! Too many iterations!";
                return -1;
            }

            answer = answer + nCr(i, k);
            k = k - 1;
        }
    }

    return answer;

}

long decode48(vector<int> input) {
    int total = 0;
    for (int i = 0; i <= 7; ++i) {
        total = total + input[i];
    }

    int mid = total / 8;

    long answer = 0;
    int k = 4;

    for (int i = 7; i >= 0; --i)
    {
        //cout << "\n i = "<<i;
        if (input[7 - i] < mid) {
            if (k == 0) {
                cout << "\n Error! Too many black bars!";
                return -1;
            }

            answer = answer + nCr(i, k);
            k = k - 1;
        }
    }

    if (k != 0) {
        cout << "\n Error! Not enough black bars!";
        return -1;
    }

    return --answer;
}

long factorial(long n) {
    //cout <<"\n Recursing at n = "<<n;
    return (n < 2) ? 1 : factorial(n - 1) * n;
}

long nCr(long n, long r) {
    return (factorial(n) / (factorial(n - r) * factorial(r)));

}