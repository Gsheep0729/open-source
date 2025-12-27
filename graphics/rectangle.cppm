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
