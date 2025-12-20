# 项目: Course_selection_system(学生写的)

## 项目特征总结
* **语言标准**: C++23（深度应用 C++20/23 Modules 模块分区与实现单元分离特性）
* **构建系统**: CMake 4.1.1+，启用 C++23 Modules 实验性支持，配置主模块与分区的编译依赖
* **架构模式**: **模块化分区架构 (Module Partition Architecture)**，实现接口与实现的物理分离
  - `registrar` 主模块：业务协调与单例管理（`.cppm` 接口 + `.cpp` 实现）
  - `registrar:student` 模块分区：学生实体建模与选课行为（`.cppm` 接口 + `.cpp` 实现）
  - `registrar:course` 模块分区：课程实体建模与花名册管理（`.cppm` 接口 + `.cpp` 实现）
* **核心功能流程**:
  1. **系统初始化**: `Registrar::initialize()` 硬编码创建学生与课程实体
  2. **选课注册**: `Registrar::studentEnrollsInCourse()` 双向关联学生与课程
  3. **花名册查询**: `Course::roster()` 委托学生对象输出信息，生成课程名单
  4. **课表查询**: `Student::schedule()` 委托课程对象输出信息，生成个人课表
* **设计模式与协作机制**:
  - **单例模式**: `Registrar::singleton()` 静态局部变量保证全局唯一性与线程安全
  - **双向弱关联**: `Student::_courses` 与 `Course::_students` 通过裸指针实现对象间协作
  - **委托模式**: 花名册与课表生成通过对象间消息委托实现，降低耦合
  - **容量控制**: `Course::acceptEnrollment()` 内置80人上限，实现限流逻辑
* **关键技术实现**:
  - **模块分区**: 使用 `export module registrar:student` 语法实现子模块接口导出
  - **前向声明**: `export class Student;` 解决 `Course` 与 `Student` 的循环依赖
  - **静态计数器**: `Course::cm_totalCount` 跟踪系统内课程对象总数
  - **动态内存**: `new` 创建实体对象，教学示例中未释放（演示裸指针使用）
  - **类型安全格式化**: `std::format` 构建字符串，避免传统 `printf` 类型风险
* **代码组织风格**:
  - 接口单元（`.cppm`）仅包含类定义与导出接口
  - 实现单元（`.cpp`）通过 `module registrar;` 归属主模块，完成具体逻辑
  - 详尽的中文注释，函数职责单一，遵循自顶向下设计


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

