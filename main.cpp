#include <bits/stdc++.h>
using namespace std;

// Problem: Build a BST from seven node values given in level-order and
// output the cnt-th largest key.
// Input: 8 integers separated by newlines: 7 keys (level order), then cnt.
// Assumptions: All keys are distinct, exactly 7 nodes, proper BST exists.

struct Node {
    int val;
    Node *left{};
    Node *right{};
    explicit Node(int v): val(v) {}
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

    // Reconstruct the BST by assigning children positions in a full binary tree
    // shape based on level-order indices. For index i, children are 2*i+1 and 2*i+2
    // if within bound. This is consistent with the problem statement that records
    // the tree structure in level order.
    vector<Node*> nodes(7, nullptr);
    for (int i = 0; i < 7; ++i) nodes[i] = new Node(level[i]);
    for (int i = 0; i < 7; ++i) {
        int l = 2*i + 1, r = 2*i + 2;
        if (l < 7) nodes[i]->left = nodes[l];
        if (r < 7) nodes[i]->right = nodes[r];
    }
    Node* root = nodes[0];

    // Traverse in reverse in-order (right, node, left) to collect kth largest.
    int seen = 0;
    int answer = -1;
    function<void(Node*)> dfs = [&](Node* cur){
        if (!cur || seen >= cnt) return;
        dfs(cur->right);
        if (seen < cnt) {
            ++seen;
            if (seen == cnt) {
                answer = cur->val;
                return;
            }
        }
        dfs(cur->left);
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

