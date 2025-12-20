// Module registrar, course partition: defines Student class
// File: student.cppm   Version: 1.0      License: AGPLv3
// Created: Wei Gong open-src@qq.com      2025-12-12
//
// Description:
//     The interface and implementation of Student class are logically separated.

// Change Log:
//     [v1.1] Wei Gong open-src@qq.com   2025-12-12
//         * added the implementation of Student class

export module registrar:student; // 学生模块分区，定义Student类
import std;

using std::string; using std::vector;

// 学生类，表示一个学生
export class Student
{
public:
    Student(string id, string name); // 构造函数

    void enrollsIn(class Course* course); // 学生选课
    string schedule(); // 返回学生课表字符串
    string info(); // 返回学生信息字符串
    bool hasId(string id); // 检查学生ID是否匹配

private:
    string m_name; // 学生姓名
    string m_id; // 学号

    vector<class Course*> _courses; // 学生选修的课程列表
};

// ----- Partial implementation of class Student -----

Student::Student(string id, string name)
    : m_name(name)
    , m_id(id)
{}

string Student::info()
{
    return format("{}   {}\n", m_id, m_name);
}

bool Student::hasId(string id)
{
    return id == m_id;
}
