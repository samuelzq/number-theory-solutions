/**
 * UVA 11353 - A Different Kind of Sorting
 * https://vjudge.net/problem/UVA-11353
 *
 * 题目要求：按照质因子个数（从小到大）排序，如果质因子个数相同，按数值大小排序
 *
 * 算法思路：
 * 1. 使用筛法思想，在标记合数的同时记录每个数的最小质因子
 * 2. 利用DP递推：一个数的质因子总数 = 去除最小质因子后的数的质因子总数 + 1
 * 3. 对数字按(质因子总数, 数值)排序
 *
 * @File:   uva_11353.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-10
 **/
#include <bits/stdc++.h>

using namespace std;

const int N = 2000000;  // 题目给定的最大范围

// 存储数字信息的结构体
struct NumberInfo {
    int value;      // 数字本身
    int factor_cnt; // 质因子总数（包括重复的）
} numbers[N + 10];

int factor_count[N + 10];  // factor_count[i] = 数字i的质因子总数

// 比较函数：先按质因子个数升序，再按数值升序
bool compare(const NumberInfo& a, const NumberInfo& b) {
    if (a.factor_cnt == b.factor_cnt)
        return a.value < b.value;
    return a.factor_cnt < b.factor_cnt;
}

// 计算每个数的质因子总数（使用DP思想）
void compute_factor_counts() {
    // 初始化：1的特殊处理（1没有质因子）
    factor_count[1] = 0;

    // 使用类似筛法的思想
    for (int i = 2; i <= N; i++) {
        // 如果factor_count[i] == 0，说明i是质数（还未被处理）
        if (factor_count[i] == 0) {
            // i是质数，质因子总数=1
            factor_count[i] = 1;

            // 标记i的所有倍数，并记录最小质因子
            for (int j = i * 2; j <= N; j += i) {
                if (factor_count[j] == 0) {
                    // 如果还没有记录最小质因子，当前质数i就是j的最小质因子
                    // 标记一个特殊值，表示"已经被访问过，且最小质因子是i"
                    // 这里用i作为标记，实际上存储的是最小质因子
                    factor_count[j] = i;
                }
            }
        } else if (factor_count[i] != 1) {
            // 如果factor_count[i] != 1且!=0，说明i是合数
            // factor_count[i]此时存储的是i的最小质因子
            int smallest_prime = factor_count[i];
            // 递推公式：合数的质因子总数 = 去掉最小质因子后的数的质因子总数 + 1
            // i / smallest_prime 就是去掉最小质因子后的数
            factor_count[i] = factor_count[i / smallest_prime] + 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // 计算所有数的质因子总数
    compute_factor_counts();

    // 构建数字信息数组
    for (int i = 1; i <= N; i++) {
        numbers[i].value = i;
        numbers[i].factor_cnt = factor_count[i];
    }

    // 按照题目要求排序
    sort(numbers + 1, numbers + N + 1, compare);

    // 处理输入查询
    int n;
    int case_num = 1;

    while (scanf("%d", &n) && n != 0) {
        printf("Case %d: %d\n", case_num++, numbers[n].value);
    }

    return 0;
}
