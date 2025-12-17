/**
 * @file    main.cpp
 * @date    2025-12-04
 * @author  GY
 * @brief   主程序 - 电子钱包管理系统入口
 */
import std;
import data;
import io;
import calc;
import sort;

using std::print;
using std::exception;

int main()
{
    Account myAccount;
    try {
        read(myAccount);
        computeSummary(myAccount);
        computeSort(myAccount);
        print(myAccount);
    } catch (const exception& e) {
        print("error: {}\n", e.what());
    } catch (...) {
        print("Other error!\n");
    }

    // 打印当前路径
    print("以下是你的运行路径\n");
    print("当前程序工作目录：{}\n", std::filesystem::current_path().string());

    return 0;
}
