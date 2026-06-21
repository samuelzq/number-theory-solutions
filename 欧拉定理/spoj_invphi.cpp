/**
 * SPOJ - INVPHI (Smallest Inverse Euler Totient Function)
 * 题目链接：https://www.spoj.com/problems/INVPHI/
 *
 * 思路：预处理所有可能的逆，然后 O(1) 查询
 * 1. 用筛法计算 1~MAXM 的欧拉函数值
 * 2. 建立反向映射 minv[x] = 最小的 i 使得 φ(i) = x
 * 3. 对每个查询直接输出结果
 *
 * @File:   spoj_invphi.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-23
 *
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000000;
const int MAXM = 202918035;

int phi_odd[(MAXM + 1) / 2 + 5];    // 只存奇数索引
int minv[MAXN + 5];

// 辅助函数：获取 phi[i]
int get_phi(int i) {
    if (i & 1) return phi_odd[i >> 1];
    // 偶数的情况需要特殊处理，但大部分解是奇数 [citation:7]
    // 可以用完整数组或特殊逻辑
    return 0;
}

// 辅助函数：设置 phi[i]
void set_phi(int i, int val) {
    if (i & 1) {
        phi_odd[i >> 1] = val;
    }
}

void precompute() {
    // 初始化奇数索引
    for (int i = 1; i <= MAXM; i += 2) {
        set_phi(i, i);
    }

    // 筛法（只处理奇数）
    for (int i = 3; i <= MAXM; i += 2) {
        if (get_phi(i) == i) {
            for (int j = i; j <= MAXM; j += i) {
                if (j & 1) {  // 只更新奇数
                    set_phi(j, get_phi(j) / i * (i - 1));
                }
            }
        }
    }

    // 建立反向映射（只处理奇数）
    for (int i = 1; i <= MAXM; i += 2) {
        int p = get_phi(i);
        if (p <= MAXN && minv[p] == 0) {
            minv[p] = i;
        }
    }

    // 手动补上三个偶数解 [citation:7]
    minv[16842752] = 33817088;
    minv[33685504] = 67634176;
    minv[67371008] = 135268352;
    minv[1] = 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        cout << (minv[n] ? minv[n] : -1) << '\n';
    }

    return 0;
}
