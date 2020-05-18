class TreeNode:
    def __init__(self, val):
        self.left = None
        self.right = None
        self.val = val


def x(N):
    N -= 1
    if N == 0: return [TreeNode(0)]
    ret = []
    for l in range(1, min(20, N), 2):
        for left in x(l):
            for right in x(N - l):
                root = TreeNode(0)
                root.left = left
                root.right = right
                ret += [root]
    return ret


def main():
    x(3)


if __name__ == "__main__":
    main()
