/**
 * https://www.luogu.com.cn/problem/P2613
 *
 * @File:   P2613.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-24
 *
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll; // 使用 long long 类型

const ll MOD = 19260817; // 定义模数

// 扩展欧几里得算法求逆元
// 解方程 ax + by = gcd(a, b)，返回 gcd，并通过引用返回 x, y
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x); // 递归，注意交换 x, y 的位置
    y -= (a / b) * x; // 更新系数 y
    return d;
}

// 核心：读入大数并直接取模
// 由于输入可能高达10000位，必须边读入字符串边取模
ll readMod() {
    string s;
    cin >> s;
    ll res = 0;
    for (char c : s) {
        res = (res * 10 + (c - '0')) % MOD; // 模拟逐位计算并取模
    }
    return res;
}

int main() {
    // 关闭同步流以提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 读入 a 和 b，并直接对 MOD 取模
    ll a = readMod();
    ll b = readMod();

    // 情况1：如果 b 模 MOD 后为 0，则逆元不存在（除数为0）
    if (b == 0) {
        cout << "Angry!" << endl;
        return 0;
    }

    // 情况2：求 b 的逆元
    ll x, y;
    // 因为 MOD 是质数且 b != 0，所以 gcd(b, MOD) 必为 1
    ll g = exgcd(b, MOD, x, y); // 解方程 b*x + MOD*y = 1

    // 扩展欧几里得算法得到的 x 可能是负数，将其调整到 [0, MOD) 范围内
    x = (x % MOD + MOD) % MOD; // 此时 x 就是 b 模 MOD 的逆元 b^{-1}

    // 计算最终结果：(a * b^{-1}) mod MOD
    ll ans = (a * x) % MOD;
    cout << ans << endl;

    return 0;
}
