#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iomanip>


class list_node {
    std::string data;
    std::shared_ptr<list_node> next;
public:
    list_node(std::string _st): data(_st), next(nullptr) {};

    list_node() {};

    std::shared_ptr<list_node> get_next() {
        return next;
    }

    void set_next(std::shared_ptr<list_node> n) {
        next = n;
    }

    void set(std::string _st) {
        data = _st;
    }

    std::string &get() {
        return data;
    }
};


class my_list {
    std::shared_ptr<list_node> head;
    std::shared_ptr<list_node> tail;
public:
    my_list() {
        head = nullptr;
        tail = nullptr;
    }

    ~my_list() {
        // release its memory
        while (head != nullptr) {
            auto temp = head->get_next();
            head.reset();
            head = temp;
        }
    }

    bool empty() {
        return head == nullptr;
    }

    void push_back(std::string st) {
        // allocate new node, and initialize it
        std::shared_ptr<list_node> node {new list_node(st)};

        if (empty()) {
            tail = node;
            head = node;
        } else {
            tail->set_next(node);
            tail = node;
        }
    }

    void push_front(std::string st) {
        // allocate new node and initialize it
        std::shared_ptr<list_node> node {new list_node(st)};

        if (empty()) {
            tail = node;
            head = node;
        } else {
            node->set_next(head);
            head = node;
        }
    }

    /*
     * TODO: implement this function.
     * - Print the strings in the order they appear in the list, separated by " -> "
     * - Must iterate through entire list to get each string in order.
     *
     * Output example: "Tokyo -> Ottawa -> Washington -> London -> Madrid
    */
    void print() {
        if (head == nullptr)
            return;

        for (std::shared_ptr<list_node> current {head}; current != nullptr; current = current->get_next()) {
            if (current->get_next() == nullptr)
                std::cout << current->get();
            else
                std::cout << current->get() << " -> ";
        }
        std::cout << std::endl;
    }

    /*
     * TODO: implement this function.
     * - Return true if the given string is in the list but false otherwise.
     * - Must iterate through entire list to look for given string.
    */
    bool exists(std::string str) {
        for (std::shared_ptr<list_node> current {head}; current != nullptr; current = current->get_next()) {
            if (current->get() == str)
                return true;
        }
        return false;
    }

    /*
     * TODO: implement this function.
     * - Remove the node that contains the given string.
     * - Must iterate through entire list to look for given string.
    */
    void remove_node(std::string str) {
        if (head->get() == str)
            head = head->get_next();

        for (std::shared_ptr<list_node> current {head}; current != nullptr; current = current->get_next()) {
            if (current->get_next() != nullptr) {
                if (current->get_next()->get() == str) {
                    current->set_next(current->get_next()->get_next());
                }
            }
        }
    }

    std::string &front() {
        // retrieve the string at the front of the list
        return head->get();
    }

    std::string &back() {
        // retrieve the string at the back of the list
        return tail->get();
    }

};


int main() {
    my_list list;

    std::string line;
    // read one string at a time and insert at the end of the list
    while (getline(std::cin, line)) {
        list.push_back(line);
    }

    std::cout << "Capitals:" << std::endl;

    list.print();

    std::cout << std::endl;

    std::cout << std::boolalpha << "is Ottawa in the list? " << list.exists("Ottawa") << std::endl;
    std::cout << std::boolalpha << "is Brazilia in the list? " << list.exists("Brazilia") << std::endl;

    // Let us remove some elements
    list.remove_node("London");
    std::cout << "\nCapitals after removing London:" << std::endl;
    list.print();

    list.remove_node("Tokyo");
    std::cout << "\nCapitals after removing Tokyo:" << std::endl;
    list.print();

    list.remove_node("Stockholm");
    std::cout << "\nCapitals after removing Stockholm:" << std::endl;
    list.print();

    // Let us test an empty list

    my_list emptyList;

    std::cout << "Print empty list:" << std::endl;

    emptyList.print();

    std::cout << std::boolalpha << "is anything in the list? " << list.exists("") << std::endl;
}