/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第12周作业/multi-module/gradeio.cppm
 * @date    2025-11-28
 * @author  GY
 * @brief   成绩输入输出模块 - 处理成绩的读取和打印
 */
export module gradeio;  // 声明模块名称

import std;
import grade;  // 导入Grade数据结构

using std::print;
using std::ifstream;
using std::string;
using std::runtime_error;
using std::getline;
using std::istringstream;
using std::invalid_argument;

export {
    // 从文件读取所有学生成绩
    void read(CourseGrade& cg);

    // 打印所有学生成绩
    void print(CourseGrade& cg);

    // 输入流操作符 - 读取单个学生成绩
    std::istream& operator>>(std::istream& is, Grade& g);
}

// 函数实现

void read(CourseGrade& cg)
{
    print("Reading all student grades (name midterm final homework) from a file... \n");
    ifstream ifs("../../coursegrade.dat");
    if(!ifs) throw runtime_error("fail to open file");
    // read and store all the grades
    string line; istringstream iss;
    while(std::getline(ifs, line)){            // std::getline按行读取成功时，返回good的ifs
        iss.str(line);                         // 字符串输入流iss封装字符串line进行流式输入
        Grade g;                               // 假定能够对g进行iss >> g读取操作
        if(iss >> g) cg.push_back(g);          // 读取成绩成功后，添加g到cg中
        else iss.clear();
    }
    if(ifs.eof()) print("Reading done!\n\n");  // 读取完毕则打印
}

void print(CourseGrade& cg)
{
    print("Course: {}\nCredit: {}\nStudents: {}\n",
          "software construction and implementation", 5, cg.size());  // 打印课程信息和统计
    print("name      total\n");
    for(auto &g: cg){                 // 遍历所有学生成绩并打印
        print("{:<10}{:<.1f}\n", g.name, g.total);  // 姓名左对齐，成绩保留1位小数
    }
}

std::istream& operator>>(std::istream& is, Grade& g)
{
    print("  Reading a student grade... ");
    if (is) is >> g.name >> g.midterm >> g.final;          // 读取姓名、期中、期末成绩
    if(!is.eof()&&is.fail())                              // 如果读取失败且不是EOF
        throw invalid_argument("Incorrect name, midterm and final grade.");  // 抛出异常

    if (is){                                               // 如果流状态正常
        for (double h; is >> h;)                           // 循环读取所有作业成绩
            g.homeworks.push_back(h);                      // 添加到homeworks向量

        if(!is.eof() && is.fail())                         // 如果失败且不是EOF
            throw invalid_argument("Incorrect homework grade.");  // 抛出异常

        if(is.eof() && g.homeworks.size() != 0) {          // 如果是EOF且读取到了作业
            is.clear();                                    // 清除EOF标志
            print("Done!  {}\n", g.name);                   // 打印成功信息
        }
    }
    if(!is) print("Error!\n");                            // 如果流状态异常，打印错误

    return is;
}
