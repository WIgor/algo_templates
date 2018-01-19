#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

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
                sum = max(sum, array[level_start + l - 1]);
            }
            if (r & 1) {
                sum = max(sum, array[level_start + r - 2]);
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
            for (int i = 0; i < (int32_t) level_start; i++) {
                array[level_start + i - 1] =
                        max(array[prev_level_start + (2 * i) - 1], array[prev_level_start + (2 * i)]);
            }
        } while (level_start);
    }

    void update(uint32_t idx, T t) {
        uint32_t index = idx;
        uint32_t level_start = MAX_ITEMS;
        while (level_start) {
            array[level_start + index - 1] = max(array[level_start + index - 1], t);
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

void buildAllSums(vector<int64_t>& cumulativeSums, int32_t window, vector<int64_t>& target) {
    for (int32_t i = 0; (i + window - 1) < (int32_t)target.size(); i++) {
        target[i] = cumulativeSums[i + window] - cumulativeSums[i];
    }
}

int64_t fast(vector<int64_t>& a, vector<int32_t>& b) {
    vector<int64_t> cumulativeSumArray(a.size() + 1);
    cumulativeSumArray[0] = 0;
    for (int32_t i = 1; i <= (int32_t)a.size(); i++) {
        cumulativeSumArray[i] = cumulativeSumArray[i - 1] + a[i - 1];
    }

    int64_t result = 0;
    vector<int32_t> windows(2);
    vector<unique_ptr<SegmentsTree<int64_t, 0>>> st(2);
    st[0] = make_unique<SegmentsTree<int64_t, 0>>(a.size());
    st[1] = make_unique<SegmentsTree<int64_t, 0>>(a.size());

    vector<vector<int64_t>> dp(2, vector<int64_t>(a.size()));
    for (int i = (int32_t) b.size() - 1; i >= 0; i--) {
        result = 0;
        windows[i % 2] = b[i];
        if (i == (int32_t) b.size() - 1) {
            buildAllSums(cumulativeSumArray, windows[i % 2], dp[i % 2]);
            st[i % 2]->build(dp[i % 2]);
            result = st[i % 2]->query(0, (int32_t)a.size());
        } else {
            buildAllSums(cumulativeSumArray, windows[i % 2], dp[i % 2]);
            for (int j = 0; (j + windows[i % 2] - 1) < (int32_t)a.size(); j++) {
                int64_t prevMax = st[(i + 1) % 2]->query((uint32_t)j + 1, (uint32_t) j + windows[i % 2] - windows[(i + 1) % 2]);
                dp[i % 2][j] -= prevMax;
                if (result < dp[i % 2][j]) {
                    result = dp[i % 2][j];
                }
            }
            st[i % 2]->build(dp[i % 2]);
        }
    }
    return result;
}

int main() {

    ios::sync_with_stdio(0);
    int IO_BUFFER_SIZE = 4096;
    char io_buffer[IO_BUFFER_SIZE];
    cin.rdbuf()->pubsetbuf(io_buffer, IO_BUFFER_SIZE);

    int64_t T;
    cin >> T;

    for (int t = 0; t < T; t++) {

        int32_t N, M;
        cin >> N >> M;

        vector<int64_t> A(N);
        vector<int32_t> B(M);

        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        for (int i = 0; i < M; i++) {
            cin >> B[i];
        }

        int64_t result = fast(A, B);

        cout << result;
    }
}