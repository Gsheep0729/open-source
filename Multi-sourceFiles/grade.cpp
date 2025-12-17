/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/grade/grade.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   实现学生成绩计算功能
 */

export module calc;

import data;
import std;


using std::print;


// 导出函数声明
export double score(Grade& g);
export void computeScore(CourseGrade& cg);

// 实现函数
double score(Grade& g)
{
    // median 来自 data 模块，无需 std::
    return 0.2 * g.midterm + 0.4 * g.final + 0.4 * median(g.homeworks);
}

void computeScore(CourseGrade& cg)
{
    print("Processing all student grades... \n");
    for(auto& g: cg){
        g.total = score(g);
    }
    print("Processing done!\n\n");
}
