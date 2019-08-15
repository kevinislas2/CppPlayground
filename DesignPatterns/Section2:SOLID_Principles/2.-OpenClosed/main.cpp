/*
    Open-Closed principle:

    Systems should be open to extension (for example: by inheritance)
    But close to modification
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product
{
    string name;
    Color color;
    Size size;
};

struct ProductFilter
{

    /*
    Works, but this means that if we need more filters we would need to add code for each filter
    (what if we need to filter by size or by size/color?)
    Lots of duplicated code + we need to recompile
     */
    vector<Product*> by_color(vector<Product*> items, Color color)
    {
        vector<Product*> result;
        for (auto& i : items) {
            if(i->color == color) {
                result.push_back(i);
            }
        }
        return result;
    }
};

/*
Enterprise pattern (Specification):
We define interfaces for a Specification and a Filter
*/

template<typename T> struct Specification
{
    virtual bool is_satisfied(T* item) = 0;

    // Allow concatenation of Specifications through AndSpecification (BREAKS)
    // AndSpecification<T> operator&&(Specification<T>&& other) {
    //     return AndSpecification<T>(*this, other);
    // }
};

//Now we define Specifications

struct ColorSpecification : Specification<Product> // Specialization of template
{
    Color color;

    ColorSpecification(Color color) : color(color) {}

    bool is_satisfied(Product *item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> // Specialization of template
{
    Size size;

    explicit SizeSpecification(const Size size) : size(size) {}

    bool is_satisfied(Product *item) override {
        return item->size == size;
    }
};

// We can combine SizeSpecification and ColorSpecification using a combinator
template <typename T> struct AndSpecification : Specification<T> {
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T> &first,
                    Specification<T> &second) : first(first), second(second) {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};


template<typename T>
struct Filter {
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override {

        vector<Product*> result;
        for (auto& item : items) {
            if(spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

int main() {

    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    vector<Product*> items { &apple, &tree, &house };

    // ProductFilter pf;
    // auto green_things = pf.by_color(items, Color::green);
    // for (auto& item : green_things) {
    //     cout << item->name << " is green\n";
    // }

    BetterFilter bf;
    ColorSpecification greenSpecification(Color::green);

    for(auto& item : bf.filter(items, greenSpecification)) {
        cout << item->name << " is green\n";
    }

    // Find all the green and large using the combiner AndSpecification
    SizeSpecification largeSpecification(Size::large);
    AndSpecification<Product> green_and_large{greenSpecification, largeSpecification};

    for(auto& item : bf.filter(items, green_and_large)) {
        cout << item->name << " is green and large\n";
    }

    // BREAKS
    // // // Use && to concatenate specifications (operator is defined in Specification template)
    // auto spec = greenSpecification && largeSpecification;

    // for(auto& item : bf.filter(items, spec)) {
    //     cout << item->name << " is green and large\n";
    // }
    return 0;
}