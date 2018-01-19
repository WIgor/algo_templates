#pragma once

#include <vector>

using namespace std;

class FenwikTree {
    vector<int> rbt;
public:
    FenwikTree(int size) : rbt(size, 0) {
    }

    int Sum(int i) {
        int result = 0;
        while (i >= 0) {
            result += rbt[i];
            i = (i & (i + 1)) - 1;
        }
        return result;
    }

    void Inc(int i, int delta) {
        while (i < rbt.size()) {
            rbt[i] += delta;
            i = i | (i+1);
        }
    }

};
