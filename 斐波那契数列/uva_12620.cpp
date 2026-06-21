/**
 * https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4343
 * https://vjudge.net/problem/UVA-12620
 *
 * @File:   uva_12620.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 100;          // 模100
const int CYCLE = 300;        // 斐波那契数列模100的周期

// 预计算一个完整周期的斐波那契数（模100）
vector<int> precomputeFibMod() {
    vector<int> fib(CYCLE + 1);
    fib[1] = 1;
    fib[2] = 1;

    for (int i = 3; i <= CYCLE; i++) {
        fib[i] = (fib[i-1] + fib[i-2]) % MOD;
    }

    return fib;
}

// 预计算前缀和
vector<long long> precomputePrefixSum(const vector<int>& fib) {
    vector<long long> prefix(CYCLE + 1, 0);

    for (int i = 1; i <= CYCLE; i++) {
        prefix[i] = prefix[i-1] + fib[i];
    }

    return prefix;
}

// 计算第1到第n项的和（考虑周期性）
long long sumUpToN(long long n, const vector<int>& fib, const vector<long long>& prefix) {
    if (n <= 0) return 0;

    // 计算完整周期的个数和余数
    long long completeCycles = n / CYCLE;
    long long remainder = n % CYCLE;

    // 一个完整周期的和
    long long sumOneCycle = prefix[CYCLE];

    // 结果 = 完整周期的和 + 剩余部分的和
    long long result = completeCycles * sumOneCycle;
    result += prefix[remainder];

    return result;
}

int main() {
    // 预计算一个周期的斐波那契数和前缀和
    vector<int> fib = precomputeFibMod();
    vector<long long> prefix = precomputePrefixSum(fib);

    int T;
    cin >> T;

    while (T--) {
        long long N, M;
        cin >> N >> M;

        // 计算从第1项到第M项的和
        long long sumM = sumUpToN(M, fib, prefix);

        // 计算从第1项到第N-1项的和
        long long sumNminus1 = sumUpToN(N - 1, fib, prefix);

        // 结果 = 第N到第M项的和
        long long result = sumM - sumNminus1;

        cout << result << endl;
    }

    return 0;
}
