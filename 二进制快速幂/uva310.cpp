/**
 * https://vjudge.net/problem/UVA-310
 *
 * @File:   uva310.cpp
 * @Author: Lao Zhang samuelzhang77@outlook.com
 * @Date:   2026-01-04
 *
 */
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

// 执行一次 D0L 系统的迭代演化
string evolve(const string& current, const string& ruleA, const string& ruleB) {
    string nextGen = "";
    for (char c : current) {
        if (c == 'a') nextGen += ruleA;
        else if (c == 'b') nextGen += ruleB;
    }
    return nextGen;
}

bool solve() {
    string ruleA, ruleB, start, target;
    // 读取四行输入
    if (!(cin >> ruleA >> ruleB >> start >> target)) return false;

    unordered_set<string> visited;
    string current = start;

    // 迭代上限：防止无限循环或长度爆炸
    // 考虑到题目属性，如果 120 代还不出现，后续出现的概率极低
    for (int i = 0; i < 120; ++i) {
        // 检查当前字符串是否包含目标子串 z
        if (current.find(target) != string::npos) {
            cout << "YES" << endl;
            return true;
        }

        // 如果字符串过长且增长很快，只保留可能产生 z 的部分（可选优化）
        // 但 15 字符规模下，直接模拟通常可行
        if (current.length() > 2000) { 
            // 启发式剪枝：如果已经非常长还没找到，且长度持续增加，判定为 NO
            break; 
        }

        // 记忆化去重：如果回到了之前的状态，说明进入了死循环
        if (visited.count(current)) break;
        visited.insert(current);

        current = evolve(current, ruleA, ruleB);
    }

    cout << "NO" << endl;
    return true;
}

int main() {
    // 循环处理每一个测试数据块
    while (solve());
    return 0;
}
