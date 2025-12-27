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
