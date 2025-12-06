/*****************************************************************//**
 * @file   DEQueue.h
 * @brief  A double-ended queue (deque) implementation using a circular
 *         doubly-linked list with sentinel node for efficient O(1)
 *         insertions and deletions at both ends.
 *
 * @tparam T The type of elements stored in the deque
 *
 * @author Fahad Hassan
 * @date   01 12 2025
 *********************************************************************/


#ifndef GUARD_DEQUE_H
#define GUARD_DEQUE_H

#include <utility>
#include <cstddef>
#include <stdexcept>

template<typename T>
class DEQIterator;

template<typename T>
class Deque
{
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        template<class... Args>
        explicit Node(Args&&... args) : data(std::forward<Args>(args)...) {})
    };

    friend class DEQIterator<T>;

private:
    Node* m_Sentinel;
    std::size_t m_Size;

    void initialize_sentinel();

public:
    Deque();
    ~Deque();

    Deque(const Deque<T>& other);
    Deque(Deque<T>&& other) noexcept;
    Deque<T>& operator=(Deque<T> other);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    bool empty() const noexcept;
    std::size_t size() const noexcept;

    template<typename... Args>
    void emplace_back(Args&&... args);

    template<typename U>
    void push_back(U&& value);

    template<typename... Args>
    void emplace_front(Args&&... args);

    template<typename U>
    void push_front(U&& value);

    void pop_back();

    void pop_front();

    void clear() noexcept;

    DEQIterator<T> begin();
    DEQIterator<T> end();
    const DEQIterator<T> begin() const;
    const DEQIterator<T> end() const;
    const DEQIterator<T> cbegin() const;
    const DEQIterator<T> cend() const;

    void swap(Deque<T>& other) noexcept;
};

template<typename T>
void swap(Deque<T>& left, Deque<T>& right) noexcept;

template<typename T>
class DEQIterator
{
    using Node = typename Deque<T>::Node;

private:
    Node* m_Pointer;

public:
    DEQIterator(Node* pointer = nullptr);

    DEQIterator<T>& operator++();
    DEQIterator<T>& operator++(int);

    DEQIterator<T>& operator--();
    DEQIterator<T>& operator--(int);

    T& operator*() noexcept;
    const T& operator*() const noexcept;

    T* operator->() noexcept;
    const T* operator->() const noexcept;

    bool operator==(const DEQIterator<T>& other) const;
    bool operator!=(const DEQIterator<T>& other) const;
};

template<typename T>
inline void Deque<T>::initialize_sentinel()
{
    m_Sentinel = new Node(T());
    m_Sentinel->prev = m_Sentinel;
    m_Sentinel->next = m_Sentinel;
}

template<typename T>
inline Deque<T>::Deque()
    : m_Size(0)
{
    initialize_sentinel();
}

template<typename T>
inline Deque<T>::~Deque()
{
    clear();
    delete m_Sentinel;
}

template<typename T>
inline Deque<T>::Deque(const Deque<T>& other)
    : m_Size(0)
{
    initialize_sentinel();

    for (const auto& item : other)
    {
        push_back(item);
    }
}

template<typename T>
inline Deque<T>::Deque(Deque<T>&& other) noexcept
    : m_Sentinel(other.m_Sentinel), m_Size(other.m_Size)
{
    other.m_Size = 0;
    other.initialize_sentinel();
}

template<typename T>
inline Deque<T>& Deque<T>::operator=(Deque<T> other) noexcept
{
    swap(other);
    return *this;
}

template<typename T>
inline bool Deque<T>::empty() const noexcept
{
    return m_Size == 0;
}

template<typename T>
inline std::size_t Deque<T>::size() const noexcept
{
    return m_Size;
}

template<typename T>
inline T& Deque<T>::front()
{
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return m_Sentinel->next->data;
}

template<typename T>
inline const T& Deque<T>::front() const
{
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return m_Sentinel->next->data;
}

template<typename T>
inline T& Deque<T>::back()
{
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return m_Sentinel->prev->data;
}

template<typename T>
inline const T& Deque<T>::back() const
{
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return m_Sentinel->prev->data;
}

template<typename T>
template<typename... Args>
inline void Deque<T>::emplace_back(Args&&... args)
{
    Node* tail = m_Sentinel->prev;
    Node* newNode = new Node(std::forward<Args>(args)...);

    newNode->prev = tail;
    newNode->next = m_Sentinel;
    tail->next = newNode;
    m_Sentinel->prev = newNode;

    m_Size++;
}

template<typename T>
template<typename U>
inline void Deque<T>::push_back(U&& value)
{
    emplace_back(std::forward<U>(value));
}

template<typename T>
template<typename... Args>
inline void Deque<T>::emplace_front(Args&&... args)
{
    Node* head = m_Sentinel->next;
    Node* newNode = new Node(std::forward<Args>(args)...);

    newNode->next = head;
    newNode->prev = m_Sentinel;
    head->prev = newNode;
    m_Sentinel->next = newNode;

    m_Size++;
}

template<typename T>
template<typename U>
inline void Deque<T>::push_front(U&& value)
{
    emplace_front(std::forward<U>(value));
}

template<typename T>
inline void Deque<T>::pop_back()
{
    if (empty()) 
        return;

    Node* toDelete = m_Sentinel->prev;
    Node* newTail = toDelete->prev;

    newTail->next = m_Sentinel;
    m_Sentinel->prev = newTail;

    delete toDelete;
    m_Size--;
}

template<typename T>
inline void Deque<T>::pop_front()
{
    if (empty()) 
        return;

    Node* toDelete = m_Sentinel->next;
    Node* newHead = toDelete->next;

    m_Sentinel->next = newHead;
    newHead->prev = m_Sentinel;

    delete toDelete;
    m_Size--;
}

template<typename T>
inline DEQIterator<T> Deque<T>::begin()
{
    return DEQIterator<T>(m_Sentinel->next);
}

template<typename T>
inline DEQIterator<T> Deque<T>::end()
{
    return DEQIterator<T>(m_Sentinel);
}

template<typename T>
inline const DEQIterator<T> Deque<T>::begin() const
{
    return DEQIterator<T>(m_Sentinel->next);
}

template<typename T>
inline const DEQIterator<T> Deque<T>::end() const
{
    return DEQIterator<T>(m_Sentinel);
}

template<typename T>
inline const DEQIterator<T> Deque<T>::cbegin() const
{
    return DEQIterator<T>(m_Sentinel->next);
}

template<typename T>
inline const DEQIterator<T> Deque<T>::cend() const
{
    return DEQIterator<T>(m_Sentinel);
}

template<typename T>
inline void Deque<T>::swap(Deque<T>& other) noexcept
{
    std::swap(m_Sentinel, other.m_Sentinel);
    std::swap(m_Size, other.m_Size);
}

template<typename ...Args>
inline void emplace_back(Args && ...args)
{
}

template<typename U>
inline void push_back(U&& value)
{
}

template<typename ...Args>
inline void emplace_front(Args && ...args)
{
}

template<typename U>
inline void push_front(U&& value)
{
}

template<typename T>
void swap(Deque<T>& left, Deque<T>& right) noexcept
{
    left.swap(right);
}

template<typename T>
inline DEQIterator<T>::DEQIterator(Node* pointer)
    : m_Pointer(pointer)
{
}

template<typename T>
inline DEQIterator<T>& DEQIterator<T>::operator++()
{
    m_Pointer = m_Pointer->next;
    return *this;
}

template<typename T>
inline DEQIterator<T>& DEQIterator<T>::operator--()
{
    m_Pointer = m_Pointer->prev;
    return *this;
}

template<typename T>
inline DEQIterator<T>& DEQIterator<T>::operator++(int)
{
    DEQIterator temp = *this;
    ++(*this);

    return temp;
}

template<typename T>
inline DEQIterator<T>& DEQIterator<T>::operator--(int)
{
    DEQIterator temp = *this;
    --(*this);

    return temp;
}

template<typename T>
inline T& DEQIterator<T>::operator*() noexcept
{
    return m_Pointer->data;
}

template<typename T>
inline const T& DEQIterator<T>::operator*() const noexcept
{
    return m_Pointer->data;
}

template<typename T>
inline T* DEQIterator<T>::operator->() noexcept
{
    return &(m_Pointer->data);
}

template<typename T>
inline const T* DEQIterator<T>::operator->() const noexcept
{
    return &(m_Pointer->data);
}

template<typename T>
inline bool DEQIterator<T>::operator==(const DEQIterator<T>& other) const noexcept
{
    return m_Pointer == other.m_Pointer;
}

template<typename T>
inline bool DEQIterator<T>::operator!=(const DEQIterator<T>& other) const noexcept
{
    return m_Pointer != other.m_Pointer;
}

#endif // !GUARD_DEQUE_H