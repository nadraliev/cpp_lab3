//
// Created by andrew on 3/20/18.
//

#ifndef CPP_LAB3_DEQUE_H
#define CPP_LAB3_DEQUE_H

#include <iterator>

template <typename T>
class deque {
private:
    struct node {
        T data;
        node *next;
        node *previous;
    };

    node *head;
    node *tail;
    int size = 0;

public:
    void emplace_back(T _element) {
        node* newNode = new node;
        newNode->data = _element;
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        size++;
    }

    void emplace_from(T);

    void emplace(T, int);

    void assign(T, int);

    void remove(int);

    T front();

    T back();

    T at(int);

    T dequeu_front();

    T dequeu_back();

    class iterator : public std::iterator<
            std::output_iterator_tag,
            T,
            int,
            const T *,
            T> {
        node *current = nullptr;
    public:
        explicit iterator(node *_head) {
            current = _head;
        }

        iterator &operator++() {
            current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(iterator other) const { return current == other.current; }

        bool operator!=(iterator other) const { return !(*this == other); }

        T operator*() const { return current->data; }
    };
    class reverse_iterator : public std::iterator<
            std::output_iterator_tag,
            T,
            int,
            const T *,
            T> {
        node *current = nullptr;
    public:
        explicit reverse_iterator(node *_head) {
            current = _head;
        }

        reverse_iterator &operator++() {
            current = current->previous;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(reverse_iterator other) const { return current == other.current; }

        bool operator!=(reverse_iterator other) const { return !(*this == other); }

        T operator*() const { return current->data; }
    };
    iterator begin() { return iterator(head);}
    iterator end() { return iterator(nullptr);}
    reverse_iterator rbegin() { return reverse_iterator(tail);}
    reverse_iterator rend() { return reverse_iterator(nullptr);}
};

#endif //CPP_LAB3_DEQUE_H
