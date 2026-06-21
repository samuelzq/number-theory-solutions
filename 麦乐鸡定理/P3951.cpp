/**
 * https://www.luogu.com.cn/problem/P3951
 *
 * @File:   P3951.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-31
 *
 */
#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b; // 输入两个互质的金币面值
    // 根据赛尔梅斯定理，答案即为 a * b - a - b
    cout << a * b - a - b << endl;
    return 0;
}
