/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/student.cppm
 * @date    2025-12-16
 * @author  GY
 * @brief   学生模块接口，提供学生(Student)类的定义，管理学生信息和所选课程列表
 */

export module registrar:student; // 定义子模块 student
import std;

using std::string;
using std::vector;

// 前向声明 Course 类，因为 vector<Course*> 需要它
export class Course;

export class Student {
public:
    Student(string id, string name);

    // 选课操作
    void enrollsIn(class Course* course);

    // 获取信息
    string info();

    // 检查 ID
    bool hasId(string id);

private:
    string m_id;
    string m_name;
    vector<class Course*> _courses; // 存储所选课程的指针
};
