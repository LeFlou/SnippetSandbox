#include <iostream>
#include <functional>

struct Interface
{
    virtual void Do() = 0;
};

struct Implem1 : Interface
{
    virtual void Do() override final
    {
        std::cout << "Implem1::Do" << std::endl;
    }
};

struct Implem2 : Interface
{
    virtual void Do() override final
    {
        std::cout << "Implem2::Do" << std::endl;
    }
};

class X
{
public:
    void SetCreator(std::function<Interface*()>& creator)
    {
        this->creator = creator;
    }

    Interface* Create()
    {
        return creator();
    }

private:
    std::function<Interface*()> creator;
};

template <typename T>
Interface* Create()
{
    return new T();
}

int main()
{
    X x;

    x.SetCreator(std::function<Interface*()>(Create<Implem1>));

    x.Create()->Do();

    x.SetCreator(std::function<Interface*()>(Create<Implem2>));

    x.Create()->Do();

    int dummy;
    std::cin >> dummy;
}