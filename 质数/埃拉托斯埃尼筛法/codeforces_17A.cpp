/**
 * Codeforces - Noldbach Problem (问题 17A)
 * 题目链接: https://codeforces.com/problemset/problem/17/A
 *
 * 题目大意：判断在 2 到 n 的范围内，是否存在至少 k 个质数，
 *           可以表示为“两个相邻质数之和再加 1”的形式。
 *           例如 19 = 7 + 11 + 1，其中 7 和 11 是相邻质数。
 *
 * @File:   Codeforces_17A.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-11
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2005;      // 定义数组大小，略大于 n 的最大值 1000

char is_prime[N];        // 标记数组，0表示质数，1表示合数（注意这里逻辑是反的）
int primes[N];           // 存储从2开始的所有质数
int primes_cnt = 0;      // 质数个数

/**
 * 埃拉托斯特尼筛法，生成 N 以内的所有质数
 * 注意：代码中 is_prime[i] = 0 表示 i 是质数，=1 表示合数
 */
void sieve(void)
{
    // 0 和 1 不是质数
    is_prime[0] = is_prime[1] = 1;

    // 埃氏筛核心
    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i] == 0) {          // 如果 i 是质数
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = 1;         // 将 i 的所有倍数标记为合数
        }
    }

    // 收集所有质数到 primes 数组
    primes[0] = 2;                        // 第一个质数是2
    primes_cnt = 1;
    for (int i = 3; i <= N; i += 2) {     // 只检查奇数，因为偶数除了2都不是质数
        if (is_prime[i] == 0) {
            primes[primes_cnt++] = i;     // 存储质数
        }
    }
}

int main(void)
{
    int n, k;
    sieve();                               // 预处理：生成所有需要的质数

    cin >> n >> k;                         // 读入范围 n 和需求 k
    int cnt = 0;                           // 计数器：统计符合条件的质数个数

    // 遍历所有不超过 n 的质数 primes[i]
    for (int i = 0; primes[i] <= n; i++) {
        // 内层循环：寻找相邻质数对 (primes[j], primes[j+1])
        for (int j = 0; j < i; j++) {       // j < i 确保 primes[j+1] 不超过当前数
            // 检查条件：当前质数 primes[i] 是否可以写成：
            // 相邻质数对的和 + 1，即 primes[i] = primes[j] + primes[j+1] + 1
            if (primes[j + 1] + primes[j] == primes[i] - 1) {
                // 条件等价于 primes[j] + primes[j+1] + 1 == primes[i]
                cnt++;                       // 找到一个符合条件的质数
                break;                       // 找到一个即可，跳出内层循环
            }
        }
    }

    // 判断是否至少存在 k 个
    if (cnt >= k)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
