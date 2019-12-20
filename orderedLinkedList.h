/*
 * Created by Griffin Davis on 11/4/2019.
 * CS2337-002 D. Vogel
 *
 * orderedLinkedList.h
 * This file uses linkedList.h to build an ordered linkedList.
*/

#ifndef ORDEREDLINKEDLIST_H_
#define ORDEREDLINKEDLIST_H_

#include "linkedList.h"

#include <cstddef>

template<class DataType>
class orderedLinkedList {
	public:
		typedef linkedList<DataType> unorderedLinkedList;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		typedef typename unorderedLinkedList::iterator iterator;
		typedef const iterator const_iterator;
	private:
		unorderedLinkedList list;
	public:
		// default constructor
		orderedLinkedList();
		// copy constructor
		orderedLinkedList(const orderedLinkedList &other);
		// assignment operator
		const orderedLinkedList& operator=(const orderedLinkedList &other);
		// destructor
		virtual ~orderedLinkedList();
		// iterators
		iterator begin() {
			return list.begin();
		}

		iterator end() {
			return list.end();
		}

		const_iterator begin() const {
			return list.begin();
		}

		const_iterator end() const {
			return list.end();
		}

		// number of items in the list
		virtual std::size_t size() const;
		// is the list empty (true) or does it have entries (false)
		virtual bool empty() const;
		// print the items in the list
		virtual void print() const;
		// display the contents of the list to the ostream&
		virtual void print(std::ostream &out) const;
		// display debug information on the passed in ostream
		virtual void debug(std::ostream &out) const;
		// find the element and return an iterator for it
		virtual iterator find(const DataType &existingItem);
		// remove the node equal to currentItem
		virtual bool erase(const DataType &currentItem);
		// remove the node by address existingNode
		virtual iterator erase(iterator iter);
		// insert the new item into the list (in sorted order)
		// a duplicate entry will be ignored
		virtual void insert(const DataType &newItem);
		// get the last entry
		iterator back() {
		   return list.back();
		}

		const_iterator back() const {
		   return list.back();
		}
};

template<class DataType>
orderedLinkedList<DataType>::orderedLinkedList() {
    unorderedLinkedList list;
}

template<class DataType>
orderedLinkedList<DataType>::orderedLinkedList(const orderedLinkedList &other) {
    unorderedLinkedList list(other);
}

template<class DataType>
const orderedLinkedList<DataType>& orderedLinkedList<DataType>::operator=(const orderedLinkedList &other) {
    list = other.list;
    return *this;
}

template<class DataType>
orderedLinkedList<DataType>::~orderedLinkedList() {
//    delete &list;
}

template<class DataType>
std::size_t orderedLinkedList<DataType>::size() const {
    return list.size();
}

template<class DataType>
bool orderedLinkedList<DataType>::empty() const {
    return list.empty();
}

template<class DataType>
void orderedLinkedList<DataType>::print() const {
    list.print();
}

template<class DataType>
void orderedLinkedList<DataType>::print(std::ostream &out) const {
    list.print(out);
}

template<class DataType>
void orderedLinkedList<DataType>::debug(std::ostream &out) const {
    list.debug(out);
}

template<class DataType>
typename orderedLinkedList<DataType>::iterator orderedLinkedList<DataType>::find(const DataType &existingItem) {
    return list.find(existingItem);
}

template<class DataType>
bool orderedLinkedList<DataType>::erase(const DataType &currentItem) {
    return list.erase(currentItem);
}

template<class DataType>
typename orderedLinkedList<DataType>::iterator orderedLinkedList<DataType>::erase(orderedLinkedList::iterator iter) {
    return list.erase(iter);
}

template<class DataType>
void orderedLinkedList<DataType>::insert(const DataType &newItem) {
    listNode<DataType>* cur = list.getFirstNode();
    if (cur == nullptr) {
        list.push_front(newItem);
        return;
    }
    while (cur) {
        if (newItem < cur->data()) {
            list.insert_before(cur, newItem);
            return;
        }
        cur = cur->next();
    }
    // Needs to be appended
    list.push_back(newItem);
}

#endif /* ORDEREDLINKEDLIST_H_ */
