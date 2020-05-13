class Tree:

    def __init__(self, key):
        self.key = key
        self.count_left = 0
        self.left_child = None
        self.right_child = None


def count(node, key):
    if node is None:
        return 0
    if key < node.key:
        return count(node.left_child, key)
    # plus one because current node is smaller than the key
    return 1 + node.count_left + count(node.right_child, key)


def insert(node, key):
    if node is None:
        return Tree(key)

    if key < node.key:
        node.count_left += 1
        node.left_child = insert(node.left_child, key)
    else:
        node.right_child = insert(node.right_child, key)
    return node


def remove(node, key):
    if node is None:
        return None

    if node.key == key:
        # Find successor to parent
        if node.right_child is None:
            return node.left_child
        if node.left_child is None:
            return node.right_child

        next_lowest = node.right_child
        while next_lowest.left_child is not None:
            next_lowest = next_lowest.left_child

        node.key = next_lowest.key
        node.right_child = remove(node.right_child, next_lowest.key)
        return node
    if key < node.key:
        node.count_left -= 1
        node.left_child = remove(node.left_child, key)
    else:
        node.right_child = remove(node.right_child, key)
    return node


def number_of_teams(ratings):
    # Count left is the number of numbers the current node is greater than, for any number added AFTER it, e.g. in [3,2,1] for 3 == 2, [7,9,1] for 7 == 1
    # Start with the front and the back because theyll never be pivots
    node_left = Tree(ratings[0])
    node_right = Tree(ratings[-1])
    counter = 0
    ratings_len = len(ratings)
    for i in range(1, ratings_len - 1):
        insert(node_right, ratings[i])
    for i in range(1, ratings_len - 1):
        remove(node_right, ratings[i])
        # Anything lower than current pivot on left
        __lower_ascending = count(node_left, ratings[i])
        # Anything lower than current pivot on right
        __lower_descending = count(node_right, ratings[i])

        # Anything greater than current pivot on left
        __greater_descending = i - __lower_ascending
        # Anything greater than current pivot on right
        __greater_ascending = (ratings_len - 1 - i - __lower_descending)
        counter += (__lower_ascending * __greater_ascending) + (__lower_descending * __greater_descending)
        insert(node_left, ratings[i])
    return counter

