/*****************************************************************//**
 * @file   HashTable.h
 * @brief  A generic Hash Table using Separate Chaining with linked lists.
 *
 * @author Fahad Hassan
 * @date   02 12 2025
 *********************************************************************/

#ifndef GUARD_HASHTABLE_H
#define GUARD_HASHTABLE_H

#include <Foundation/LinkedList.h>
#include <utility>
#include <cstddef>
#include <stdexcept>

template<typename Key, typename Value, typename HashFunc>
class HTIterator;

template<typename Key, typename Value, typename HashFunc>
class HashTable
{
    struct Entry
    {
        Key key;
        Value value;

        Entry(const Key& k, const Value& v) : key(k), value(v) {}

        bool operator==(const Entry& other) const
        {
            return key == other.key;
        }
    };

    friend class HTIterator<Key, Value, HashFunc>;

private:
    LinkedList<Entry>* m_Table;
    std::size_t m_Capacity;
    std::size_t m_Size;
    HashFunc m_HashFunc;

    std::size_t hash(const Key& key) const;
    void rehash(std::size_t new_capacity);

public:
    explicit HashTable(std::size_t capacity = 101);
    ~HashTable();

    HashTable(const HashTable<Key, Value, HashFunc>& other);
    HashTable(HashTable<Key, Value, HashFunc>&& other) noexcept;
    HashTable<Key, Value, HashFunc>& operator=(HashTable<Key, Value, HashFunc> other);

    Value& at(const Key& key);
    const Value& at(const Key& key) const;

    Value& operator[](const Key& key);

    bool contains(const Key& key) const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    float load_factor() const noexcept;

    void insert(const Key& key, const Value& value);
    void insert(Key&& key, Value&& value);

    template<typename... Args>
    void emplace(const Key& key, Args&&... args);

    bool erase(const Key& key);
    void clear() noexcept;

    HTIterator<Key, Value, HashFunc> begin();
    HTIterator<Key, Value, HashFunc> end();
    const HTIterator<Key, Value, HashFunc> begin() const;
    const HTIterator<Key, Value, HashFunc> end() const;
    const HTIterator<Key, Value, HashFunc> cbegin() const;
    const HTIterator<Key, Value, HashFunc> cend() const;

    void swap(HashTable<Key, Value, HashFunc>& other) noexcept;
};

template<typename Key, typename Value, typename HashFunc>
class HTIterator
{
    using BucketIterator = LLIterator<typename HashTable<Key, Value, HashFunc>::Entry>;

private:
    LinkedList<typename HashTable<Key, Value, HashFunc>::Entry>* m_Table;
    std::size_t m_Capacity;
    std::size_t m_BucketIndex;
    BucketIterator m_BucketIterator;

    void advance_to_next_valid();

public:
    HTIterator(LinkedList<typename HashTable<Key, Value, HashFunc>::Entry>* table,
        std::size_t capacity,
        std::size_t bucket_index,
        BucketIterator bucket_iter);

    HTIterator<Key, Value, HashFunc>& operator++();
    HTIterator<Key, Value, HashFunc> operator++(int);

    typename HashTable<Key, Value, HashFunc>::Entry& operator*() noexcept;
    const typename HashTable<Key, Value, HashFunc>::Entry& operator*() const noexcept;

    typename HashTable<Key, Value, HashFunc>::Entry* operator->() noexcept;
    const typename HashTable<Key, Value, HashFunc>::Entry* operator->() const noexcept;

    bool operator==(const HTIterator<Key, Value, HashFunc>& other) const;
    bool operator!=(const HTIterator<Key, Value, HashFunc>& other) const;
};

template<typename Key, typename Value, typename HashFunc>
void swap(HashTable<Key, Value, HashFunc>& left, HashTable<Key, Value, HashFunc>& right) noexcept;

template<typename Key, typename Value, typename HashFunc>
inline std::size_t HashTable<Key, Value, HashFunc>::hash(const Key& key) const
{
    return m_HashFunc(key) % m_Capacity;
}

template<typename Key, typename Value, typename HashFunc>
inline void HashTable<Key, Value, HashFunc>::rehash(std::size_t new_capacity)
{
    LinkedList<Entry>* old_table = m_Table;
    std::size_t old_capacity = m_Capacity;

    m_Capacity = new_capacity;
    m_Table = new LinkedList<Entry>[m_Capacity];
    m_Size = 0;

    for (std::size_t i = 0; i < old_capacity; ++i)
    {
        for (auto& entry : old_table[i])
        {
            insert(entry.key, entry.value);
        }
    }

    delete[] old_table;
}

template<typename Key, typename Value, typename HashFunc>
inline HashTable<Key, Value, HashFunc>::HashTable(std::size_t capacity)
    : m_Capacity(capacity), m_Size(0)
{
    m_Table = new LinkedList<Entry>[m_Capacity];
}

template<typename Key, typename Value, typename HashFunc>
inline HashTable<Key, Value, HashFunc>::~HashTable()
{
    delete[] m_Table;
}

template<typename Key, typename Value, typename HashFunc>
inline HashTable<Key, Value, HashFunc>::HashTable(const HashTable<Key, Value, HashFunc>& other)
    : m_Capacity(other.m_Capacity), m_Size(other.m_Size)
{
    m_Table = new LinkedList<Entry>[m_Capacity];

    for (std::size_t i = 0; i < m_Capacity; ++i)
    {
        m_Table[i] = other.m_Table[i];
    }
}

template<typename Key, typename Value, typename HashFunc>
inline HashTable<Key, Value, HashFunc>::HashTable(HashTable<Key, Value, HashFunc>&& other) noexcept
    : m_Table(other.m_Table), m_Capacity(other.m_Capacity), m_Size(other.m_Size)
{
    other.m_Table = nullptr;
    other.m_Capacity = 0;
    other.m_Size = 0;
}

template<typename Key, typename Value, typename HashFunc>
inline HashTable<Key, Value, HashFunc>& HashTable<Key, Value, HashFunc>::operator=(HashTable<Key, Value, HashFunc> other)
{
    swap(other);
    return *this;
}

template<typename Key, typename Value, typename HashFunc>
inline bool HashTable<Key, Value, HashFunc>::empty() const noexcept
{
    return m_Size == 0;
}

template<typename Key, typename Value, typename HashFunc>
inline std::size_t HashTable<Key, Value, HashFunc>::size() const noexcept
{
    return m_Size;
}

template<typename Key, typename Value, typename HashFunc>
inline std::size_t HashTable<Key, Value, HashFunc>::capacity() const noexcept
{
    return m_Capacity;
}

template<typename Key, typename Value, typename HashFunc>
inline float HashTable<Key, Value, HashFunc>::load_factor() const noexcept
{
    return static_cast<float>(m_Size) / static_cast<float>(m_Capacity);
}

template<typename Key, typename Value, typename HashFunc>
inline bool HashTable<Key, Value, HashFunc>::contains(const Key& key) const
{
    std::size_t index = hash(key);

    for (const auto& entry : m_Table[index])
    {
        if (entry.key == key)
            return true;
    }

    return false;
}

template<typename Key, typename Value, typename HashFunc>
inline Value& HashTable<Key, Value, HashFunc>::at(const Key& key)
{
    std::size_t index = hash(key);

    for (auto& entry : m_Table[index])
    {
        if (entry.key == key)
            return entry.value;
    }

    throw std::out_of_range("Key not found in hash table");
}

template<typename Key, typename Value, typename HashFunc>
inline const Value& HashTable<Key, Value, HashFunc>::at(const Key& key) const
{
    std::size_t index = hash(key);

    for (const auto& entry : m_Table[index])
    {
        if (entry.key == key)
            return entry.value;
    }

    throw std::out_of_range("Key not found in hash table");
}

template<typename Key, typename Value, typename HashFunc>
inline Value& HashTable<Key, Value, HashFunc>::operator[](const Key& key)
{
    std::size_t index = hash(key);

    for (auto& entry : m_Table[index])
    {
        if (entry.key == key)
            return entry.value;
    }

    m_Table[index].emplace_back(key, Value());
    m_Size++;

    return m_Table[index].back().value;
}

template<typename Key, typename Value, typename HashFunc>
inline void HashTable<Key, Value, HashFunc>::insert(const Key& key, const Value& value)
{
    if (load_factor() > 0.75f)
    {
        rehash(m_Capacity * 2);
    }

    std::size_t index = hash(key);

    for (auto& entry : m_Table[index])
    {
        if (entry.key == key)
        {
            entry.value = value;
            return;
        }
    }

    m_Table[index].emplace_back(key, value);
    m_Size++;
}

template<typename Key, typename Value, typename HashFunc>
inline void HashTable<Key, Value, HashFunc>::insert(Key&& key, Value&& value)
{
    std::size_t index = hash(key);

    for (auto& entry : m_Table[index])
    {
        if (entry.key == key)
        {
            entry.value = std::move(value);
            return;
        }
    }

    m_Table[index].emplace_back(std::move(key), std::move(value));
    m_Size++;
}

template<typename Key, typename Value, typename HashFunc>
template<typename... Args>
inline void HashTable<Key, Value, HashFunc>::emplace(const Key& key, Args&&... args)
{
    std::size_t index = hash(key);

    for (auto& entry : m_Table[index])
    {
        if (entry.key == key)
        {
            entry.value = Value(std::forward<Args>(args)...);
            return;
        }
    }

    m_Table[index].emplace_back(key, Value(std::forward<Args>(args)...));
    m_Size++;
}

template<typename Key, typename Value, typename HashFunc>
inline bool HashTable<Key, Value, HashFunc>::erase(const Key& key)
{
    std::size_t index = hash(key);
    LinkedList<Entry>& bucket = m_Table[index];

    auto it = bucket.begin();
    auto prev = bucket.end();

    while (it != bucket.end())
    {
        if ((*it).key == key)
        {
            LinkedList<Entry> new_bucket;
            for (auto& entry : bucket)
            {
                if (!(entry.key == key))
                    new_bucket.push_back(entry);
            }

            bucket = std::move(new_bucket);
            m_Size--;
            return true;
        }
        ++it;
    }

    return false;
}

template<typename Key, typename Value, typename HashFunc>
inline void HashTable<Key, Value, HashFunc>::clear() noexcept
{
    for (std::size_t i = 0; i < m_Capacity; ++i)
    {
        m_Table[i].clear();
    }

    m_Size = 0;
}

template<typename Key, typename Value, typename HashFunc>
inline void HashTable<Key, Value, HashFunc>::swap(HashTable<Key, Value, HashFunc>& other) noexcept
{
    using std::swap;
    swap(this->m_Table, other.m_Table);
    swap(this->m_Capacity, other.m_Capacity);
    swap(this->m_Size, other.m_Size);
}

template<typename Key, typename Value, typename HashFunc>
inline void swap(HashTable<Key, Value, HashFunc>& left, HashTable<Key, Value, HashFunc>& right) noexcept
{
    left.swap(right);
}

template<typename Key, typename Value, typename HashFunc>
inline HTIterator<Key, Value, HashFunc>::HTIterator(
    LinkedList<typename HashTable<Key, Value, HashFunc>::Entry>* table,
    std::size_t capacity,
    std::size_t bucket_index,
    BucketIterator bucket_iter)
    : m_Table(table), m_Capacity(capacity), m_BucketIndex(bucket_index), m_BucketIterator(bucket_iter)
{
}

template<typename Key, typename Value, typename HashFunc>
inline void HTIterator<Key, Value, HashFunc>::advance_to_next_valid()
{
    ++m_BucketIterator;

    while (m_BucketIterator == m_Table[m_BucketIndex].end())
    {
        ++m_BucketIndex;

        if (m_BucketIndex >= m_Capacity)
            return;

        m_BucketIterator = m_Table[m_BucketIndex].begin();
    }
}

template<typename Key, typename Value, typename HashFunc>
inline HTIterator<Key, Value, HashFunc>& HTIterator<Key, Value, HashFunc>::operator++()
{
    advance_to_next_valid();
    return *this;
}

template<typename Key, typename Value, typename HashFunc>
inline HTIterator<Key, Value, HashFunc> HTIterator<Key, Value, HashFunc>::operator++(int)
{
    HTIterator temp = *this;
    advance_to_next_valid();
    return temp;
}

template<typename Key, typename Value, typename HashFunc>
inline typename HashTable<Key, Value, HashFunc>::Entry& HTIterator<Key, Value, HashFunc>::operator*() noexcept
{
    return *m_BucketIterator;
}

template<typename Key, typename Value, typename HashFunc>
inline const typename HashTable<Key, Value, HashFunc>::Entry& HTIterator<Key, Value, HashFunc>::operator*() const noexcept
{
    return *m_BucketIterator;
}

template<typename Key, typename Value, typename HashFunc>
inline typename HashTable<Key, Value, HashFunc>::Entry* HTIterator<Key, Value, HashFunc>::operator->() noexcept
{
    return &(*m_BucketIterator);
}

template<typename Key, typename Value, typename HashFunc>
inline const typename HashTable<Key, Value, HashFunc>::Entry* HTIterator<Key, Value, HashFunc>::operator->() const noexcept
{
    return &(*m_BucketIterator);
}

template<typename Key, typename Value, typename HashFunc>
inline bool HTIterator<Key, Value, HashFunc>::operator==(const HTIterator<Key, Value, HashFunc>& other) const
{
    return m_BucketIndex == other.m_BucketIndex && m_BucketIterator == other.m_BucketIterator;
}

template<typename Key, typename Value, typename HashFunc>
inline bool HTIterator<Key, Value, HashFunc>::operator!=(const HTIterator<Key, Value, HashFunc>& other) const
{
    return !(*this == other);
}

template<typename Key, typename Value, typename HashFunc>
inline HTIterator<Key, Value, HashFunc> HashTable<Key, Value, HashFunc>::begin()
{
    for (std::size_t i = 0; i < m_Capacity; ++i)
    {
        if (!m_Table[i].empty())
        {
            return HTIterator<Key, Value, HashFunc>(m_Table, m_Capacity, i, m_Table[i].begin());
        }
    }

    return end();
}

template<typename Key, typename Value, typename HashFunc>
inline HTIterator<Key, Value, HashFunc> HashTable<Key, Value, HashFunc>::end()
{
    return HTIterator<Key, Value, HashFunc>(m_Table, m_Capacity, m_Capacity, LLIterator<Entry>(nullptr));
}

template<typename Key, typename Value, typename HashFunc>
inline const HTIterator<Key, Value, HashFunc> HashTable<Key, Value, HashFunc>::begin() const
{
    for (std::size_t i = 0; i < m_Capacity; ++i)
    {
        if (!m_Table[i].empty())
        {
            return HTIterator<Key, Value, HashFunc>(m_Table, m_Capacity, i, m_Table[i].begin());
        }
    }

    return end();
}

template<typename Key, typename Value, typename HashFunc>
inline const HTIterator<Key, Value, HashFunc> HashTable<Key, Value, HashFunc>::end() const
{
    return HTIterator<Key, Value, HashFunc>(m_Table, m_Capacity, m_Capacity, LLIterator<Entry>(nullptr));
}

template<typename Key, typename Value, typename HashFunc>
inline const HTIterator<Key, Value, HashFunc> HashTable<Key, Value, HashFunc>::cbegin() const
{
    return begin();
}

template<typename Key, typename Value, typename HashFunc>
inline const HTIterator<Key, Value, HashFunc> HashTable<Key, Value, HashFunc>::cend() const
{
    return end();
}

#endif // !GUARD_HASHTABLE_H