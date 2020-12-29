#ifndef _ORDERED_TREE_H
#define _ORDERED_TREE_H
#include<iostream>

template <typename T>
class OrderedTree{
private:
    struct TreeNode{
        T data;
        TreeNode *leftSubtree;
        TreeNode *rightSubtree;
        TreeNode(const T& data, TreeNode *left = nullptr, TreeNode *right = nullptr):
           data(data), leftSubtree(left), rightSubtree(right){}
    };

    TreeNode *root;


    static TreeNode* copyNode(TreeNode *node){
        if(node == nullptr) return nullptr;
        TreeNode *left = copyNode(node->leftSubtree);
        TreeNode *right = copyNode(node->rightSubtree);
        return new TreeNode(node->data, left, right);
    }

    static void deleteNode(TreeNode *node){
        if(node == nullptr) return;
        deleteNode(node->leftSubtree);
        deleteNode(node->rightSubtree);
        delete node;
    }

    static void addNode(const T& data, TreeNode*& node){
        if(node == nullptr)
            node = new TreeNode(data);
        else if(data <= node->data)
            addNode(data, node->leftSubtree);
        else addNode(data, node->rightSubtree);
    }

    static void printNode(const TreeNode* node, std::ostream& os){
        if(node == nullptr) return;
        printNode(node->leftSubtree, os);
        os<<node->data<<" ";
        printNode(node->rightSubtree, os);
    }
public:
    OrderedTree(){
        root = nullptr;
    }
    OrderedTree(const T& data){
        root = new TreeNode(data);
    }
    OrderedTree(const OrderedTree<T>& other){
        root = copyNode(other.root);
    }
    OrderedTree<T> operator=(const OrderedTree<T>& other){
        if(this != &other){
            deleteNode(root);
            root = copyNode(other.root);
        }
        return *this;
    }
    ~OrderedTree(){
        deleteNode(root);
        root = nullptr;
    }


    const bool isEmpty() const{
        return root == nullptr;
    }

    void add(const T& data){
        addNode(data, root);
    }
    void print(std::ostream& os = std::cout){
        printNode(root, os);
        os<<std::endl;
    }

};


#endif // _ORDERED_TREE_H
