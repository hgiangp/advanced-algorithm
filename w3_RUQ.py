num_nodes, num_queries = map(int, input().split(' '))
INF = 2147483647 # 2^31 - 1 

n = 1 
# the size of the array is power of 2 
n = 1 << num_nodes.bit_length()

tree_no_nodes = 2 * n - 1 # size of the tree
D = [INF] * tree_no_nodes

def update(s, t, x): 
    l = s + n 
    r = t + n 
    while l < r: 
        idx_tree = int((idx_tree - 1) / 2) 
        D[idx_tree] = min(D[2 * idx_tree + 1], D[2 * idx_tree + 2])


# [a, b)
def query(a, b, k, l, r): 
    l = l + n
    r = r + n
    if r <= a or b <= l: 
        return INF
    
    lazy_evaluate(k)
    
    if a <= l and r <= b:
        return D[k]
    
    vl = query(a, b, 2*k+1, l, (l+r)//2)
    vr = query(a, b, 2*k+2, (l+r)//2, r)
    return min(vl, vr)

def update(a, b, k, l, r, x): 
    l = l + n
    r = r + n
    lazy_evaluate(k) 
    if r <= a or b <= l: 
        return 
    if a <= l and r <= b:
        lazy[k] = x 
    else: 
        update(a, b, 2*k + 1, l, (l + r)//2, x)
        update(a, b, 2*k + 2, (l + r)//2, r, x)
        # D[k] = min(D[2*k+1], D[2*k+2])
    lazy_evaluate(k)

def find(i): 
    return query(i, i+1, 0, 0, n)


l = [input() for _ in range(num_queries)]

for i in range(num_queries):
    com, *params = map(int, l[i].split(' '))
    if com == 0: 
        s, t, x = params 
        update(s, t+1, 0, 0, n, x)
    elif com == 1: 
        s = params[0] 
        print(find(s))