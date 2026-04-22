// src.hpp - Implementation of templated LinkedList, Stack, and Queue
// Only iostream and cstdio are permitted per problem statement.

#include <iostream>
#include <cstdio>

// Templated LinkedList supporting push/pop at both ends, size, copy, print.
// Also declares virtual methods to be overridden by Stack and Queue.
template <typename T>
class LinkedList {
protected:
    struct Node {
        T val;
        Node* prev;
        Node* next;
        Node(const T& v) : val(v), prev(NULL), next(NULL) {}
    };

    Node* head;
    Node* tail;
    int n;

    // Unsafe accessors (assumes non-empty) for derived classes
    const T& frontValueUnsafe() const { return head->val; }
    const T& backValueUnsafe() const { return tail->val; }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = NULL;
        n = 0;
    }

public:
    // Default constructor
    LinkedList() : head(NULL), tail(NULL), n(0) {}

    // Copy constructor (deep copy)
    LinkedList(const LinkedList& other) : head(NULL), tail(NULL), n(0) {
        Node* cur = other.head;
        while (cur) {
            pushBack(cur->val);
            cur = cur->next;
        }
    }

    // Destructor
    virtual ~LinkedList() { clear(); }

    // Insert at front
    void pushFront(const T& val) {
        Node* node = new Node(val);
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
        ++n;
    }

    // Insert at back
    void pushBack(const T& val) {
        Node* node = new Node(val);
        node->prev = tail;
        if (tail) tail->next = node;
        tail = node;
        if (!head) head = node;
        ++n;
    }

    // Remove from front; return removed value or default T() if empty
    T popFront() {
        if (!head) return T();
        Node* node = head;
        T value = node->val;
        head = head->next;
        if (head) head->prev = NULL;
        else tail = NULL;
        delete node;
        --n;
        return value;
    }

    // Remove from back; return removed value or default T() if empty
    T popBack() {
        if (!tail) return T();
        Node* node = tail;
        T value = node->val;
        tail = tail->prev;
        if (tail) tail->next = NULL;
        else head = NULL;
        delete node;
        --n;
        return value;
    }

    // Return size
    int size() const { return n; }

    // Print elements separated by a space and ending with newline
    void print() const {
        Node* cur = head;
        while (cur) {
            std::cout << cur->val << ' ';
            cur = cur->next;
        }
        std::cout << '\n';
    }

    // Virtual interface (will not be called on base in tests per problem)
    virtual const char* name() { return "LinkedList"; }
    virtual T peak() { return T(); }
    virtual T pop() { return T(); }
    virtual void push(T) {}
};

// Stack: LIFO behavior using LinkedList; no new member variables.
template <typename T>
class Stack : public LinkedList<T> {
public:
    virtual const char* name() { return "Stack"; }

    virtual T peak() {
        // Guaranteed non-empty when called
        return this->backValueUnsafe();
    }

    virtual T pop() {
        return this->popBack();
    }

    virtual void push(T val) {
        this->pushBack(val);
    }
};

// Queue: FIFO behavior using LinkedList; no new member variables.
template <typename T>
class Queue : public LinkedList<T> {
public:
    virtual const char* name() { return "Queue"; }

    virtual T peak() {
        // Guaranteed non-empty when called
        return this->frontValueUnsafe();
    }

    virtual T pop() {
        return this->popFront();
    }

    virtual void push(T val) {
        this->pushBack(val);
    }
};

