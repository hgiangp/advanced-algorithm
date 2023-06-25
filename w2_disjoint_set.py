num_nodes, num_queries = map(int, input().split(' '))

p = [i for i in range(num_nodes)]
rank = [0] * num_nodes

def find_set(x): 
    if x != p[x]: 
        p[x] = find_set(p[x])
    return p[x]

def link(x, y): 
    if rank[x] > rank[y]: 
        p[y] = x 
    else: 
        p[x] = y 
        if rank[x] == rank[y]: 
            rank[y] += 1 

def union(x, y): 
    link(find_set(x), find_set(y))

def same(x, y): 
    return find_set(x) == find_set(y)

for _ in range(num_queries): 
    op, x, y = map(int, input().split(' '))
    if op == 0: 
        union(x, y)
    else: 
        if same(x, y) == True: 
            print(1) 
        else: 
            print(0)