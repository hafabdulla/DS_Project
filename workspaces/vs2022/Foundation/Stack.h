/*****************************************************************//**
 * @file   Stack.h
 * @brief  Adapter for Deque.h to provide a stack interface.
 * 
 * @author Fahad Hassan
 * @date   06 12 2025
 *********************************************************************/

#ifndef GUARD_STACK_H
#define GUARD_STACK_H

#include "Deque.h"

template<typename T>
class StackIterator;

template<typename T>
class Stack : private Deque<T>
{
public:
    Stack() = default;
    ~Stack() = default;

    Stack(const Stack<T>& other)     : Deque<T>(other) {}
    Stack(Stack<T>&& other) noexcept : Deque<T>(std::move(other)) {}
    Stack<T>& operator=(Stack<T> other);

    void push(const T& value);
    void push(T&& value);
    template<typename... Args>
    void emplace(Args&&... args);
    void pop();
    T& top();
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;
    void swap(Stack<T>& other) noexcept;

    StackIterator<T> begin();
    StackIterator<T> end();
    const StackIterator<T> begin() const;
    const StackIterator<T> end() const;
    const StackIterator<T> cbegin() const;
    const StackIterator<T> cend() const;
};

template<typename T>
void swap(Stack<T>& left, Stack<T>& right) noexcept;

template<typename T>
class StackIterator
{
    using DequeIter = DEQIterator<T>;

private:
    DequeIter m_Iterator;

public:
    StackIterator(DequeIter iter) : m_Iterator(iter) {}

    StackIterator<T>& operator++();
    StackIterator<T> operator++(int);

    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;

    bool operator==(const StackIterator<T>& other) const;
    bool operator!=(const StackIterator<T>& other) const;
};

template<typename T>
inline Stack<T>& Stack<T>::operator=(Stack<T> other)
{
    Deque<T>::operator=(std::move(other));
    return *this;
}

template<typename T>
inline void Stack<T>::push(const T& value)
{
    Deque<T>::push_back(value);
}

template<typename T>
inline void Stack<T>::push(T&& value)
{
    Deque<T>::push_back(std::move(value));
}

template<typename T>
inline void Stack<T>::pop()
{
    Deque<T>::pop_back();
}

template<typename T>
template<typename ...Args>
inline void Stack<T>::emplace(Args && ...args)
{
    Deque<T>::emplace_back(std::forward<Args>(args)...);
}

template<typename T>
inline T& Stack<T>::top()
{
    return Deque<T>::back();
}

template<typename T>
inline bool Stack<T>::empty() const noexcept
{
    return Deque<T>::empty();
}

template<typename T>
inline std::size_t Stack<T>::size() const noexcept
{
    return Deque<T>::size();
}
template<typename T>
inline void Stack<T>::clear() noexcept
{
    Deque<T>::clear();
}

template<typename T>
inline void Stack<T>::swap(Stack<T>& other) noexcept
{
    Deque<T>::swap(other);
}

template<typename T>
inline StackIterator<T> Stack<T>::begin()
{
    return StackIterator<T>(Deque<T>::begin());
}

template<typename T>
inline StackIterator<T> Stack<T>::end()
{
    return StackIterator<T>(Deque<T>::end());
}

template<typename T>
inline const StackIterator<T> Stack<T>::begin() const
{
    return StackIterator<T>(Deque<T>::begin());
}

template<typename T>
inline const StackIterator<T> Stack<T>::end() const
{
    return StackIterator<T>(Deque<T>::end());
}

template<typename T>
inline const StackIterator<T> Stack<T>::cbegin() const
{
    return StackIterator<T>(Deque<T>::cbegin());
}

template<typename T>
inline const StackIterator<T> Stack<T>::cend() const
{
    return StackIterator<T>(Deque<T>::cend());
}

template<typename T>
inline void swap(Stack<T>& left, Stack<T>& right) noexcept
{
    left.swap(right);
}

template<typename T>
inline StackIterator<T>& StackIterator<T>::operator++()
{
    ++m_Iterator;
    return *this;
}

template<typename T>
inline StackIterator<T> StackIterator<T>::operator++(int)
{
    StackIterator temp = *this;
    ++m_Iterator;
    return temp;
}

template<typename T>
inline T& StackIterator<T>::operator*()
{
    return *m_Iterator;
}

template<typename T>
inline const T& StackIterator<T>::operator*() const
{
    return *m_Iterator;
}

template<typename T>
inline T* StackIterator<T>::operator->()
{
    return m_Iterator.operator->();
}

template<typename T>
inline const T* StackIterator<T>::operator->() const
{
    return m_Iterator.operator->();
}

template<typename T>
inline bool StackIterator<T>::operator==(const StackIterator<T>& other) const
{
    return m_Iterator == other.m_Iterator;
}

template<typename T>
inline bool StackIterator<T>::operator!=(const StackIterator<T>& other) const
{
    return m_Iterator != other.m_Iterator;
}

#endif // !GUARD_STACK_H