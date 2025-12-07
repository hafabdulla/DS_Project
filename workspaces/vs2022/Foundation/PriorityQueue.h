/*****************************************************************//**
 * @file   PriorityQueue.h
 * @brief  Binary Min-Heap implementation for Dijkstra's Algorithm.
 *
 * @author Fahad Hassan
 * @date   08 12 2025
 *********************************************************************/

#ifndef GUARD_PRIORITYQUEUE_H
#define GUARD_PRIORITYQUEUE_H

#include <stdexcept>
#include <utility>

template <typename T>
class PriorityQueue
{
private:
    T* m_Data;
    std::size_t m_Size;
    std::size_t m_Capacity;

    void resize(std::size_t new_capacity)
    {
        T* new_data = new T[new_capacity];
        for (std::size_t i = 0; i < m_Size; ++i)
        {
            new_data[i] = std::move(m_Data[i]);
        }
        delete[] m_Data;
        m_Data = new_data;
        m_Capacity = new_capacity;
    }

    void heapify_up(std::size_t index)
    {
        while (index > 0)
        {
            std::size_t parent = (index - 1) / 2;
            if (m_Data[index] < m_Data[parent])
            {
                std::swap(m_Data[index], m_Data[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapify_down(std::size_t index)
    {
        while (true)
        {
            std::size_t left = 2 * index + 1;
            std::size_t right = 2 * index + 2;
            std::size_t smallest = index;

            if (left < m_Size && m_Data[left] < m_Data[smallest])
                smallest = left;

            if (right < m_Size && m_Data[right] < m_Data[smallest])
                smallest = right;

            if (smallest != index)
            {
                std::swap(m_Data[index], m_Data[smallest]);
                index = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:
    explicit PriorityQueue(std::size_t capacity = 16)
        : m_Size(0), m_Capacity(capacity)
    {
        m_Data = new T[m_Capacity];
    }

    ~PriorityQueue()
    {
        delete[] m_Data;
    }

    bool empty() const 
    { 
        return m_Size == 0; 
    }

    std::size_t size() const 
    { 
        return m_Size; 
    }

    void push(const T& value)
    {
        if (m_Size == m_Capacity)
        {
            resize(m_Capacity * 2);
        }
        m_Data[m_Size] = value;
        heapify_up(m_Size);
        m_Size++;
    }

    void pop()
    {
        if (empty()) return;

        m_Data[0] = std::move(m_Data[m_Size - 1]);
        m_Size--;
        if (m_Size > 0)
        {
            heapify_down(0);
        }
    }

    const T& top() const
    {
        if (empty()) throw std::out_of_range("Priority Queue is empty");
        return m_Data[0];
    }
};

#endif // !GUARD_PRIORITYQUEUE_H