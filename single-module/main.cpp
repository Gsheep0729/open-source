/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第12周作业/single-module/main.cpp
 * @date    2025-11-28
 * @author  GY
 * @brief   单模块版本
 */
import std;  // 导入标准库
import student; // 导入学生成绩处理模块

using std::print;

// 第1次重构，添加错误处理
int main()
{
    CourseGrade courseGrade;
    try {
        read(courseGrade);
        computeSort(courseGrade);
        print(courseGrade);
    } catch (const std::exception& e) {
        print("error: {}\n", e.what());
    } catch (...) {
        print("Other error!\n");
    }

    return 0;
}
