class Node: 
    def __init__(self, val, left_node=None, right_node=None):
        self.val = val 
        self.left = left_node 
        self.right = right_node


def build_tree(pre_order, in_order):
    if not pre_order or not in_order: 
        return None 
    
    root = Node(val=pre_order[0])

    root_idx = in_order.index(pre_order[0])
    root.left = build_tree(pre_order[1:root_idx+1], in_order[:root_idx])
    root.right = build_tree(pre_order[root_idx+1:], in_order[root_idx+1:])

    return root

num_nodes = input()
pre_order = list(map(int, input().split(' ')))
in_order = list(map(int, input().split(' ')))


post_order = []
def postorder_tree_walk(node: Node):
    if node.left != None: 
        postorder_tree_walk(node.left)
    if node.right != None: 
        postorder_tree_walk(node.right)
    post_order.append(node.val)

root = build_tree(pre_order, in_order)
postorder_tree_walk(root)
print(*post_order)