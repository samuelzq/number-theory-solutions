/**
 *
 * @File:   test_cycle.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-02-07
 *
 */
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 验证循环节的更准确方法
void verifyCycle() {
    vector<int> fib(2);
    fib[0] = 1;  // f(1)
    fib[1] = 1;  // f(2)

    map<pair<int, int>, int> seen;  // 记录(f(i), f(i+1))出现的位置

    // 记录起始状态
    seen[{1, 1}] = 1;  // (f(1), f(2))出现在位置1

    for (int i = 2; ; i++) {
        // 计算下一项
        int next = (fib[i-1] + fib[i-2]) % 100;
        fib.push_back(next);

        // 检查当前连续两项是否出现过
        pair<int, int> current_pair = {fib[i-1], fib[i]};

        if (seen.count(current_pair)) {
            int start_pos = seen[current_pair];
            cout << "Found cycle!" << endl;
            cout << "Start position: " << start_pos << endl;
            cout << "Current position: " << i << endl;
            cout << "Cycle length: " << i - start_pos << endl;
            break;
        }

        // 记录当前状态
        seen[current_pair] = i;
    }
}

int main() {
    verifyCycle();
    return 0;
}
