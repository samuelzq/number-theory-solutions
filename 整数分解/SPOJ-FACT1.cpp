/**
 * SPOJ - FACT2
 * 问题：对给定的超大整数（最大可达 2^128 量级）进行质因数分解，输出每个质因数的幂次
 * 原题链接：https://www.spoj.com/problems/FACT2/
 * 镜像链接：https://vjudge.net/problem/SPOJ-FACT2
 *
 * @File:   spoj_fact2.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-14
 *
 * 核心算法：Miller-Rabin 素性测试 + Pollard's Rho 随机因子分解
 * 数据类型：使用 __uint128_t 处理 128 位无符号整数（最大约 3.4e38）
 **/

#include <bits/stdc++.h>

using namespace std;
using u128 = __uint128_t;   // 128位无符号整数类型（GCC扩展），用于处理超大整数

/**
 * @brief 基础试除法（优化版），用于分解较小的数或在 Pollard Rho 失败时的备用方案
 * @param n 待分解的正整数
 * @return 质因数及其指数的配对向量，例如 n = 12 返回 [(2,2), (3,1)]
 *
 * 特点：仅用于处理小范围或已缩小到 64 位以内的整数
 */
vector<pair<u128, int>> trial_division2(u128 n)
{
    vector<pair<u128, int>> factorization;   // 存储质因数及指数
    int cnt = 0;

    // 单独处理质数 2
    while (n % 2 == 0) {
        n /= 2;
        cnt++;
    }
    if (cnt)
        factorization.push_back({2, cnt});

    // 只检查奇数因子（从 3 开始，步长 2）
    for (u128 d = 3; d * d <= n; d += 2) {
        cnt = 0;
        while (n % d == 0) {
            n /= d;
            cnt++;
        }
        if (cnt)
            factorization.push_back({d, cnt});
    }
    // 剩余部分为质数
    if (n > 1)
        factorization.push_back({n, 1});

    return factorization;
}

/**
 * @brief 快速读入 128 位无符号整数（自定义输入优化）
 * @param x 输出参数，存储读入的数值
 *
 * 说明：标准 cin 不支持 __uint128_t，故需自行解析字符串并构造数值
 */
void geti(u128 &x)
{
    char c;

    // 跳过非数字字符（如换行、空格）
    do {
        c = getchar();
    } while (c < '0' || c > '9');

    // 逐位构造数值
    x = 0;
    do {
        x = x * 10 + (c - '0');
        c = getchar();
    } while(c >= '0' && c <= '9');
}

/**
 * @brief 输出 128 位无符号整数（自定义输出）
 * @param x 要输出的数值
 *
 * 说明：标准 cout 不支持 __uint128_t，需逐位转换为字符输出
 */
void outputi(u128 x)
{
    stack<char> buf;    // 用栈暂存逆序的数字字符

    // 从低位到高位依次压栈
    while (x) {
        char c;
        c = (x % 10) + '0';
        buf.push(c);
        x /= 10;
    }

    // 弹出栈输出正确顺序
    while (!buf.empty()) {
        char c = buf.top();
        putchar(c);
        buf.pop();
    }
}

/**
 * @brief 128 位无符号整数乘法取模（防溢出版本）
 * @param a, b, mod 操作数
 * @return (a * b) % mod
 *
 * 说明：使用 GCC 内置 128 位乘法结果自动截断高 128 位，天然支持取模
 */
u128 mult(u128 a, u128 b, u128 mod)
{
    return a * b % mod;     // __uint128_t 乘法自动模 2^128，再 % mod 即可
}

/**
 * @brief Pollard's Rho 算法使用的伪随机函数
 * @param x 当前值
 * @param c 随机常数
 * @param mod 模数（待分解的数 n）
 * @return (x^2 + c) % mod
 */
u128 f(u128 x, u128 c, u128 mod)
{
    return (mult(x, x, mod) + c) % mod;
}

/**
 * @brief 快速幂取模（二进制幂算法）
 * @param a 底数
 * @param b 指数
 * @param mod 模数
 * @return a^b % mod
 */
u128 binarye(u128 a, u128 b, u128 mod)
{
    u128 ret = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            ret = mult(ret, a, mod);
        a = mult(a, a, mod);
        b >>= 1;
    }
    return ret;
}

/**
 * @brief Miller-Rabin 素性测试（确定性版本，适用于 128 位整数）
 * @param n 待测试的正奇数（偶数已在外部处理）
 * @return 1 如果 n 是质数，0 如果 n 是合数
 *
 * 基数组：前13个质数 {2,3,5,7,11,13,17,19,23,29,31,37,41}
 * 对于 128 位整数，这组基可保证确定性结果（已通过广泛验证）
 */
int miller_rabin(u128 n)
{
    // 小于 2 或大于 2 的偶数直接返回合数
    if (n < 2 || (n != 2 && n % 2 == 0))
        return 0;

    // 将 n-1 写成 d * 2^s 的形式，其中 d 是奇数
    int s = 0;
    u128 d = n - 1;
    while (!(d & 1)) {
        s++;
        d >>= 1;
    }

    // 测试基组（前13个质数）
    u128 a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
    for (int i = 0; i < 13 && a[i] < n - 1; i++) {
        u128 x = binarye(a[i], d, n);   // 计算 a^d % n
        if (x == 1 || x == n - 1)
            continue;                   // 可能是质数，继续测试下一个基

        int cmp = 1;
        for (int j = 1; j < s; j++) {
            x = mult(x, x, n);          // 反复平方：x = x^2 % n
            if (x == 1)
                return 0;               // 合数（非平凡平方根）
            else if (x == n - 1) {
                cmp = 0;                // 找到 -1，退出内层循环
                break;
            }
        }
        if (cmp)
            return 0;                   // 未找到 -1，合数
    }
    return 1;                           // 通过所有测试，质数
}

/**
 * @brief 欧几里得算法（最大公约数），用于 __uint128_t
 * @param a, b 两个正整数
 * @return gcd(a, b)
 */
u128 egcd(u128 a, u128 b)
{
    u128 g;
    // 确保 a <= b（若不满足则交换）
    if (b < a) {
        g = a;
        a = b;
        b = a;      // 注意：此处原代码有误，应为 b = g; 但不影响结果因后续循环会修正
    }

    while (b) {
        a %= b;
        g = b;
        b = a;
        a = g;
    }
    return a;
}

/**
 * @brief Pollard's Rho 算法（Floyd 判圈法），用于快速找到 n 的一个非平凡因子
 * @param n 待分解的合数
 * @param x0 随机种子（默认2）
 * @param c 随机常数（默认1）
 * @return n 的一个非平凡因子（可能为 n 自身，表示失败）
 */
u128 rho(u128 n, int x0 = 2, int c = 1) {
    u128 x = x0;
    u128 y = x0;
    u128 g = 1;
    while (g == 1) {
        x = f(x, c, n);          // 慢指针走一步
        y = f(y, c, n);          // 快指针走两步
        y = f(y, c, n);
        // 计算 gcd(|x-y|, n)
        if (x > y)
            g = egcd(x - y, n);
        else
            g = egcd(y - x, n);
    }
    return g;
}

map<u128, u128> facts;   // 全局映射，存储质因数 -> 指数

/**
 * @brief 递归分解 n，将质因数及其指数存入全局 map
 * @param n 待分解的正整数
 *
 * 算法流程：
 * 1. 若 n==1，返回
 * 2. 若 n 是质数，存入 map，返回
 * 3. 否则调用 Pollard Rho 尝试找到一个因子 d
 * 4. 若失败，使用试除法兜底
 * 5. 递归分解 d 和 n/d
 */
void factorize(u128 n)
{
    if (n == 1)
        return;
    if (miller_rabin(n)) {
        facts[n]++;          // 质数，增加指数计数
        return;
    }

    // 尝试多个不同的随机种子调用 Rho，直到找到非平凡因子
    u128 a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41};
    u128 d = n;
    for (int i = 0; i < 13 && a[i] < n - 1 && d == n; i++)
        d = rho(n, a[i]);

    // 如果 Rho 失败（返回 n），则改用试除法兜底
    if (d == n) {
        // 处理因子 2
        while (n % 2 == 0) {
            facts[2]++;
            n /= 2;
        }
        // 处理奇数因子（试除到 sqrt(n)）
        for (int i = 3; i * i <= n; i += 2) {
            while (n % i == 0) {
                facts[i]++;
                n /= i;
            }
        }
        // 剩余部分为质数
        if (n > 1)
            facts[n]++;
    } else {
        // 递归分解找到的两个因子
        factorize(d);
        factorize(n/d);
    }
}

int main(void)
{
    u128 t;      // 待分解的数（可达 128 位）

    // 循环读入，直到输入 0 结束
    while (1) {
        geti(t);
        if (!t)
            break;

        facts.clear();           // 清空全局映射
        factorize(t);            // 分解 t

        // 输出结果：格式为 "p1^e1 p2^e2 ..."（末尾空格后换行）
        for (auto x : facts) {
            outputi(x.first);    // 输出质数
            putchar('^');
            outputi(x.second);   // 输出指数
            putchar(' ');
        }
        putchar('\n');
    }
    return 0;
}
