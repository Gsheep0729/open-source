// Module registrar: defines Registrar class
// File: registrar.cppm   Version: 1.0      License: AGPLv3
// Created: Wei Gong open-src@qq.com      2025-12-12
//
// Description:
//     The interface and implementation of Register class are logically separated.

// Change Log:
//     [v1.1] Wei Gong open-src@qq.com   2025-12-12
//         * added the singleton interface Registrar::singleton().
//     [v1.2] Wei Gong open-src@qq.com   2025-12-12
//         * added the implementation of Registrar class
//         * added the implementation of Student-Course object interactions
//     [v1.3] Wei Gong open-src@qq.com   2025-12-12 18:04:07
//         * added Registar::studentSchedule()
//         * added the implementation of Student::schedule

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

// 学生选课：查找学生和课程，如果存在则调用学生的enrollsIn方法
void Registrar::studentEnrollsInCourse(string sid, string cid){
    Student* student = findStudentById(sid);
    Course* course = findCourseById(cid);

    if (student && course) {
        student->enrollsIn(course);
    }
}

// 查看学生课表：查找学生并打印其schedule
void Registrar::studentSchedule(const string &sid)
{
    auto s = findStudentById(sid);
    print("{}\n",s->schedule());
}

// 查看课程花名册：查找课程并打印其roster
void Registrar::courseRoster(string cid){
    auto c = findCourseById(cid);
    print("{}\n", c->roster());
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

// ----- Implementation of Student-Course object interactions -----

void Student::enrollsIn(Course *course){
    if(course->acceptEnrollment(this))
        _courses.push_back(course);
}

string Course::roster(){
    auto rst = format("{} selected by the students:\n", m_name);
    for (auto s : _students) {
        rst += s->info(); // 课程对象委托学生对象自己输出相关信息
    }
    return rst;
}

string Student::schedule()
{
    auto s = format("{}'s schedule:\n", m_name);
    for(auto &c: _courses){
        s += c->info();
    }
    return s;
}
