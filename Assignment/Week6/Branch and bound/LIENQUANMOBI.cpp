/// hhoangcp

#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long

using namespace std;

struct Point {
    int x, y;
    bool operator < (const Point &other) {
        if (x + y != other.x + other.y) return x + y < other.x + other.y;
        return abs(x - y) < abs(other.x - other.y);
    }
};

int dx[8] = {1, 1, 1, -1, -1, -1, 0, 0};
int dy[8] = {-1, 1, 0, -1, 1, 0, -1, 1};

vector<Point> P;
int a[206][206], ans[206][206], m, n;

bool Backtracking(int pos) {
    if (pos >= (int) P.size()) {
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j <= n; ++j) cout << ans[i][j] << ' ';
            cout << '\n';
        }

        return true;
    }

    int x = P[pos].x, y = P[pos].y;
    for(int c = 0; c < 2; ++c) {
        ans[x][y] = c;

        bool ok = true;
        for(int i = 0; i < 8; ++i) {
            int u = x + dx[i];
            int v = y + dy[i];
            if (1 <= u && u <= m && 1 <= v && v <= n) ok &= a[u][v] >= ans[x][y];
        }

        if (!ok) continue;

        for(int i = 0; i < 8; ++i) {
            int u = x + dx[i];
            int v = y + dy[i];
            if (1 <= u && u <= m && 1 <= v && v <= n) a[u][v] -= ans[x][y];
        }

        ok = true;
        if (x > 1 && y > 1) ok &= a[x - 1][y - 1] == 0;
        if (x == m && y > 1) ok &= a[x][y - 1] == 0;
        if (y == n && x > 1) ok &= a[x - 1][y] == 0;
        if (x == m && y == n) ok &= a[x][y] == 0;

        if (ok) {
            if (Backtracking(pos + 1)) return true;
        }

        for(int i = 0; i < 8; ++i) {
            int u = x + dx[i];
            int v = y + dy[i];
            if (1 <= u && u <= m && 1 <= v && v <= n) a[u][v] += ans[x][y];
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> m >> n;
    for(int i = 1; i <= m; ++i)
    for(int j = 1; j <= n; ++j) {
        cin >> a[i][j];
        P.push_back({i, j});
    }

    sort(P.begin(), P.end());
    Backtracking(0);

    return 0;
}
