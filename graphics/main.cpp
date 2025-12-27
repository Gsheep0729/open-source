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
