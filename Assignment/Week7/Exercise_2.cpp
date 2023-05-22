/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

struct Tnode {
    int c;
    double freq;

    Tnode *Left, *Right;

    Tnode(int c, double freq) {
        this->c = c, this->freq = freq;
        Left = Right = NULL;
    }
};

typedef Tnode *node;

struct cmp {
    bool operator () (const node &A, const node &B) {
        if (A == NULL) return false;
        if (B == NULL) return A != NULL;

        return A->freq > B->freq;
    }
};

void Huffman_Tree(node &root, const map<char, double> &freq) {
    priority_queue<node, vector<node>, cmp> PQ;

    for(auto u: freq) PQ.push(new Tnode((int) u.first, u.second));

    while (PQ.size() > 1) {
        node Left = PQ.top(); PQ.pop();
        node Right = PQ.top(); PQ.pop();

        node Top = new Tnode(256, Left->freq + Right->freq);
        Top->Left = Left; Top->Right = Right;
        PQ.push(Top);
    }

    root = PQ.top();
}

string tmp = "";
map<char, string> codes;

void Store_Codes(node root) {
    if (root == NULL) return;
    if (root->Left == root->Right && root->Left == NULL) {
        codes[root->c] = tmp;
        return;
    }

    if (root->Left != NULL) {
        tmp.push_back('0');
        Store_Codes(root->Left);
        tmp.pop_back();
    }

    if (root->Right != NULL) {
        tmp.push_back('1');
        Store_Codes(root->Right);
        tmp.pop_back();
    }
}

string Huffman_Encoding(string s) {
    string ans = "";
    for(char c: s) 
    ans = ans + codes[c];
    return ans;
}

string Huffman_Decoding(node root, string s) {
    node curr = root;
    string ans = "";

    for(char c: s) {
        if (c == '0') curr = curr->Left;
        else curr = curr->Right;

        if (curr->Left == curr->Right && curr->Right == NULL) {
            ans.push_back(curr->c);
            curr = root;
        }
    }

    return ans;
}

int main() {
    map<char, double> freq;

    freq.insert({'A', 0.4});
    freq.insert({'B', 0.1});
    freq.insert({'C', 0.2});
    freq.insert({'_', 0.15});
    freq.insert({'D', 0.15});

    node root; string s;
    Huffman_Tree(root, freq);
    Store_Codes(root);
    cout << "String to encode: "; getline(cin, s);
    cout << "Encoded string: " << Huffman_Encoding(s) << '\n';
    cout << "String to decode: "; getline(cin, s);
    cout << "Decoded string: " << Huffman_Decoding(root, s) << '\n';

    return 0;
}

