/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th week/Course_selection_system/student.cpp
 * @date    2025-12-16
 * @author  GY
 * @brief   Student 类的实现文件
 */

module registrar; // 属于 registrar 模块的实现单元
import std;

using std::string;
using std::format;
using std::print;
using std::println;

// ================= Student 类的实现 =================

// 构造函数：初始化学生对象
Student::Student(string id, string name)
    : m_id(id), m_name(name) {}

// 返回学生的基本信息字符串
string Student::info() {
    return format("{} {}\n", m_id, m_name);
}

// 检查学生ID是否匹配
bool Student::hasId(string id) {
    return id == m_id;
}

// 学生发起选课（第25页逻辑）
void Student::enrollsIn(Course* course) {
    // 调用课程的接受方法，如果成功，则添加到自己的课程列表中
    if (course->acceptEnrollment(this)) {
        _courses.push_back(course);
    }
}
