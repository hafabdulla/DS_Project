/*****************************************************************//**
 * @file   Graph.h
 * @brief  Weighted graph implementaiton.
 * 
 * @author Fahad Hassan
 * @date   08 12 2025
 *********************************************************************/

#ifndef GUARD_GRAPH_H
#define GUARD_GRAPH_H

#include "LinkedList.h"
#include "HashTable.h"

template <typename IDType>
struct Edge
{
    IDType destination;
    double weight;

    Edge() : weight(0.0) {}
    Edge(const IDType& dest, double weight) : destination(dest), weight(weight) {}

    bool operator==(const Edge& other) const
    {
        return destination == other.destination;
    }
};

template <typename IDType, typename VertexType, typename HashFunc>
class Graph
{
private:
    HashTable<IDType, VertexType, HashFunc> m_Vertices;
    HashTable<IDType, LinkedList<Edge<IDType>>, HashFunc> m_AdjacencyList;

public:
    explicit Graph(std::size_t capacity = 101);
    ~Graph() = default;

    void AddVertex(const IDType& id, const VertexType& vertex);
    void AddEdge(const IDType& sourceID, const IDType& destID, double weight);
    bool HasVertex(const IDType& id) const;
    VertexType* GetVertex(const IDType& id);
    const LinkedList<Edge<IDType>>* GetNeighbors(const IDType& id) const;
};

template<typename IDType, typename VertexType, typename HashFunc>
inline Graph<IDType, VertexType, HashFunc>::Graph(std::size_t capacity)
    : m_Vertices(capacity), m_AdjacencyList(capacity)
{
}

template<typename IDType, typename VertexType, typename HashFunc>
inline void Graph<IDType, VertexType, HashFunc>::AddVertex(const IDType& id, const VertexType& vertex)
{
    if (!m_Vertices.contains(id))
    {
        m_Vertices.insert(id, vertex);
        m_AdjacencyList.insert(id, LinkedList<Edge<IDType>>());
    }
}

template<typename IDType, typename VertexType, typename HashFunc>
inline void Graph<IDType, VertexType, HashFunc>::AddEdge(const IDType& sourceID, const IDType& destID, double weight)
{
    if (m_Vertices.contains(sourceID) && m_Vertices.contains(destID))
    {
        m_AdjacencyList[sourceID].push_back(Edge<IDType>(destID, weight));
    }
}

template<typename IDType, typename VertexType, typename HashFunc>
inline bool Graph<IDType, VertexType, HashFunc>::HasVertex(const IDType& id) const
{
    return m_Vertices.contains(id);
}

template<typename IDType, typename VertexType, typename HashFunc>
inline VertexType* Graph<IDType, VertexType, HashFunc>::GetVertex(const IDType& id)
{
    if (m_Vertices.contains(id))
    {
        return &m_Vertices.at(id);
    }
    return nullptr;
}

template<typename IDType, typename VertexType, typename HashFunc>
inline const LinkedList<Edge<IDType>>* Graph<IDType, VertexType, HashFunc>::GetNeighbors(const IDType& id) const
{
    if (m_AdjacencyList.contains(id))
    {
        return &m_AdjacencyList.at(id);
    }
    return nullptr;
}

#endif