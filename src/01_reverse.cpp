#include <iostream>

void reverseArray(int* arr, int n) {
    // 先检查空数组，避免计算 arr - 1。
    if (arr == nullptr || n <= 1) return;
    int* left = arr;
    int* right = arr + n - 1;
    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        ++left;
        --right;
    }
}

#ifndef ASSIGNMENT_TEST
int main() {
    int n = 0;
    int arr[100];
    if (!(std::cin >> n) || n < 0 || n > 100) {
        std::cerr << "数组长度必须是 0 到 100 的整数\n";
        return 1;
    }
    for (int* p = arr; p < arr + n; ++p) {
        if (!(std::cin >> *p)) {
            std::cerr << "数组元素输入失败\n";
            return 1;
        }
    }
    reverseArray(arr, n);
    for (const int* p = arr; p < arr + n; ++p) {
        if (p != arr) std::cout << ' ';
        std::cout << *p;
    }
    std::cout << '\n';
    return 0;
}
#endif
