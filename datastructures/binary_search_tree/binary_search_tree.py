from typing import Optional


class TreeNode:
    def __init__(self, key, val, left_child=None, right_child=None, parent=None):
        self.key = key
        self.val = val
        self.parent = parent
        self.left_child = left_child
        self.right_child = right_child


class BinarySearchTree:

    def __init__(self):
        self.root = None
        self.size = 0

    def length(self):
        return self.size

    def __len__(self):
        return self.size

    def __iter__(self):
        return self.root.__iter__()

    def insert(self, key, val):
        if not self.root:
            self.root = TreeNode(key, val)
        else:
            # self._insert(self.root, key, val)
            self._insert_v2(self.root, None, key, val)

    def _insert_v2(self, current_node: TreeNode, parent, key, val):
        if current_node is None:
            return TreeNode(key, val, parent=parent)

        if key < current_node.key:
            current_node.left_child = self._insert_v2(current_node.left_child, current_node, key, val)
        else:
            current_node.right_child = self._insert_v2(current_node.right_child, current_node, key, val)
        return current_node

    def get(self, key) -> Optional[TreeNode]:
        node = self._get(self.root, key)
        return node if node is not None else None

    def _get(self, current_node, key) -> Optional[TreeNode]:
        if not current_node:
            return None
        if current_node.key == key:
            return current_node

        if key < current_node.key:
            return self._get(current_node.left_child, key)
        else:
            return self._get(current_node.right_child, key)

    def delete(self, key):
        # Need to handle root case here, when size is only one
        self._delete(self.root, key=key)

    def _delete(self, current_node, key):
        # When deleting you can choose either the successor of the node (leftmost in the right tree) or predesessor (rightmost in the left tree)
        if current_node is None:
            return None

        if current_node.key == key:
            # Find successor to parent
            if current_node.right_child is None:
                return current_node.left_child
            if current_node.left_child is None:
                return current_node.right_child

            next_lowest = current_node.right_child
            while next_lowest.left_child is not None:
                next_lowest = next_lowest.left_child

            current_node.key = next_lowest.key
            current_node.right_child = self._delete(current_node.right_child, next_lowest.key)
            return current_node

        if key < current_node.key:
            current_node.left_child = self._delete(current_node.left_child, key)
        else:
            current_node.right_child = self._delete(current_node.right_child, key)

        return current_node


def main() -> None:
    bst = BinarySearchTree()
    tests = [5, 30, 2, 40, 25, 4]
    for number in tests:
        bst.insert(number, 5)

    bst.delete(30)
    assert bst.root.right_child.key == 40

    bst = BinarySearchTree()
    tests = [17, 5, 35, 2, 11, 29, 38, 9, 16, 7, 8]
    for number in tests:
        bst.insert(number, 5)

    bst.delete(5)
    assert bst.root.left_child.key == 7
    assert bst.root.left_child.right_child.left_child.left_child.key == 8

    bst = BinarySearchTree()
    tests = [3, 6, 7, 5, 1]
    for number in tests:
        bst.insert(number, 5)

    x = bst
    bst.delete(6)
    assert bst.root.right_child.key == 7
    bst.delete(7)
    assert bst.root.right_child.key == 5
    bst.delete(5)
    assert bst.root.right_child is None


if __name__ == "__main__":
    main()
