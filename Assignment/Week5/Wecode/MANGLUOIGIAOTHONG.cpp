/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define llong long long

using namespace std;

vector<int> V[100006];
int n, m;
bool visited[100006];

int BFS(int s) {
    visited[s] = true;
    queue<int> Q; Q.push(s);
    int num = 0;

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        ++num;

        for(int v: V[u])
        if (!visited[v]) {
            visited[v] = true;
            Q.push(v);
        }
    }

    return num;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    llong ans = 0;
    int sum = 0;
    for(int s = 1; s <= n; ++s)
    if (!visited[s]) {
        int num = BFS(s);
        ans += 1LL * sum * num;
        sum += num;
    }

    cout << ans;

    return 0;
}
