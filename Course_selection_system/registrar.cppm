/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/registrar.cppm
 * @date    2025-12-16
 * @author  GY
 * @brief   主模块接口，提供注册管理器(Registrar)类，负责系统的整体业务逻辑
 */

export module registrar;      // 导出主模块
export import :student;       // 导出并导入 student 分区
export import :course;        // 导出并导入 course 分区
import std;

using std::string;
using std::vector;

export class Registrar {
public:
    // 获取单例对象的静态方法
    static Registrar& singleton();

    // 初始化数据（硬编码创建学生和课程）
    void initialize();

    // 业务操作：学生选课
    void studentEnrollsInCourse(string sid, string cid);

    // 业务操作：打印课程花名册
    void courseRoster(string cid);

private:
    // 私有构造函数，防止外部创建对象
    Registrar() = default;

    // 内部辅助函数
    class Student* findStudentById(const string& id);
    class Course* findCourseById(const string& id);

    // 管理所有的实体对象
    vector<class Student*> _students;
    vector<class Course*> _courses;
};
