/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/course.cppm
 * @date    2025-12-16
 * @author  GY
 * @brief   课程模块接口，提供课程(Course)类的定义，管理课程信息和选课学生列表
 */

export module registrar:course; // 定义子模块 course
import std;

using std::string;
using std::vector;

// 前向声明 Student 类
export class Student;

export class Course {
public:
    Course(string id, string name);

    // 接受选课
    bool acceptEnrollment(class Student* student);

    // 获取花名册
    string roster();

    // 获取课程信息
    string info();

    // 检查 ID
    bool hasId(string id);

private:
    string m_id;
    string m_name;
    short m_credit = 0;
    static int cm_totalCount; // 静态数据成员，记录课程总数
    vector<class Student*> _students; // 存储选课学生的指针
};
