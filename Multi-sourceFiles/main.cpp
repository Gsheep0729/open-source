/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/grade/main.cpp
 * @date    2025-11-23
 * @author  GY
 * @brief   主程序文件，整合各模块功能实现完整的成绩处理系统
 */

import data;
import io;
import calc;
import sort;
import std;


using std::print;
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
        print("error: {}\n", e.what());
    } catch (...) {
        print("Other error!\n");
    }

    print("以下是你的运行路径\n");
    print("当前程序工作目录：{}\n", std::filesystem::current_path().string());

    return 0;
}
