/**
 * @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/第12周作业/multi-module/math.cppm
 * @date    2025-11-28
 * @author  GY
 * @brief   数学工具模块 - 提供通用的数学函数
 */
export module math;  // 声明模块名称

import std;

export {
    // 模板函数：计算中位数
    template<typename T> requires (std::integral<T> || std::floating_point<T>)
    T median(std::vector<T> vec);
}

// 中位数计算实现
// 第四层分解
template<typename T> requires (std::integral<T> || std::floating_point<T>)
T median(std::vector<T> vec)
{
    auto size = vec.size();
    if (size == 0)
        throw std::domain_error("empty vec.");

    std::ranges::stable_sort(vec);

    auto mid = size / 2;
    if (size % 2 == 0)
        return (vec[mid] + vec[mid - 1]) / 2;
    else
        return vec[mid];
}
