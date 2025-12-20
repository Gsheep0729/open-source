/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/registrar.cppm
 * @date    2025-12-20
 * @author  GY
 * @brief   Module registrar: defines Registrar class
 * 
 * The interface and implementation of Registrar class are logically separated.
 * 
 * Change Log:
 * [v1.1] GY   2025-12-16
 *   * added the singleton interface Registrar::singleton().
 * [v1.2] GY   2025-12-16
 *   * added the implementation of Registrar class
 *   * added the implementation of Student-Course object interactions
 * [v1.3] GY   2025-12-16
 *   * added Registrar::studentSchedule()
 * [v1.4] GY   2025-12-16
 *   * added Registrar::studentDropsCourse() method
 */

export module registrar;
export import :student;
export import :course;

// 主模块，导出Registrar类，并导入student和course分区

import std;
using std::string; using std::vector;

// 注册管理器类，单例模式，管理学生和课程列表
export class Registrar
{
public:
    static Registrar& singleton();  //static function member 获取单例实例
    void studentEnrollsInCourse(string sid, string cid); // 学生选课
    void studentDropsCourse(string sid, string cid); // 学生退课
    void studentSchedule(const string& sid); // 查看学生课表
    void courseRoster(string cid); // 查看课程花名册
    void initialize(); // 初始化系统，添加示例学生和课程

private:
    Registrar();  // Prohibit creating objects directly 私有构造函数，禁止直接创建对象
    class Student* findStudentById(const string& id); // 根据学号查找学生
    class Course* findCourseById(const string& id); // 根据课程号查找课程

    vector<class Course*> _courses; // 课程列表
    vector<class Student*> _students; // 学生列表
};

// ----- The implementaion of class Registrar -----
// 获取单例实例，静态局部变量保证线程安全
Registrar &Registrar::singleton(){
    static Registrar instance;
    return instance;
}

// 初始化系统：添加示例学生和课程
void Registrar::initialize(){
    _students.push_back(new Student("S001", "Thomas"));
    _students.push_back(new Student("S002", "Jerry"));
    _students.push_back(new Student("S003", "Baker"));
    _students.push_back(new Student("S004", "Tom"));
    _students.push_back(new Student("S005", "Musk"));

    _courses.push_back(new Course("CS101", "C Programming"));
    _courses.push_back(new Course("CS201", "Data structure"));
    _courses.push_back(new Course("MATH101", "Advanced Math"));
}

Registrar::Registrar(){}

Student *Registrar::findStudentById(const string &id){
    for (auto& student :_students) {
        if (student->hasId(id))
            return student;
    }
    return nullptr;
}

Course *Registrar::findCourseById(const string &id){
    for (auto& course : _courses) {
        if (course->hasId(id) )
            return course;
    }
    return nullptr;
}

// 学生选课：查找学生和课程，如果存在则调用学生的enrollsIn方法
void Registrar::studentEnrollsInCourse(string sid, string cid){
    Student* student = findStudentById(sid);
    Course* course = findCourseById(cid);

    if (student && course) {
        student->enrollsIn(course);
    }
}

// 学生退课：查找学生和课程，如果存在则调用学生的drops方法
void Registrar::studentDropsCourse(string sid, string cid){
    Student* student = findStudentById(sid);
    Course* course = findCourseById(cid);

    if (student && course) {
        student->drops(course);
    } else {
        std::print("退课操作失败: 无效的学生ID ({}) 或 课程ID ({})\n", sid, cid);
    }
}

// 查看学生课表：查找学生并打印其schedule
void Registrar::studentSchedule(const string &sid)
{
    auto s = findStudentById(sid);
    if (s) {
        std::print("{}\n",s->schedule());
    } else {
        std::print("查询失败: 未找到ID为 {} 的学生。\n", sid);
    }
}

// 查看课程花名册：查找课程并打印其roster
void Registrar::courseRoster(string cid){
    auto c = findCourseById(cid);
    if (c) {
        std::print("{}\n", c->roster());
    }
}

// ----- Implementation of Student-Course object interactions -----

void Student::enrollsIn(Course *course){
    if(course->acceptEnrollment(this))
        _courses.push_back(course);
}

void Student::drops(Course *course){
    if (course) {
        // 1. 从课程名单中移除该学生
        course->removeEnrollment(this);

        // 2. 从自己的选课列表中移除该课程
        auto it = std::remove(_courses.begin(), _courses.end(), course);
        std::size_t removed = std::distance(it, _courses.end());
        _courses.erase(it, _courses.end());

        if (removed > 0) {
            // 使用 c->info() 获取课程信息，去掉末尾可能的换行符以便格式化
            string c_info = course->info();
            if (!c_info.empty() && c_info.back() == '\n') c_info.pop_back();
            std::print("学生 {} 退选课程 \"{}\" 成功。\n", m_name, c_info);
        }
    }
}

string Course::roster(){
    auto rst = std::format("{} selected by the students:\n", m_name);
    for (auto s : _students) {
        rst += s->info(); // 课程对象委托学生对象自己输出相关信息
    }
    return rst;
}

string Student::schedule()
{
    if (_courses.empty()) {
        return std::format("{} 暂未选修任何课程。\n", m_name);
    }

    auto s = std::format("{} 的当前课表:\n", m_name);
    for(auto &c: _courses){
        s += std::format("  - {}", c->info());
    }
    return s;
}
