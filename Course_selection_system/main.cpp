/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/14th/Course_selection_system/main.cpp
 * @date    2025-12-15
 * @author  GY
 * @brief   主程序入口，演示学生选课系统的完整流程：初始化数据、模拟选课、查看结果
 */
// main.cpp
import registrar;
import std;

int main() {
    // 1. 初始化系统（加载数据）
    Registrar::singleton().initialize();

    // 为了方便调用，可以使用引用或指针别名（参考第26页）
    // auto& system = Registrar::singleton();
    // 或者直接调用如下：

    // 2. 模拟选课过程
    Registrar::singleton().studentEnrollsInCourse("S001", "CS101");
    Registrar::singleton().studentEnrollsInCourse("S001", "CS201");
    Registrar::singleton().studentEnrollsInCourse("S001", "MATH101");

    Registrar::singleton().studentEnrollsInCourse("S002", "CS101");
    Registrar::singleton().studentEnrollsInCourse("S002", "MATH101");

    Registrar::singleton().studentEnrollsInCourse("S003", "CS201");
    Registrar::singleton().studentEnrollsInCourse("S003", "MATH101");

    Registrar::singleton().studentEnrollsInCourse("S004", "CS101");
    Registrar::singleton().studentEnrollsInCourse("S004", "CS201");

    Registrar::singleton().studentEnrollsInCourse("S005", "CS201");

    std::println(); // 空行

    // 3. 查看选课结果（花名册）
    Registrar::singleton().courseRoster("CS101");
    Registrar::singleton().courseRoster("CS201");
    Registrar::singleton().courseRoster("MATH101");

    return 0;
}
