/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第12周作业/multi-module/main.cpp
 * @date    2025-11-28
 * @author  GY
 * @brief   多模块版本 - 使用多个模块实现成绩管理系统
 */

import std;            // 导入标准库
import grade;          // 导入成绩数据结构模块
import gradeio;        // 导入成绩输入输出模块
import gradeprocess;   // 导入成绩处理模块

using std::print;

// 第1次重构，添加错误处理
int main()
{
    CourseGrade courseGrade;  // 创建成绩容器
    try {
        // 读取成绩数据
        read(courseGrade);
        // 处理并排序成绩
        computeSort(courseGrade);
        // 打印排序后的成绩
        print(courseGrade);
    } catch (const std::exception& e) {
        // 捕获标准异常并打印错误信息
        print("error: {}\n", e.what());
    } catch (...) {
        // 捕获未知异常
        print("Other error!\n");
    }

    return 0;  // 程序成功结束
}
