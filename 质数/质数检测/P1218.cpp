/**
 * https://www.luogu.com.cn/problem/P1218
 *
 * @File:   P1218.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2024-06-02
 *
 */
#include <iostream>
using namespace std;
int a[] = {2, 3, 5, 7};
int d;

int binpower(int base, int e, int mod) {
    int result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (long long)result * base % mod;
        base = (long long)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(int n, int a, int d, int s) {
    int x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (long long)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(int n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    int d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

void dfs(int p, int n)
{
    if (n == d) {
        cout << p << endl;
        return;
    }

    for (int i = 1; i <= 9; i += 2) {
        if (!MillerRabin(p * 10 + i))
            continue;
        dfs(p * 10 + i, n + 1);
    }
}


int main(void)
{
    cin >> d;

    for (int i = 0; i < 4; i++) {
        dfs(a[i], 1);
    }

    return 0;
}
