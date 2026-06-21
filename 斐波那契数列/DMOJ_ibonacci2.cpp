/**
 * https://dmoj.ca/problem/fibonacci2
 * https://vjudge.net/problem/DMOJ-fibonacci2
 *
 * @File:   DMOJ_ibonacci2.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

// 矩阵乘法：计算两个2x2矩阵的乘积，结果取模MOD
vector<vector<long long>> multiply(const vector<vector<long long>>& a,
                                  const vector<vector<long long>>& b) {
    vector<vector<long long>> result(2, vector<long long>(2, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

// 矩阵快速幂：计算矩阵base的exp次幂，exp以字符串形式给出（非常大的数）
vector<vector<long long>> powerMatrix(const vector<vector<long long>>& base, string exp) {
    vector<vector<long long>> result = {{1, 0}, {0, 1}}; // 单位矩阵
    vector<vector<long long>> current = base;

    // 从最低位到最高位处理指数的每一位数字
    for (int i = exp.size() - 1; i >= 0; i--) {
        int digit = exp[i] - '0';

        // 对当前位进行二进制幂运算（base^digit）
        for (int j = 0; j < digit; j++) {
            result = multiply(result, current);
        }

        // 计算current^10，为处理下一位做准备
        vector<vector<long long>> temp = current;
        for (int j = 0; j < 9; j++) { // current^10 = current * current^9
            temp = multiply(temp, current);
        }
        current = temp;
    }

    return result;
}

// 计算第N个斐波那契数，N以字符串形式给出
long long fibonacci(string n) {
    // 处理特殊情况：F(0)=0, F(1)=1
    if (n == "0") return 0;
    if (n == "1") return 1;

    // 将n减1，因为矩阵幂公式：[[1,1],[1,0]]^n = [[F(n+1),F(n)],[F(n),F(n-1)]]
    // 我们要计算F(n)，所以需要计算矩阵的(n-1)次幂

    // 从最低位开始减1
    int i = n.size() - 1;
    while (i >= 0 && n[i] == '0') {
        n[i] = '9';
        i--;
    }
    if (i >= 0) {
        n[i]--;
    }
    // 如果产生了前导零，去掉它们
    if (n[0] == '0' && n.size() > 1) {
        n = n.substr(1);
    }

    // 斐波那契矩阵
    vector<vector<long long>> base = {{1, 1}, {1, 0}};
    // 计算矩阵的(n-1)次幂
    vector<vector<long long>> result = powerMatrix(base, n);

    // result[0][0] 对应 F((n-1)+1) = F(n)
    return result[0][0];
}

int main() {
    string n;
    cin >> n;
    cout << fibonacci(n) << endl;
    return 0;
}
