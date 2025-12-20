# 项目: compostion_demo

## 项目特征总结
* **语言**: C++23（使用 `export module` 模块语法，`import std;` 导入标准库）
* **构建系统**: 基于 C++ Modules 的构建（推测使用 CMake 4.1.1+ 支持模块特性，符合同类项目配置习惯）
* **架构模式**: 简单模块化设计，单模块 + 主程序结构
  - `a` 模块（`a.cppm`）：定义核心类 `A` 及成员函数，封装数据与资源
  - `main.cpp`：导入 `a` 模块，演示类的使用场景
* **核心功能**: 展示对象的创建、复制赋值、移动赋值等操作，通过 `info()` 方法打印对象地址、数据成员（`m_i`）及资源（`m_r`）的状态，直观呈现值语义与移动语义的差异
* **关键技术**:
  - C++23 Modules 模块系统（模块定义与导入）
  - 移动语义（`std::move`）与复制语义的实践
  - 对象生命周期与资源管理（`vector` 作为资源成员的处理）
* **代码风格**: 类的声明与实现统一在模块接口单元（`.cppm`），注释简洁明了，通过分步打印对象状态辅助理解语义行为
* **设计目的**: 教学演示项目，帮助理解 C++ 中对象的复制、移动操作对数据成员和资源的影响，直观展示值类型的语义特性

---




---

## File: a.cppm
```cppm
export module a;
import std;
using std::print;

// 0 规则实现
export class A
{
public:
    A(int i, int r);

    void info();

    int m_i;  // data
    std::vector<int> m_r;   // resource manager
};


A::A(int i, int r)
    :m_i(i), m_r{r}
{}

void A::info()
{
    print("           object: {:p}\n", static_cast<void*>(this));
    print("               data member: m_i = {}\n", m_i);
    if(!m_r.empty())
        print("               resource:    *ptr = {},  ptr = {}\n", m_r[0], static_cast<void*>(&m_r[0]));
    else
        print("               resource is empty: ptr = nullptr\n");
}

```

---

## File: main.cpp
```cpp
import std;
import a;

using std::print;

int main()
{
    print("# A a(1, -1);\n");
    print("# a.info();\n");
    A a(1, -1);
    a.info();

    print("------------------------------------------------------------\n");
    print("# A b(2, -2);// 参数初始化\n");
    A b(2, -2);
    print("# b.info();\n");
    b.info();

    print("------------------------------------------------------------\n");
    print("# b = std::move(a) // 移动赋值\n");
    b = std::move(a);
    print("# a.info();\n");
    a.info();

    print("# b.info();\n");
    b.info();

    print("------------------------------------------------------------\n");
    print("# b.m_i = 3;\n");
    print("# *(b.p) = -3;\n");
    b.m_i = 3;
    b.m_r[0] = -3;

    print("# a.info();\n");
    a.info();

    print("# b.info();\n");
    b.info();

    print("------------------------------------------------------------\n");
    print("# a = b // 复制赋值\n");
    a = b;
    print("# a.info();\n");
    a.info();

    print("# b.info();\n");
    b.info();

    print("\nreturning from main()......\n");
    return 0;
}


```

---

