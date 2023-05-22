/// hhoangcp

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>
#define llong long long

using namespace std;
using namespace chrono;

struct TEdge {
    int u, v, w;

    bool operator < (const TEdge &other) const {
        return w < other.w;
    }
};

vector<TEdge> Edges;
vector<int> par;
vector<vector<TEdge>> V;
vector<int> C, heap, pos;
vector<bool> inMST;
int n, m, n_heap;

int Find(int u) {
    if (par[u] < 0) return u;
    return par[u] = Find(par[u]);
}

bool Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return false;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    return true;
}

void Kruskal() {
    auto start = high_resolution_clock::now();

    sort(Edges.begin(), Edges.end());

    llong ans = 0;
    for(TEdge e: Edges)
    if (Union(e.u, e.v)) ans += e.w;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Result (Kruskal) << " << ans << '\n';
    cout << "Time: " << duration.count() << ' ' << "ms\n";
}

void UpdateHeap(int u) {
    if (pos[u] == 0) heap[++n_heap] = u, pos[u] = n_heap;

    int child = pos[u], parent = child / 2;
    while (parent > 0) {
        if (C[heap[parent]] <= C[heap[child]]) break;
        swap(pos[heap[parent]], pos[heap[child]]);

        swap(heap[parent], heap[child]);
        child = parent, parent = child / 2;
    }
}

int PopHeap() {
    int top = heap[1]; pos[top] = 0;
    heap[1] = heap[n_heap--];
    if (n_heap == 0) return top;

    pos[heap[1]] = 1;

    int parent = 1, child = parent * 2;
    while (child <= n_heap) {
        if (child < n_heap && C[heap[child]] > C[heap[child+1]]) ++child;
        if (C[heap[parent]] <= C[heap[child]]) break;

        swap(pos[heap[parent]], pos[heap[child]]);
        swap(heap[parent], heap[child]);
        parent = child, child = parent * 2;
    }

    return top;
}

void Prim() {
    auto start = high_resolution_clock::now();

    C[1] = 0;
    UpdateHeap(1);

    do {
        int u = PopHeap();
        inMST[u] = true;

        for(TEdge e: V[u])
        if (!inMST[e.v] && C[e.v] > e.w) {
            C[e.v] = e.w;
            UpdateHeap(e.v);
        }
    } while (n_heap > 0);

    llong ans = 0;
    for(int u = 1; u <= n; ++u) ans += C[u];

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);


    cout << "Result (Prim) << " << ans << '\n';
    cout << "Time: " << duration.count() << ' ' << "ms\n";
}

void Input(fstream &fi) {
    fi >> n >> m;

    V.assign(n + 1, vector<TEdge>());
    inMST.assign(n + 1, false);
    C.assign(n + 1, (int) 1e9 + 7);
    heap.assign(n + 1, 0);
    pos.assign(n + 1, 0);
    par.assign(n + 1, -1);

    for(int i = 1; i <= m; ++i) {
        int u, v, w; fi >> u >> v >> w;
        Edges.push_back({u, v, w});
        V[u].push_back({u, v, w});
        V[v].push_back({v, u, w});
    }

    fi.close();
}

void Clear() {
    n = m = 0;
    V.clear();
    inMST.clear();
    C.clear();
    heap.clear();
    pos.clear();
    par.clear();
    Edges.clear();
}

int main() {
    fstream fi;
    fi.open("Dense_connected_graph.txt", ios_base::in);
    Input(fi);
    cout << "Dense connected graph: (n = " << n << ", m = " << m << ")\n";
    Kruskal();
    Prim();
    Clear();

    cout << '\n';
    fi.open("Sparse_connected_graph.txt", ios_base::in);
    Input(fi);
    cout << "Sparse connected graph: (n = " << n << ", m = " << m << ")\n";
    Kruskal();
    Prim();
    Clear();

    return 0;
}
