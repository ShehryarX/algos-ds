
#include <iostream>
#include <string>

#define SPACE_OUTPUT std::cout << "---" << std::endl;

template <typename T>
class BST {
   private:
    struct Node;
    Node *root;
    Node *createNode(T data);
    Node *insert(Node *head, T data);
    Node *remove(Node *head, T data);
    bool has(Node *head, T data);
    void print(Node *head);
    T findMinimumValue(Node *head);
    void reverse(Node *head);  // removes BST property!
    unsigned int size;
    void removeAll(Node *head);

   public:
    BST();
    BST(T data);
    virtual ~BST();
    void insert(T data);
    void remove(T data);
    bool has(T data);
    void print();
    void reverse();  // removes BST property!
    inline unsigned int getSize() { return size; }
};

template <typename T>
struct BST<T>::Node {
    T data;
    Node *left;
    Node *right;
};

template <typename T>
typename BST<T>::Node *BST<T>::createNode(T data) {
    BST<T>::Node *node = new Node();
    node->left = node->right = nullptr;
    node->data = data;
    return node;
}

template <typename T>
T BST<T>::findMinimumValue(Node *head) {
    if (nullptr == head->left) {
        return head->data;
    } else {
        return findMinimumValue(head->left);
    }
}

template <typename T>
BST<T>::BST() : root(nullptr) {}

template <typename T>
BST<T>::BST(T data) : root(createNode(data)) {}

template <typename T>
void BST<T>::removeAll(Node *head) {
    if (nullptr == head) {
        return;
    }

    if (nullptr == head->left && nullptr == head->right) {
        delete head;
    } else {
        removeAll(head->left);
        removeAll(head->right);
    }

    delete head;
}

template <typename T>
BST<T>::~BST() {
    removeAll(root);
}

template <typename T>
typename BST<T>::Node *BST<T>::insert(Node *head, T data) {
    if (nullptr == head) {
        return createNode(data);
    }

    if (data < head->data) {
        head->left = insert(head->left, data);
    } else {
        head->right = insert(head->right, data);
    }

    return head;
}

template <typename T>
typename BST<T>::Node *BST<T>::remove(Node *head, T data) {
    if (nullptr == head) {
        return nullptr;
    }
    if (data < head->data) {
        head->left = remove(head->left, data);
    } else if (data > head->data) {
        head->right = remove(head->right, data);
    } else {
        if (nullptr == head->left && nullptr == head->right) {
            return nullptr;
        } else if (nullptr == head->left) {
            Node *temp = head->right;
            delete head;
            return temp;
        } else if (nullptr == head->right) {
            Node *temp = head->left;
            delete head;
            return temp;
        } else {
            Node *minOnRightSubtree = createNode(findMinimumValue(head));
            head->data = minOnRightSubtree->data;
            head->right = remove(head->right, minOnRightSubtree->data);
        }
    }

    return head;
}

template <typename T>
bool BST<T>::has(Node *head, T data) {
    if (nullptr == head) return false;
    if (head->data == data)
        return true;
    else if (data < head->data) {
        return has(head->left, data);
    } else {
        return has(head->right, data);
    }
}

template <typename T>
void BST<T>::reverse(Node *head) {
    if (nullptr == head) {
        return;
    }

    Node *temp = head->left;
    head->left = head->right;
    head->right = temp;

    reverse(head->left);
    reverse(head->right);
}

template <typename T>
void BST<T>::print(Node *head) {
    if (nullptr == head) return;
    print(head->left);
    std::cout << head->data << std::endl;
    print(head->right);
}

template <typename T>
void BST<T>::insert(T data) {
    size++;
    root = insert(root, data);
}

template <typename T>
void BST<T>::remove(T data) {
    size--;
    root = remove(root, data);
}

template <typename T>
bool BST<T>::has(T data) {
    has(root, data);
}

template <typename T>
void BST<T>::reverse() {
    reverse(root);
}

template <typename T>
void BST<T>::print() {
    print(root);
}

int main() {
    BST<std::string> bst;
    bst.insert("Hello");
    bst.insert("ABC");
    bst.insert("DEF");
    bst.insert("Another word");
    bst.insert("Coolio");
    bst.remove("lmao");
    bst.remove("Coolio");
    bst.print();

    SPACE_OUTPUT

    bst.reverse();
    bst.print();
}
