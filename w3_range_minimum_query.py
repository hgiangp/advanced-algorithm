num_nodes, num_queries = map(int, input().split(' '))
INF = 2147483647 # 2^31 - 1 

def initRMQ(num_nodes: int): 
    n = 1 

    # the size of the array is power of 2 
    while n < num_nodes: 
        n *= 2

    tree_no_nodes = 2 * n - 1 # size of the tree
    D = [INF] * tree_no_nodes
    return D, n 

D, n = initRMQ(num_nodes) # init tree 

def update(k, x): 
    idx_tree = k + n - 1
    D[idx_tree] = x 
    while idx_tree > 0: 
        idx_tree = int((idx_tree - 1) / 2) 
        D[idx_tree] = min(D[2 * idx_tree + 1], D[2 * idx_tree + 2])

# [a, b)
def query(a, b, k, l, r): 
    if r <= a or b <= l: 
        return INF

    if a <= l and r <= b: 
        return D[k]

    vl = query(a, b, k*2 + 1, l, (l+r)/2) 
    vr = query(a, b, k*2 + 2, (l+r)/2, r)  
    return min(vl, vr)

# [a, b]
def findMin(a, b): 
    return query(a, b+1, 0, 0, n)

l = [input() for _ in range(num_queries)]

for i in range(num_queries):
    com, x, y = map(int, l[i].split(' '))
    if com == 0: 
        update(x, y)
    elif com == 1: 
        print(findMin(x, y))
    