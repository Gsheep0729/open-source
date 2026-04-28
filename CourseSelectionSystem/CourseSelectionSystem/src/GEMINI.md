# 选课管理系统 (Course Selection System)

## 项目概述

**选课管理系统** 是一个旨在管理完整选课流程的 C++ 应用程序。该项目展示了严格的 **4层架构**（表现层、应用逻辑层、领域层、数据管理层），并使用了现代 **C++20/23 模块 (Modules)** 特性。

系统核心业务逻辑设计为与数据库无关，通过在数据管理层采用 **代理模式 (Proxy Pattern)** 来实现。实际的数据库交互由一个独立的静态库 (`lib_db_core`) 处理，该库封装了 PostgreSQL 操作，确保了关注点的清晰分离。

### 关键技术
*   **语言:** C++23 (启用 Modules)
*   **构建系统:** CMake (v4.1.1 实验性特性以支持 modules)
*   **数据库:** PostgreSQL (通过 `libpqxx`)
*   **架构:** 领域驱动设计 (DDD) 原则，4层架构，PIMPL 惯用手法。

### 架构说明

1.  **表现层 (`presentation`)**:
    *   处理用户交互，基于 CLI (命令行界面)。
    *   将操作委托给应用逻辑层。
    *   **严禁包含业务逻辑。**

2.  **应用逻辑层 (`application`)**:
    *   包含控制器 (Controller，例如 `SystemController`)。
    *   协调表现层与领域层/数据管理层之间的数据流转。
    *   **不直接访问数据库。**

3.  **领域层 (`domain`)**:
    *   包含纯业务对象 (`Student`, `Course`, `Teacher`, `TimeSlot`)。
    *   实现核心业务规则（例如：时间冲突检测、容量检查）。
    *   **严格禁止包含 SQL 或数据库依赖。**

4.  **数据管理层 (`infrastructure`)**:
    *   使用代理模式实现持久化 (`StudentProxy`, `CourseProxy`)。
    *   通过 `lib_db_core` 连接数据库。
    *   负责数据库行数据与领域对象之间的转换。

## 构建与运行

### 前置要求
*   **C++ 编译器:** Clang 16+ 或 GCC 14+ (必须支持 C++ Modules 和 C++23)。
*   **CMake:** 版本 3.28+ (项目指定了 4.1.1 实验性特性，请确保兼容性)。
*   **PostgreSQL:** 数据库服务已运行。
*   **libpqxx:** 已安装 PostgreSQL C++ 客户端库。
*   **PkgConfig:** 用于依赖项解析。

### 构建指南

项目使用标准的 CMake 工作流。

```bash
# 1. 创建构建目录
mkdir build
cd build

# 2. 配置项目
# 确保你位于包含顶层 CMakeLists.txt 的根目录下
cmake .. 

# 3. 构建项目
cmake --build .
```

### 数据库设置

运行应用程序之前，请确保你的 PostgreSQL 数据库已使用所需的架构初始化。

1.  创建一个数据库 (例如 `course_system`)。
2.  执行位于 `src/sql/update_schema.sql` 的架构脚本。
    *   必需的表：`users` (用户), `courses` (课程), `enrollments` (选课记录)。

### 运行应用程序

```bash
./src/CourseSelectionSystem/CourseSelectionSystem
```

## 开发规范

### 文件结构与命名
*   **模块:** C++ 模块接口单元使用 `.cppm` 扩展名。
*   **实现:** 模块实现单元或标准源文件使用 `.cpp` 扩展名。
*   **头文件:** `lib_db_core` 的公共接口使用标准的 `.h` 头文件以确保持久稳定性。

### 编码准则
*   **领域层纯净性:** `domain` 命名空间绝不能包含数据库头文件（如 `<pqxx/pqxx>`）或 SQL 字符串。
*   **数据库抽象:** 所有原始 SQL 执行必须发生在 `lib_db_core` 或 `infrastructure` 代理中。
*   **错误处理:**
    *   数据库错误应在 `lib_db_core` 内部捕获，并通过返回码或特定异常报告，而不是抛出原始库异常。
    *   `query` 方法返回 `std::optional<Result>` 以优雅地处理空查询或失败查询。
    *   `NULL` 数据库字段应转换为字符串 `""`。
*   **类型定义:**
    *   `Row` 定义为 `std::vector<std::string>`。
    *   `Result` 定义为 `std::vector<Row>`。

### 文档资源
*   **需求说明:** 详见 `doc/选课系统需求规格说明书.md`。
*   **DB 封装设计:** 详见 `src/PostgreSQL 独立库封装需求文档.md`，了解数据库封装的设计原理。