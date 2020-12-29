#ifndef _TREE_H
#define _TREE_H
#include<iostream>
#include<stack>
#include<sstream>


/// Cutting the first characters of a string
std::string move(std::string& str, const int step = 1){
    str = str.substr(step);
    return str;
}

template <typename T>
T readData(std::string str){
    std::stringstream read(str);
    int data;
    read>>data;
    return data;
}

/**
The TreeNode structure is the minimum representation of a tree.
The BinaryTree class is a wrapper class which contains all necessary methods to work with the Binary tree abstraction.
*/
template <typename T>
struct BinaryTree{
private:
    struct TreeNode{
        T data;
        TreeNode *leftSubtree;
        TreeNode *rightSubtree;

        TreeNode(const T& data, TreeNode *left = nullptr, TreeNode *right = nullptr):
           data(data), leftSubtree(left), rightSubtree(right){}
    };

    TreeNode *root;

    ///Copying the tree recursively
    static TreeNode* copyNode(const TreeNode *node){
        if(node == nullptr) return nullptr;
        TreeNode *new_node = new TreeNode(node->data);
        new_node->leftSubtree = copyNode(node->leftSubtree);
        new_node->rightSubtree = copyNode(node->rightSubtree);
        return new_node;
    }

    ///Deleting the tree recursively
    static void deleteNode(TreeNode *node){
        if(node == nullptr) return;
        deleteNode(node->leftSubtree);
        deleteNode(node->rightSubtree);
        delete node;
    }

    ///Printing Left-Node-Right
    static void LNR(const TreeNode* node, std::ostream& os){
        if(node == nullptr) return;
        LNR(node->leftSubtree, os);
        os<<node->data<<" ";
        LNR(node->rightSubtree, os);
    }


    /**
     * Reads a lisp representation of a tree
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
    static TreeNode* readLisp(std::string& str, T (*read)(std::string)){
        move(str, str.find('('));  ///(data( -> data(
        if(str[1] == ')') return nullptr;  /// ()
        move(str);
        TreeNode *tree = new TreeNode(read(str));

        tree->leftSubtree = readLisp(str, read);
        move(str, str.find('(') + 1);

        while(str[0]  == ')') move(str);
        tree->rightSubtree = readLisp(str, read);
        return tree;
    }

public:
    BinaryTree(){
        root = nullptr;
    }
    BinaryTree(const T& data){
        root = new TreeNode(data);
    }
    BinaryTree(const BinaryTree<T>& other){
        root = copyNode(other.root);
    }
    BinaryTree<T> operator=(const BinaryTree<T>& other){
        if(this != &other){
            deleteNode(root);
            root = copyNode(other.root);
        }
        return *this;
    }
    ~BinaryTree(){
        deleteNode(root);
        root = nullptr;
    }


    const bool isEmpty() const{
        return root == nullptr;
    }

    /**
    Printing the tree in Left-Node-Right way.
    This method allows passing an outstream object as a parameter and printing the tree in a file.
    */
    void printLNR(std::ostream& os = std::cout){
        LNR(root, os);
        os<<std::endl;
    }

    /**
    Tree iterator
    Can be used to traverse the tree in Left-Node-Right way or in a certain direction.
    */
    class Iterator{
    private:
        //Each element is a pair of the tree node and flag if the node is already tracked
        std::stack<std::pair<TreeNode*, bool> > nodes;

        void add(TreeNode *node, bool traversed = false){
            nodes.push(std::make_pair(node, traversed));
        }

        void remove(){
            nodes.pop();
        }

        T& getData(){
            return nodes.top().first->data;
        }

        ///Moves to the most left node
        void push_left_branch(TreeNode* node){
            if(node == nullptr) return;
            add(node);
            push_left_branch(node->leftSubtree);
        }

    public:
        ///Returns false when the whole tree is traversed
        bool operator++(){
            nodes.pop();
            if(empty())
                return false;
            std::pair<TreeNode*, bool> node = nodes.top();
            remove();

            //if tracked
            if(node.second == true){
                return !empty();
            }
            //if not
            push_left_branch(node.first->rightSubtree);
            add(node.first, true);
            return true;
        }

        ///Returns the data of the node
        T& operator*(){
            return getData();
        }

        ///Moves the iterator to the left child
         bool toLeft(){
            TreeNode* node = nodes.top().first;
            if(node->leftSubtree == nullptr) return false;
            add(node->leftSubtree);
            return true;
        }

        ///Moves the iterator to the right child
        bool toRight(){
            TreeNode* node = nodes.top().first;
            if(node->rightSubtree == nullptr) return false;
            add(node->rightSubtree);
            return true;
        }

        ///Moves the iterator to the parent
        bool back(){
           if(empty()) return false;
           remove();
           return true;
        }

        bool empty() const{
            return nodes.empty();
        }

        friend class BinaryTree;
    };

    ///Adds a left child to a node
    void addLeft(const T& data, BinaryTree<T>::Iterator it){
        TreeNode *node = it.nodes.top().first;
        if(node->leftSubtree == nullptr)
            node->leftSubtree = new TreeNode(data, nullptr, nullptr);
    }

    ///Adds a right child to a node
    void addRight(const T& data, BinaryTree<T>::Iterator it){
        TreeNode *node = it.nodes.top().first;
        if(node->rightSubtree == nullptr)
            node->rightSubtree = new TreeNode(data, nullptr, nullptr);
    }

    ///Iterator to the most left node
    Iterator begin() const{
        Iterator it;
        it.push_left_branch(root);
        return it;
    }

    ///Iterator to the root of the tree
    Iterator treeroot() const{
        Iterator it;
        it.add(root);
        return it;
    }

    static BinaryTree<T> fromLisp(std::string str, T (*read)(std::string) = readData){
        BinaryTree<T> tree;
        TreeNode *root_ = readLisp(str, read);
        tree.root = root_;
        return tree;
    }

};



#endif // _TREE_H
