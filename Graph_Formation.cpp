#ifndef _GRAPH_FORMATION_
#define _GRAPH_FORMATION_
#include <iostream>
#include<unordered_map>
#include <fstream>
#include <vector>
#include <utility>
#define V 70409

class Edge
{
    public:
    int source;
    int target;
    float weight;
    float prob = 0;

    Edge(int _source, int _target, float _weight) : source(_source), target(_target), weight(_weight) {}
};

class Node 
{
public:
    int id;
    float threshold; // for implementing linear cascading model
    int state;

    Node(int _id, float _threshold, int _state) : id(_id), threshold(_threshold), state(_state) {}
    /*Node(int _id, int _state) : id(_id), state(_state) {
        threshold = 0;
    }*/
};

class Graph
{
    public:
    //std::vector<std::vector<int>> A; //Adjacency Matrix
    std::vector<Edge> Edges; 
    std::unordered_map<int, Node> nodes;
    std::vector<int> degin;
    std::vector<int> degout;
    int v,e;
    Graph(FILE* fp)
    {
        int s,t;
        double w;
        for (int i = 0; i < V; i++) 
        {
        std::vector<int> row;
        degin.push_back(0);
        degout.push_back(0);
        /*for (int j = 0; j < V; j++) 
        {
            row.push_back(0); // Add 0 to each column
        }
        A.push_back(row); // Add the row to the 2D vector*/
        }
        fscanf(fp, "%d %d\n",&v,&e);
        int j = 0;
        for(int i=0; i<e; i++)
        {
            fscanf(fp, "%d %d %lf\n",&s,&t,&w);
            if(s<=V && t<=V)
            {
                if(nodes.find(s) == nodes.end())
                {
                    nodes.insert({j++,Node(s,0,0)});
                }
                if(nodes.find(t) == nodes.end())
                {
                    nodes.insert({j++,Node(t,0,0)});
                }
                Edges.push_back(Edge(s,t,w));
                //std::cout<<A[s][t]<<" "<<w<<"\n";
                degin[t]++;
                degout[s]++;
            }
        }
    }
};

int main()
{
    FILE* fp = fopen("Network_IC-u_LT-u.txt","r");
    Graph* G = new Graph(fp);
    for(int i=0; i<G->Edges.size(); i++)
    {
        std::cout<<G->Edges[i].source<<" "<<G->Edges[i].target<<"\n";
    }
    for (const auto& node : G->nodes) {
        std::cout << node.second.id << " " << node.second.state << "\n";
    }
   /* for(int i=0; i<G->A.size(); i++)
    {
        for(int j=0; j<G->A[i].size(); j++)
        {
            G->A[i][j] > 0 ? 1 : 0;
        }
        std::cout<<"\n";
    }//*/
    fclose(fp);
}
#endif