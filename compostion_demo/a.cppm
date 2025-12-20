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
