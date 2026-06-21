/**
 * Codeforces - Colliders (问题 154B)
 * 题目链接: https://codeforces.com/problemset/problem/154/B
 *
 * 题目大意：有 n 个对撞机，初始都是关闭的。处理 m 个请求，每个请求是激活 (+) 或关闭 (-) 一个编号为 i 的对撞机。
 *           关键约束：任意两个处于激活状态的对撞机的编号必须互质（即 gcd 为 1）。
 *           如果尝试激活一个与已激活设备不互质的对撞机，则激活失败，并报告冲突。
 *
 * @File: Codeforces_154B.cpp
 * * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-12
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;      // 定义最大数量，略大于 n 的最大值 1e5

int d[N];                   // d[i]：存储 i 的最小质因子（例如 d[6]=2, d[15]=3, d[7]=7）
int prime_num = 0;          // 质数个数，本代码中未使用
int md[N];                  // md[p]：记录当前正在使用的、包含质因子 p 的那个对撞机编号
bool stats[N];              // stats[i]：对撞机 i 的当前状态，true=激活，false=关闭
int evenc = 0;              // 特殊标记：记录当前激活的偶数编号对撞机（因为所有偶数都有公因子2）

/**
 * 筛法预处理：计算每个数的最小质因子
 * 结果存储在 d[] 中。例如，d[12] = 2 (最小质因子), d[5] = 5 (质数本身)
 */
void sieve(void)
{
    d[1] = 1;               // 1 没有质因子，特殊处理
    for (int i = 2; i <= N; i++) {
        if (d[i] == 0) {    // 如果 d[i] 为0，说明 i 是质数（因为没有被更小的数标记过）
            for (int j = 2 * i; j <= N; j += i) // 标记 i 的所有倍数，记录它们的最小质因子 i
                d[j] = i;
            d[i] = i;        // 质数的最小质因子就是它自己
            prime_num++;
        }
    }
}

/**
 * 检查尝试激活编号为 n 的对撞机是否会与当前已激活的设备冲突
 * @param n   待激活的编号
 * @param tot 未使用
 * @return    0 表示无冲突；非0表示冲突，返回冲突的对撞机编号
 *
 * 原理：检查 n 的每个不同质因子 p，是否已经被其他激活的设备占用（md[p] != 0）
 */
int check(int n, int tot)
{
    // 处理偶数的特殊情况：所有偶数都共享质因子2，所以如果已经有偶数激活（evenc != 0），直接冲突
    if (!(n % 2) && evenc)
        return evenc;

    int a, t;
    t = n;
    a = d[n];               // 获取 n 的最小质因子
    while (a != 1) {        // 遍历 n 的所有不同质因子（利用 d 数组迭代）
        if (md[a])          // 如果这个质因子 a 已经被其他设备占用
            return md[a];   // 返回占用该质因子的设备编号
        t /= a;             // 去除当前质因子，继续寻找下一个不同的质因子
        a = d[t];
    }
    return 0;               // 所有质因子都未被占用，无冲突
}

/**
 * 当成功激活设备 n 时，记录它所占用的所有质因子
 * @param n 成功激活的设备编号
 */
void set_m(int n)
{
    int a, t;
    t = n;
    a = d[n];
    while (a != 1) {        // 遍历 n 的所有不同质因子
        md[a] = n;          // 标记质因子 a 被设备 n 占用
        t /= a;
        a = d[t];
    }
}

/**
 * 当关闭设备 n 时，清除它占用的所有质因子标记
 * @param n 关闭的设备编号
 */
void clear_m(int n)
{
    int a, t;
    t = n;
    a = d[n];
    while (a != 1) {        // 遍历 n 的所有不同质因子
        md[a] = 0;          // 清除质因子 a 的占用标记
        t /= a;
        a = d[t];
    }
}

int main(void)
{
    int n, m;
    sieve();                // 预处理：计算所有数的最小质因子

    cin >> n >> m;
    while(m--) {
        char op;
        int c;

        cin >> op >> c;     // 读取请求：操作符和编号

        if (op == '-') {    // 关闭操作
            if (stats[c] == 0)                  // 如果已经关闭
                cout << "Already off\n";
            else {                               // 成功关闭
                if (evenc == c)                  // 如果关闭的是当前记录的偶数，清空 evenc
                    evenc = 0;
                stats[c] = 0;                    // 更新状态
                clear_m(c);                      // 清除它占用的所有质因子标记
                cout << "Success\n";
            }
        } else if (op == '+') { // 激活操作
            if (stats[c] == 1)                   // 如果已经激活
                cout << "Already on\n";
            else {
                int cf = check(c, n);             // 检查是否有冲突
                if (cf)                            // 有冲突
                    cout << "Conflict with " << cf << '\n';
                else {                             // 无冲突，成功激活
                    if (c % 2 == 0)                // 如果是偶数，记录到 evenc
                        evenc = c;
                    stats[c] = 1;                   // 更新状态
                    set_m(c);                        // 标记它占用的所有质因子
                    cout << "Success\n";
                }
            }
        }
    }
    return 0;
}
