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
private:
    node *_at(int _index) {
        if (_index < 0 && _index >= size) {
            //TODO throw exception
        }
        node *current = head;
        for (int i = 0; i < _index; i++)
            current = current->next;
        return current;
    }


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

    void emplace_front(T _element) {
        node *newNode = new node;
        newNode->data = _element;
        if (size == 0) {
            head = newNode;
            tail = newNode;
        } else {
            head->previous = newNode;
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void emplace(T _element, int _position) {
        if (_position == 0) {
            emplace_front(_element);
        } else if (_position == size) {
            emplace_back(_element);
        } else if (_position > size || _position < 0) {
            //TODO throw exception
        } else {
            node *newNode = new node;
            newNode->data = _element;
            node *previous = _at(_position - 1);
            previous->next->previous = newNode;
            previous->next = newNode;
        }
        size++;
    }

    void assign(T _element, int _position) {
        _at(_position)->data = _element;
    }

    void remove(int _position) {
        if (_position < 0 || _position >= size) {
            //TODO throw exception
        }
        if (_position == 0) {
            node *temp = head->next;
            delete head;
            temp->previous = nullptr;
            head = temp;
        } else if (_position == size - 1) {
            node *temp = tail->previous;
            delete tail;
            temp->next = nullptr;
            tail = temp;
        } else {
            node *previous = _at(_position - 1);
            node *next = previous->next->next;
            delete previous->next;
            previous->next = next;
            next->previous = previous;
        }
    }

    T front() {
        if (head == nullptr) {
            //TODO throw exception
        }
        return head->data;
    }

    T back() {
        if (tail == nullptr) {
            //TODO throw exception
        }
        return tail->data;
    }

    T at(int _index) {
        return _at(_index)->data;
    }

    T dequeu_front() {
        T data = front();
        remove(0);
        return data;
    }

    T dequeu_back() {
        T data = back();
        remove(size - 1);
        return data;
    }

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
