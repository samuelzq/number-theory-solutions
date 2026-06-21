/**
 *
 * @File:   Codeforces_217B.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, r;
    cin >> n >> r;

    if (n == 1) {
        if (r == 1) {
            cout << "0\nT\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
        return 0;
    }

    if (r == 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    if (n > r) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    int best_k = -1;
    int best_b = -1;

    for (int b = 1; b < r; ++b) {
        int a = r;
        int c = b;
        int sum = 0;
        int k = 0;
        bool exceeded = false;
        while (c != 0) {
            int q = a / c;
            sum += q;
            if (sum > n) {
                exceeded = true;
                break;
            }
            k++;
            int rem = a % c;
            a = c;
            c = rem;
        }
        if (exceeded) {
            continue;
        }
        if (a != 1) {
            continue;
        }
        if (sum == n) {
            if (k > best_k) {
                best_k = k;
                best_b = b;
            }
        }
    }

    if (best_k == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    int mistakes = n - (best_k + 1);

    int top0, bottom0;
    if (best_k % 2 == 1) {
        top0 = best_b;
        bottom0 = r;
    } else {
        top0 = r;
        bottom0 = best_b;
    }

    vector<int> Q;
    int a = r;
    int c = best_b;
    while (c != 0) {
        int q = a / c;
        Q.push_back(q);
        int rem = a % c;
        a = c;
        c = rem;
    }

    char first_type = (top0 > bottom0) ? 'T' : 'B';
    vector<pair<char, int>> blocks;

    for (int i = 0; i < best_k; ++i) {
        char type;
        if (i % 2 == 0) {
            type = first_type;
        } else {
            type = (first_type == 'T') ? 'B' : 'T';
        }
        int len = Q[i];
        if (i == best_k - 1 && type == 'B') {
            if (len > 1) {
                blocks.emplace_back('B', len - 1);
                blocks.emplace_back('T', 1);
            } else {
                blocks.emplace_back('B', 1);
            }
        } else {
            blocks.emplace_back(type, len);
        }
    }

    string rev;
    rev.reserve(n);
    for (const auto& block : blocks) {
        rev.append(block.second, block.first);
    }

    string forward(rev.rbegin(), rev.rend());

    cout << mistakes << '\n';
    cout << forward << '\n';

    return 0;
}
