template <typename T>
Vector<T>::Vector() : m_ptr(nullptr), size(0), cap(0) {}

template <typename T>
Vector<T>::~Vector() {
    delete[] m_ptr;
}

template <typename T>
Vector<T>::Vector(const Vector& other) : size(other.size), cap(other.cap) {
    m_ptr = new T[cap];
    for (size_t i = 0; i < size; ++i) {
        m_ptr[i] = other.m_ptr[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] m_ptr;
        size = other.size;
        cap = other.cap;
        m_ptr = new T[cap];
        for (size_t i = 0; i < size; ++i) {
            m_ptr[i] = other.m_ptr[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : size(other.size), cap(other.cap), m_ptr(other.m_ptr) {
    other.size = 0;
    other.cap = 0;
    other.m_ptr = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] m_ptr;
        size = other.size;
        cap = other.cap;
        m_ptr = other.m_ptr;
        other.size = 0;
        other.cap = 0;
        other.m_ptr = nullptr;
    }
    return *this;
}

template <typename T>
size_t Vector<T>::get_size() const {
    return size;
}

template <typename T>
size_t Vector<T>::get_cap() const {
    return cap;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size == cap) {
        size_t new_cap = (cap == 0) ? 1 : cap * 2;
        T* new_ptr = new T[new_cap];
        for (size_t i = 0; i < size; ++i) {
            new_ptr[i] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = new_ptr;
        cap = new_cap;
    }
    m_ptr[size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
void Vector<T>::clear() {
    size = 0;
}

template <typename T>
template <typename... Args>
T* Vector<T>::emplace(size_t pos, Args&&... args) {
    if (pos > size) {
        throw std::out_of_range("Position out of range");
    }

    if (size == cap) {
        reserve(cap > 0 ? cap * 2 : 1);
    }

    for (size_t i = size; i > pos; --i) {
        m_ptr[i] = std::move(m_ptr[i - 1]);
    }

    new(&m_ptr[pos]) T(std::forward<Args>(args)...);
    ++size;
    return &m_ptr[pos];
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args&&... args) {
    if (size == cap) {
        reserve(cap > 0 ? cap * 2 : 1);
    }

    new(&m_ptr[size++]) T(std::forward<Args>(args)...);
}

template <typename T>
void Vector<T>::resize(size_t new_size) {
    if (new_size > cap) {
        size_t new_cap = new_size;
        T* new_ptr = new T[new_cap];
        for (size_t i = 0; i < size; ++i) {
            new_ptr[i] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = new_ptr;
        cap = new_cap;
    }
    size = new_size;
}

template <typename T>
void Vector<T>::reserve(size_t new_cap) {
    if (new_cap > cap) {
        T* new_ptr = new T[new_cap];
        for (size_t i = 0; i < size; ++i) {
            new_ptr[i] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = new_ptr;
        cap = new_cap;
    }
}

template <typename T>
void Vector<T>::assign(size_t count, const T& value) {
    clear();
    reserve(count);
    for (size_t i = 0; i < count; ++i) {
        push_back(value);
    }
}

template <typename T>
template <typename U>
void Vector<T>::assign(U first, U last) {
    clear();
    for (U it = first; it != last; ++it) {
        push_back(*it);
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (size < cap) {
        T* new_ptr = new T[size];
        for (size_t i = 0; i < size; ++i) {
            new_ptr[i] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = new_ptr;
        cap = size;
    }
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[index];
}

template <typename T>
T& Vector<T>::front() const {
    return m_ptr[0];
}

template <typename T>
T& Vector<T>::back() const {
    return m_ptr[size - 1];
}

template <typename T>
T* Vector<T>::data() const {
    return m_ptr;
}

template <typename T>
void Vector<T>::swap(Vector& other) {
    std::swap(size, other.size);
    std::swap(cap, other.cap);
    std::swap(m_ptr, other.m_ptr);
}

template <typename T>
void Vector<T>::insert(size_t pos, const T& value) {
    if (pos > size) {
        throw std::out_of_range("Position out of range");
    }
    if (size == cap) {
        size_t new_cap = (cap == 0) ? 1 : cap * 2;
        T* new_ptr = new T[new_cap];
        for (size_t i = 0; i < pos; ++i) {
            new_ptr[i] = m_ptr[i];
        }
        new_ptr[pos] = value;
        for (size_t i = pos; i < size; ++i) {
            new_ptr[i + 1] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = new_ptr;
        cap = new_cap;
    } else {
        for (size_t i = size; i > pos; --i) {
            m_ptr[i] = m_ptr[i - 1];
        }
        m_ptr[pos] = value;
    }
    ++size;
}

template <typename T>
void Vector<T>::erase(size_t pos) {
    if (pos >= size) {
        throw std::out_of_range("Position out of range");
    }
    for (size_t i = pos; i < size - 1; ++i) {
        m_ptr[i] = m_ptr[i + 1];
    }
    --size;
}

template <typename T>
template <typename Pred>
void Vector<T>::erase_if(Pred pred) {
    size_t new_size = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!pred(m_ptr[i])) {
            m_ptr[new_size++] = std::move(m_ptr[i]);
        }
    }

    for (size_t i = new_size; i < size; ++i) {
        m_ptr[i].~T(); 
    }

    size = new_size;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    return iterator(m_ptr);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(m_ptr + size);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const {
    return const_iterator(m_ptr);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const {
    return const_iterator(m_ptr + size);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() { 
    return reverse_iterator(end()); 
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() { 
    return reverse_iterator(begin()); 
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const { 
    return const_reverse_iterator(cend()); 
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const { 
    return const_reverse_iterator(cbegin()); 
}
