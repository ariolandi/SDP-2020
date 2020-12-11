#ifndef _TREE_H
#define _TREE_H
#include<iostream>

/**
 * Helping functions for reading a tree from string
 */
namespace Helpers{
    /// Converting a string to int
    int fromStr(std::string str){
        int x = 0, i = 0;
        while(i < str.size() && str[i] >= '0' && str[i] <= '9'){
            x = x*10 + str[i++] - '0';   /// x = x*10 + (str[i] - '0')
        }
        return x;
    }

    /// Cutting the first characters of a string
    std::string move(std::string& str, const int step = 1){
        str = str.substr(step);
        return str;
    }
}

namespace StructTree{
    /**
     * TreeNode struct
     * Every tree node has a data, left and right subtree
     * This is the minimal representation of a tree
     */
    template <class T>
    struct TreeNode{
        T data;
        TreeNode<T> *leftSubtree;
        TreeNode<T> *rightSubtree;

        TreeNode(const T& data_, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr):
            data(data_), leftSubtree(left), rightSubtree(right){}

        /// Deleting the tree recursively
        ~TreeNode(){
            if(leftSubtree) delete leftSubtree;
            if(rightSubtree) delete rightSubtree;
        }

        /// Adds a left subtree
        void addLeft(TreeNode<T> *tree){
            if(leftSubtree == nullptr) leftSubtree = tree;
        }

        ///We have to deleteWe have to delete Adds a right subtree
        void addRight(TreeNode<T> *tree){
            if(rightSubtree == nullptr) rightSubtree = tree;
        }

        /// Checks if the node is a leaf
        bool isLeaf()const {
            return leftSubtree == nullptr && rightSubtree == nullptr;
        }
    };

    /// Prints a tree: Left-Node-Right
    template <class T>
    void printLNR(TreeNode<T> *tree){
        if(tree == nullptr) return ;
        printLNR(tree->leftSubtree);
        std::cout<<tree->data<<" ";
        printLNR(tree->rightSubtree);
    }

    /// Prints a tree: Left-Right-Node
    template <class T>
    void printLRN(TreeNode<T> *tree){
        if(tree == nullptr) return ;
        printLRN(tree->leftSubtree);
        printLRN(tree->rightSubtree);
        std::cout<<tree->data<<" ";
    }

    /**
     * Reads a lisp representation of a int tree
     * empty_tree := ()
     * tree := (<root> left_subtree right_subtree) | empty_tree
     * left_subtree := tree
     * right_subtree := tree
     * Example: (5(4()())(7(2()(3()())(4()())))
     *           5
     *          / \
     *         4   7
     *            / \
     *           2   4
     *            \
     *             3
     */
    TreeNode<int>* readLisp(std::string& str){
        if(str[1] == ')') return nullptr;  /// ()
        Helpers::move(str);
        TreeNode<int> *tree = new TreeNode<int>(Helpers::fromStr(str));

        Helpers::move(str, str.find('('));  ///(data( -> data(
        tree->addLeft(readLisp(str));  ///(fjfh( | hfhhf)() )

        Helpers::move(str, str.find('(') + 1);
        while(str[0]  == ')') Helpers::move(str);

        tree->addRight(readLisp(str));
        return tree;
    }

    /**
     * Reads a subsequence representation of a int tree
     * An empty tree is marked by default symbol
     * Example: 5 4 -1 -1 7 2 -1 3 -1 -1 4 -1 -1
     *           5
     *          / \
     *         4   7
     *            / \
     *           2   4
     *            \
     *             3
     */
    TreeNode<int>* readTree(std::istream &is = std::cin, int defaultNode = -1){
        int root;
        is>>root;
        if(root == defaultNode) return nullptr;
        TreeNode<int> *tree = new TreeNode<int>(root);
        tree->leftSubtree = readTree(is, defaultNode);
        tree->rightSubtree = readTree(is, defaultNode);
        return tree;
    }
}


#endif // _TREE_H
