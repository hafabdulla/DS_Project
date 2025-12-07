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
#include "PriorityQueue.h"
#include <limits>

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

template <typename IDType>
struct DijkstraNode 
{
    IDType id;
    double dist;

    // Operator < for MinHeap (Smaller distance = Higher priority)
    bool operator<(const DijkstraNode& other) const {
        return dist < other.dist;
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

    LinkedList<IDType> GetShortestPath(const IDType& startID, const IDType& endID, double& outTotalDistance);
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

template<typename IDType, typename VertexType, typename HashFunc>
inline LinkedList<IDType> 
Graph<IDType, VertexType, HashFunc>::GetShortestPath(const IDType& startID, const IDType& endID, double& outTotalDistance)
{
    LinkedList<IDType> path;
    outTotalDistance = 0.0;

    if (!HasVertex(startID) || !HasVertex(endID)) return path;

    HashTable<IDType, double, HashFunc> distMap(200);
    HashTable<IDType, IDType, HashFunc> predMap(200);

    PriorityQueue<DijkstraNode<IDType>> pq;

    distMap.insert(startID, 0.0);
    pq.push({ startID, 0.0 });

    const double INF = std::numeric_limits<double>::max();  // infinity

    while (!pq.empty())
    {
        DijkstraNode<IDType> current = pq.top();
        pq.pop();

        if (current.id == endID) 
            break;

        if (distMap.contains(current.id) && current.dist > distMap.at(current.id))
            continue;

        const LinkedList<Edge<IDType>>* neighbors = GetNeighbors(current.id);
        if (neighbors)
        {
            for (const auto& edge : *neighbors)
            {
                double currentKnownDist = distMap.contains(edge.destination) ? distMap.at(edge.destination) : INF;
                double newDist = distMap.at(current.id) + edge.weight;

                if (newDist < currentKnownDist)
                {
                    distMap.insert(edge.destination, newDist);
                    predMap.insert(edge.destination, current.id);
                    pq.push({ edge.destination, newDist });
                }
            }
        }
    }

    if (distMap.contains(endID))
    {
        outTotalDistance = distMap.at(endID);
        IDType curr = endID;
        path.push_front(curr);

        while (curr != startID)
        {
            if (!predMap.contains(curr)) 
            { 
                path.clear(); 
                return path; 
            }
            curr = predMap.at(curr);
            path.push_front(curr);
        }
    }

    return path;
}
#endif