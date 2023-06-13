class Graph: 
    def __init__(self, num_nodes):
        self.num_nodes = num_nodes 
        self.graph = list(list() for _ in range(num_nodes))
    
    def add_edge(self, u, v): 
        self.graph[u].append(v)
    
    def isCyclic_util(self, v, visited, rec_stack): 
        visited[v] = True
        rec_stack[v] = True
        for neighbor in self.graph[v]: 
            if visited[neighbor] == False: 
                if self.isCyclic_util(neighbor, visited, rec_stack) == True: 
                    return True
            elif rec_stack[neighbor] == True: 
                return True  
        
        rec_stack[v] = False
        return False 
    
    def isCyclic(self): 
        visited = [False] * self.num_nodes 
        rec_stack = [False] * self.num_nodes 

        for node in range(self.num_nodes): 
            if visited[node] == False: 
                if self.isCyclic_util(node, visited, rec_stack) == True: 
                    return True 
        
        return False

V, E = map(int, input().split(' '))

g = Graph(V)
for _ in range(E): 
    u, v = map(int, input().split(' '))
    g.add_edge(u, v)

if g.isCyclic(): 
    print(1)
else: 
    print(0)