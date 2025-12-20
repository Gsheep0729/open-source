/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/course.cppm
 * @date    2025-12-20
 * @author  GY
 * @brief   Partition 'course' of module 'registrar' - defines Course class
 * 
 * The interface and implementation of Course class are logically separated.
 * 
 * Change Log:
 * [v1.1] GY   2025-12-16
 *   * added static data member 'cm_totalCount': counts all Course objects in the system.
 * [v1.2] GY   2025-12-16
 *   * added the implementation of the Course class.
 * [v1.3] GY   2025-12-16
 *   * added Course::info() and Course::roster()
 * [v1.4] GY   2025-12-16
 *   * added Course::removeEnrollment() method
 */

export module registrar:course; // 课程模块分区，定义Course类
import std;

using std::string; using std::vector;

// 课程类，表示一门课程
export class Course
{
public:
    Course(string id, string name); // 构造函数

    bool acceptEnrollment(class Student* student); // 接受学生选课
    void removeEnrollment(class Student* student); // 移除学生选课
    string roster(); // 返回课程花名册字符串
    string info(); // 返回课程信息字符串
    bool hasId(string id); // 检查课程ID是否匹配
private:
    string m_name; // 课程名称
    string m_id; // 课程编号
    short m_credit; // 学分（未使用）
    static int cm_totalCount;  // static data member 课程对象总数

    vector<class Student*> _students; // 选修该课程的学生列表
};

// ----- Partial implementation of class Course -----

int Course::cm_totalCount = 0; // initialize static data memeber

Course::Course(string id, string name)
    : m_name(name)
    , m_id(id)
{
    cm_totalCount++;
}

bool Course::acceptEnrollment(Student *student){
    if(_students.size() < 80){  // 假定某个课程的最大人数为80
        _students.push_back(student);
        std::print("\"{}\" 选课成功！目前选择该课程的人数: {}\n",
              m_name, _students.size());
        return true;
    }
    return false;
}

void Course::removeEnrollment(Student *student){
    // 使用 erase-remove 惯用法从 vector 中删除指定元素
    _students.erase(std::remove(_students.begin(), _students.end(), student), _students.end());
}

string Course::info(){
    return std::format("{}   {}\n", m_id, m_name);
}

bool Course::hasId(string id){
    return id == m_id;
}


