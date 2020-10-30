#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node
{
    vector<struct Edge*> mEdges;
};

struct Edge
{
    Node* mFrom;
    Node* mTo;
    
    float mWeight;
};

struct Graph
{
    vector<Node*> mNodes;
};

struct AStarScratch
{
    const Edge* mParentEdge = nullptr;
    
    float mHeuristic = 0.f;
    float mPathCost = 0.f;
    
    bool mInOpenSet = false;
    bool mInClosedSet = false;
};

float ManhattanHeuristic(const Node* start, const Node* goal)
{
    return 0.f;
}

using AStarMap = unordered_map<const Node*, AStarScratch>;

bool AStar(const Graph& graph, const Node* start, const Node* goal, AStarMap& outMap)
{
    vector<const Node*> openSet;
    
    const Node* current = start;
    outMap[current].mInClosedSet = true;
    
    do
    {
        for (const Edge* edge : current->mEdges)
        {
            const Node* neighbor = edge->mTo;
            AStarScratch& data = outMap[neighbor];
            
            if (!data.mInClosedSet)
            {
                if (!data.mInOpenSet)
                {
                    data.mParentEdge = edge;
                    data.mHeuristic = ManhattanHeuristic(neighbor, goal);
                    data.mPathCost = outMap[current].mPathCost + edge->mWeight;
                    data.mInOpenSet = true;
                    openSet.emplace_back(neighbor);
                }
                else
                {
                    float newPathCost = outMap[current].mPathCost + edge->mWeight;
                    if (newPathCost < data.mPathCost)
                    {
                        data.mParentEdge = edge;
                        data.mPathCost = newPathCost;
                    }
                }
            }
        }
        
        if (openSet.empty())
            break;
        
        auto iter = min_element(openSet.begin(), openSet.end(), [&outMap](const Node* a, const Node* b){
            float fa = outMap[a].mHeuristic + outMap[a].mPathCost;
            float fb = outMap[b].mHeuristic + outMap[b].mPathCost;
            return fa < fb;
        });
        
        current = *iter;
        openSet.erase(iter);
        outMap[current].mInOpenSet = true;
        outMap[current].mInClosedSet = true;
    } while (current != goal);
    
    return (current == goal);
}
