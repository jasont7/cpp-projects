#ifndef __list_hpp__
#define __list_hpp__

#include <functional>
#include <memory>
#include <algorithm>


template <typename T>
class link_node {
private:
    T data;
    std::shared_ptr<link_node<T>> next;
public:
    link_node(T _i): data(_i), next(nullptr) {}
    link_node() {}

    T& get() { 
        return data;
    }
    void set(T _i) { 
        data = _i;
    }

    std::shared_ptr<link_node<T>> get_next() { 
        return next;
    }
    void set_next(std::shared_ptr<link_node<T>> n) {
        next = n;
    }
};

template <typename T>
class link_list {
private:
    std::shared_ptr<link_node<T>> head;
    std::shared_ptr<link_node<T>> tail;
    int num_nodes;
public:
    // default constructor
    link_list(): head(nullptr), tail(nullptr), num_nodes(0) {}

    // copy constructor
    link_list(const link_list& otherList) {
        *this = otherList;
    }

    ~link_list() {
        clear();
    }
    
    bool empty() {
        return head == nullptr;
    }

    int size() {
        return num_nodes;
    }
    
    // outputs each element of the list, separated by " -> "
    void print() {
        if (head == nullptr) {
            std::cout << std::endl;
            return;
        }

        for (std::shared_ptr<link_node<T>> current {head}; current != nullptr; current = current->get_next()) {
            if (current->get_next() == nullptr)
                std::cout << current->get();
            else
                std::cout << current->get() << " -> ";
        }
        std::cout << std::endl;
    }
    
    // returns a reference to the front of the list
    T& front() {
        if (empty())
            throw std::runtime_error("list is empty");
        
        return head->get();
    }

    // returns a reference to the back of the list
    T& back() {
        if (empty())
            throw std::runtime_error("list is empty");
        
        return tail->get();
    }

    // deletes the element at the beginning of the list
    void pop_front() {
        if (empty())
            throw std::runtime_error("list is empty");

        head = head->get_next();
        num_nodes--;
    }

    // inserts value at the end of the list
    void push_back(T val) {
        auto node = std::make_shared<link_node<T>>(val);

        if (empty()) {
            tail = node;
            head = node;
        } else {
            tail->set_next(node);
            tail = node;
        }
        num_nodes++;
    }
    
    // inserts value at the beginning of the list
    void push_front(T val) {
        auto node = std::make_shared<link_node<T>>(val);

        if (empty()) {
            head = node;
            tail = node;
        } else {
            node->set_next(head);
            head = node;
        }
        num_nodes++;
    }
    
    bool exists(T val) {
        for (std::shared_ptr<link_node<T>> current = head; current != nullptr; current = current->get_next()) {
            if (current->get() == val)
                return true;
        }
        return false;
    }
    
    // removes all elements of the list
    void clear() {
        while (head != nullptr) {
            std::shared_ptr<link_node<T>> tmp = head->get_next();
            head.reset();
            head = tmp;
        }
        tail = nullptr;
        num_nodes = 0;
    }
    
    // Adds the provided value to the list in sorted order. Assumes the list is in sorted order
    void insert_ordered(T val) {
        if (empty()) {
            push_back(val);
            return;
        }
        if (val < head->get()) {
            push_front(val);
            return;
        }

        auto curr = head;
        while (curr != nullptr) {
            if (curr->get_next() == nullptr) {
                push_back(val);
                return;
            }

            // check if val is between curr and curr.next
            if (val >= curr->get() && val <= curr->get_next()->get()) {
                auto node = std::make_shared<link_node<T>>(val);
                node->set_next(curr->get_next());
                curr->set_next(node);
                num_nodes++;
                return;
            }
            curr = curr->get_next();
        }
    }
    
    bool operator==(const link_list& otherList) {
        // check that both lists are the same size
        if (num_nodes != otherList.num_nodes)
            return false;
        
        auto c1 = head;
        auto c2 = otherList.head;
        while (c1 != nullptr) {
            if (c1->get() != c2->get())
                return false;

            c1 = c1->get_next();
            c2 = c2->get_next();
        }

        return true;
    }
    bool operator!=(const link_list& otherList) {
        return !(*this == otherList);
    }
    
    // Assignment operator - set this list to be a copy of the provided otherList
    void operator=(const link_list& otherList) {
        clear();
        auto curr = otherList.head;
        while (curr != nullptr) {
            push_back(curr->get());
            curr = curr->get_next();
        }
    }
    
    //Given a callback function (which takes a single argument, a reference to the
    //element type of this list, and returns void), call the function on every element
    //of the this list, in forward order.
    void apply(std::function<void(T&)> callback) {
        auto curr = head;
        while (curr != nullptr) {
            callback(curr->get());
            curr = curr->get_next();
        }
    }
    
    //Given a callback function (which takes a single argument, a reference to the
    //element type of this list, and returns an argument of some other type Q), return
    //a new link_list of element type Q whose elements are created by applying the
    //callback to each element in this list.
    template <typename Q>
    link_list<Q> map(std::function<Q(T&)> callback) {
        link_list<Q> newList;

        auto curr = head;
        while (curr != nullptr) {
            newList.push_back(callback(curr->get()));
            curr = curr->get_next();
        }
        return newList;
    }
};


#endif