/**
 * @file    io.cppm
 * @date    2025-12-04
 * @author  GY
 * @brief   IO模块 - 处理文件读取和屏幕输出
 */
export module io;

import std;
import data;

using std::print;
using std::string;
using std::ifstream;
using std::runtime_error;
using std::istringstream;
using std::invalid_argument;
using std::istream;
using std::getline;

export {
    // 读取账户信息
    void read(Account& account);
    // 打印账户信息
    void print(Account& account);
    // 输入流重载
    std::istream& operator>>(std::istream& is, MonthlyStatement& ms);
}

// 函数实现
void read(Account& account)
{
    print("Reading an ewallet account from a file... \n");
    // 确保路径正确，参照你的 gradeio.cppm 写法 [cite: 21]
    ifstream ifs("../../ewallet.dat");
    if(!ifs) throw runtime_error("fail to open file");

    string line;
    // 1. 读取头信息
    if(getline(ifs, line)) {
        istringstream iss(line);
        if(!(iss >> account.name >> account.gender >> account.age >> account.currentBalance)) {
             throw invalid_argument("Invalid account header format");
        }
    } else {
        throw runtime_error("File is empty");
    }

    // 2. 读取交易记录
    istringstream iss;
    while(getline(ifs, line)){
        if (line.empty()) continue;
        iss.clear();
        iss.str(line);

        MonthlyStatement ms;
        if(iss >> ms) account.monthlyStatements.push_back(ms);
    }
    if(ifs.eof()) print("Reading done!\n\n");
}

void print(Account& account)
{
    // 参照 gradeio.cppm 的格式化输出 [cite: 27, 29]
    print("Ewallet Account: {}  {}   Age:{}   CurrentBalance: {:.2f}\n",
          account.name, account.gender, account.age, account.currentBalance);
    print("Account Currency:CNY        Calender Year 2025\n");
    print("Monthly Transactions:\n");

    for (const auto& ms : account.monthlyStatements) {
        print("  {} netBalance:{:.2f}\n", ms.month, ms.summary.netBalance);

        print("         transactions:");
        for (auto t : ms.transactions) {
            print(" {:.2f}", t);
        }
        print("\n");

        print("         {} incomes: {:.2f}\n", ms.summary.incomeCount, ms.summary.totalIncome);
        print("         {} pays: {:.2f}\n", ms.summary.payCount, ms.summary.totalPay);
    }
}

std::istream& operator>>(std::istream& is, MonthlyStatement& ms)
{
    if (is >> ms.month) {
        CNY val;
        while (is >> val) {
            ms.transactions.push_back(val);
        }
        if (!is.bad()) is.clear();
    }
    return is;
}
