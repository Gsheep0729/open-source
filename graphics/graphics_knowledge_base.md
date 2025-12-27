# 项目: graphics

## 项目特征总结

* **语言标准**: C++23（深度应用 C++20/23 Modules 模块分区与继承多态特性）
* **构建系统**: 基于 C++ Modules 的构建（需 CMake 4.1.1+ 支持模块分区编译）
* **架构模式**: **模块化分区继承架构 (Module Partition Inheritance Architecture)**
  - `graphics:shape` 模块分区：定义抽象基类 `Shape` 与值类 `Point`
  - `graphics:circle` 模块分区：实现具体图形类 `Circle`
  - `graphics:rectangle` 模块分区：实现具体图形类 `Rectangle`
  - `graphics` 主模块：统一导出所有图形类接口
* **核心功能**: 图形类层次结构设计 → 多态对象创建与管理 → 统一操作接口调用 → 资源生命周期管理
* **设计模式与面向对象特征**:
  - **抽象基类模式**: `Shape` 类包含纯虚函数 `resize()`，定义泛化接口，强制子类实现
  - **模板方法模式**: `Shape::display()` 提供共似接口骨架，子类覆盖实现细节并回调基类行为
  - **多态与动态绑定**: 通过基类指针 `Shape*` 和 `unique_ptr<Shape>` 容器实现运行时多态调用
  - **RAII 资源管理**: 虚析构函数确保通过基类指针删除派生类对象时，子类析构函数能被正确调用
  - **值语义**: `Point` 类作为数据成员，支持拷贝与移动语义，封装二维坐标状态
* **关键技术实现**:
  - **模块分区继承链**: `circle`/`rectangle` 分区显式导入 `shape` 分区，主模块统一导出
  - **虚函数覆盖机制**: 使用 `override` 关键字确保 `resize`、`display` 和析构函数覆盖正确性
  - **抽象操作泛化**: 将子类相似操作提升为基类纯虚接口（`virtual void resize(double) = 0`），强制所有图形支持缩放
  - **共似接口操作**: 基类提供 `display()` 默认实现（打印原点），子类覆盖时通过 `Shape::display()` 调用保留基类行为
  - **智能指针管理**: `main.cpp` 使用 `std::unique_ptr<Shape>` 容器管理多态对象，自动处理资源释放
  - **批量操作函数**: `resizeShapes()` 和 `displayShapes()` 演示针对接口编程，统一处理异质图形集合
* **类职责划分**:
  - `Point`: 值对象，封装二维坐标状态与字符串转换行为（`toString()`）
  - `Shape`: 抽象概念，定义图形通用属性（`m_origin`）、移动行为（`move()`）和可泛化接口（`resize`、`display`）
  - `Circle`: 具体图形，扩展半径属性、直径计算行为（`diameter()`）和圆形特有缩放逻辑
  - `Rectangle`: 具体图形，扩展宽高属性与矩形特有缩放逻辑
* **代码风格**:
  - 接口与实现统一封装在模块接口单元（`.cppm`），教学演示简洁性优先
  - 构造函数使用成员初始化列表，派生类显式调用基类构造器初始化原点
  - 覆盖方法通过 `Shape::display()` 调用保留基类共似行为，再扩展子类特有逻辑
  - 详尽的执行日志打印（`print` 语句）贯穿对象创建、多态调用和析构流程，辅助理解动态绑定与对象生命周期




---

## File: main.cpp
```cpp
/**
* @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/16th/graphics/main.cpp
* @date    2025-12-25
* @author  GY
* @brief   Graphics图形库测试程序入口
*
* 本文件是Graphics图形库的测试程序入口。
* 演示了基于继承和多态的图形处理。
* 使用基类指针容器统一管理不同类型的图形对象，并通过动态绑定调用泛化的 resize 操作。
*
* Change Log:
* [v1.0] GY   2025-12-24
* * 属性和方法的泛化
* [v2.0] GY   2025-12-25
* * 操作 resize 的泛化与动态绑定测试
* * 使用 unique_ptr 管理多态对象
* [v3.0] GY   2025-12-25
* * 增加接口操作 display 的多态调用测试
*/
import graphics;
import std;

using std::print;
using std::vector;
using std::unique_ptr;
using std::make_unique;

// 统一调整所有图形大小的全局函数
// 针对接口编程：只依赖基类 Shape 的接口，而不依赖具体的子类
// 这是泛化设计带来的最大好处：代码复用和解耦
void resizeShapes(vector<unique_ptr<Shape>>& shapes, double ratio) {
    print("\n--- Batch Resizing (Polymorphism Demo) ---\n");
    for (auto& s : shapes) {
        // 多态调用：运行时根据对象的实际类型（动态类型）调用对应的 resize 方法
        // 编译器只知道 s 是 Shape*，但运行时会找到 Circle::resize 或 Rectangle::resize
        s->resize(ratio);
    }
    print("------------------------------------------\n");
}

// [新增 v3.0] 统一显示所有图形信息的全局函数
void displayShapes(const vector<unique_ptr<Shape>>& shapes) {
    print("\n--- Batch Display (Interface Operation Demo) ---\n");
    for (const auto& s : shapes) {
        // 多态调用：
        // 1. 运行时确定 s 的动态类型 (Circle 或 Rectangle)
        // 2. 调用子类的 display()
        // 3. 子类 display() 内部会回调 Shape::display()
        s->display();
    }
    print("------------------------------------------------\n");
}

int main() {
    // 泛化与多态在实际使用中的演示
    Point p(0, 0);

    // 使用容器管理多态对象
    // vector 存储基类指针 unique_ptr<Shape>，可以指向任何派生类对象
    vector<unique_ptr<Shape>> shapes;

    print("Creating objects...\n");
    // 添加 Circle 对象 (unique_ptr<Circle> 隐式转换为 unique_ptr<Shape>)
    shapes.push_back(make_unique<Circle>(p, 10.0));

    // 添加 Rectangle 对象
    shapes.push_back(make_unique<Rectangle>(p, 5.0, 4.0));

    // [新增 v3.0] 测试接口操作：显示初始状态
    displayShapes(shapes);

    // 执行多态操作：批量调整大小
    // resizeShapes 函数完全不知道 Circle 或 Rectangle 的存在，只知道 Shape
    resizeShapes(shapes, 2.0);

    // [新增 v3.0] 再次显示以验证状态变化
    displayShapes(shapes);

    print("\nCleaning up (Virtual Destructor Demo)...\n");
    // vector 析构时会自动调用 unique_ptr 的析构
    // 由于 Shape 拥有虚析构函数，delete 基类指针会正确调用子类的析构函数

    return 0;
}

```

---

## File: graphics.cppm
```cppm
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

```

---

## File: circle.cppm
```cppm
/**
* @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/16th/graphics/circle.cppm
* @date    2025-12-25
* @author  GY
* @brief   圆形类Circle定义
*
* 本模块定义了圆形类Circle，继承自Shape基类。
* 实现了基类的抽象操作resize，支持多态调用。
*
* Change Log:
* [v1.0] GY   2025-12-25
* * 属性和方法的泛化
* [v2.0] GY   2025-12-25
* * 覆盖(override)基类抽象操作 resize
* * 增加析构函数
* [v3.0] GY   2025-12-25
* * 覆盖接口操作 display，并调用基类实现
*/
export module graphics:circle;

import :shape; // 导入基类分区
import std;

using std::print;

// Circle类 - 特化（Specialization）的体现
export class Circle : public Shape {
public:
    Circle(Point origin, double r = 0.0);
    ~Circle() override; // 覆盖析构函数

    // 覆盖操作：resize (注意：增加了 override 关键字)
    // 实现了基类定义的抽象接口，支持通过 Shape* 进行多态调用
    void resize(double ratio) override;

    // [新增 v3.0] 覆盖接口操作
    // 实现了“特定于子类”的行为细节，同时复用基类行为
    void display() override;

    // 特有操作 - 完全的特化，只有圆形才有直径概念
    double diameter();

private:
    double m_radius; // 特有属性 - 圆形的特化属性
};

// ----- Implementation -----

Circle::Circle(Point origin, double r)
    : Shape(origin), m_radius(r)
{}

Circle::~Circle() {
    print("Circle::~Circle() called.\n");
}

// resize方法 - 覆盖方法（动态绑定）
void Circle::resize(double ratio) {
    print(">>> [Polymorphism] Circle::resize() radius = {} before resize. ", m_radius);
    m_radius *= ratio;
    print("radius = {} after resize.\n", m_radius);
}

// [新增 v3.0] 共似接口操作的实现
void Circle::display() {
    print(" ***display a Circle: ");

    // [关键点] 调用公共子行为的基类方法
    Shape::display();

    // 执行子类特有的行为
    print(", radius = {}\n", m_radius);
}

double Circle::diameter() {
    return 2 * m_radius;
}

```

---

## File: rectangle.cppm
```cppm
/**
* @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/16th/graphics/rectangle.cppm
* @date    2025-12-25
* @author  GY
* @brief   矩形类Rectangle定义
*
* 本模块定义了矩形类Rectangle，继承自Shape基类。
* 实现了基类的抽象操作resize，支持多态调用。
*
* Change Log:
* [v1.0] GY   2025-12-25
* * 属性和方法的泛化
* [v2.0] GY   2025-12-25
* * 覆盖(override)基类抽象操作 resize
* * 增加析构函数
* [v3.0] GY   2025-12-25
* * 覆盖接口操作 display，并调用基类实现
*/
export module graphics:rectangle;

import :shape;
import std;

using std::print;

// Rectangle类 - 另一个特化的体现
export class Rectangle : public Shape {
public:
    Rectangle(Point origin, double width, double length);
    ~Rectangle() override; // 覆盖析构函数

    // 覆盖操作：resize
    // 实现了基类定义的抽象接口，支持通过 Shape* 进行多态调用
    void resize(double ratio) override;

    // [新增 v3.0] 覆盖接口操作
    void display() override;

private:
    double m_width;   // 特有属性 - 矩形的宽度
    double m_length;  // 特有属性 - 矩形的长度
};

// ----- Implementation -----

Rectangle::Rectangle(Point origin, double width, double length)
    : Shape(origin), m_width(width), m_length(length)
{}

Rectangle::~Rectangle() {
    print("Rectangle::~Rectangle() called.\n");
}

// resize方法 - 覆盖方法（动态绑定）
void Rectangle::resize(double ratio) {
    print(">>> [Polymorphism] Rectangle::resize() w={}, l={} before. ", m_width, m_length);
    m_width *= ratio;
    m_length *= ratio;
    print("w={}, l={} after.\n", m_width, m_length);
}

// [新增 v3.0] 共似接口操作的实现
void Rectangle::display() {
    print(" ***display a Rectangle: ");

    // [关键点] 调用公共子行为的基类方法
    Shape::display();

    // 执行子类特有的行为
    print(", size = {}x{}\n", m_width, m_length);
}

```

---

## File: shape.cppm
```cppm
/**
* @file    /run/media/root/铠侠D/桌面文件/开源技术群资料/作业/16th/graphics/shape.cppm
* @date    2025-12-25
* @author  GY
* @brief   图形基类Shape和辅助类Point定义
*
* 本模块定义了图形系统的基类Shape和辅助类Point。
* Shape是所有图形类的基类，提供通用的位置属性和移动功能。
* 在v2.0中，Shape成为了抽象基类，泛化了resize操作。
*
* Change Log:
* [v1.0] GY   2025-12-24
* * 属性和方法的泛化
* [v2.0] GY   2025-12-25
* * 操作 resize 的泛化（定义为纯虚函数）
* * 增加虚析构函数支持多态
* [v3.0] GY   2025-12-25
* * 接口操作 display 的泛化（共似接口操作）
*/
export module graphics:shape;

import std;
using std::string;
using std::format;
using std::print;

// 辅助类 Point:表示二维坐标系中的点
export class Point {
public:
    Point(double x = 0.0, double y = 0.0);
    string toString() const;//提供坐标转换和字符串表示功能
private:
    double m_x, m_y;
};

// 基类 Shape - 泛化（Generalization）与多态（Polymorphism）的基础
// 泛化：提取共同特征（属性m_origin和行为move）
// 抽象：定义抽象操作resize，强制子类实现
export class Shape {
public:
    Shape(Point p);

    // 虚析构函数：支持多态对象的正确销毁
    // 确保通过基类指针删除派生类对象时，派生类的析构函数能被调用
    virtual ~Shape();

    // 泛化的方法：被所有子类继承
    // 这是所有图形都具有的共同行为，体现了接口的泛化（静态绑定）
    void move(Point newP);

    // 操作的泛化：抽象操作
    // 这是一个纯虚函数，定义了接口但没有提供基类实现
    // 它强制所有具体的图形子类必须提供resize的具体实现
    // 支持动态绑定（多态调用）
    virtual void resize(double ratio) = 0;

    // [新增 v3.0] 接口操作：动态绑定 (共似的行为)
    // 虚函数（非纯虚），提供默认的“公共子行为”实现
    // 子类覆盖时通常会调用此基类方法
    virtual void display();

private: // 使用 protected 以便子类访问（如果需要），或遵循封装保持 private
    // 泛化的属性：所有图形都具有原点位置
    Point m_origin;
};

// ----- Implementation -----

// Shape构造函数
Shape::Shape(Point p) : m_origin(p) {}

// Shape虚析构函数实现
Shape::~Shape() {
    print("Shape::~Shape() called.\n");
}

// move方法实现 - 普通操作（静态绑定）
void Shape::move(Point newP) {
    print("Shape::move() moving to a new Point: {}\n", newP.toString());
    m_origin = newP;
}

// [新增 v3.0] 接口操作的基类实现：打印所有图形共有的原点信息
void Shape::display() {
    print("origin = {}", m_origin.toString());
}

// ----- Point类实现 -----

Point::Point(double x, double y)
    : m_x(x), m_y(y)
{}

string Point::toString() const {
    // 使用 std::format 函数将坐标值格式化为字符串形式 "(x, y)"
    // format 参数说明：
    // - 第一个参数 "{}" 是格式字符串，{} 是占位符
    // - 后续参数 m_x, m_y 是要插入到占位符位置的值
    // 返回格式为 "(x坐标, y坐标)" 的字符串，例如 "(3.5, 4.2)"
    return format("({}, {})", m_x, m_y);
}

```

---

