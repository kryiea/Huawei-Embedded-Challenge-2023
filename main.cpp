#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 10000 + 10;

int N{}; // 节点数量 2 ≤ N
int M{}; // 边的数量 M ≤ 5000
int T{}; // 业务数量 2 ≤ T ≤ 10,000
int P{}; // 单边通道数量 2 ≤ P ≤ 80
int D{}; // 最大衰减距离 2 ≤ D ≤ 1000

//实现邻接表的结构体
struct Edge {
    int to; // 边的终点
    int weight; // 边的权重
    int next; // 下一条边的编号
};
//vector实现邻接表，数量为节点数MAXN
vector<Edge> edges[MAXN];


// 存储业务数据
struct Business {
    int from; // 业务起点
    int to; // 业务终点
};
//vector实现业务数据，数量为业务数T
vector<Business> businesses(T);



void init(); // 初始化输入数据
void dijkstra(); // Dijkstra算法


int main() {
    init(); // 初始化输入数据



    return 0;
}


void init() {
    // 输入数据
    cin >> N >> M >> T >> P >> D;
    // 初始化邻接表
    for (int i = 0; i < M; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges[from].push_back({to, weight, i}); // 去
        edges[to].push_back({from, weight, i}); // 回
    }
    // 初始化业务
    for (int i = 0; i < T; ++i) {
        int from, to;
        cin >> from >> to;
        businesses[i] = {from, to};
    }
}

// Dijkstra算法
void dijkstra() {
    // 依据业务起点和终点，寻找最短路径，并存储在path中
    for (int i = 0; i < T; ++i) {
        int from = businesses[i].from;
        int to = businesses[i].to;
        // 初始化距离数组
        vector<int> dist(N + 1, INT_MAX);
        // 初始化路径数组
        vector<int> path(N + 1, -1);
        // 初始化优先队列
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        // 初始化距离数组
        dist[from] = 0;
        // 初始化路径数组
        path[from] = from;
        // 初始化优先队列
        q.push({0, from});
        // Dijkstra算法
        while (!q.empty()) {
            // 取出队首元素
            auto [d, u] = q.top();
            q.pop();
            // 如果当前距离大于已知距离，则跳过
            if (d > dist[u]) continue;
            // 遍历当前节点的所有邻接点
            for (auto &e : edges[u]) {
                // 如果当前距离加上邻接点的权重大于已知距离，则跳过
                if (dist[u] + e.weight > dist[e.to]) continue;
                // 更新距离数组
                dist[e.to] = dist[u] + e.weight;
                // 更新路径数组
                path[e.to] = u;
                // 将邻接点加入优先队列
                q.push({dist[e.to], e.to});
            }
        }
    }

}
