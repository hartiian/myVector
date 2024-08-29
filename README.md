#include <iostream>
#include "header.h"

int main() {
    Vector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    std::cout << "After push_back: Size = " << vec.get_size() << ", Capacity = " << vec.get_cap() << std::endl;

    std::cout << "Element at index 1: " << vec[1] << std::endl;
    vec[1] = 25;
    std::cout << "Modified element at index 1: " << vec[1] << std::endl;

    vec.insert(1, 15);
    std::cout << "After insert(1, 15): ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    vec.pop_back();
    std::cout << "After pop_back: Size = " << vec.get_size() << std::endl;

    std::cout << "Front element: " << vec.front() << std::endl;
    std::cout << "Back element: " << vec.back() << std::endl;

    vec.emplace_back(40);
    std::cout << "After emplace_back(40): Back element = " << vec.back() << std::endl;

    vec.resize(5);
    std::cout << "After resize(5): Size = " << vec.get_size() << ", Capacity = " << vec.get_cap() << std::endl;

    vec.clear();
    std::cout << "After clear: Size = " << vec.get_size() << std::endl;

    vec.assign(3, 50);
    std::cout << "After assign(3, 50): Size = " << vec.get_size() << std::endl;
    std::cout << "Element at index 1: " << vec[1] << std::endl;

    vec.emplace(1, 60);
    std::cout << "After emplace(1, 60): Element at index 1 = " << vec[1] << std::endl;

    std::cout << "All elements: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    vec.shrink_to_fit();
    std::cout << "After shrink_to_fit: Capacity = " << vec.get_cap() << std::endl;

    Vector<int> vec_copy = vec;
    std::cout << "Copied vector: ";
    for (auto it = vec_copy.begin(); it != vec_copy.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    Vector<int> vec_move = std::move(vec);
    std::cout << "Moved vector: ";
    for (auto it = vec_move.begin(); it != vec_move.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
