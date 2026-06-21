#include <iostream>
#include <queue>
#include <cstring> // 用于memset
#include <iomanip> // 用于setw

using namespace std;

const int MAXN = 405; // 最大棋盘尺寸

struct Point {
    int x, y;
};

int n, m, sx, sy;
int dist[MAXN][MAXN]; // 距离数组，也兼作visited标记

// 马走日的8个方向
const int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

// 检查坐标(x, y)是否在棋盘内且未被访问
bool isValid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m && dist[x][y] == -1;
}

void bfs() {
    queue<Point> q;
    // 初始化距离数组为-1，表示未访问
    memset(dist, -1, sizeof(dist));

    // 起点处理
    dist[sx][sy] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        int x = current.x;
        int y = current.y;

        // 遍历8个方向
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 如果新位置合法且未被访问
            if (isValid(nx, ny)) {
                // 更新新位置的距离：当前距离 + 1
                dist[nx][ny] = dist[x][y] + 1;
                // 将新位置加入队列，以便后续扩展
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    cin >> n >> m >> sx >> sy;
    bfs();
    
    // 输出结果，使用setw(5)进行格式化对齐
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << left << setw(5) << dist[i][j];
        }
        cout << endl;
    }
    return 0;
}
