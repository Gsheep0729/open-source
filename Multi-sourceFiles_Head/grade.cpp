/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/Multi-sourceFiles_Head/grade.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   实现学生成绩计算功能
 */

#include "grade.h"
#include "data.h"
#include <iostream>

using std::cout;

// 实现函数
double score(Grade& g)
{
    // median 来自 data 模块，无需 std::
    return 0.2 * g.midterm + 0.4 * g.final + 0.4 * median(g.homeworks);
}

void computeScore(CourseGrade& cg)
{
    cout << "Processing all student grades... \n";
    for(auto& g: cg){
        g.total = score(g);
    }
    cout << "Processing done!\n\n";
}