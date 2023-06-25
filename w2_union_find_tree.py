num_nodes, num_queries = map(int, input().split(' '))

p = [i for i in range(num_nodes)]
rank = [0] * num_nodes
weight = [0] * num_nodes 

def findSet(x): 
    if p[x] == x:
        return x
    y = findSet(p[x])
    weight[x] += weight[p[x]]  
    p[x] = y 
    return y
     

def link(x, y, w): 
    if rank[x] > rank[y]: 
        p[y] = x
        weight[y] -= w 
    else: 
        p[x] = y 
        weight[x] += w 
        if rank[x] == rank[y]: 
            rank[y] += 1 

def union(x, y, w): 
    rootx = findSet(x)
    rooty = findSet(y)
    w_diff = - weight[x] + weight[y] + w 
    # if rootx != rooty:
    link(rootx, rooty, w_diff)

def same(x, y): 
    return findSet(x) == findSet(y)

l = [input() for _ in range(num_queries)]

for i in range(num_queries):
    tmp = tuple(map(int, l[i].split(' ')))
    u, v = tmp[1]-1, tmp[2]-1
    if tmp[0] == 0:
        union(u, v, tmp[3]) 
    elif tmp[0] == 1: 
        if same(u, v): 
            print(weight[u] - weight[v]) 
        else:
            print('?')