#include <bits/stdc++.h>
using namespace std;

// Problem: Build a BST from seven node values given in level-order and
// output the cnt-th largest key.
// Input: 8 integers separated by newlines: 7 keys (level order), then cnt.
// Assumptions: All keys are distinct, exactly 7 nodes, proper BST exists.

struct Node {
    int val = 0;
    int left = -1;
    int right = -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> a;
    a.reserve(8);
    long long x;
    for (int i = 0; i < 8; ++i) {
        if (!(cin >> x)) return 0; // graceful exit on bad input
        a.push_back(x);
    }
    // First 7 are level-order nodes, last is cnt
    vector<int> level(7);
    for (int i = 0; i < 7; ++i) level[i] = static_cast<int>(a[i]);
    int cnt = static_cast<int>(a[7]);

    // Reconstruct the BST shape using indices: for i, children are 2*i+1 and 2*i+2
    array<Node,7> nodes;
    for (int i = 0; i < 7; ++i) nodes[i].val = level[i];
    for (int i = 0; i < 7; ++i) {
        int l = 2*i + 1, r = 2*i + 2;
        if (l < 7) nodes[i].left = l;
        if (r < 7) nodes[i].right = r;
    }
    int root = 0;

    // Traverse in reverse in-order (right, node, left) to collect kth largest.
    int seen = 0;
    int answer = -1;
    function<void(int)> dfs = [&](int idx){
        if (idx < 0 || seen >= cnt) return;
        dfs(nodes[idx].right);
        if (seen < cnt) {
            ++seen;
            if (seen == cnt) {
                answer = nodes[idx].val;
                return;
            }
        }
        dfs(nodes[idx].left);
    };
    dfs(root);

    if (answer == -1) {
        // Fallback: if cnt is invalid, nothing found. Problem likely ensures valid cnt.
        // Still, print nothing or 0? According to statement, just output an integer.
        // We'll print 0 to be safe, but this path should not occur with valid inputs.
        cout << 0;
    } else {
        cout << answer;
    }
    cout << '\n';

    return 0;
}
