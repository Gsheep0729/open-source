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

