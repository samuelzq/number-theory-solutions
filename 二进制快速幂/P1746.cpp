#include <iostream>
#include <queue>
#include <cstring> // 用于memset

using namespace std;

const int MAXN = 1005; // 根据题目n<=1000设置

struct Point {
    int x, y;
};

int n;
int sx, sy, ex, ey;
char g[MAXN][MAXN]; // 存储网格地图
int dist[MAXN][MAXN]; // 距离数组，兼作访问标记

// 四个方向：上、下、左、右
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// 检查坐标(x, y)是否合法
bool isValid(int x, int y) {
    // 1. 是否在边界内
    // 2. 该格子是否可通行（不是障碍物'1'）
    // 3. 是否未被访问过
    return (x >= 1 && x <= n && y >= 1 && y <= n) 
           && g[x][y] != '1' 
           && dist[x][y] == -1;
}

void bfs() {
    queue<Point> q;
    // 初始化距离数组为-1
    memset(dist, -1, sizeof(dist));
    
    // 起点处理
    dist[sx][sy] = 0;
    q.push({sx, sy});
    
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        int x = current.x;
        int y = current.y;
        
        // 如果到达终点，可以选择提前退出，提高效率
        // if (x == ex && y == ey) break;
        
        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (isValid(nx, ny)) {
                // 更新新位置的距离
                dist[nx][ny] = dist[x][y] + 1;
                // 将新位置加入队列
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    cin >> n;
    // 读入网格地图，注意下标从1开始
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> g[i][j];
        }
    }
    cin >> sx >> sy >> ex >> ey;
    
    bfs();
    
    // 输出终点到起点的最短距离
    cout << dist[ex][ey] << endl;
    
    return 0;
}
