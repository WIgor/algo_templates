#pragma once

#include <vector>
#include <string>

using namespace std;

class PrefixFunction {
public:
    vector<int> pf;
    PrefixFunction(string s) {
        pf.reserve(s.size());
        pf.push_back(0);
        for (int i = 1; i < s.size(); i++) {

        }
    }

};