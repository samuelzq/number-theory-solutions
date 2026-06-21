/**
 *
 * @File:   Codeforces_199A.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    if (n == 0) {
        cout << "0 0 0" << endl;
    } else if (n == 1) {
        cout << "0 0 1" << endl;
    } else if (n == 2) {
        cout << "0 1 1" << endl;
    } else {
        // 对于 n ≥ 3，总是可以表示为：
        // n = 2 * F(k) + F(k-1)，其中 n = F(k+2)
        // 实际上就是：n, F(k), F(k), F(k-1)
        
        // 我们需要找到小于n的最大斐波那契数
        int a = 0, b = 1;
        while (a + b < n) {
            int temp = a + b;
            a = b;
            b = temp;
        }
        
        // 此时 b 是小于等于n的最大斐波那契数
        // 我们需要找到 F(k) 和 F(k-1) 使得 n = 2*F(k) + F(k-1)
        // 实际上就是：F(k) = a, F(k-1) = a的前一个
        
        // 继续向前找
        int c = b - a;  // 前一个斐波那契数
        
        cout << c << " " << a << " " << a << endl;
    }
    
    return 0;
}
