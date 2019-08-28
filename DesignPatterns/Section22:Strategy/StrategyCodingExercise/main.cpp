/*

Strategy Coding Exercise
Consider the quadratic equation and its cannonical solution:

a * x^2 + bx + c = 0

x = (-b ± sqrt(b^2 - 4ac)) / 2a

The part b^2 - 4ac is called the discriminant. Suppose we want to provide an API with
two different strategies for calculating the discriminant:

1.- In OrdinaryDiscriminantStrategy, if the discriminant is negative, we return it as-is.
    This is OK, since our main API returns std::complex numbers anyway.

2.- Inn RealDiscriminantStrategy, if the discriminant is negative, the return value is NaN
    (not a number). NaN propagates throughout the calculation, so the equation solver gives
    two NaN values.

Please implement both of these strategies as well as the equation solver itself. 
With regards to plus-minus in the formula, please return the + result as the first element
and - as the second.

*/

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cmath>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    // todo
    double calculate_discriminant(double a, double b, double c) {
        return (b*b) - (4 * a * c);
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    // todo
    double calculate_discriminant(double a, double b, double c) {
        auto result = (b*b) - (4 * a * c);

        return result < 0 ? std::nan("") : result;
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;

public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        // todo
        auto discriminantNoSqrt = std::complex<double>{strategy.calculate_discriminant(a, b, c)};
        auto discriminant = sqrt(discriminantNoSqrt);

        auto r1 = complex<double>{(-b + discriminant) / (2 * a)};
        auto r2 = complex<double>{(-b - discriminant) / (2 * a)};

        auto result = tuple<complex<double>, complex<double>>(r1, r2); 
        // I was previously returning the tuple through an initializer list
        // (which I find more elegant), but udemy's compiler kept complaining
        return result;
    }
};

int main()
{
    OrdinaryDiscriminantStrategy ordinaryDiscriminant;
    RealDiscriminantStrategy realDiscriminant;

    QuadraticEquationSolver solver{ordinaryDiscriminant};

    //auto solution = solver.solve(1, 30, 4);
    auto solution = solver.solve(1, 3, 4); // nan
    cout << get<0>(solution) << '\n';
    cout << get<1>(solution) << '\n';

    
    QuadraticEquationSolver solver2{realDiscriminant};
    auto solution2 = solver2.solve(1, 3, 4); // nan
    cout << get<0>(solution2) << '\n';
    cout << get<1>(solution2) << '\n';

    return 0;
}