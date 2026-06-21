#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXM = 105;

vector<ll> convolution(const vector<ll>& a, const vector<ll>& b, int M) {
    vector<ll> res(M, 0);
    for (int i = 0; i < M; i++) {
        if (a[i] == 0) continue;
        for (int j = 0; j < M; j++) {
            if (b[j] == 0) continue;
            int idx = (i + j) % M;
            res[idx] = (res[idx] + a[i] * b[j]) % MOD;
        }
    }
    return res;
}

vector<ll> polyPow(const vector<ll>& base, ll power, int M) {
    vector<ll> res(M, 0);
    res[0] = 1;
    vector<ll> cur = base;
    while (power > 0) {
        if (power & 1) {
            res = convolution(res, cur, M);
        }
        cur = convolution(cur, cur, M);
        power >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L, M;
    cin >> N >> L >> M;

    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    for (int i = 0; i < N; i++) cin >> C[i];

    vector<ll> cntA(M, 0), cntB(M, 0), cntBC(M, 0);
    for (int i = 0; i < N; i++) cntA[A[i] % M]++;
    for (int i = 0; i < N; i++) cntB[B[i] % M]++;
    for (int i = 0; i < N; i++) cntBC[(B[i] + C[i]) % M]++;

    // 中间 B 的个数 = L-2
    vector<ll> midDist;
    if (L == 2) {
        midDist.assign(M, 0);
        midDist[0] = 1;
    } else {
        midDist = polyPow(cntB, L - 2, M);
    }

    vector<ll> A_BC_conv = convolution(cntA, cntBC, M);

    ll ans = 0;
    for (int s = 0; s < M; s++) {
        int idx = (-s % M + M) % M;
        ans = (ans + midDist[s] * A_BC_conv[idx]) % MOD;
    }

    cout << ans << endl;

    return 0;
}
