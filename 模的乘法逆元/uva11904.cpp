/**
 * UVa 11904 - One Unit Machine
 * 解题思路：乘法原理 + 隔板法
 * 从前往后依次处理每个作业，将当前作业的单元插入到已排好的序列中
 *
 * @File:   uva11904.cpp
 * @Author: Lao Zhang <samuelzhang77@yahoo.com>
 * @Date:   2022-01-26
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;  // 模数，是一个质数
const int N = 1e6;        // 最大可能的阶乘数
#define LL long long      // 定义长整型别名
LL f[N + 1];              // f[i] 存储 i! (阶乘) 模 MOD 的值

/**
 * 预计算阶乘数组 f[0] 到 f[N]
 * 用于后续快速计算组合数
 */
void factorials(void)
{
	LL ret = 1;
	f[0] = ret;                    // 0! = 1
	for (int i = 1; i <= N; i++)
		f[i] = ret = ret * i % MOD; // i! = (i-1)! * i % MOD
}

/**
 * 扩展欧几里得算法
 * 求解 ax + by = gcd(a, b) 的一组整数解 (x, y)
 * 参数: a, b - 输入的两个整数
 *       x, y - 引用参数，用于返回解
 * 返回: gcd(a, b)
 */
int ext_euclidean(int a, int b, int &x, int &y)
{
	if (b == 0) {                  // 递归终止条件
		x = 1;
		y = 0;
		return a;
	}
	
	int x1, y1;
	int g = ext_euclidean(b, a % b, x1, y1);  // 递归求解
	x = y1;                          // 回溯得到原方程的解
	y = x1 - y1 * (a / b);
	return g;
}

/**
 * 求 a 在模 m 下的逆元
 * 使用扩展欧几里得算法实现，要求 gcd(a, m) = 1
 * 参数: a - 要求逆元的数
 *       m - 模数
 * 返回: a 的模逆元，如果不存在则返回 -1
 */
int inv_mod(int a, int m)
{
	int x, y;
	int g = ext_euclidean(a, m, x, y);  // 求解 ax + my = gcd(a, m)
	if (g != 1) {                        // 如果 gcd ≠ 1，逆元不存在
		return -1;
	} else {
		x = (x % m + m) % m;              // 调整 x 到 [0, m-1] 范围
		return x;
	}
}

/**
 * 计算组合数 C(a, b) mod MOD
 * 公式: C(a, b) = a! / (b! * (a-b)!) mod MOD
 * 由于除法在模运算中要转换为乘以逆元，所以:
 * C(a, b) = f[a] * inv_mod(f[a-b] * f[b] % MOD, MOD) % MOD
 * 参数: a, b - 组合数的上下标
 * 返回: C(a, b) mod MOD
 */
LL comb(LL a, LL b)
{
	if (a < b)                       // 如果 a < b，组合数为 0
		return 0;
	if (a == b)                       // 如果 a == b，组合数为 1
		return 1;
	// 计算分母 b! * (a-b)! 模 MOD，再求其逆元，最后乘以分子 a!
	return f[a] * inv_mod(f[a - b] * f[b] % MOD, MOD) % MOD;
}

int main(void)
{
	int t;
	factorials();                      // 预计算阶乘表
	cin >> t;
	
	for (int i = 1; i <= t; i++) {
		LL n, sum = 0, ans = 1;
		cin >> n;                        // 输入作业数量
		
		// 从前往后依次处理每个作业
		while (n--) {
			int k;
			cin >> k;                      // 当前作业的单元数
			
			/**
			 * 核心公式：把当前作业的 k-1 个普通单元
			 * 插入到已有 sum 个单元形成的空隙中
			 * 插入方式数为 C(k-1 + sum, sum)
			 * 
			 * 解释：
			 * - 已有 sum 个单元，形成 sum+1 个空隙
			 * - 需要放 k-1 个相同的球（普通单元）
			 * - 隔板法公式：C((k-1) + (sum+1) - 1, (sum+1)-1) 
			 *   = C(k-1 + sum, sum)
			 */
			ans = ans * comb(k - 1 + sum, sum) % MOD;
			sum += k;                      // 将当前作业的所有单元加入已处理集合
		}
		
		cout << "Case " << i << ": " << ans << '\n';
	}
	return 0;
}
