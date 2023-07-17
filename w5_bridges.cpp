#include <bits/stdc++.h>
using namespace std;
#define MAX_NODES 100000 

int prenum[MAX_NODES], lowest[MAX_NODES], parent[MAX_NODES]; 
bool visited[MAX_NODES]; 

class Graph
{
public: 
    int num_vertices; 
    int t;     
    vector<int> adjList[MAX_NODES]; 
    
public: 
    Graph(int num_vertices)
    {
        this->num_vertices = num_vertices;
        this->t = 0; 
    }
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v); 
        adjList[v].push_back(u); 
    }
    void dfs(int u, int p)
    {
        prenum[u] = lowest[u] = this->t; 
        (this->t)++;
        visited[u] = true;
        for (auto v: this->adjList[u]) 
        {
            if (!visited[v])
            {
                parent[v] = u; 
                dfs(v, u); 
                lowest[u] = min(lowest[u], lowest[v]); 
            }
            else if (v != p)
            {
                // edge (u, v) is a Back-edge
                lowest[u] = min(lowest[u], prenum[v]); 
            }
        }
    }
    void bridges()
    {
        this->t = 1; 
        dfs(0, -1); 
        vector<pair<int, int>> bridges; 

        for (int u = 1; u < this->num_vertices; u++)
        {
            if (lowest[u] == prenum[u])
            {
                bridges.push_back(make_pair(min(u, parent[u]), max(u, parent[u]))); 
            }
        }
        sort(bridges.begin(), bridges.end()); 
        for (auto b: bridges)
            cout << b.first << " " << b.second << endl; 
    }
};

int main() 
{
    int num_vertices, num_edges; 
    cin >> num_vertices >> num_edges;
    Graph g = Graph(num_vertices); 

    for (int i = 0; i < num_edges; i++)
    {
        int s, t; 
        cin >> s >> t; 
        g.addEdge(s, t); 
    }
    g.bridges(); 
}