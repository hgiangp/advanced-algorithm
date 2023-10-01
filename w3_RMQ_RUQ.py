num_nodes, num_queries = map(int, input().split(' '))
INF = 2147483647 # 2^31 - 1 

n = 1 
# the size of the array is power of 2 
while n < num_nodes: 
    n *= 2

tree_no_nodes = 2 * n - 1 # size of the tree
D = [INF] * tree_no_nodes
lazy = [None] * tree_no_nodes 

def lazy_evaluate(k): 
    if lazy[k] == None: return 
    D[k] = lazy[k]
    if k < n - 1: # not leaf 
        lazy[2*k + 1] = lazy[k]
        lazy[2*k + 2] = lazy[k]
    lazy[k] = None

# [a, b)
def query(a, b, k, l, r): 
    if r <= a or b <= l: 
        return INF
    
    lazy_evaluate(k)
    
    if a <= l and r <= b:
        return D[k]
    
    vl = query(a, b, 2*k+1, l, (l+r)//2)
    vr = query(a, b, 2*k+2, (l+r)//2, r)
    return min(vl, vr)

def update(a, b, k, l, r, x): 
    lazy_evaluate(k) 
    if r <= a or b <= l: 
        return 
    if a <= l and r <= b:
        lazy[k] = x 
    else: 
        update(a, b, 2*k + 1, l, (l + r)//2, x)
        update(a, b, 2*k + 2, (l + r)//2, r, x)
        D[k] = min(D[2*k+1], D[2*k+2])
    lazy_evaluate(k)

# [a, b]
def findMin(a, b): 
    return query(a, b+1, 0, 0, n)

l = [input() for _ in range(num_queries)]

for i in range(num_queries):
    com, *params = map(int, l[i].split(' '))
    if com == 0: 
        s, t, x = params 
        update(s, t+1, 0, 0, n, x)
    elif com == 1: 
        s, t = params 
        print(findMin(s, t))        