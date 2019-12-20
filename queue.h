/*
 * Created by Griffin Davis on 11/29/2019.
 * CS2337-002 D. Vogel
 *
 * queue.h
 * This file implements a basic linked list queue for a given data type.
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#include <cstddef>
#include <cassert>
#include <iostream>

template <class Type>
class queue;

template <class Type>
class queueEntry {
    friend class queue<Type>;

protected:
    Type dataValue;
    queueEntry<Type> *pNext;

    queueEntry(const Type &newData, queueEntry<Type> *newNext = nullptr)
            : dataValue(newData), pNext(newNext) {};
    virtual ~queueEntry();
    virtual void next(queueEntry<Type> *pNext);
    virtual queueEntry<Type>* next();
    virtual Type& data();
    virtual const Type& data() const;
};

template <class Type>
queueEntry<Type>::~queueEntry() {
    delete pNext;
}

template <class Type>
void queueEntry<Type>::next(queueEntry<Type>* pNext) {
    this->pNext = pNext;
}

template<class Type>
queueEntry<Type> *queueEntry<Type>::next() {
    return pNext;
}

template <class Type>
Type& queueEntry<Type>::data() {
    return dataValue;
}

template <class Type>
const Type& queueEntry<Type>::data() const {
    return dataValue;
}

template <class Type>
class queue {
private:
    queueEntry<Type> *pFront;
    queueEntry<Type> *pEnd;
    std::size_t count;
public:
    queue();
    virtual ~queue();
    queue(const queue &other);
    const queue& operator=(const queue &rhs);
    const Type& front() const;
    Type& front();
    const Type& back() const;
    Type& back();
    queueEntry<Type>* getPFront() const;
    bool empty() const;
    std::size_t size() const;
    void push(const Type &value);
    void pop();
    void clear();
    void debug() const;
    void debug(std::ostream &out) const;
    // used by applications using the queue to work with all
    //  of the items in the queue from end to front.
    void traverse(void (*applicationFunction) (const Type &nextItem));
};

template<class Type>
queue<Type>::queue() {
    pFront = nullptr;
    pEnd = nullptr;
    count = 0;
}

template<class Type>
queue<Type>::queue(const queue &other) {
    pFront = nullptr;
    pEnd = nullptr;
    count = 0;
    queueEntry<Type>* cur = other.getPFront();
    while(cur) {
        push(cur->data());
        cur = cur->next();
    }
}

template<class Type>
const queue<Type>& queue<Type>::operator=(const queue &rhs) {
    if (this != &rhs) { // Don't self assign
        clear();

        queueEntry<Type>* cur = rhs.getPFront();
        while(cur) {
            push(cur->data());
            cur = cur->next();
        }
    }

    return *this;
}

template<class Type>
queue<Type>::~queue() {
    clear();
}

template<class Type>
const Type& queue<Type>::front() const {
    return pFront->data();
}

template<class Type>
Type& queue<Type>::front() {
    return pFront->data();
}

template<class Type>
const Type& queue<Type>::back() const {
    return pEnd->data();
}

template<class Type>
Type& queue<Type>::back() {
    return pEnd->data();
}

template<class Type>
queueEntry<Type>* queue<Type>::getPFront() const {
    return pFront;
}

template<class Type>
bool queue<Type>::empty() const {
    return count == 0;
}

template<class Type>
std::size_t queue<Type>::size() const {
    return count;
}

template<class Type>
void queue<Type>::push(const Type& value) {
    queueEntry<Type>* newNode = new queueEntry<Type>(value);
    if (pFront == nullptr) {
        // Empty queue
        pFront = newNode;
        pEnd = newNode;
        count++;
    } else {
        // Non-empty queue
        pEnd->next(newNode);
        pEnd = newNode;
        count++;
    }
}

template<class Type>
void queue<Type>::pop() {
    if (pFront != nullptr) {
        // Queue is not empty
        queueEntry<Type>* temp = pFront;
        pFront = pFront->next();
        temp->next(nullptr);
        delete temp;
        count--;

        // Handle newly empty queue
        if (pFront == nullptr) {
            pEnd = nullptr;
        }
    }
}

template<class Type>
void queue<Type>::clear() {
    queueEntry<Type>* cur = pFront;
    queueEntry<Type>* nxt;
    while (cur) {
        nxt = cur->next();
        cur->next(nullptr);
        delete cur;
        cur = nxt;
        count--;
    }
    pFront = nullptr;
    pEnd = nullptr;
}

template<class Type>
void queue<Type>::debug() const
{
	debug(std::cout);
}

template<class Type>
void queue<Type>::debug(std::ostream &out) const
{
	{
		out << "Number of items in queue: " << count << std::endl;
		out << "Front of queue is entry @" << pFront << std::endl;
		out << "End of queue is entry @" << pEnd << std::endl;
		out << std::endl;

		queueEntry<Type> *pNext = pFront;

		while (pNext != nullptr)
		{
			out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
			pNext = pNext->next();
		}
	}
}

template<class Type>
void queue<Type>::traverse(void (*applicationFunction) (const Type &nextItem)) {
    queueEntry<Type>* cur = pFront;
    while(cur) {
        applicationFunction(cur->data());
        cur = cur->next();
    }
}

#endif /* QUEUE_H_ */
