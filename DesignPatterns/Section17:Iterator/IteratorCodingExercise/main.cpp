/*
Iterator Coding Exercise

Given the following definition of a Node<T>, please implement preorder traversal that returns a sequence of Ts.
*/

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Node
{
    T value;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right) {
      left->parent = right->parent = this;
    }

    // traverse the node and its children preorder
    // and put all the results into `result`
    void preorder_traversal(vector<Node<T>*>& result)
    {
        // todo
        
        vector<Node*> nodeTraversal{this};

        while(!nodeTraversal.empty()) {
            Node* node = nodeTraversal.back();
            nodeTraversal.pop_back();

            result.push_back(node);

            if(node->right) {
                nodeTraversal.push_back(node->right);
            }
            if(node->left) {
                nodeTraversal.push_back(node->left);
            }
        }
    }
};

int main()
{
    return 0;
}