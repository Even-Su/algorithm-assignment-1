#include <iostream>

void preorderTraversal(const int* tree, int n, int i) {
    if (tree == nullptr || i < 0 || i >= n || tree[i] == -1) return;
    std::cout << tree[i] << ' ';
    // 只有孩子下标在范围内才计算 2*i+1/2，兼顾整数运算安全。
    if (n >= 2 && i <= (n - 2) / 2) preorderTraversal(tree, n, 2 * i + 1);
    if (n >= 3 && i <= (n - 3) / 2) preorderTraversal(tree, n, 2 * i + 2);
}

void inorderTraversal(const int* tree, int n, int i) {
    if (tree == nullptr || i < 0 || i >= n || tree[i] == -1) return;
    if (n >= 2 && i <= (n - 2) / 2) inorderTraversal(tree, n, 2 * i + 1);
    std::cout << tree[i] << ' ';
    if (n >= 3 && i <= (n - 3) / 2) inorderTraversal(tree, n, 2 * i + 2);
}

void postorderTraversal(const int* tree, int n, int i) {
    if (tree == nullptr || i < 0 || i >= n || tree[i] == -1) return;
    if (n >= 2 && i <= (n - 2) / 2) postorderTraversal(tree, n, 2 * i + 1);
    if (n >= 3 && i <= (n - 3) / 2) postorderTraversal(tree, n, 2 * i + 2);
    std::cout << tree[i] << ' ';
}

void buildTestTree(int* tree, int n) {
    if (tree == nullptr || n <= 0) return;
    for (int i = 0; i < n; ++i) tree[i] = -1;
    // 示例前 5 个槽位恰好为 1..5，其余为空。
    for (int i = 0; i < n && i < 5; ++i) tree[i] = i + 1;
}

#ifndef ASSIGNMENT_TEST
int main() {
    const int n = 7;
    int tree[n];
    buildTestTree(tree, n);
    std::cout << "前序："; preorderTraversal(tree, n, 0); std::cout << '\n';
    std::cout << "中序："; inorderTraversal(tree, n, 0); std::cout << '\n';
    std::cout << "后序："; postorderTraversal(tree, n, 0); std::cout << '\n';
    return 0;
}
#endif
