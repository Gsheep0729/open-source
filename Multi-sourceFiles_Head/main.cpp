/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/Multi-sourceFiles_Head/main.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   主程序文件，整合各模块功能实现完整的成绩处理系统
 */

#include "data.h"
#include "io.h"
#include "grade.h"
#include "sort.h"
#include <iostream>
#include <exception>

using std::cout;
using std::exception;

int main()
{
    CourseGrade courseGrade;
    try {
        read(courseGrade);
        computeScore(courseGrade);
        computeSort(courseGrade);
        print(courseGrade);
    } catch (const exception& e) {
        cout << "error: " << e.what() << "\n";
    } catch (...) {
        cout << "Other error!\n";
    }

    return 0;
}
