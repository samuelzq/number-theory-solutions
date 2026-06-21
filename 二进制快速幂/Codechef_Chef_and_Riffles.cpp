#include <iostream>
#include <vector>
using namespace std;

vector<int> applyPermutation(vector<int> sequence, vector<int> permutation) {
    vector<int> newSequence(sequence.size());
    for (int i = 0; i < sequence.size(); i++) {
        newSequence[i] = sequence[permutation[i]];
    }
    return newSequence;
}

vector<int> permute(vector<int> sequence, vector<int> permutation, long long k) {
    while (k > 0) {
        if (k & 1) {
            sequence = applyPermutation(sequence, permutation);
        }
        permutation = applyPermutation(permutation, permutation);
        k >>= 1;
    }
    return sequence;
}

vector<int> buildPermutation(int N) {
    vector<int> perm(N);
    for (int i = 0; i < N; i++) {
        if (i < N/2) {
            perm[i] = 2 * i;
        } else {
            perm[i] = 2 * (i - N/2) + 1;
        }
    }
    return perm;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        int N;
        long long K;
        cin >> N >> K;

        // 初始序列：恒等排列
        vector<int> sequence(N);
        for (int i = 0; i < N; i++) {
            sequence[i] = i + 1;
        }

        // 构建一次 riffle 的置换
        vector<int> perm = buildPermutation(N);

        // 应用 K 次置换
        vector<int> result = permute(sequence, perm, K);

        // 输出结果
        for (int i = 0; i < N; i++) {
            cout << result[i];
            if (i < N - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
