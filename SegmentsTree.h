#include <iostream>
#include <vector>

using namespace std;

template<class T, T ZERO>
class SegmentsTree {
    uint32_t MAX_ITEMS;
    vector<T> array;

    uint32_t binary_ceiling(uint32_t v) {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    const T better_query(uint32_t l, uint32_t r) {
        uint32_t level_start = MAX_ITEMS;

        T sum = ZERO;
        do {
            if (l & 1) {
                sum = sum + array[level_start + l - 1];
            }
            if (r & 1) {
                sum = sum + array[level_start + r - 2];
            }
            l = (l + 1) >> 1;
            r >>= 1;
            level_start >>= 1;
        } while (l < r);

        return sum;
    }

public:
    SegmentsTree(uint32_t max_items) {
        MAX_ITEMS = binary_ceiling(max_items);
        if (max_items == MAX_ITEMS) MAX_ITEMS <<= 1;
        array.resize(2 * MAX_ITEMS);
    }

    void build(const vector<T> &initial) {
        uint32_t level_start = MAX_ITEMS;

        auto target = array.begin();
        advance(target, level_start - 1);
        copy(initial.begin(), initial.end(), target);

        do {
            auto prev_level_start = level_start;
            level_start >>= 1;
            for (int i = 0; i < level_start; i++) {
                array[level_start + i - 1] =
                        array[prev_level_start + (2 * i) - 1] + array[prev_level_start + (2 * i)];
            }
        } while (level_start);
    }

    void update(uint32_t idx, T t) {
        uint32_t index = idx;
        uint32_t level_start = MAX_ITEMS;
        while (level_start) {
            array[level_start + index - 1] = array[level_start + index - 1] + t;
            index >>= 1;
            level_start >>= 1;
        }
    }

    const T query(uint32_t l, uint32_t r) {
        return better_query(l, r);
    }

    const T operator[](uint32_t index) {
        return array[MAX_ITEMS + index - 1];
    }

};
