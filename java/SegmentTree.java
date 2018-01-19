public class SegmentTree {

        public static class Value {
            int max;
            int min;

            public Value(int max, int min) {
                this.max = max;
                this.min = min;
            }

            @Override
            public String toString() {
                return "Value{" +
                        "max=" + max +
                        ", min=" + min +
                        '}';
            }
        }

        Value[] array;

        int roundTo2Pow(int v) {
            v--;
            v |= v >> 1;
            v |= v >> 2;
            v |= v >> 4;
            v |= v >> 8;
            v |= v >> 16;
            v++;
            return v;
        }

        public SegmentTree(int[] data) {
            int maxPos = roundTo2Pow(data.length);
            array = new Value[maxPos * 2];

            int pos = maxPos;
            for (int v : data) {
                array[pos] = new Value(v, v);
                pos++;
            }

            for (int i = maxPos - 1; i > 0; i--) {
                Value left = array[i * 2];
                Value right = array[i * 2 + 1];
                array[i] = merge(left, right);
            }
        }

        private Value merge(Value v1, Value v2) {
            return new Value(Math.max(v1 != null ? v1.max : 0, v2 != null ? v2.max : 0),
                    Math.min(v1 != null ? v1.min : Integer.MAX_VALUE, v2 != null ? v2.min : Integer.MAX_VALUE));
        }

        public Value query(int l, int r) {
            return query(1, l, r, 0, array.length / 2);
        }

        private Value query(int index, int l, int r, int tl, int tr) {
            if (l == tl && r == tr) return array[index];

            int m = (tl + tr) / 2;
            if (r <= m) {
                return query(index * 2, l, r, tl, m);
            } else if (l >= m) {
                return query(index * 2 + 1, l, r, m, tr);
            } else {
                return merge(query(index * 2, l, m, tl, m), query(index * 2 + 1, m, r, m, tr));
            }
        }
    }