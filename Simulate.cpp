#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<random>
#include<queue>
#include "Graph_Formation.cpp"
#include "Set_Network_Charecteristics.cpp"

/*
    Namespace containing influence simulation functions of network graphs according to various models
*/

namespace Simulate 
{ 
    int S_Independent_Cascading(Graph* G, std::vector<int> seed, int k)
    {
        std::queue<int> Q;
        std::vector<int>visit;
        float prob = 0;
        int t = 0;
        for(int i=0; i < k; i++)
    {
        Q.push(seed[i]);
        visit[seed[i]] = 1;
        t++;
    }
    Network_Config::Set_Activation_Prob(G);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    // Perform a single time step of the simulation
    while (!Q.empty()) {
            int currentNode = Q.front();
            Q.pop();
            Node* n,*x;
                for(auto& node: G->nodes)
                {
                    if(node.second.id == currentNode)
                    {
                        n = &node.second;
                        break;
                    }
                }
            for (auto edge : G->Edges) {
                if(edge.source == n->id)
                {
                for(auto& node: G->nodes)
                {
                    if(node.second.id == edge.target)
                    {
                        x = &node.second;
                        break;
                    }
                }
                if (x->state == 0) {
                    // Check if the neighbor gets activated
                    double randomProb = static_cast<double>(rand()) / RAND_MAX;
                    if (randomProb >= edge.prob) {
                        x->state = 1;
                        Q.push(x->id);
                        visit[x->id] = 1;
                    }
                }
            }
            }
            }
        }

    int S_Linear_Thershold(Graph* G, std::vector<int> seed, int k)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        int t = 0;
        for(auto& node: G->nodes)
            {
                if(find(seed.begin(), seed.end(), node.second.id) != seed.end())
                {
                    node.second.state = 1;
                }
            }
        Network_Config::Set_Threshold(G);
        // Perform a single time step of the simulation
        auto simulateStep = [&](std::vector<Edge>& edges, std::unordered_map<int, Node>& nodes) {
            for (auto& node : nodes) {
                if (node.second.state == 0) {
                    float totalWeight = 0;
                    float activeWeight = 0;

                for (const Edge& edge : edges) {
                    if (edge.target == node.first) {
                        totalWeight += edge.weight;
                        if (nodes[edge.source].state == 1) {
                            activeWeight += edge.weight;
                        }
                    }
                }

                float activationProb = activeWeight / totalWeight;

                if (dis(gen) <= activationProb && activationProb >= node.second.threshold) {
                    node.second.state = 1;
                    t += 1;
                }
            }
        }
    };

    // Run the simulation until convergence
    while (true) {
        std::unordered_map<int, Node> oldNodes = G->nodes;
        simulateStep(G->Edges, G->nodes);
        if (oldNodes == G->nodes) {
            break;
        }
    }
    return t;
    }
}