/// hhoangcp

#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long

using namespace std;

int n, minC;
string s, best;

bool check() {
    int sz = s.size();
    for(int i = 1; i * 2 <= (int) s.size(); ++i)
    if (s.substr(sz - i, i) == s.substr(sz - 2 * i, i)) return false;
    return true;
}

void Backtracking(int pos, int numC) {
    if (!check()) return;

    if (pos >= n) {
        if (numC < minC) {
            minC = numC;
            best = s;
        }

        return;
    }

    for(char i = 'A'; i <= 'C'; ++i) {
        if (pos > 0 && s.back() == i) continue;
        if (i == 'C' && numC + 1 + (n - pos - 1) / 4 >= minC) continue;

        s.push_back(i);
        Backtracking(pos + 1, numC + (i == 'C'));
        s.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    cin >> n; s = best = ""; minC = n;
    Backtracking(0, 0);
    cout << best;

    return 0;
}
