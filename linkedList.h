/*
 * Created by Griffin Davis on 11/4/2019.
 * CS2337-002 D. Vogel
 *
 * linkedList.h
 * This file implements a linkedList utilizing iterators.
*/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>

// forward declaration of the template class linkedList
template<class DataType>
class linkedList;

// forward declaration of iterator
template<class DataType>
class linkedListIterator;

// listNode class
template<class DataType>
class listNode {
	// make DoubleLinkedList<DataType> a friend class
	friend class linkedList<DataType>;
	friend class linkedListIterator<DataType>;
	private:
		// contains the actual data
		DataType dataType;
		// pointer to the next item in the list or nullptr if at the end
		listNode<DataType>* pNext;
		// pointer to the previous item in the list or nullptr if at the start
		listNode<DataType>* pPrevious;
	public:
		// default constructor
		listNode();
		// constructor with data
		listNode(const DataType &newItem);
	protected:
		// get the next node
		listNode* next() const {
			return pNext;
		}

		// get the previous node
		listNode* previous() const {
			return pPrevious;
		}

		// return the data stored in the node as a const
		const DataType& data() const {
			return dataType;
		}

		// return the data stored in the node
		DataType& data() {
			return dataType;
		}

		// update the data
		void data(DataType& data) {
			dataType = data;
    }

		// update the next node
		void next(listNode *nextNode) {
			pNext = nextNode;
		}

		// update the previous node
		void previous(listNode *previousNode) {
			pPrevious = previousNode;
		}
};

// iterator for the linkedList
template<class DataType>
class linkedListIterator {
	typedef DataType 								   value_type;
	typedef DataType& 								reference;
	typedef const DataType& 						const_reference;
	typedef DataType* 								pointer;
	typedef const DataType* 						const_pointer;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef std::ptrdiff_t 							difference_type;
	typedef std::size_t								size_type;
	typedef linkedListIterator						iterator;
	typedef const linkedListIterator	  			const_iterator;

	friend class linkedList<DataType>;
	private:
		listNode<DataType> *current;
	public:
		linkedListIterator(listNode<DataType> *current)
			: current(current) {
		}

		virtual ~linkedListIterator() {
		}

		reference operator*() {
		   assert(current != nullptr);
			return current->data();
		}

		const_reference operator*() const {
		   assert(current != nullptr);
			return current->data();
		}

		pointer operator->() {
		   assert(current != nullptr);
			return &(current->data());
		}

		const_pointer operator->() const {
		   assert(current != nullptr);
			return &(current->data());
		}

		iterator operator++() {
			if (current != nullptr) {
				current = current->next();
			}
			return *this;
		}

		iterator operator++(int) {
			iterator it = *this;
			if (current != nullptr) {
				current = current->next();
			}
			return it;
		}

    iterator operator--() {
	    if (current != nullptr) {
	        current = current->previous();
	    }
	    return *this;
    }

    iterator operator--(int) {
	    iterator it = *this;
	    if (current !=nullptr) {
	        current = current->previous();
	    }
	    return it;
    }

    bool operator==(const_iterator &other) const {
        return current == other.current;
    }

    bool operator!=(const_iterator &other) const {
        return current != other.current;
    }

    listNode<DataType>* getCurrent() const {
        return current;
    }
};

// linkedList class
template<class DataType>
class linkedList {
	private:
		listNode<DataType>* firstNode;
		listNode<DataType>* lastNode;
    int count;

	public:
		typedef linkedListIterator<DataType> iterator;
		typedef const linkedListIterator<DataType> const_iterator;

		// default constructor
		linkedList();

		// copy constructor
		linkedList(const linkedList &other);

		// assignment operator
		const linkedList& operator=(const linkedList &other);

		// destructor
		virtual ~linkedList();

		// return the number of nodes in the list
		std::size_t size() const {
			return count;
		}

		// return true if the list is empty
		bool empty() const {
    	return count==0;
		}

		// display the contents of the list to std::cout
		void print() const {
			print(std::cout);
		}

		// display the contents of the list to the ostream&
		void print(std::ostream &out) const;

		// iterators
		iterator begin() {
			return iterator(firstNode);
		}

		const_iterator begin() const {
			return iterator(firstNode);
		}

		iterator end() {
			return iterator(nullptr);
		}

		const_iterator end() const {
			return iterator(nullptr);
		}

		// output contents of the linkedList to out
		void debug(std::ostream &out) const;

		// add an item to the front of the list
		virtual void push_front(const DataType &newItem);
		// add an item to the back of the list
		virtual void push_back(const DataType &newItem);
		// remove an item from the front of the list
		virtual void pop_front();
		// remove an item from the back of the list
		virtual void pop_back();
		// insert newItem before the node specified by the iterator
		virtual void insert_before (iterator iter, const DataType &newItem);
		// insert newItem after the node specified by the iterator
		virtual void insert_after (iterator iter, const DataType &newItem);
		// find the node and return the iterator for that element.
		// Return end() if not found
		virtual iterator find(const DataType &existingItem);
		// remove the node equal to currentItem
		virtual bool erase(const DataType &currentItem);
		// remove the node by address existingNode
		virtual iterator erase(iterator iter);
		// return the iterator for the last node
		virtual iterator back() {
			return linkedListIterator<DataType>(lastNode);
		}
		virtual const_iterator back() const {
			return linkedListIterator<DataType>(lastNode);
		}
		virtual listNode<DataType>* getFirstNode() {
		  return firstNode;
    }
    virtual listNode<DataType>* getSecondNode() {
        return firstNode;
    }
    virtual void clear() {
	    listNode<DataType>* cur = firstNode;
	    while (cur) {
        firstNode = firstNode->next();
      	delete cur;
        cur = firstNode;
	    }
	    count = 0;
      delete firstNode;
      firstNode = nullptr;
      lastNode = nullptr;
    }
};

// listNode member functions
// default constructor
template <class DataType>
listNode<DataType>::listNode()
	: dataType(), pNext(nullptr), pPrevious(nullptr) {
}

// initialization constructor
template <class DataType>
listNode<DataType>::listNode(const DataType &newItem)
	: dataType(newItem), pNext(nullptr), pPrevious(nullptr) {
}

// display a debug version of the list
template<class DataType>
void linkedList<DataType>::debug(std::ostream &out) const {
	const unsigned int ADDRWIDTH = 10;
	out << "START DEBUG" << std::endl;
	out << "first  =" << std::setw(ADDRWIDTH) << firstNode;
	out << ", last=" << std::setw(ADDRWIDTH) << lastNode;
	out << ", # nodes=" << size() << std::endl;
	unsigned int count = 1;

	for (auto current=firstNode; current!= nullptr; current=current->next()) {
		out << "node " << std::setw(2) << count;
		out << "=" << std::setw(ADDRWIDTH) << current;
		out << ", next=" << std::setw(ADDRWIDTH)
			<< current->next();
		out << ", previous=" << std::setw(ADDRWIDTH)
			<< current->previous();
		out << ", value=" << current->data() << std::endl;
		count++;
	}
	out << "END DEBUG" << std::endl;
}

// linkedList member functions
// default constructor
template<class DataType>
linkedList<DataType>::linkedList() {
	firstNode = nullptr;
	lastNode = nullptr;
	count = 0;
}

// find the node and return the address to the node. Return nullptr if not found
template<class DataType>
typename linkedList<DataType>::iterator linkedList<DataType>::find(const DataType &existingItem) {
  listNode<DataType>* cur = firstNode;
  while (cur) {
    if (cur->data() == existingItem) {
      return cur;
    }
    cur = cur->next();
  }
  return nullptr;
}

// remove the node equal to currentItem
template<class DataType>
bool linkedList<DataType>::erase(const DataType &currentItem) {
  listNode<DataType>* cur = firstNode;
  while (cur) {
    if (cur->data() == currentItem) {
      if (firstNode == lastNode) {
        // Handle single node list
        delete firstNode;
        firstNode = nullptr;
        lastNode = nullptr;
        count--;
      } else if (cur == firstNode) {
        // Handle firstNode
        listNode<DataType>* temp = firstNode;
        firstNode = firstNode->next();
        firstNode->previous(nullptr);
        count--;
        delete temp;
      } else if (cur == lastNode) {
        // Handle lastNode
        listNode<DataType>* temp = lastNode;
        lastNode = lastNode->previous();
        lastNode->next(nullptr);
        count--;
        delete temp;
      } else if (cur != lastNode) {
        // Handle inner node
        listNode<DataType>* prev = cur->previous();
        listNode<DataType>* suc = cur->next();
        prev->next(suc);
        suc->previous(prev);
        delete cur;
        count--;
      }
      return true;
    }
    cur = cur->next();
  }
  return false;
}

// remove the node by iterator
template<class DataType>
typename linkedList<DataType>::iterator  linkedList<DataType>::erase(linkedList<DataType>::iterator iter) {
  for (iterator i = begin(); i != end(); i++) {
    if (i == iter) { // Found specified node
        listNode<DataType>* cur = i.getCurrent();
        if (firstNode == lastNode) {
          // Handle single node list
          firstNode = nullptr;
          lastNode = nullptr;
          count--;
        } else if (cur == firstNode) {
          // Handle firstNode
          firstNode = firstNode->next();
          firstNode->previous(nullptr);
          count--;
        } else if (cur == lastNode) {
          // Handle lastNode
          lastNode = lastNode->previous();
          lastNode->next(nullptr);
          count--;
        } else if (cur != lastNode) {
          // Handle inner node
          listNode<DataType> *prev = cur->previous();
          listNode<DataType> *suc = cur->next();
          prev->next(suc);
          suc->previous(prev);
          count--;
        }
        delete i.getCurrent();
        return cur;
      }
  }
  return nullptr;
}

// other member functions go here.
// copy constructor
template<class DataType>
linkedList<DataType>::linkedList(const linkedList &other) {
  listNode<DataType>* head = new listNode<DataType>;
  listNode<DataType>* copyFirst = other.firstNode;

  head->data(copyFirst->data());
  firstNode = head;
  lastNode = head;
  count++;

  listNode<DataType>* cur = copyFirst->next();
  while(cur) {
    push_back(cur->data());
    count++;
    cur = cur->next();
  }
}

// assignment operator
template<class DataType>
const linkedList<DataType>& linkedList<DataType>::operator=(const linkedList &other) {
  // Don't self assign
  if (this != &other) {
    clear();

    listNode<DataType>* head = new listNode<DataType>;
    listNode<DataType>* copyFirst = other.firstNode;
    head->data(copyFirst->data());
    firstNode = head;
    lastNode = head;
    count++;

    listNode<DataType>* cur = copyFirst->next();
    while(cur) {
      push_back(cur->data());
      cur = cur->next();
    }
  }

  return *this;
}

// destructor
template<class DataType>
linkedList<DataType>::~linkedList() {
  listNode<DataType>* cur = firstNode;
  listNode<DataType>* nxt;

  while(cur) {
	  nxt = cur->next();
	  count--;
	  delete cur;
	  cur = nxt;
  }
  firstNode = nullptr;
  lastNode = nullptr;
}

// add an item to the front of the list
template<class DataType>
void linkedList<DataType>::push_front(const DataType &newItem) {
  listNode<DataType>* newNode = new listNode<DataType>(newItem);
  newNode->next(nullptr);
  newNode->previous(nullptr);

  if (firstNode == nullptr) {
    firstNode = newNode;
    lastNode = newNode;
  } else {
    newNode->next(firstNode);
    firstNode->previous(newNode);
    firstNode = newNode;
  }
  count++;
}

// add an item to the back of the list
template<class DataType>
void linkedList<DataType>::push_back(const DataType &newItem) {
  listNode<DataType>* newNode = new listNode<DataType>(newItem);
  newNode->next(nullptr);
  newNode->previous(nullptr);

  if (firstNode == nullptr) {
    firstNode = newNode;
    lastNode = newNode;
  } else {
    lastNode->next(newNode);
    newNode->previous(lastNode);
    lastNode = newNode;
  }
  count++;
}

// remove an item from the front of the list
template<class DataType>
void linkedList<DataType>::pop_front() {
  if (firstNode->next()) {
    listNode<DataType>* temp = firstNode;
    firstNode = firstNode->next();
    firstNode->previous(nullptr);
    count--;
    delete temp;
  } else {
    count--;
    delete firstNode;
    firstNode = nullptr;
    lastNode = nullptr;
  }
}

// remove an item from the back of the list
template<class DataType>
void linkedList<DataType>::pop_back() {
  if (lastNode->previous()) {
    listNode<DataType>* temp = lastNode;
    lastNode = lastNode->previous();
    lastNode->next(nullptr);
    count--;
    delete temp;
  } else {
    count--;
    delete lastNode;
    firstNode = nullptr;
    lastNode = nullptr;
  }
}

// insert newItem before the node specified by the iterator
template<class DataType>
void linkedList<DataType>::insert_before(iterator iter, const DataType &newItem) {
  listNode<DataType>* newNode = new listNode<DataType>(newItem);
  newNode->next(nullptr);
  newNode->previous(nullptr);

  if (firstNode == nullptr) {
    // Handle empty list insertion
    firstNode = newNode;
    lastNode = newNode;
    count++;
    return;
  }

  for (iterator i = begin(); i != end(); i++) {
    if (i == iter) { // Found specified node
      listNode<DataType>* cur = i.getCurrent();
      if (cur->previous()) {
        // Handle last or inner node
        listNode<DataType>* pre = cur->previous();
        newNode->previous(pre);
        newNode->next(cur);
        cur->previous(newNode);
        pre->next(newNode);
        count++;
      } else if (cur == firstNode) {
        // Handle firstNode insertion
        push_front(newItem);
      }
      break;
    }
  }
}

// insert newItem after the node specified by the iterator
template<class DataType>
void linkedList<DataType>::insert_after(iterator iter, const DataType &newItem) {
  listNode<DataType>* newNode = new listNode<DataType>(newItem);
  newNode->next(nullptr);
  newNode->previous(nullptr);

  if (firstNode == nullptr) {
    // Handle empty list insertion
    firstNode = newNode;
    lastNode = newNode;
    count++;
    return;
  }

  for (iterator i = begin(); i != end(); i++) {
    if (i == iter) { // Found specified node
      listNode<DataType> *cur = i.getCurrent();
      if (cur->next()) {
        // Handle first or inner node
        listNode<DataType> *nxt = cur->next();
        newNode->previous(cur);
        newNode->next(nxt);
        nxt->previous(newNode);
        cur->next(newNode);
        count++;
      } else if (cur == lastNode) {
        // Handle lastNode insertion
        push_back(newItem);
      }
      break;
    }
  }
}

// Print the contents of the list
template<class DataType>
void linkedList<DataType>::print(std::ostream &out) const {
  for (iterator i = begin(); i != end(); i++) {
    out << i.getCurrent()->data() << std::endl;
  }
}

#endif /* DOUBLELINKEDLIST_H_ */
