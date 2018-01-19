#pragma once

#include <vector>
#include <string>

using namespace std;

class PrefixFunction {
public:
    vector<int> func_values;

    PrefixFunction(const string &str) {
        if (str.length() != 0) {
            func_values.reserve(str.length());
            func_values.push_back(0);
            if (str.length() != 1) {

                int32_t i = 0, j = 1;
                while (j < str.length()) {
                    if (str[i] == str[j]) {
                        i++;
                        j++;
                        func_values.push_back(i);
                    } else if (str[i] != str[j] && i == 0) {
                        j++;
                        func_values.push_back(i);
                    } else {
                        i = func_values[i - 1];
                    }
                }

            }
        }
    }
};