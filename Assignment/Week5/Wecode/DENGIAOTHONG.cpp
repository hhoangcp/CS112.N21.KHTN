/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define llong long long

using namespace std;

/// 3^9 = 19683
const int MAX = 19683;

int t[9], power[9], num[9], tmp[9];
bool tick[9];
string S[9];

/// V -> 0
/// D -> 1
/// X -> 2

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    for(int i = 0; i < 9; ++i) {
        if (i == 0) power[i] = 1; else power[i] = power[i - 1] * 3;
        cin >> t[i] >> S[i];
    }

    string inp; cin >> inp;

    int ans = 1e9;
    for(int mask = 0; mask < MAX; ++mask) {
        int sum = 0;
        for(int i = 0; i < 9; ++i) {
            if (inp[i] == 'X') tmp[i] = 2;
            if (inp[i] == 'D') tmp[i] = 1;
            if (inp[i] == 'V') tmp[i] = 0;
        }

        for(int i = 0; i < 9; ++i) {
            num[i] = (mask / power[i]) % 3;
            if (!num[i]) continue;

            for(char c: S[i]) (tmp[c - '1'] += num[i]) %= 3;
            sum += t[i] * num[i];
        }

        int val = 0;
        for(int i = 0; i < 9; ++i) val += tmp[i] * power[i];

        if (val == MAX - 1) ans = min(ans, sum);
    }

    if (ans == 1e9) ans = -1;
    cout << ans;

    return 0;
}
