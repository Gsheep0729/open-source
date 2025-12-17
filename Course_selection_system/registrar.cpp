/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th week/Course_selection_system/registrar.cpp
 * @date    2025-12-16
 * @author  GY
 * @brief   Register 类的实现文件（Manager类）
 */

module registrar; // 属于 registrar 模块的实现单元
import std;

using std::string;
using std::format;
using std::print;
using std::println;

// ================= Registrar 类的实现 =================

// 单例模式实现（第25页）
// 返回静态实例的引用，保证全局唯一
Registrar& Registrar::singleton() {
    static Registrar instance;
    return instance;
}

// 初始化数据：创建并加载学生和课程的硬编码数据（第25页）
// 在实际应用中，数据应从数据库或配置文件加载
void Registrar::initialize() {
    // 创建学生列表
    _students.push_back(new Student("S001", "Thomas"));
    _students.push_back(new Student("S002", "Jerry"));
    _students.push_back(new Student("S003", "Baker"));
    _students.push_back(new Student("S004", "Tom"));
    _students.push_back(new Student("S005", "Musk"));

    // 打印学生列表
    println("student list:\n sid student");
    for(auto& s : _students) {
        print("{}", s->info());
    }
    println("");

    // 创建课程
    _courses.push_back(new Course("CS101", "C Programming"));
    _courses.push_back(new Course("CS201", "Data Structure"));
    _courses.push_back(new Course("MATH101", "Advanced Math"));

    // 创建课程列表
    _courses.push_back(new Course("CS101", "C Programming"));
    for(auto& c : _courses) {
        print("{}", c->info());
    }
    println("");
}

// 根据学生ID查找对应的学生对象指针
// @param id: 学生ID
// @return: 找到则返回对应学生指针，否则返回 nullptr
Student* Registrar::findStudentById(const string& id) {
    for (auto& s : _students) {
        if (s->hasId(id)) return s;
    }
    return nullptr;
}

// 根据课程ID查找对应的课程对象指针
// @param id: 课程ID
// @return: 找到则返回对应课程指针，否则返回 nullptr
Course* Registrar::findCourseById(const string& id) {
    for (auto& c : _courses) {
        if (c->hasId(id)) return c;
    }
    return nullptr;
}

// 业务逻辑：处理学生选课
// @param sid: 学生ID
// @param cid: 课程ID
// 流程：先查找学生和课程对象，然后调用学生的选课方法
void Registrar::studentEnrollsInCourse(string sid, string cid) {
    Student* s = findStudentById(sid);
    Course* c = findCourseById(cid);

    if (s && c) {
        s->enrollsIn(c);
    }
}

// 业务逻辑：查看并打印课程花名册（名单）
// @param cid: 课程ID
// 显示选择该课程的所有学生信息
void Registrar::courseRoster(string cid) {
    Course* c = findCourseById(cid);
    if (c) {
        print("{}\n", c->roster());
    }
}
