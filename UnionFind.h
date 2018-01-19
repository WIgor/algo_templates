#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class UnionFind {
    vector<int32_t> array;
    vector<int32_t> weight;
public:
    UnionFind(const int32_t n) {
        array.reserve(n);
        weight.reserve(n);
        for (int32_t i = 0; i < n; i++) {
            array.push_back(i);
            weight.push_back(1);
        }
    }

    int32_t Find(const int32_t v) {
        int32_t parent, current = v;
        stack<int32_t> path;
        while (true) {
            parent = array[current];
            if (parent != current) {
                path.push(current);
                current = parent;
            } else {
                break;
            }
        }

        while (!path.empty()) {
            array[path.top()] = parent;
            path.pop();
        }

        return parent;
    }

    bool Union(const int32_t u, const int32_t v) {
        int32_t uprnt = Find(u);
        int32_t vprnt = Find(v);

        if (uprnt != vprnt) {
            if (weight[uprnt] < weight[vprnt]) {
                swap(uprnt, vprnt);
            }
            array[vprnt] = uprnt;
            weight[uprnt] += weight[vprnt];
            return true;
        } else {
            return false;
        }
    }
};