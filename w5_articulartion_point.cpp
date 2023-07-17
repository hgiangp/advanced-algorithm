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

    void art_points()
    {
        this->t = 1;
        vector<int> art_points; 
        int nc = 0;  // the number of chilren of the root

        dfs(0, -1);  // root is 0
        for (int u = 1; u < this->num_vertices; u++)
        {
            int p = parent[u]; 
            // check if whether p in art_points 
            if (find(art_points.begin(), art_points.end(), p) != art_points.end())
            {
                continue; // found 
            }
            
            if (p == 0)
                nc++;
            else if (prenum[p] <= lowest[u])
                art_points.push_back(p); 
        }

        if (nc > 1)
            art_points.push_back(0); // root is an articulation point

        sort(art_points.begin(), art_points.end()); 
        for (auto v: art_points)
            cout << v << endl; 
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
    g.art_points(); 
}