/*****************************************************************//**
 * @file   Tree.h
 * @brief  N-ary tree using key
 * 
 * @author Fahad Hassan
 * @date   07 12 2025
 *********************************************************************/

#ifndef GUARD_TREE_H
#define GUARD_TREE_H

#include "LinkedList.h"
#include <utility>
#include <cstddef>
#include <stdexcept>

template<typename K, typename V>
class Tree
{
    struct Node
    {
        K key;
        V value;
        Node* parent;
        LinkedList<Node*> children;

        Node(const K& k, const V& v, Node* par = nullptr)
            : key(k), value(v), parent(par) 
        {
        }
    };

private:
    Node* m_Root;
    std::size_t m_Size;

    void destroySubtree(Node* node);
    Node* findNode(Node* current, const K& key);
    Node* copySubtree(Node* source, Node* parent);

    template<typename Func>
    void preOrderTraversalImpl(Node* node, Func& visit) const;

public:
    Tree();
    ~Tree();

    Tree(const Tree<K, V>& other);
    Tree(Tree<K, V>&& other) noexcept;
    Tree<K, V>& operator=(Tree<K, V> other);

    void AddRoot(const K& key, const V& value);
    void AddChild(const K& parentKey, const K& childKey, const V& childValue);

    bool Contains(const K& key) const;
    const V& GetValue(const K& key) const;
    V& GetValue(const K& key);

    template<typename Func>
    void PreOrderTraversal(Func visit) const;

    template<typename Func>
    void TraverseSubtree(const K& subRootKey, Func visit) const;

    bool IsEmpty() const noexcept;
    std::size_t Size() const noexcept;
    void Clear();
    void Swap(Tree<K, V>& other) noexcept;
};

template<typename K, typename V>
inline Tree<K, V>::Tree()
    : m_Root(nullptr), m_Size(0)
{
}

template<typename K, typename V>
inline Tree<K, V>::~Tree()
{
    Clear();
}

template<typename K, typename V>
inline Tree<K, V>::Tree(const Tree<K, V>& other)
    : m_Root(nullptr), m_Size(0)
{
    if (other.m_Root)
    {
        m_Root = copySubtree(other.m_Root, nullptr);
        m_Size = other.m_Size;
    }
}

template<typename K, typename V>
inline Tree<K, V>::Tree(Tree<K, V>&& other) noexcept
    : m_Root(other.m_Root), m_Size(other.m_Size)
{
    other.m_Root = nullptr;
    other.m_Size = 0;
}

template<typename K, typename V>
inline Tree<K, V>& Tree<K, V>::operator=(Tree<K, V> other)
{
    Swap(other);
    return *this;
}

template<typename K, typename V>
inline void Tree<K, V>::destroySubtree(Node* node)
{
    if (!node) return;

    for (Node* child : node->children)
    {
        destroySubtree(child);
    }

    delete node;
}

template<typename K, typename V>
inline typename Tree<K, V>::Node*
Tree<K, V>::copySubtree(Node* source, Node* parent)
{
    if (!source) return nullptr;

    Node* newNode = new Node(source->key, source->value, parent);

    for (Node* child : source->children)
    {
        Node* newChild = copySubtree(child, newNode);
        newNode->children.push_back(newChild);
    }

    return newNode;
}

template<typename K, typename V>
inline typename Tree<K, V>::Node*
Tree<K, V>::findNode(Node* current, const K& key)
{
    if (!current) return nullptr;

    if (current->key == key)
        return current;

    for (Node* child : current->children)
    {
        Node* found = findNode(child, key);
        if (found) return found;
    }

    return nullptr;
}

template<typename K, typename V>
inline void Tree<K, V>::AddRoot(const K& key, const V& value)
{
    if (m_Root)
        throw std::logic_error("Tree already has a root");

    m_Root = new Node(key, value, nullptr);
    m_Size++;
}

template<typename K, typename V>
inline void Tree<K, V>::AddChild(const K& parentKey, const K& childKey, const V& childValue)
{
    Node* parent = findNode(m_Root, parentKey);
    if (!parent)
        throw std::invalid_argument("Parent node with given key not found");

    Node* newChild = new Node(childKey, childValue, parent);
    parent->children.push_back(newChild);
    m_Size++;
}

template<typename K, typename V>
inline bool Tree<K, V>::Contains(const K& key) const
{
    return const_cast<Tree*>(this)->findNode(m_Root, key) != nullptr;
}

template<typename K, typename V>
inline const V& Tree<K, V>::GetValue(const K& key) const
{
    Node* node = const_cast<Tree*>(this)->findNode(m_Root, key);
    if (!node)
        throw std::out_of_range("Key not found in tree");

    return node->value;
}

template<typename K, typename V>
inline V& Tree<K, V>::GetValue(const K& key)
{
    Node* node = findNode(m_Root, key);

    if (!node)
        throw std::out_of_range("Key not found in tree");

    return node->value;
}

template<typename K, typename V>
inline bool Tree<K, V>::IsEmpty() const noexcept
{
    return m_Root == nullptr;
}

template<typename K, typename V>
inline std::size_t Tree<K, V>::Size() const noexcept
{
    return m_Size;
}

template<typename K, typename V>
inline void Tree<K, V>::Clear()
{
    destroySubtree(m_Root);
    m_Root = nullptr;
    m_Size = 0;
}

template<typename K, typename V>
inline void Tree<K, V>::Swap(Tree<K, V>& other) noexcept
{
    std::swap(m_Root, other.m_Root);
    std::swap(m_Size, other.m_Size);
}

template<typename K, typename V>
template<typename Func>
inline void Tree<K, V>::preOrderTraversalImpl(Node* node, Func& visit) const
{
    if (!node) return;

    visit(node->key, node->value);

    for (Node* child : node->children)
    {
        preOrderTraversalImpl(child, visit);
    }
}

template<typename K, typename V>
template<typename Func>
inline void Tree<K, V>::PreOrderTraversal(Func visit) const
{
    preOrderTraversalImpl(m_Root, visit);
}

template<typename K, typename V>
template<typename Func>
inline void Tree<K, V>::TraverseSubtree(const K& subRootKey, Func visit) const
{
    Node* subRoot = const_cast<Tree*>(this)->findNode(m_Root, subRootKey);

    if (subRoot)
    {
        preOrderTraversalImpl(subRoot, visit);
    }
}

template<typename K, typename V>
void swap(Tree<K, V>& left, Tree<K, V>& right) noexcept
{
    left.Swap(right);
}

#endif // !GUARD_TREE_H