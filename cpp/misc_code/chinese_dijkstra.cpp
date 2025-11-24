#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
using namespace std;

const double INF = numeric_limits<double>::infinity();

class Graph {
private:
    int n;    // 顶点数
    vector<vector<pair<int,double>>> adj;   // 邻接表：adj[u] 存放所有 (v, weight) 对

public:
    // 原来的 size 构造器，保留也没问题
    Graph(int size): n(size), adj(size){} // 创建一个大小为 size 的 vector，每个元素默认是一个空的 vector<pair<int, double>>

    // 从文件读入的构造函数
    // 文件格式：
    //   N
    //   u v w
    //   u v w
    //   ...
    
    Graph(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cerr << "Cannot open file " << filename << "\n"; // cerr 是 C++ 提供的标准错误输出流（Console ERRor）。和 cout 类似，它也会在终端中输出内容，但用于输出 错误信息。
	                                                         // 优点是：cerr 通常不会被重定向，适合调试和报告问题。
            exit(1);                                         // exit(0) 表示 正常退出；exit(1) 或其他非零值，表示 发生错误，是一种通用的“失败”标志。
        }
        in >> n;            // >> 是 C++ 中的提取运算符（extraction operator），用于从输入流中读取数据
        adj.assign(n, {});  // 创建 n 个空的 vector<pair<int,double>>，{}：含义：是一个“空的东西”，也就是一个默认构造的对象
        int u, v;
        double w;
        while (in >> u >> v >> w) {  // 只要还能从文件中成功依次读取三项数据 u, v, w，就继续执行循环体。也就是不断读取接下来的边：u v w
            // 无向图，存两遍
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }


    int size() const { return n; } 



    // 返回 u 的所有邻居 (v, weight)
    const vector<pair<int,double>>& neighbors(int u) const {
        return adj[u]; // assign已经把 adj[u] 初始化为一个空的 vector<pair<int,double>>，所以可以直接返回
    }



    // Prim 算法，返回 {MST 总权重, MST 边列表}
    // MST 边列表里存的都是 (父节点, 子节点)
    pair<double, vector<pair<int,int>>> mstPrim() const {
        vector<double> key(n, INF);    // 表示将顶点 v 加入 MST 所需的最小边权
        vector<bool>   inMst(n, false);
        vector<int>    parent(n, -1);  // MST 树的父节点

        key[0] = 0;   // 从 0 号点开始
        for (int cnt = 0; cnt < n; ++cnt) { // March thru 所有的nodes
            // 找到当前 outside MST 中，key 最小的顶点 u
            int u = -1;
            double best = INF;
            for (int i = 0; i < n; ++i) {           // 选当前最小的点
                if (!inMst[i] && key[i] < best) {
                    best = key[i];
                    u = i;
                }
            }
            if (u == -1) break;         // 图不连通时跳出
            inMst[u] = true;

            // 用 u 去修改他所有邻边 加入 MST 的权重，因为这个u带来了影响。
            for (auto [v, w] : adj[u]) {
                if (!inMst[v] && w < key[v]) {
                    key[v]    = w;
                    parent[v] = u;
                }
            }
        }



        // 汇总结果
        double totalWeight = 0;
        vector<pair<int,int>> edges;
        for (int v = 1; v < n; ++v) {
            if (parent[v] != -1) {
                edges.emplace_back(parent[v], v); // 是根据容器中元素的类型来推断你传进去的参数应当如何被构造，等价于edges.push_back(std::make_pair(parent[v], v));
                totalWeight += key[v];
            }
        }
        return {totalWeight, edges};
    }
};

int main() {

    Graph g("/Users/dongwenou/Downloads/CPP for C Programmers/Class1_Module4/HW3_data.txt");

    auto [cost, edges] = g.mstPrim();
    cout << "MST total cost = " << cost << "\n";
    cout << "Edges in the MST:\n";
    for (auto [u, v] : edges) {
        cout << u << " - " << v << "\n";
    }
    return 0;
}

// 结构化绑定（Structured Bindings）
// 你希望将这个 pair 的两个成员直接拆成两个变量来用。就可以这么做
// auto [a, b] = some_pair;       // 拆 pair
// auto [x, y, z] = some_tuple;   // 拆 tuple（需要 #include <tuple>）