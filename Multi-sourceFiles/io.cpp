/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/grade/io.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   实现文件读取和成绩输出功能
 */

export module io;

import data;
import std;


using std::print;
using std::string;
using std::ifstream;
using std::runtime_error;
using std::istringstream;
using std::invalid_argument;
using std::istream;
using std::getline;


// 导出函数声明
export void read(CourseGrade& cg);
export void print(CourseGrade& cg);
export istream& operator>>(istream& is, Grade& g);

// 实现函数
void read(CourseGrade& cg)
{
    print("Reading all student grades (name midterm final homework) from a file... \n");
    ifstream ifs("../../coursegrade.dat");
    if(!ifs) throw runtime_error("fail to open file");

    string line;
    istringstream iss;
    while(getline(ifs, line)){
        iss.str(line);
        Grade g;
        if(iss >> g) cg.push_back(g);
        else iss.clear();
    }
    if(ifs.eof()) print("Reading done!\n\n");
}

void print(CourseGrade& cg)
{
    print("Course: {}\nCredit: {}\nStudents: {}\n",
          "software construction and implementation", 5, cg.size());
    print("name      total\n");
    for(auto &g: cg){
        print("{:<10}{:<.1f}\n", g.name, g.total);
    }
}

istream& operator>>(istream& is, Grade& g)
{
    print("  Reading a student grade... ");
    if (is) is >> g.name >> g.midterm >> g.final;
    if(!is.eof()&&is.fail())
        throw invalid_argument("Incorrect name, midterm and final grade.");

    if (is){
        for (double h; is >> h;)
            g.homeworks.push_back(h);

        if(!is.eof() && is.fail())
            throw invalid_argument("Incorrect homework grade.");

        if(is.eof() && g.homeworks.size() != 0) {
            is.clear();
            print("Done!  {}\n", g.name);
        }
    }
    if(!is) print("Error!\n");

    return is;
}
