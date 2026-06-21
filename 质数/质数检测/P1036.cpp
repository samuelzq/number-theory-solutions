/**
 * https://www.luogu.com.cn/problem/P1036
 *
 * @File:   P1036.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-04-04
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;


// ==================== Miller-Rabin 素数判断 ====================
int binpower(int a, int d, int mod) {
    int res = 1;
    a %= mod;
    while (d) {
        if (d & 1) res = (long long)(res * a % mod);
        a = (long long)(a * a % mod);
        d >>= 1;
    }
    return res;
}

bool check_composite(int n, int a, int d, int r) {
    int x = binpower(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int i = 1; i < r; i++) {
        x = (long long)(x * x % n);
        if (x == n - 1) return false;
    }
    return true;
}

bool MillerRabin(int n) {
    if (n < 2) return false;
    // 小素数快速判断
    int small[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int p : small) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }

    int r = 0;
    int d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 7, 61}) {
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
// ============================================================

int n, k;
int a[25];
int ans = 0;

// DFS 枚举所有组合
// start: 当前从哪个下标开始选
// cnt:  已经选了几个数
// sum:   当前选中的数的和
void dfs(int start, int cnt, int sum) {
    if (cnt == k) {
        if (MillerRabin(sum)) ans++;
        return;
    }
    for (int i = start; i < n; i++) {
        dfs(i + 1, cnt + 1, sum + a[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dfs(0, 0, 0);
    cout << ans << endl;

    return 0;
}
