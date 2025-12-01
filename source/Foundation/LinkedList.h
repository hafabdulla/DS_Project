/*****************************************************************//**
 * @file   LinkedList.h
 * @brief  Singly Linked List
 *
 * @author Fahad Hassan
 * @date   27 11 2025
 *********************************************************************/

#ifndef GUARD_LINKEDLIST_H
#define GUARD_LINKEDLIST_H

#include <utility>
#include <cstddef>
#include <stdexcept>

template<typename T>
class LLIterator;

template<typename T>
class LinkedList
{
    struct Node
    {
        T data;
        Node* next = nullptr;

        template<class... Args>
        explicit Node(Args&&... args) : data(std::forward<Args>(args)...) {}
    };

    friend class LLIterator<T>;

private:
    Node* m_Front;
    Node* m_Back;
    std::size_t m_Size;

public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList<T>& other);         // copy constructor
    LinkedList(LinkedList<T>&& other) noexcept;     // move constructor
    LinkedList<T>& operator=(LinkedList<T> other);  // copy or move assignment

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

    void pop_front();

    // void pop_back();

    void clear() noexcept;

    LLIterator<T> begin();
    LLIterator<T> end();
    const LLIterator<T> begin() const;
    const LLIterator<T> end() const;
    const LLIterator<T> cbegin() const;
    const LLIterator<T> cend() const;

    void swap(LinkedList<T>& other) noexcept;
};

template<typename T>
void swap(LinkedList<T>& left, LinkedList<T>& right) noexcept;

template<typename T>
class LLIterator
{
    using Node = typename LinkedList<T>::Node;

private:
    Node* m_Pointer;

public:
    LLIterator(Node* pointer);

    LLIterator& operator++();
    LLIterator operator++(int);

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    bool operator==(const LLIterator<T>& other) const;
    bool operator!=(const LLIterator<T>& other) const;
};

template<typename T>
inline LinkedList<T>::LinkedList()
    : m_Front(nullptr), m_Back(nullptr), m_Size(0)
{
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
    clear();
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& other)
    : m_Front(nullptr), m_Back(nullptr), m_Size(0)
{
    Node* current = other.m_Front;

    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
}

template<typename T>
inline LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept
    : m_Front(other.m_Front), m_Back(other.m_Back), m_Size(other.m_Size)
{
    other.m_Front = nullptr;
    other.m_Back = nullptr;
    other.m_Size = 0;
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> other)
{
    swap(other);
    return *this;
}

template<typename T>
inline T& LinkedList<T>::front()
{
    if (empty())
        throw std::out_of_range("List is empty!");

    return m_Front->data;
}

template<typename T>
inline const T& LinkedList<T>::front() const
{
    if (empty())
        throw std::out_of_range("List is empty!");

    return m_Front->data;
}

template<typename T>
inline T& LinkedList<T>::back()
{
    if (empty())
        throw std::out_of_range("List is empty!");

    return m_Back->data;
}

template<typename T>
inline const T& LinkedList<T>::back() const
{
    if (empty())
        throw std::out_of_range("List is empty!");

    return m_Back->data;
}

template<typename T>
inline bool LinkedList<T>::empty() const noexcept
{
    return m_Size == 0;
}

template<typename T>
inline size_t LinkedList<T>::size() const noexcept
{
    return m_Size;
}

template<typename T>
template<typename U>
inline void LinkedList<T>::push_back(U&& value)
{
    emplace_back(std::forward<U>(value));
}

template<typename T>
template<typename... Args>
inline void LinkedList<T>::emplace_back(Args&&... args)
{
    Node* new_node = new Node(std::forward<Args>(args)...);

    if (m_Back == nullptr)
        m_Front = new_node;
    else
        m_Back->next = new_node;

    m_Back = new_node;
    m_Size++;
}

template<typename T>
template<typename ...Args>
inline void LinkedList<T>::emplace_front(Args && ...args)
{
    Node* new_node = new Node(std::forward<Args>(args)...);

    if (m_Front == nullptr)
        m_Back = new_node;
    else
        new_node->next = m_Front;

    m_Front = new_node;
    m_Size++;
}

template<typename T>
template<typename U>
inline void LinkedList<T>::push_front(U&& value)
{
    emplace_front(std::forward<U>(value));
}

template<typename T>
inline void LinkedList<T>::pop_front()
{
    if (m_Front == nullptr)
        return;

    Node* popped_node = m_Front;
    m_Front = m_Front->next;

    if (m_Front == nullptr)
        m_Back = nullptr;

    delete popped_node;
    m_Size--;
}

template<typename T>
inline void LinkedList<T>::clear() noexcept
{
    while (m_Front != nullptr)
    {
        Node* temp = m_Front;
        m_Front = m_Front->next;

        delete temp;
    }

    m_Back = nullptr;
    m_Size = 0;
}

template<typename T>
inline LLIterator<T> LinkedList<T>::begin()
{
    return LLIterator<T>(m_Front);
}

template<typename T>
inline LLIterator<T> LinkedList<T>::end()
{
    return LLIterator<T>(nullptr);
}

template<typename T>
inline const LLIterator<T> LinkedList<T>::begin() const
{
    return LLIterator<T>(m_Front);
}

template<typename T>
inline const LLIterator<T> LinkedList<T>::end() const
{
    return LLIterator<T>(nullptr);
}

template<typename T>
inline const LLIterator<T> LinkedList<T>::cbegin() const
{
    return LLIterator<T>(m_Front);
}

template<typename T>
inline const LLIterator<T> LinkedList<T>::cend() const
{
    return LLIterator<T>(nullptr);
}

template<typename T>
inline void LinkedList<T>::swap(LinkedList<T>& other) noexcept
{
    using std::swap;
    swap(this->m_Front, other.m_Front);
    swap(this->m_Back, other.m_Back);
    swap(this->m_Size, other.m_Size);
}

template<typename T>
inline void swap(LinkedList<T>& obj1, LinkedList<T>& obj2) noexcept
{
    obj1.swap(obj2);
}

template<typename T>
inline LLIterator<T>::LLIterator(Node* pointer)
    : m_Pointer(pointer)
{
}

template<typename T>
inline LLIterator<T>& LLIterator<T>::operator++()
{
    m_Pointer = m_Pointer->next;
    return *this;
}

template<typename T>
inline LLIterator<T> LLIterator<T>::operator++(int)
{
    LLIterator<T> temp = *this;
    m_Pointer = m_Pointer->next;
    return temp;
}

template<typename T>
inline T& LLIterator<T>::operator*()
{
    return m_Pointer->data;
}

template<typename T>
inline const T& LLIterator<T>::operator*() const
{
    return m_Pointer->data;
}

template<typename T>
inline T* LLIterator<T>::operator->()
{
    return &(m_Pointer->data);
}

template<typename T>
inline const T* LLIterator<T>::operator->() const
{
    return &(m_Pointer->data);
}

template<typename T>
inline bool LLIterator<T>::operator==(const LLIterator<T>& other) const
{
    return m_Pointer == other.m_Pointer;
}

template<typename T>
inline bool LLIterator<T>::operator!=(const LLIterator<T>& other) const
{
    return !(*this == other);
}

#endif // !GUARD_LINKEDLIST_H