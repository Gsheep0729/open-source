/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/grade/data.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   定义成绩数据结构和中位数计算函数
 */
export module data;

import std;

using std::string;
using std::vector;
using std::domain_error;
using std::floating_point;
using std::integral;


// 定义数据结构
export struct Grade {
    string name;
    double midterm;
    double final;
    vector<double> homeworks;
    double total;
};

export using CourseGrade = vector<Grade>;

// 模板概念和函数声明
export template<typename T>
concept Numeric = integral<T> || floating_point<T>;

export template<Numeric T>
T median(vector<T> vec);

// 实现median函数
template<Numeric T>
T median(vector<T> vec) {
    auto size = vec.size();
    if (size == 0)
        throw domain_error("empty vec.");

    // 注意：ranges::stable_sort 保留 std:: 前缀更清晰
    std::ranges::stable_sort(vec);

    auto mid = size / 2;
    if (size % 2 == 0)
        return (vec[mid] + vec[mid - 1]) / 2;
    else
        return vec[mid];
}

// 显式实例化
template double median(vector<double> vec);
template float median(vector<float> vec);
template int median(vector<int> vec);
