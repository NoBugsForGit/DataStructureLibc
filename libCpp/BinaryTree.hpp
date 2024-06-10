#include <iostream>
#include <queue>
#include <stack>

// 模板类定义
template <typename T>
class BinaryTree
{
public:
    T val;             // 节点值
    BinaryTree *left;  // 左子节点指针
    BinaryTree *right; // 右子节点指针

    // 默认构造函数
    BinaryTree()
    {
        this->val = -1;
        left = nullptr;
        right = nullptr;
    }

    // 带参数的构造函数
    BinaryTree(T val) : val(val), left(nullptr), right(nullptr) {}

    // 析构函数，递归删除所有节点
    ~BinaryTree()
    {
        delete left;
        delete right;
    }

    // 按层次遍历输出
    void printLevelOrder()
    {
        if (this == nullptr)
            return; // 如果树为空，直接返回

        std::queue<BinaryTree *> queue;
        queue.push(this); // 将根节点加入队列

        while (!queue.empty())
        {
            BinaryTree *current = queue.front(); // 取出队列前端的节点
            queue.pop();

            std::cout << current->val << " "; // 打印当前节点的值

            if (current->left != nullptr)
            {
                queue.push(current->left); // 如果左子节点存在，将其加入队列
            }
            if (current->right != nullptr)
            {
                queue.push(current->right); // 如果右子节点存在，将其加入队列
            }
        }
        std::cout << std::endl;
    }

    // 前序遍历
    void printPreOrder()
    {
        if (this == nullptr)
            return;
        std::cout << this->val << " ";
        if (this->left != nullptr)
            this->left->printPreOrder();
        if (this->right != nullptr)
            this->right->printPreOrder();
    }

    // 中序遍历
    void printInOrder()
    {
        if (this == nullptr)
            return;
        if (this->left != nullptr)
            this->left->printInOrder();
        std::cout << this->val << " ";
        if (this->right != nullptr)
            this->right->printInOrder();
    }

    // 后序遍历
    void printPostOrder()
    {
        if (this == nullptr)
            return;
        if (this->left != nullptr)
            this->left->printPostOrder();
        if (this->right != nullptr)
            this->right->printPostOrder();
        std::cout << this->val << " ";
    }

    // 返回前序遍历序列（非递归）
    std::vector<BinaryTree *> getPreOrder()
    {
        std::vector<BinaryTree *> nodes;
        if (this == nullptr)
            return nodes;

        std::stack<BinaryTree *> stack;
        stack.push(this);

        while (!stack.empty())
        {
            BinaryTree *current = stack.top();
            stack.pop();
            nodes.push_back(current);

            if (current->right != nullptr)
            {
                stack.push(current->right);
            }
            if (current->left != nullptr)
            {
                stack.push(current->left);
            }
        }
        return nodes;
    }

    // 返回中序遍历序列（非递归）
    std::vector<BinaryTree *> getInOrder()
    {
        std::vector<BinaryTree *> nodes;
        if (this == nullptr)
            return nodes;

        std::stack<BinaryTree *> stack;
        BinaryTree *current = this;

        while (current != nullptr || !stack.empty())
        {
            while (current != nullptr)
            {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();
            nodes.push_back(current);
            current = current->right;
        }
        return nodes;
    }

    // 返回后序遍历序列（非递归）
    std::vector<BinaryTree *> getPostOrder()
    {
        std::vector<BinaryTree *> nodes;
        if (this == nullptr)
            return nodes;

        std::stack<BinaryTree *> stack1, stack2;
        stack1.push(this);

        while (!stack1.empty())
        {
            BinaryTree *current = stack1.top();
            stack1.pop();
            stack2.push(current);

            if (current->left != nullptr)
            {
                stack1.push(current->left);
            }
            if (current->right != nullptr)
            {
                stack1.push(current->right);
            }
        }

        while (!stack2.empty())
        {
            nodes.push_back(stack2.top());
            stack2.pop();
        }
        return nodes;
    }

    // 返回层次遍历序列
    std::vector<BinaryTree *> getLevelOrder()
    {
        std::vector<BinaryTree *> nodes;
        if (this == nullptr)
            return nodes;

        std::queue<BinaryTree *> queue;
        queue.push(this);

        while (!queue.empty())
        {
            BinaryTree *current = queue.front();
            queue.pop();
            nodes.push_back(current);

            if (current->left != nullptr)
            {
                queue.push(current->left);
            }
            if (current->right != nullptr)
            {
                queue.push(current->right);
            }
        }
        return nodes;
    }

    // 判断两棵树是否相同
    bool isSame(BinaryTree *b1, BinaryTree *b2)
    {
        if (!b1 && !b2)
            return true;
        if (!b1 || !b2)
            return false;
        return (b1->val == b2->val) && isSame(b1->left, b2->left) && isSame(b1->right, b2->right);
    }

    // 重载
    BinaryTree *operator==(BinaryTree *a, BinaryTree *b)
    {
        return isSame(a, b);
    }
};