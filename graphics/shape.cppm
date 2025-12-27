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
