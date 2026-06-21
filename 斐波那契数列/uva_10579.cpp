/**
 * https://vjudge.net/problem/UVA-10579/origin
 * https://vjudge.net/problem/UVA-10579
 *
 * @File:   uva_10579.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 大整数相加，用vector<int>表示
vector<int> addBigInt(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) sum += a[i--];
        if (j >= 0) sum += b[j--];

        result.push_back(sum % 10);
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());
    return result;
}

// 将vector<int>转换为字符串
string vectorToString(const vector<int>& num) {
    string result;
    for (int digit : num) {
        result.push_back(digit + '0');
    }
    return result;
}

// 计算斐波那契数
string fibonacci(int n) {
    if (n == 0) return "0";
    if (n == 1 || n == 2) return "1";

    vector<int> prev1 = {1};  // f(1)
    vector<int> prev2 = {1};  // f(2)

    for (int i = 3; i <= n; i++) {
        vector<int> current = addBigInt(prev1, prev2);
        prev2 = prev1;
        prev1 = current;
    }

    return vectorToString(prev1);
}

int main() {
    int n;
    while (cin >> n) {
        cout << fibonacci(n) << endl;
    }
    return 0;
}
