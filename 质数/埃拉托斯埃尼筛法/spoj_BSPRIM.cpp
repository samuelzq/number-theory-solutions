/**
 * https://www.spoj.com/problems/BSPRIME/
 * https://vjudge.net/problem/SPOJ-BSPRIME
 *
 * @File:   spoj_BSPRIM.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-09
 *
 */
#include <bits/stdc++.h>

#define LL long long
const int Limit = 101865020;         // 质数筛选上限：约1.02亿
const int L1D_CACHE_SIZE = 37768;    // L1缓存大小，用于分段筛法优化
const int N = 1.5e8 + 7;             // 结果数组大小
unsigned prime[5899179],numPrime;    // 存储所有质数以及质数个数
unsigned binary[150000007];          // 存储预处理结果：binary[i] = 前i位中1的个数
using namespace std;

/**
 * 简单筛法：生成不超过lim的质数表
 * @param lim 上限
 * @param is_prime 标记数组
 */
void simple_sieve(LL lim, vector<bool> &is_prime)
{
	for (LL i = 2; i * i <= lim; i++) {
		if (is_prime[i]) {
			for (LL j = i * i; j <= lim; j += i)
				is_prime[j] = 0;
		}
	}
}

/**
 * 分段筛法：高效生成大范围质数
 * @param limit 筛法上限
 * @param segment_size 分段大小，默认使用L1缓存大小
 */
inline void segmented_sieve(int limit, int segment_size = L1D_CACHE_SIZE)
{
	int sqrt = (int)std::sqrt(limit);
	int count = (limit < 2) ? 0 : 1;
	int s = 2;
	int n = 3;

	vector<char> segment(segment_size);

	// 生成基础质数表（不超过sqrt(limit)）
	vector<bool> is_prime(sqrt + 1, 1);
	simple_sieve(sqrt + 1, is_prime);

	vector<unsigned> primes;
	vector<unsigned> next;
	int p = 2;
	for (unsigned low = 0; low <= limit; low += segment_size) {
		fill(segment.begin(), segment.end(), 1);

		int high = min(low + segment_size - 1, (unsigned)limit);    // 当前段上界

		// 收集基础质数（当s的平方不超过当前段上界时）;
		for (; s * s <= high; s++) {
			if (is_prime[s]) {
				primes.push_back((int) s);
				next.push_back((int)(s * s - low));
			}
		}

		// 用基础质数标记当前段的合数
		for (size_t i = 1; i < primes.size(); i++) {
			int k = primes[i] * 2;
			int j = next[i];
			for (; j < segment_size; j += k)
				segment[j] = 0;
			next[i] = j - segment_size;
		}

		// 收集当前段中的质数（只检查奇数）
		prime[1] = 2;
		prime[2] = 3;
		for (; n <= high; n += 2) {
			if (segment[n - low])
				prime[p++] = n;
		}
	}
	numPrime = p;
}

/**
 * 计算函数：生成二进制拼接序列中每个位置的累积1的个数
 * 算法：遍历每个质数，将其32位二进制表示的每一位依次处理，
 *       统计到当前位置为止遇到的1的总数，存入binary数组
 */
void compute()
{
	int b = 0, ind = 1;

	for (int i = 1; i < numPrime; i++) {
		int j, flag = 0;
		int num;
		num = prime[i];

		// 处理32位二进制表示的每一位
		for (j = 0; j < 32; j++) {
			if (num < 0) {          // 检查最高位：num<0表示最高位为1
				b += 1;             // 当前位是1，计数加1
				binary[ind++] = b;  // 记录当前位置的累积计数
				flag = 1;           // 发现最高有效位
			} else if (flag) {      // 当前位是有效的 0，累积计数不变
				binary[ind++] = b;
			}
			num =  num << 1;
		}
	}
}

int main()
{
	unsigned tc,n;
	segmented_sieve(Limit, L1D_CACHE_SIZE);

	compute();
	cin >> tc;
	while (tc--) {
		cin >> n;
		cout << binary[n] << '\n';
	}
}

