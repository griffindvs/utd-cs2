/*
 * Created by Griffin Davis on 11/29/2019.
 * CS2337-002 D. Vogel
 *
 * stack.h
 * This file implements a basic linked list stack for a given data type.
*/

#ifndef STACK_H_
#define STACK_H_

#include <cstddef>
#include <cassert>
#include <iostream>

template <class Type>
class stack;

template <class Type>
class stackEntry {
    friend class stack<Type>;
private:
    Type dataValue;
    stackEntry<Type>* pNext;
protected:
    stackEntry(const Type &newData, stackEntry<Type>* newNext = nullptr)
        : dataValue(newData), pNext(newNext) {};
    virtual ~stackEntry();
    virtual void next(stackEntry<Type>* pNext);
    virtual stackEntry<Type>* next();
    virtual Type& data();
    virtual const Type& data() const;
};

template <class Type>
stackEntry<Type>::~stackEntry() {
    delete pNext;
}

template <class Type>
void stackEntry<Type>::next(stackEntry<Type>* pNext) {
    this->pNext = pNext;
}

template<class Type>
stackEntry<Type> *stackEntry<Type>::next() {
    return pNext;
}

template <class Type>
Type& stackEntry<Type>::data() {
    return dataValue;
}

template <class Type>
const Type& stackEntry<Type>::data() const {
    return dataValue;
}

template <class Type>
class stack {
private:
    stackEntry<Type>* pTop;
    std::size_t count;

public:
    stack();
    stack(const stack &other);
    const stack& operator=(const stack &rhs);
    virtual ~stack();
    stackEntry<Type>* getPTop() const;
    Type& top();
    const Type& top() const;
    bool empty() const;
    std::size_t size() const;
    void push(const Type &value);
    void pop();
    void debug() const;
    void debug(std::ostream &out) const;
    void print() const;
    void clear();
};

template <class Type>
stack<Type>::stack() {
    pTop = nullptr;
    count = 0;
}


template <class Type>
stack<Type>::stack(const stack &other) {
    // Build temporary stack to hold reversed version
    stack<Type>* tempStack = new stack<Type>();
    stackEntry<Type>* cur = other.getPTop();
    while(cur) {
        tempStack->push(cur->data());
        cur = cur->next();
    }

    // Copy from temporary stack to this
    pTop = nullptr;
    cur = tempStack->getPTop();
    while(cur) {
        push(cur->data());
        cur = cur->next();
    }
}

template <class Type>
const stack<Type>& stack<Type>::operator=(const stack &rhs) {
    if (this != &rhs) { // Don't self assign
        clear();

        // Build temporary stack to hold reversed version
        stack<Type>* tempStack = new stack<Type>();
        stackEntry<Type>* cur = rhs.getPTop();
        while(cur) {
            tempStack->push(cur->data());
            cur = cur->next();
        }

        // Copy from temporary stack to this
        pTop = nullptr;
        cur = tempStack->getPTop();
        while(cur) {
            push(cur->data());
            cur = cur->next();
        }
    }

    return *this;
}

template <class Type>
stack<Type>::~stack() {
    clear();
}

template<class Type>
stackEntry<Type>* stack<Type>::getPTop() const {
    return pTop;
}

template <class Type>
Type& stack<Type>::top() {
    return pTop->data();
}

template <class Type>
const Type& stack<Type>::top() const {
    return pTop->data();
}

template <class Type>
bool stack<Type>::empty() const {
    return count == 0;
}

template <class Type>
std::size_t stack<Type>::size() const {
    return count;
}

template <class Type>
void stack<Type>::push(const Type &value) {
    stackEntry<Type>* newNode = new stackEntry<Type>(value);
    newNode->next(pTop);
    pTop = newNode;
    count++;
}

template <class Type>
void stack<Type>::pop() {
    if (pTop != nullptr) {
        stackEntry<Type>* temp = pTop;
        pTop = pTop->next();
        temp->next(nullptr);
        delete temp;
        count--;
    }
}

template <class Type>
void stack<Type>::debug() const {
	debug(std::cout);
}

template <class Type>
void stack<Type>::debug(std::ostream &out) const {
		out << "Number of items in stack: " << count << std::endl;
		out << "Top of stack is entry @" << pTop << std::endl;

		stackEntry<Type> *pNext = pTop;

		while (pNext != nullptr) {
			out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
			pNext = pNext->next();
		}
}

template <class Type>
void stack<Type>::print() const {
    stackEntry<Type>* cur = pTop;
    std::cout << cur->data() << std::endl;
    cur = cur->next();

    while (cur != nullptr) {
        std::cout << cur->data() << std::endl;
        cur = cur->next();
    }
}

template <class Type>
void stack<Type>::clear() {
    stackEntry<Type>* cur = pTop;
    stackEntry<Type>* nxt;
    while(cur) {
        nxt = cur->next();
        count--;
        cur->next(nullptr);
        delete cur;
        cur = nxt;
    }
    pTop = nullptr;
}

#endif /* STACK_H_ */
