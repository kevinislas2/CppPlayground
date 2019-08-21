#include <string>
#include <iostream>
#include <algorithm>

#include <boost/iterator/iterator_facade.hpp>

using namespace std;

struct Node
{
    string value;
    Node* next{nullptr};

    Node(const string& value)
        : value{value}
    {}

    Node(const string& value, Node* parent)
        : value{value}
    {
        parent->next = this;
    }
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag>
{
    Node* current{nullptr};

    ListIterator() {}

    ListIterator(Node* current)
        : current{current}
    {}

    private:
        friend class boost::iterator_core_access;

        //Convention
        void increment() { current = current->next;}
        bool equal(const ListIterator& other) const
        {
            return other.current == current;
        }

        Node& dereference() const {
            return *current;
        }
};

int main()
{
    Node alpha{"alpha"};
    Node beta{"beta", &alpha};
    Node gamma{"gamma", &beta};

    for_each(ListIterator{&alpha}, ListIterator{}, [](const Node& n){
        cout << n.value << '\n';
    });
    return 0;
}