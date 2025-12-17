// A program that calculates the scores of all students in a course
// Created: Wei Gong (open-src@qq.com)      2025-11-16
// Version: 1.0      License: AGPLv3
//
// Top-down, stepwise refinement approach
//
// First refactor(main()/read()): Introduced error-handling code.
以下面这段代码的语法为参照，重新完成：
import std;

using std::vector;
using std::string;
using std::istream;
using std::ifstream;
using std::print;
using std::ranges::stable_sort;
using std::runtime_error;
using std::istringstream;
using std::domain_error;
using std::invalid_argument;
using std::exception;

//顶层分解
struct Grade; //类型声明
using CourseGrade = vector<Grade>; //类型别名

extern void read(CourseGrade& cg);
extern void computeSort(CourseGrade& cg);
extern void print(CourseGrade& cg);

// 第1次重构，添加错误处理
int main()
{
    CourseGrade courseGrade;
    try {
        read(courseGrade);
        computeSort(courseGrade);
        print(courseGrade);
    } catch (const exception& e) {
        print("error: {}\n", e.what());
    } catch (...) {
        print("Other error!\n");
    }
    // 打印当前工作目录
    std::print("以下是你的运行路径");
    std::print("当前程序工作目录：{}\n", std::filesystem::current_path().string());

    return 0;
}

struct Grade //类型定义
{
    string name;
    double midterm;
    double final;
    vector<double> homeworks;
    double total; //总成绩，该数据成员可声明，也可不用声明
};

// 第二层分解
// 第1次重构，添加错误检测
extern istream& operator>>(istream& is, Grade& g);
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


//排序函数
extern double score(Grade& g);
void computeSort(CourseGrade& cg)
{
    print("Processing all student grades... \n");
    for(auto& g: cg){
        g.total = score(g);  //假定能够进行score(g)操作
    }
    stable_sort(cg, [](auto& g1, auto& g2){
        return g1.total <= g2.total;
    });
    print("Processing done!\n\n");
}




//打印函数
void print(CourseGrade& cg)
{
    print("Course: {}\nCredit: {}\nStudents: {}\n",
          "software construction and implementation", 5, cg.size());
    print("name      total\n");
    for(auto &g: cg){
        print("{:<10}{:<.1f}\n", g.name, g.total);
    }
}

// 第三层分解
// 第1次重构，添加错误检测
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

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T median(std::vector<T> vec);

double score(Grade& g)
{
    return 0.2 * g.midterm + 0.4 * g.final + 0.4 * median(g.homeworks);
}

// 第四层分解
template<Numeric T>
T median(std::vector<T> vec)
{
    auto size = vec.size();
    if (size == 0)
        throw domain_error("empty vec.");

    stable_sort(vec);

    auto mid = size / 2;
    if (size % 2 == 0)
        return (vec[mid] + vec[mid - 1]) / 2;
    else
        return vec[mid];
}
