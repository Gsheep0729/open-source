/**
* @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/16th/graphics/graphics.cppm
* @date    2025-12-25
* @author  GY
* @brief   Graphics图形库主模块接口
*
* 本模块是Graphics图形库的主模块接口文件。
* 负责导出所有图形相关的子模块，包括shape、circle、rectangle等。
* 提供统一的图形库接口供外部使用。
*
* Change Log:
* [v1.0] GY   2025-12-24
* * 属性和方法的泛化
* [v2.0] GY   2025-12-25
* * 操作 resize 的泛化
*/
export module graphics;

// 模块导出体现了泛化的层次结构：
// 1. :shape - 泛化的基类模块，定义公共接口（包含抽象操作）
// 2. :circle - 特化的子类模块，实现圆形特有功能
// 3. :rectangle - 特化的子类模块，实现矩形特有功能
// 通过统一导出，外部代码可以使用完整的泛化体系
export import :shape;     // 导出基类分区 - 泛化的核心
export import :circle;    // 导出子类分区 - 特化的实现
export import :rectangle; // 导出子类分区 - 特化的实现
