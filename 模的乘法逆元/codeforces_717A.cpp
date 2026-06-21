/**
 * https://codeforces.com/problemset/problem/717/A
 *
 * @File:   codeforces_717A.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-03-15
 *
 */
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

// 快速幂 (a^b % MOD)
ll power(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 模逆元
ll modInv(ll a) {
    return power(a, MOD - 2);
}

// 扩域数结构体：表示 a + b * sqrt(5)
struct ExtNum {
    ll a, b; // a + b * sqrt(5)

    ExtNum(ll _a = 0, ll _b = 0) : a(_a % MOD), b(_b % MOD) {
        if (a < 0) a += MOD;
        if (b < 0) b += MOD;
    }

    ExtNum operator+(const ExtNum& other) const {
        return ExtNum(a + other.a, b + other.b);
    }

    ExtNum operator-(const ExtNum& other) const {
        return ExtNum(a - other.a, b - other.b);
    }

    ExtNum operator*(const ExtNum& other) const {
        // (a + b√5)(c + d√5) = (ac + 5bd) + (ad + bc)√5
        ll new_a = (a * other.a % MOD + 5 * b * other.b % MOD) % MOD;
        ll new_b = (a * other.b % MOD + b * other.a % MOD) % MOD;
        return ExtNum(new_a, new_b);
    }

    ExtNum power(ll exp) const {
        ExtNum res(1, 0);
        ExtNum base = *this;
        while (exp > 0) {
            if (exp & 1) res = res * base;
            base = base * base;
            exp >>= 1;
        }
        return res;
    }

    ExtNum inv() const {
        // (a + b√5)^-1 = (a - b√5) / (a^2 - 5b^2)
        ll denom = (a * a % MOD - 5 * b * b % MOD) % MOD;
        if (denom < 0) denom += MOD;
        ll inv_denom = modInv(denom);
        return ExtNum(a * inv_denom % MOD, (MOD - b) * inv_denom % MOD);
    }
    
    bool isOne() const {
        return a == 1 && b == 0;
    }
};

// 全局变量存储斯特林数和组合数
ll stirling[205][205];
ll C[205][205];
ll factInv[205];

// 预处理斯特林数和组合数
void precompute(int k) {
    // 组合数
    for (int i = 0; i <= k; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
    
    // 第一类斯特林数 s(n, k) = s(n-1, k-1) - (n-1)s(n-1, k)
    stirling[0][0] = 1;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= i; j++) {
            stirling[i][j] = (stirling[i-1][j-1] - (i-1) * stirling[i-1][j]) % MOD;
            if (stirling[i][j] < 0) stirling[i][j] += MOD;
        }
    }
    
    factInv[k] = modInv(1); // 实际上我们需要 k! 的逆元，这里简单处理，下面单独算
    // 其实公式里是 1/k!，我们可以最后乘。
    // 或者预先算好。这里为了简单，在计算系数时直接乘逆元。
}

ll k_factorial_inv;

// 计算 sum_{n=1}^{N} binom(F_{n+2}, k)
ExtNum solve(ll N, int k) {
    if (N == 0) return ExtNum(0, 0);
    
    ExtNum total_sum(0, 0);
    
    // 定义 phi 和 psi
    // phi = (1 + sqrt(5)) * 2^-1
    // psi = (1 - sqrt(5)) * 2^-1
    ll inv2 = modInv(2);
    ExtNum phi(inv2, inv2);
    ExtNum psi(inv2, MOD - inv2);
    ExtNum sqrt5_inv = ExtNum(0, 1).inv(); // 1/sqrt(5)

    // 系数 c_j = s(k, j) / k!
    ll k_fact = 1;
    for(int i=1; i<=k; ++i) k_fact = k_fact * i % MOD;
    ll k_fact_inv = modInv(k_fact);

    for (int j = 0; j <= k; j++) {
        if (stirling[k][j] == 0) continue;
        
        ll c_j = stirling[k][j] * k_fact_inv % MOD;
        
        // 展开 (F_{n+2})^j
        // F_{n+2} = (phi^{n+2} - psi^{n+2}) * sqrt5_inv
        // (F_{n+2})^j = sqrt5_inv^j * sum_{m=0}^j C(j, m) * phi^{(n+2)m} * (-psi)^{(n+2)(j-m)}
        
        ExtNum sqrt5_inv_pow_j = sqrt5_inv.power(j);
        
        ExtNum term_sum(0, 0);
        
        for (int m = 0; m <= j; m++) {
            // 系数部分
            ll comb = C[j][m];
            ll sign = ((j - m) % 2 == 1) ? (MOD - 1) : 1;
            ExtNum coeff(comb * sign % MOD, 0);
            
            // 底数 B = phi^m * psi^{j-m}
            ExtNum B = phi.power(m) * psi.power(j - m);
            
            // 常数部分 C_const = coeff * sqrt5_inv_pow_j * B^2
            // 因为公式里是 (n+2) 次方 = B^n * B^2
            ExtNum B2 = B.power(2);
            ExtNum C_const = coeff * sqrt5_inv_pow_j * B2;
            
            // 等比数列求和 sum_{n=1}^{N} B^n
            ExtNum geo_sum;
            if (B.isOne()) {
                // 如果 B=1，和为 N
                geo_sum = ExtNum(N % MOD, 0);
            } else {
                // sum = B * (B^N - 1) * (B - 1)^-1
                ExtNum BN = B.power(N);
                ExtNum num = B * (BN - ExtNum(1, 0));
                ExtNum den = B - ExtNum(1, 0);
                geo_sum = num * den.inv();
            }
            
            term_sum = term_sum + C_const * geo_sum;
        }
        
        // 累加到总和：c_j * term_sum
        ExtNum c_j_ext(c_j, 0);
        total_sum = total_sum + c_j_ext * term_sum;
    }
    
    return total_sum;
}

int main() {
    // 优化 IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    ll l, r;
    if (!(cin >> k >> l >> r)) return 0;
    
    precompute(k);
    
    ExtNum ans_r = solve(r, k);
    ExtNum ans_l = solve(l - 1, k);
    
    ExtNum final_ans = ans_r - ans_l;
    
    // 结果应该是整数，即 sqrt(5) 的系数为 0
    cout << final_ans.a << endl;
    
    return 0;
}
