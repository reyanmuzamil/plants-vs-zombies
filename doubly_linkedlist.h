#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template <typename T>
struct DLLNode {
    T data;
    DLLNode<T>* prev;
    DLLNode<T>* next;
    DLLNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    DLLNode<T>* head;
    DLLNode<T>* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        clear();
    }
    DLLNode<T>* pushBack(const T& val) {
        DLLNode<T>* node = new DLLNode<T>(val);
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        count++;
        return node;
    }
    DLLNode<T>* removeNode(DLLNode<T>* node) {
        if (!node) return nullptr;
        DLLNode<T>* nextNode = node->next;

        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        delete node;
        count--;
        return nextNode;
    }
    // Detaches node without deleting it 
    void detachNode(DLLNode<T>* node) {
        if (!node) return;
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        node->prev = nullptr;
        node->next = nullptr;
        count--;
    }

    void attachBack(DLLNode<T>* node) {
        if (!node) return;
        node->prev = tail;
        node->next = nullptr;
        if (!tail) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
        count++;
    }
    DLLNode<T>* getHead() const { return head; }
    bool isEmpty() const { return head == nullptr; }
    int size() const { return count; }

    void clear() {
        DLLNode<T>* curr = head;
        while (curr) {
            DLLNode<T>* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        head = tail = nullptr;
        count = 0;
    }
};
#endif