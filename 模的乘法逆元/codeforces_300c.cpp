/**
 * https://vjudge.net/problem/CodeForces-300C
 * https://codeforces.com/problemset/problem/300/C
 *
 * @File:   codeforces_300c.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-14
 *
 */
#include <bits/stdc++.h>
using namespace std;
#define LL long long

const int MOD = 1e9 + 7;  // 模数，是一个质数

/**
 * 求 n 在模 MOD 下的逆元
 * 使用费马小定理：n^(MOD-2) ≡ n^(-1) (mod MOD)
 * 用快速幂计算 n^(MOD-2)
 */
int invmod(int n)
{
    int b = MOD - 2;        // 指数为 MOD-2
    LL ret = 1;
    LL a = n;
    while (b) {              // 快速幂
        if (b & 1)
            ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

int main(void)
{
    int a, b, n;
    LL tot;                  // 用于递推当前 x 对应的数字和

    cin >> a >> b >> n;

    // 确保 a < b，方便处理
    if (a > b)
        swap(a, b);

    /**
     * 初始化 tot 为 x = n-1 时的数字和
     * 为什么是这个值？因为循环中每次先加 (b-a)，再检查
     * 所以第一次循环得到的是 x = n 时的数字和
     */
    tot = n * a - (b - a);

    LL sum = 0;      // 最终答案
    LL tt = 1;       // 当前组合数 C(n, i)，初始为 C(n, 0) = 1

    // 枚举 x 从 0 到 n
    for (int i = 0; i <= n; i++) {
        // 先更新 tot 到当前 x 对应的数字和
        tot += (b - a);          // 第 i 次循环后，tot 对应 x = i 的数字和
        int tmp = tot;            // 临时变量，用于检查数字和是否是"好数"

        // 检查数字和 tmp 的每一位是否只包含 a 和 b
        bool fg = false;
        while (tmp) {
            int d = tmp % 10;
            if (d != a && d != b) {
                fg = true;        // 有一位不是 a 或 b，标记为不合法
                break;
            }
            tmp /= 10;
        }

        // 更新组合数 tt 为 C(n, i)
        if (i == 0) {
            tt = 1;                // C(n, 0) = 1
        } else {
            /**
             * 递推公式：C(n, i) = C(n, i-1) * (n-i+1) / i
             * 除法用乘以逆元实现
             */
            tt = tt * (n - i + 1) % MOD * invmod(i) % MOD;
        }

        // 如果当前数字和是"好数"，累加组合数
        if (!fg)
            sum = (sum + tt) % MOD;
    }

    cout << sum << endl;
    return 0;
}
