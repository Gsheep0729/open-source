/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/Multi-sourceFiles_Head/data.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   定义成绩数据结构和中位数计算函数
 */

#include "data.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <concepts>
#include <algorithm>
#include <ranges>

using std::string;
using std::vector;
using std::domain_error;
using std::floating_point;
using std::integral;

// 实现median函数
template<Numeric T>
T median(vector<T> vec) {
    auto size = vec.size();
    if (size == 0)
        throw domain_error("empty vec.");

    std::ranges::sort(vec);

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