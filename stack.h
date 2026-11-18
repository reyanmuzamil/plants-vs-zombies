#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val, Node* nxt = nullptr) : data(val), next(nxt) {}
    };
    Node* topNode;
    int count;

public:
    Stack() : topNode(nullptr), count(0) {}

    ~Stack() {
        clear();
    }

    void push(const T& val) {
        topNode = new Node(val, topNode);
        count++;
    }

    bool pop(T& outVal) {
        if (!topNode) return false;
        Node* temp = topNode;
        outVal = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return true;
    }

    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }

    void clear() {
        while (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        count = 0;
    }
};

#endif