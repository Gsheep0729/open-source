/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第12周作业/multi-module/grade.cppm
 * @date    2025-11-28
 * @author  GY
 * @brief   成绩数据结构模块 - 定义成绩相关的数据类型
 */
export module grade;  // 声明模块名称

import std;

export {
    // Grade结构体 - 单个学生的成绩信息
    struct Grade {
        std::string name;                    // 学生姓名
        double midterm;                      // 期中成绩
        double final;                        // 期末成绩
        std::vector<double> homeworks;       // 平时作业成绩（可以取中位数代表平时成绩，后面也可以取平均值）
        double total;                        // 总成绩(动态计算)
    };

    // CourseGrade类型别名 - 整个课程的成绩列表

    using CourseGrade = std::vector<Grade>;
}
