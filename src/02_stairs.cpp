#include <iostream>

// 为适配常见的 64 位 long long，本程序只接受 0..91。
// n=92 时结果为 12200160415121876738，超出有符号 64 位范围。
long long climbStairsIter(int n) {
    if (n < 0 || n > 91) return -1;
    if (n <= 1) return 1; // 0 阶：什么也不做，也是一种方案。
    long long prev2 = 1, prev1 = 1;
    for (int i = 2; i <= n; ++i) {
        long long current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

long long stairsMemo(int n, long long* memo) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    memo[n] = stairsMemo(n - 1, memo) + stairsMemo(n - 2, memo);
    return memo[n];
}

long long climbStairsRecur(int n) {
    if (n < 0 || n > 91) return -1;
    long long memo[92];
    for (long long& value : memo) value = -1;
    // 仍然是递归实现；缓存避免反复求同一个子问题。
    return stairsMemo(n, memo);
}

// 教学对照：朴素递归只在小规模输入使用，不在 main 中运行。
long long climbStairsNaive(int n) {
    if (n < 0 || n > 40) return -1;
    if (n <= 1) return 1;
    return climbStairsNaive(n - 1) + climbStairsNaive(n - 2);
}

#ifndef ASSIGNMENT_TEST
int main() {
    int n = 0;
    if (!(std::cin >> n) || n < 0 || n > 40) {
        std::cerr << "请输入 0 到 40 的整数\n";
        return 1;
    }
    const long long iter = climbStairsIter(n);
    const long long recur = climbStairsRecur(n);
    std::cout << "迭代结果：" << iter << '\n';
    std::cout << "递归结果：" << recur << '\n';
    std::cout << "结果是否一致：" << (iter == recur ? "是" : "否") << '\n';
    return 0;
}
#endif
