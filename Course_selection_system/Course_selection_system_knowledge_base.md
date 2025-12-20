# 项目: Course_selection_system

## 项目特征总结





---

## File: registrar.cppm
```cppm
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

```

---

## File: main.cpp
```cpp
/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/main.cpp
 * @date    2025-12-20
 * @author  GY
 * @brief   Testing the registrar system with additional features
 */
import registrar;
import std;

int main()
{
    // alias for static function Registrar::singleton
    auto system = &Registrar::singleton;

    system().initialize();

    // Simulate some students enrolls in some courses
    system().studentEnrollsInCourse("S001", "CS101");
    system().studentEnrollsInCourse("S001", "CS201");
    system().studentEnrollsInCourse("S001", "MATH101");

    system().studentEnrollsInCourse("S002", "CS101");
    system().studentEnrollsInCourse("S002", "MATH101");

    system().studentEnrollsInCourse("S003", "CS201");
    system().studentEnrollsInCourse("S003", "MATH101");

    system().studentEnrollsInCourse("S004", "CS101");
    system().studentEnrollsInCourse("S004", "CS201");

    system().studentEnrollsInCourse("S005", "CS201");

    std::println();

    system().courseRoster("CS101");
    system().courseRoster("CS201");
    system().courseRoster("MATH101");

    system().studentSchedule("S001");
    system().studentSchedule("S003");

    // Test course withdrawal
    std::println("=== Testing course withdrawal ===");
    system().studentDropsCourse("S001", "CS101");

    std::println("\n=== After withdrawal ===");
    system().studentSchedule("S001");
    system().courseRoster("CS101");

    return 0;
}

```

---

## File: registrar_knowledge_base.md
```md
# 项目: registrar

## 项目特征总结
* **语言标准**: C++23（全面应用 C++20/23 Modules 模块分区特性）
* **构建系统**: CMake 4.1.1+，启用 C++23 Modules 实验性支持
* **架构模式**: **模块化分区设计 (Module Partition Architecture)**，职责高度分离
  - `registrar` 主模块：业务逻辑协调与单例管理
  - `registrar:student` 模块分区：学生实体及选课行为管理
  - `registrar:course` 模块分区：课程实体及花名册管理
* **核心功能**: 学生信息管理 → 课程信息管理 → 选课注册管理 → 生成课程花名册 → 查看学生课表
* **设计模式**:
  - **单例模式**（`Registrar::singleton()`）：确保注册管理器全局唯一实例
  - **双向关联**（Student ⇄ Course）：通过裸指针建立对象间的弱耦合协作关系
  - **委托模式**：`Course::roster()` 委托学生对象输出自身信息
* **关键技术**:
  - C++23 模块分区（`export module registrar:student`）解决大型模块组织问题
  - 前向声明（`export class Student;`）消除循环依赖
  - 静态数据成员（`Course::cm_totalCount`）跟踪系统状态
  - 动态内存管理（`new Student/Course`）配合原始指针（教学示例）
* **容量控制**: 课程内置80人选课上限，由 `Course::acceptEnrollment()` 实现限流逻辑
* **代码风格**: 
  - 接口与实现严格分离（`.cppm` 接口单元 + `.cpp` 实现单元）
  - 详尽的中文注释，函数职责单一，符合教学最佳实践
  - 使用 `std::format` 实现类型安全的字符串格式化


---

## File: course.cppm
```cppm
// Partition 'course' of module 'registrar' - defines Course class
// File: course.cppm   Version: 1.0      License: AGPLv3
// Created: Wei Gong open-src@qq.com      2025-12-12
//
// Description:
//     The interface and implementation of Course class are logically separated.

// Change Log:
//     [v1.1] Wei Gong open-src@qq.com   2025-12-12
//         * added static data member 'totalCount': counts all Course objects in the system.
//     [v1.2] Wei Gong open-src@qq.com   2025-12-12
//         * added the implementation of the Course class.
//     [v1.3] Wei Gong open-src@qq.com   2025-12-12 18:02:14
//         * added Course::info()

export module registrar:course; // 课程模块分区，定义Course类
import std;

using std::string; using std::vector;

// 课程类，表示一门课程
export class Course
{
public:
    Course(string id, string name); // 构造函数

    bool acceptEnrollment(class Student* student); // 接受学生选课
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
        print("\"{}\" 选课成功！目前选择该课程的人数: {}\n",
              m_name, _students.size());
        return true;
    }
    return false;
}

string Course::info(){
    return format("{}   {}\n", m_id, m_name);
}


bool Course::hasId(string id){
    return id == m_id;
}

```

---

## File: main.cpp
```cpp
// A registrar system demo
// File: main.cpp   Version: 1.0      License: AGPLv3
// Created: Wei Gong open-src@qq.com      2025-12-12
//
// Description:
//     Testing the registrar system

// Change Log:
//     [v1.1] Wei Gong open-src@qq.com   2025-12-12 17:57:41
//         * simulating student course registration, viewing course enrollment lists
//     [v1.2] Wei Gong open-src@qq.com   2025-12-12 18:07:17
//         * simulating view student schedule
import registrar;
import std;

int main()
{
    // alias for static function Registrar::singleton
    auto system = &Registrar::singleton;

    system().initialize();

    // Simulate some students erolls in some courses
    system().studentEnrollsInCourse("S001", "CS101");
    system().studentEnrollsInCourse("S001", "CS201");
    system().studentEnrollsInCourse("S001", "MATH101");

    system().studentEnrollsInCourse("S002", "CS101");
    system().studentEnrollsInCourse("S002", "MATH101");

    system().studentEnrollsInCourse("S003", "CS201");
    system().studentEnrollsInCourse("S003", "MATH101");


    system().studentEnrollsInCourse("S004", "CS101");
    system().studentEnrollsInCourse("S004", "CS201");

    system().studentEnrollsInCourse("S005", "CS201");

    std::println();

    system().courseRoster("CS101");
    system().courseRoster("CS201");
    system().courseRoster("MATH101");

    system().studentSchedule("S001");

    system().studentSchedule("S003");

    return 0;
}

```

---

## File: student.cppm
```cppm
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

```

---

## File: registrar.cppm
```cppm
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

```

---


```

---

## File: student.cppm
```cppm
/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/student.cppm
 * @date    2025-12-20
 * @author  GY
 * @brief   Module registrar, student partition: defines Student class
 * 
 * The interface and implementation of Student class are logically separated.
 * 
 * Change Log:
 * [v1.1] GY   2025-12-16
 *   * added the implementation of Student class
 * [v1.2] GY   2025-12-16
 *   * added Student::drops() method for course withdrawal
 * [v1.3] GY   2025-12-16
 *   * added Student::schedule() method
 */

export module registrar:student; // 学生模块分区，定义Student类
import std;

using std::string; using std::vector;

// 学生类，表示一个学生
export class Student
{
public:
    Student(string id, string name); // 构造函数

    void enrollsIn(class Course* course); // 学生选课
    void drops(class Course* course); // 学生退课
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
    return std::format("{}   {}\n", m_id, m_name);
}

bool Student::hasId(string id)
{
    return id == m_id;
}



```

---

## File: course.cppm
```cppm
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



```

---

