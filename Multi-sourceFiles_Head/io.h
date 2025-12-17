#pragma once
/**
 * @file    io.h
 * @date    2025-11-26
 * @author  GY
 * @brief   实现文件读取和成绩输出功能
 */

#include "data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// 函数声明
void read(CourseGrade& cg);
void print(CourseGrade& cg);
std::istream& operator>>(std::istream& is, Grade& g);

