/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第11周作业/Multi-sourceFiles_Head/io.cpp
 * @date    2025-11-26
 * @author  GY
 * @brief   实现文件读取和成绩输出功能
 */

#include "io.h"
#include "data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using std::cout;
using std::string;
using std::ifstream;
using std::runtime_error;
using std::istringstream;
using std::invalid_argument;
using std::istream;
using std::getline;
using std::fixed;
using std::setprecision;
using std::setw;
using std::left;

// 实现函数
void read(CourseGrade& cg)
{
    cout << "Reading all student grades (name midterm final homework) from a file... \n";
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
    if(ifs.eof()) cout << "Reading done!\n\n";
}

void print(CourseGrade& cg)
{
    cout << "Course: " << "software construction and implementation" << "\nCredit: " << 5 << "\nStudents: " << cg.size() << "\n";
    cout << "name      total\n";
    for(auto g: cg){
        cout << left << setw(10) << g.name << fixed << setprecision(1) << g.total << "\n";
    }
}

istream& operator>>(istream& is, Grade& g)
{
    cout << "  Reading a student grade... ";
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
            cout << "Done!  " << g.name << "\n";
        }
    }
    if(!is) cout << "Error!\n";

    return is;
}
