/**
 * @file    data.h
 * @date    2025-11-26
 * @author  GY
 * @brief   定义成绩数据结构和中位数计算函数
 */

#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <stdexcept>
#include <concepts>
#include <algorithm>
#include <ranges>

// 声明数据结构
struct Grade {
    std::string name;
    double midterm;
    double final;
    std::vector<double> homeworks;
    double total;
};

using CourseGrade = std::vector<Grade>;

// 模板概念和函数声明
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T median(std::vector<T> vec);

#endif // DATA_H