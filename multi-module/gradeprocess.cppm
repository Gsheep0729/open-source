/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第12周作业/multi-module/gradeprocess.cppm
 * @date    2025-11-28
 * @author  GY
 * @brief   成绩处理模块 - 计算和排序成绩
 */
export module gradeprocess;  // 声明模块名称

import std;
import grade;      // 导入Grade数据结构
import math;       // 导入median函数

using std::print;
using std::ranges::stable_sort;

export {
    // 计算并排序所有学生成绩
    // 第二层分解 - 函数声明
    void computeSort(CourseGrade& cg);

    // 计算单个学生的总成绩
    double score(Grade& g);
}

// 函数实现

void computeSort(CourseGrade& cg)
{
    print("Processing all student grades... \n");
    // 遍历所有学生成绩，计算总成绩
    for(auto& g: cg){
        g.total = score(g);  // 调用score函数计算总成绩并存储在total字段
    }
    // 按总成绩从小到大稳定排序
    stable_sort(cg, [](auto& g1, auto& g2){
        return g1.total <= g2.total;  // 比较两个学生的总成绩
    });
    print("Processing done!\n\n");
}

double score(Grade& g)
{
    // 计算总成绩: 0.2*期中 + 0.4*期末 + 0.4*中位数(平时作业)
    return 0.2 * g.midterm + 0.4 * g.final + 0.4 * median(g.homeworks);
}
