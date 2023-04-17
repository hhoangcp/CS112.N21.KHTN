/// hhoangcp

#include <iostream>
#define ll long long

using namespace std;

int n, m, a[1006];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    for(int i = 1; i < n; ++i)
    for(int j = 1; j <= n - i; ++j)
    if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);

    for(int len = 1; len <= (a[n] - a[1] + 1) / 2; ++len) {
        int num = 0, last = -1e9;

        for(int i = 1; i <= n; ++i)
        if (last + len < a[i] || num == 0) {
            ++num;
            last = a[i] + len;
        }

        if (num <= m) {
            cout << len;
            return 0;
        }
    }

    cout << "????";

    return 0;
}
