class DisjointSet(): 
    def __init__(self, num_nodes):
        self.p = [i for i in range(num_nodes)]
        self.rank = [0] * num_nodes
    
    def findSet(self, x): 
        if x != self.p[x]: 
            self.p[x] = self.findSet(self.p[x])
        return self.p[x]
    
    def link(self, x, y): 
        if self.rank[x] > self.rank[y]: 
            self.p[y] = x 
        else: 
            self.p[x] = y 
            if self.rank[x] == self.rank[y]: 
                self.rank[y] += 1
    
    def union(self, x, y): 
        self.link(self.findSet(x), self.findSet(y))

class Graph(): 
    def __init__(self, num_vertices):
        self.V = num_vertices 
        self.graph = []
    
    def addEdge(self, u, v, w): 
        self.graph.append([u, v, w])
    
    def KruskalMST(self):
        # MST = []
        weight = 0 
        self.graph = sorted(self.graph, key=lambda item: item[2])

        djset = DisjointSet(self.V)

        for edge in self.graph: 
            u, v, w = edge[0], edge[1], edge[2]

            if djset.findSet(u) != djset.findSet(v): 
                djset.union(u, v)
                # MST.append([u, v])
                weight += w
        
        return weight 
    
num_vertices, num_edges = map(int, input().split(' '))

g = Graph(num_vertices)

for _ in range(num_edges): 
    u, v, w = map(int, input().split(' '))
    g.addEdge(u, v, w)

print(g.KruskalMST())