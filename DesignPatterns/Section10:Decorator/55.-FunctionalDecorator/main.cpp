
#include <iostream>
#include <string>
#include <functional>

using namespace std;

struct Logger
{
    function<void()> func;
    string name;

    Logger(const function<void()> &func, const string& name)
        : func{func}, name{name}
        {}
    
    void operator()() const
    {
        cout << "Entering " << name << '\n';
        func();
        cout << "Exiting " << name << '\n';
    }
};

// Function as a template argument
template <typename Func>
struct Logger2
{
    Func func;
    string name;

    Logger2(const Func &func, const string& name)
        : func{func}, name{name}
        {}
    
    void operator()() const
    {
        cout << "Entering " << name << '\n';
        func();
        cout << "Exiting " << name << '\n';
    }
};

// Using this we can infer the type of Func via the argument
// Taking advantage that our make_logger function has void return type and no arguments
template<typename Func> auto make_logger2(Func func, const string& name)
{
    return Logger2<Func>{func, name};
}

// A more complicated example required variadic templates
double add(double a, double b)
{   
    cout << a << "+" << b << "=" << (a+b) << '\n';
    return a + b;
}

// Partial specialization
template <typename> struct Logger3;
template<typename R, typename... Args>
struct Logger3<R(Args...)>
{
    function<R(Args...)> func;
    string name;

    Logger3(const function<R(Args...)> &func, const string &name)
        : func{func}, name{name} 
        {}
    
    R operator()(Args ...args)
    {
        cout << "Entering " << name << '\n';
        R result = func(args...);
        cout << "Exiting " << name << '\n';
        return result;
    }
};

// Helper function
template<typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const string& name) {
    return Logger3<R(Args...)>(
        function<R(Args...)>(func), name
    );
}

int main()
{   
    auto log = make_logger2([](){cout << "Hello" << endl;}, "HelloFunction");
    log();

    auto logged_add = make_logger3(add, "add");
    auto result = logged_add(2, 3);
    cout << "result = " << result << '\n';
    return 0;
}