#include <iostream>
#include <string>

using namespace std;

/*
            A
           / \
          B   C
*/

template<typename T>
struct BinaryTree;

template<typename T>
struct Node
{
    T value = T();
    Node<T>* left{nullptr}, *right{nullptr}, *parent{nullptr};
    BinaryTree<T>* tree{nullptr};

    Node(T value)
        : value{value}
    {}

    Node(T value, Node<T>*left, Node<T>* right)
        : value{value}, left{left}, right{right}
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if(left) left->set_tree(t);
        if(right) right->set_tree(t);
    }

    ~Node()
    {
        if (left) delete left;
        if (right) delete right;
    }
};

//Wrapper to implement an iterator
template<typename T>
struct BinaryTree
{
    Node<T>* root{nullptr};

    BinaryTree(Node<T>* root)
        : root(root), pre_order{*this}
    {
       root->set_tree(this);
    }

    ~BinaryTree() {
        if(root) delete root;
    }

    //Iterator
    template <typename U> 
    struct PreorderIterator
    {
        Node<U>* current;
        PreorderIterator(Node<U>* current)
            : current{current}
        {}

        bool operator!=(const PreorderIterator<U>& other)
        {
            return current != other.current;
        }

        // Not sure this implementation is correct
        // IT IS ACTUALLY INORDER
        PreorderIterator<U>& operator++()
        {
            if (current->right)
            {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                Node<T>* p = current->parent;
                while (p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() {
            return *current;
        }
    }; // PreOrderIterator

    typedef PreorderIterator<T> iterator;

    iterator begin()
    {
        Node<T>* n = root;

        if(n) {
            while (n->left) {
                n = n->left;
            }
        }
        return iterator{n};
    };
    
    iterator end()
    {
        return iterator{nullptr};
    };

    class PreOrderTraversal
    {
        BinaryTree& tree;
    public:
        PreOrderTraversal(BinaryTree& tree)
            : tree{tree}
        {}

        iterator begin() {return tree.begin();}
        iterator end() { return tree.end();}
    } pre_order;
};

int main()
{
    
    BinaryTree<string> family {
        new Node<string>{"me",
            new Node<string>{"mother",
                new Node<string>{"mother's mother"},
                new Node<string>{"mothers' father"}
            },
            new Node<string>{"father"}
        }
    };

    for(auto it = family.begin(); it != family.end(); ++it)
    {
        cout << (*it).value << '\n';
    }

    for(const auto& it : family.pre_order)
    {
        cout << it.value << '\n';
    }



    return 0;
}