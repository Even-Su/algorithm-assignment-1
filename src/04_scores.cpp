#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

constexpr int MAX_STUDENTS = 100;

// 按完整 token 检查，拒绝 80abc、3.5 和超过 int 范围的输入。
bool readInteger(int& value) {
    std::string token;
    if (!(std::cin >> token)) return false;
    std::istringstream parser(token);
    char extra;
    return (parser >> value) && !(parser >> extra);
}

bool validScore(int score) { return score >= 0 && score <= 100; }

void initScores(int* scores, int n) {
    if (scores == nullptr || n <= 0) return;
    for (int i = 0; i < n; ++i) scores[i] = -1;
}

void inputScores(int* scores, int n) {
    if (scores == nullptr || n <= 0) return;
    for (int i = 0; i < n;) {
        std::cout << "请输入下标 " << i << " 的成绩（0~100）：";
        int value = 0;
        if (!readInteger(value)) {
            if (std::cin.eof() || std::cin.bad()) {
                std::cout << "\n输入结束，剩余成绩保留为未录入\n";
                return;
            }
            std::cout << "请输入整数\n";
            continue;
        }
        if (!validScore(value)) {
            std::cout << "成绩必须在 0 到 100 之间\n";
            continue;
        }
        scores[i++] = value;
    }
}

double calcAverage(const int* scores, int n) {
    if (scores == nullptr || n <= 0) return 0.0;
    long long sum = 0;
    int entered = 0;
    for (int i = 0; i < n; ++i) {
        if (validScore(scores[i])) { sum += scores[i]; ++entered; }
    }
    // 只统计有效成绩；无数据时返回约定值 0，展示时另作说明。
    return entered == 0 ? 0.0 : static_cast<double>(sum) / entered;
}

int safeGet(const int* scores, int n, int index) {
    if (index < 0 || index >= n) {
        std::cout << "下标越界\n";
        return -1;
    }
    if (scores == nullptr || !validScore(scores[index])) return -1;
    return scores[index];
}

void countGrades(const int* scores, int n, int* counts) {
    if (counts == nullptr) return;
    for (int i = 0; i < 5; ++i) counts[i] = 0;
    if (scores == nullptr || n <= 0) return;
    for (int i = 0; i < n; ++i) {
        int s = scores[i];
        if (!validScore(s)) continue;
        if (s >= 90) ++counts[0];
        else if (s >= 80) ++counts[1];
        else if (s >= 70) ++counts[2];
        else if (s >= 60) ++counts[3];
        else ++counts[4];
    }
}

void findMinMax(const int* scores, int n, int* max, int* min) {
    if (max == nullptr || min == nullptr) return;
    *max = *min = -1;
    if (scores == nullptr || n <= 0) return;
    for (int i = 0; i < n; ++i) {
        if (!validScore(scores[i])) continue;
        if (*max == -1 || scores[i] > *max) *max = scores[i];
        if (*min == -1 || scores[i] < *min) *min = scores[i];
    }
}

void printResults(const int* scores, int n, double avg,
                  const int* counts, int max, int min) {
    std::cout << "\n成绩列表：\n";
    if (scores != nullptr) {
        for (int i = 0; i < n; ++i) {
            std::cout << '[' << i << "] ";
            if (validScore(scores[i])) std::cout << scores[i];
            else std::cout << "未录入";
            std::cout << '\n';
        }
    }
    if (max == -1) std::cout << "暂无有效成绩，平均分和最高/最低分无数据\n";
    else {
        std::cout << std::fixed << std::setprecision(2) << "平均分：" << avg << '\n';
        std::cout << "最高分：" << max << "，最低分：" << min << '\n';
    }
    const char* labels[5] = {"90~100", "80~89", "70~79", "60~69", "0~59"};
    if (counts != nullptr) {
        for (int i = 0; i < 5; ++i)
            std::cout << labels[i] << " 分：" << counts[i] << " 人\n";
    }
}

#ifndef ASSIGNMENT_TEST
int main() {
    int scores[MAX_STUDENTS];
    initScores(scores, MAX_STUDENTS);
    int n = 0;
    std::cout << "请输入学生人数（0~100）：";
    if (!readInteger(n) || n < 0 || n > MAX_STUDENTS) {
        std::cerr << "学生人数无效\n";
        return 1;
    }
    inputScores(scores, n);
    int counts[5] = {0};
    int max = -1, min = -1;
    double avg = calcAverage(scores, n);
    findMinMax(scores, n, &max, &min);
    countGrades(scores, n, counts);
    int testIndex = 0;
    std::cout << "请输入要查询的下标：";
    if (readInteger(testIndex)) {
        int queried = safeGet(scores, n, testIndex);
        if (queried == -1) std::cout << "查询失败\n";
        else std::cout << "下标 " << testIndex << " 的成绩是：" << queried << '\n';
    } else std::cout << "查询输入无效或已结束，跳过查询\n";
    printResults(scores, n, avg, counts, max, min);
    return 0;
}
#endif
