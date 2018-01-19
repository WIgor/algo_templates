#pragma once

#include <vector>
#include <string>

using namespace std;

class SufixFunction {
public:
    vector<int> func_values;

    SufixFunction(const string &str) {
        if (str.length() != 0) {
            func_values.reserve(str.length());
            func_values.push_back(0);
            if (str.length() != 1) {

                int32_t i = 1, l = 0, r = -1;
                while (i < str.length()) {
                    if (r < i) {
                        l = i;
                        r = i;
                        while (l - r >= 0 && r < str.length() && str[r] == str[l - r]) {
                            r++;
                        }
                        func_values[i] = r - l;
                    }
                }

            }
        }
    }
};