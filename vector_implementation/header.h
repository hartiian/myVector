#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename T>
class Iterator;

template <typename Iterator>
class ReverseIterator;

template <typename T>
class Vector {
private:
    size_t cap;
    size_t size;
    T* m_ptr;

public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    size_t get_size() const;
    size_t get_cap() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void push_back(const T& value);
    void pop_back();
    void clear();
    
    template <typename... Args>
    T* emplace(size_t pos, Args&&... args);
    
    template <typename... Args>
    void emplace_back(Args&&... args);

    void resize(size_t new_size);
    void reserve(size_t new_cap);
    void assign(size_t count, const T& value);
    template <typename U>
    void assign(U first, U last);
    void shrink_to_fit();
    T& at(size_t index);
    bool empty() const;
    T& front() const;
    T& back() const;
    T* data() const;
    void swap(Vector& other);
    void insert(size_t pos, const T& value);
    void erase(size_t pos);
    
    template <typename Pred>
    void erase_if(Pred pred);

    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    using reverse_iterator = ReverseIterator<iterator>;
    using const_reverse_iterator = ReverseIterator<const_iterator>;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
};

template <typename T>
class Iterator {
private:
    T* data;

public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    explicit Iterator(pointer ptr = nullptr);
    reference operator*() const;
    pointer operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    Iterator operator+(difference_type n) const;
    Iterator operator-(difference_type n) const;
    difference_type operator-(const Iterator& other) const;
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    bool operator<(const Iterator& other) const;
    bool operator>(const Iterator& other) const;
    bool operator<=(const Iterator& other) const;
    bool operator>=(const Iterator& other) const;
};

template <typename Iterator>
class ReverseIterator {
public:
    using iterator_type = Iterator;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;

    explicit ReverseIterator(iterator_type it);
    reference operator*() const;
    pointer operator->() const;
    ReverseIterator& operator++();
    ReverseIterator operator++(int);
    ReverseIterator& operator--();
    ReverseIterator operator--(int);
    ReverseIterator operator+(difference_type n) const;
    ReverseIterator operator-(difference_type n) const;
    difference_type operator-(const ReverseIterator& other) const;
    bool operator==(const ReverseIterator& other) const;
    bool operator!=(const ReverseIterator& other) const;
    bool operator<(const ReverseIterator& other) const;
    bool operator<=(const ReverseIterator& other) const;
    bool operator>(const ReverseIterator& other) const;
    bool operator>=(const ReverseIterator& other) const;

private:
    iterator_type current;
};

#include "vector.cpp"

#endif 
