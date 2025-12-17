/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/grade/sort.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   实现学生成绩排序功能
 */

export module sort;

import data;
import std;


using std::ranges::stable_sort;  // ← 直接引入特定函数


// 导出函数声明
export void computeSort(CourseGrade& cg);

// 实现函数
void computeSort(CourseGrade& cg)
{
    stable_sort(cg, [](auto& g1, auto& g2){
        return g1.total > g2.total;  // 降序排列
    });
}
