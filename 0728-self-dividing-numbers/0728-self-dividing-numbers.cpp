class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> res;

        for (int i = left; i <= right; i++) {
            int temp = i;
            bool f = true;

            while (temp) {
                int div = temp % 10;

                if (div == 0 || i % div != 0) {
                    f = false;
                    break;
                }

                temp /= 10;   // move to next digit
            }

            if (f) res.push_back(i);
        }

        return res;
    }
};