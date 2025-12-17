/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th week/Course_selection_system/course.cpp
 * @date    2025-12-16
 * @author  GY
 * @brief   Course 类的实现文件
 */

module registrar; // 属于 registrar 模块的实现单元
import std;

using std::string;
using std::format;
using std::print;
using std::println;

// ================= Course 类的实现 =================

// 初始化静态成员
int Course::cm_totalCount = 0;

// 构造函数：初始化课程对象
Course::Course(string id, string name)
    : m_id(id), m_name(name) {
    cm_totalCount++;
}

// 返回课程的基本信息字符串
string Course::info() {
    return format("{} {}\n", m_id, m_name);
}

// 检查课程ID是否匹配
bool Course::hasId(string id) {
    return id == m_id;
}

// 课程接受学生选课（第24页逻辑）
bool Course::acceptEnrollment(Student* student) {
    if (_students.size() < 80) { // 假设最大容量80
        _students.push_back(student);
        print("\"{}\"选课成功! 目前选择该课程的人数: {}\n", m_name, _students.size());
        return true;
    }
    return false;
}

// 打印花名册（第25页逻辑）
string Course::roster() {
    string rst = format("{} selected by the students:\n", m_name);
    for (auto s : _students) {
        rst += s->info(); // 委托学生对象输出自己的信息
    }
    return rst;
}
