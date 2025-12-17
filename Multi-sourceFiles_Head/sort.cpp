/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/Multi-sourceFiles_Head/sort.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   实现学生成绩排序功能
 */

#include "sort.h"
#include "data.h"
#include <algorithm>
#include <ranges>

using std::ranges::sort;

// 实现函数
void computeSort(CourseGrade& cg)
{
    std::ranges::sort(cg, [](auto& g1, auto& g2){
        return g1.total > g2.total;  // 降序排列
    });
}