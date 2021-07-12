#ifndef LINKED_LIST
#define LINKED_LIST
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

#include <cassert>
#include <sstream>
#include <string>

/**
 * a simple generic singly linked list class
 * @author Jon Beck
 * @version 5 September 2019
 */
template <typename Object>
class List
{
 private:
  /**
   * A class to store data and provide a link to the next node in the list
   */
  class Node
  {
   public:
    /**
     * The constructor
     * @param newdata the data to be stored in this node
     */
    explicit Node(const Object& newdata)
      : data {newdata}, next {nullptr} {}

    Object data;
    Node* next;
  };

 public:
  /**
   * The constructor for an empty list
   */
  List() : size {0}, first {nullptr} {}

  /**
   * the copy constructor
   * @param rhs the list we are copying
   */
  explicit List(const List& rhs) : size {0}, first {nullptr}
  {
    auto node_pointer {rhs.first};
    for (size_t i {0}; i < rhs.size; i++)
    {
      push_back(node_pointer->data);
      node_pointer = node_pointer->next;
    }
  }

  /**
   * disable the rvalue constructor and operator= methods
   */
  List(List&& rhs) = delete;
  List& operator=(List&& rhs) = delete;

  /**
   * the lvalue operator= method
   * @param rhs the list we are copying
   * @return a reference to ourself, with all new elements
   */
  List& operator=(const List& rhs)
  {
    if (this != &rhs)  // don't bother to copy ourself
    {
      // first need to reclaim all space used by our nodes
      auto node_pointer {first};
      for (size_t i {0}; i < size; i++)
      {
        Node* temp = node_pointer;
        node_pointer = node_pointer-> next;
        delete temp;
      }
      first = nullptr;
      size = 0;

      // now need to copy the elements of rhs
      node_pointer = rhs.first;
      for (size_t i {0}; i < rhs.size; i++)
      {
        push_back(node_pointer->data);
        node_pointer = node_pointer->next;
      }
    }
    return *this;
  }

  /**
   * The destructor gets rid of everything that's in the list
   * and reclaims heap space
   */
  ~List()
  {
    auto node_pointer {first};
    for (size_t i {0}; i < size; i++)
    {
      auto temp {node_pointer};
      node_pointer = node_pointer->next;
      delete temp;
    }
    size = 0;
    first = nullptr;
  }

  /**
   * Put a new element onto the beginning of the list
   * @param item the data the new element will contain
   */
  void push_front(const Object& item)
  {
    auto new_node {new Node (item)};
    if (empty())
    {
      first = new_node;
    }
    else
    {
      new_node->next = first;
      first = new_node;
    }
    size++;
  }

  /**
   * Put a new element onto the end of the list
   * @param item the data the new element will contain
   */
  void push_back(const Object& item)
  {
    auto new_node {new Node (item)};
    if (empty())
    {
      first = new_node;
    }
    else
    {
      auto node_pointer = first;
      for (size_t i {0}; i < size - 1; i++)
      {
        node_pointer = node_pointer->next;
      }

      node_pointer->next = new_node;
    }
    size++;
  }

  /**
   * Reverse the list
   */
  unsigned reverse()
  {
    auto current {first};
    Node* before {nullptr};
    unsigned counter {2};
    
    for (size_t i {0}; i < size; i++)
    {
      counter += 2;
      
      auto after {current->next};
      current->next = before;
      before = current;
      current = after;
      counter += 4;
    }
    counter += 2;
     
    first = before;
    counter ++;

    return counter;
  }

  /**
   * Remove the element that's at the front of the list. Causes an
   * assertion error if the list is already empty.
   */
  void pop_front()
  {
    assert(!empty());
    auto temp {first};

    if (size == 1)
    {
      first = nullptr;
    }
    else
    {
      first = first->next;
    }
    delete temp;
    size--;
  }

  /**
   * Accessor to return the data of the element at the front of the list.
   * Causes an assertion error if the list is empty.
   * @return the data in the front element
   */
  const Object& front() const
  {
    assert(!empty());
    return first->data;
  }

  /**
   * Accessor to determine whether the list is empty
   * @return a boolean corresponding to the emptiness of the list
   */
  bool empty() const
  {
    return size == 0;
  }

  /**
   * Accessor to determine whether a given element is in the list
   * Requires operator== to be defined for the list's object type
   * @param item the thing to find
   * @return the presence or absence of the thing in the list
   */
  bool find(const Object& item, unsigned &counter) const
  {
    
    
    bool found = false;
    Node* itr = first;
    counter +=2;
    
    while (!found && itr != nullptr)
    {
      counter += 3;
      
      found = itr->data == item;
      counter += 2;
      
      itr = itr->next;
      counter++;
    }
    counter += 3;
    
    return found;
  }

  /**
   * Accessor to generate a string representation of the list
   * Requires operator<< to be defined for the list's object type
   * @return string representation of the list
   */
  std::string to_string() const
  {
    if (size == 0)
    {
      return "";
    }

    std::stringstream buffer;
    auto node_pointer {first};
    for (size_t i {0}; i < size - 1; i++)
    {
      buffer << node_pointer->data << ' ';
      node_pointer = node_pointer->next;
    }
    buffer << node_pointer->data;
    return buffer.str();
  }

 private:
  size_t size;
  Node* first;
};

#pragma clang diagnostic pop
#endif
