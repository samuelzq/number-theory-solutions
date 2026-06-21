/**
 *
 * @File:   Codeforces_193E.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;
typedef __int128_t int128;

const ll MOD = 10000000000000LL;  // 10^13

// 自定义gcd函数
ll my_gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 扩展欧几里得算法
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 中国剩余定理
ll crt(ll a, ll m, ll b, ll n) {
    ll x, y;
    ll g = ext_gcd(m, n, x, y);
    
    if ((b - a) % g != 0) {
        return -1;
    }
    
    ll lcm = m / g * n;
    ll result = a + m * ((b - a) / g * x % (n / g));
    result = (result % lcm + lcm) % lcm;
    return result;
}

// 快速计算斐波那契数模 m
ll fib_mod(ll n, ll m) {
    if (n == 0) return 0;
    if (n == 1) return 1 % m;
    
    ll a = 0, b = 1;  // 对应 F(0) 和 F(1)
    ll mask = 1;
    
    // 找到n的最高位
    while (mask <= n) mask <<= 1;
    mask >>= 1;
    
    for (; mask; mask >>= 1) {
        // 计算 F(2k) = F(k) * [2*F(k+1) - F(k)]
        ll two_b_minus_a = (2 * b % m - a % m + m) % m;
        ll f2k = (a * two_b_minus_a) % m;
        
        // 计算 F(2k+1) = F(k)^2 + F(k+1)^2
        ll f2k1 = (a * a % m + b * b % m) % m;
        
        if (n & mask) {
            a = f2k1;
            b = (f2k + f2k1) % m;
        } else {
            a = f2k;
            b = f2k1;
        }
    }
    
    return a % m;
}

// 直接搜索：计算斐波那契数直到找到 f 或达到上限
ll direct_search(ll f, ll mod, ll limit) {
    if (f == 0) return 0;
    if (f == 1) return 1;
    
    ll a = 0, b = 1 % mod;
    
    // 检查前几项
    if (a == f % mod) return 0;
    if (b == f % mod) return 1;
    
    for (ll i = 2; i <= limit; i++) {
        ll c = (a + b) % mod;
        a = b;
        b = c;
        
        if (c == f % mod) {
            // 验证是否确实等于 f（不是只是模相等）
            if (fib_mod(i, MOD) == f) {
                return i;
            }
        }
    }
    
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    ll f;
    cin >> f;
    
    // 由于模数很大，直接搜索可能更简单
    // 设置一个合理的搜索上限
    const ll SEARCH_LIMIT = 2000000;  // 200万
    
    ll result = direct_search(f, MOD, SEARCH_LIMIT);
    
    if (result != -1) {
        cout << result << endl;
    } else {
        // 如果没找到，尝试使用模数分解的方法
        
        // 分解模数
        ll mod2 = 8192;           // 2^13
        ll mod5 = 1220703125LL;   // 5^13
        
        // 周期（已知）
        ll period2 = 12288;       // π(2^13)
        ll period5 = mod5 * 4;    // π(5^13) = 4 * 5^13
        
        // 直接计算模 2^13 和 5^13 的值
        ll f_mod2 = f % mod2;
        ll f_mod5 = f % mod5;
        
        // 搜索模 2^13 的周期
        vector<ll> pos2;
        ll a = 0, b = 1 % mod2;
        
        if (a == f_mod2) pos2.push_back(0);
        if (b == f_mod2) pos2.push_back(1);
        
        for (ll i = 2; i < period2 && i < 1000000; i++) {
            ll c = (a + b) % mod2;
            a = b;
            b = c;
            if (c == f_mod2) {
                pos2.push_back(i);
            }
        }
        
        // 对于模 5^13，我们不能遍历整个周期
        // 使用更聪明的方法：直接验证可能的候选
        
        if (pos2.empty()) {
            cout << -1 << endl;
            return 0;
        }
        
        ll answer = -1;
        
        // 对于每个模 2^13 的位置，尝试找到对应的模 5^13 的位置
        for (ll p2 : pos2) {
            // 检查 p2 + k * period2 是否满足模 5^13 的条件
            for (ll k = 0; k < 100; k++) {
                ll candidate = p2 + k * period2;
                if (candidate < 0) continue;
                
                // 检查是否满足模 5^13
                if (fib_mod(candidate, mod5) == f_mod5) {
                    // 验证完整模 10^13
                    if (fib_mod(candidate, MOD) == f) {
                        if (answer == -1 || candidate < answer) {
                            answer = candidate;
                        }
                    }
                }
            }
        }
        
        if (answer == -1) {
            cout << -1 << endl;
        } else {
            cout << answer << endl;
        }
    }
    
    return 0;
}
