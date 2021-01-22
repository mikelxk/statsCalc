#include "stats.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;
vector<double> totalInput;
int main()
{
    cout << "data:";
    std::string line;
    double d;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    while (ss >> d) {
        totalInput.emplace_back(d);
        if (ss.eof()) { // Success
            break;
        }
    }
    auto st = stats<double>(totalInput);
    cout << st;
}