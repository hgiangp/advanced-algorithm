num_nodes, num_queries = map(int, input().split(' '))
INF = 2147483647 # 2^31 - 1 

# the size of the array is power of 2 
n = 1 << num_nodes.bit_length()

tree_no_nodes = 2 * n - 1 # size of the tree
D = [INF] * tree_no_nodes
# lazy = [None] * tree_no_nodes 

# def lazy_evaluate(k): 
#     if lazy[k] == None: return 
#     D[k] = lazy[k]
#     if k < n - 1: # not leaf 
#         lazy[2*k + 1] = lazy[k]
#         lazy[2*k + 2] = lazy[k]
#     lazy[k] = None

def query(a, k, l, r): 
    if r < a or a < l: 
        return INF
    
    lazy_evaluate(k)
    
    if a <= l and r <= a:
        return D[k]
    
    query(a, 2*k+1, l, (l+r)//2)
    query(a, 2*k+2, (l+r)//2, r)
    # return min(vl, vr)

def update(a, b, k, l, r, x):
    if r <= a or b <= l: 
        return 
    if a <= l and r <= b:
        lazy[k] = x 
    else: 
        update(a, b, 2*k + 1, l, (l + r)//2, x)
        update(a, b, 2*k + 2, (l + r)//2, r, x)

def find(i): 
    i += n 
    return query(i, 0, 0, n) 


l = [input() for _ in range(num_queries)]

for i in range(num_queries):
    com, *params = map(int, l[i].split(' '))
    if com == 0: 
        s, t, x = params 
        update(s, t+1, 0, 0, n, x)
    elif com == 1: 
        s = params[0] 
        print(find(s))