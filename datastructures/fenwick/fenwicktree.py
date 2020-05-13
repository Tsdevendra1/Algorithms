from typing import List


class FenwickTree:
    # https://www.youtube.com/watch?v=RgITNht_f4Q&t=301s

    def least_significant_bit(self, val) -> int:
        """
        You can also consider this as a range of responsibilities, to the cells BELOW it
        minus the number for a given index to find its child, add the number to find its parent

        The two's complement of an N-bit number is defined as its complement with respect to 2ᴺ
        Example: for 2
        2 -->   0000000000000010 (2s complement)
        -2 -->  1111111111111110 (2s complement)

        if we do & --> 0000000000000010 --> which is binary form for 2 hence  2 & -2 == 2

        :return the index of the least significant bit of the val in binary form
        """
        return val & -val

    def add(self, index: int, val: int) -> None:
        while index < len(self.tree):
            self.tree[index] += val
            index += self.least_significant_bit(index)

    def sum(self, i: int, j: int) -> int:
        # Notice the minus is not inclusive for i, because we want to include it in the range
        return self.prefix_sum(j) - self.prefix_sum(i - 1)

    def set(self, index: int, val: int) -> None:
        # First find what value is currently stored in position index
        value = self.sum(index, index)
        # Then we add the difference between the new value and current value
        self.add(index, val - value)

    def prefix_sum(self, index) -> int:
        i = index
        value = 0
        while i != 0:
            value += self.tree[i]
            i -= self.least_significant_bit(i)
        return value

    def construct_initial_list(self, initial_list) -> List:
        # PLus one because fenwick uses indexing starting at 1
        tree = [number for number in initial_list]
        tree.insert(0, 0)

        for index, number in enumerate(initial_list):
            tree_index = index + 1
            parent_index = tree_index + self.least_significant_bit(tree_index)

            if parent_index < len(tree):
                tree[parent_index] += tree[tree_index]

        return tree

    def __init__(self, initial_list: List) -> None:
        self.tree = self.construct_initial_list(initial_list)
        self.initial_list = initial_list


def main() -> None:
    test_list = [3, 4, -2, 7, 3, 11, 5, -8, -9, 2, 4, -8]
    fenwick = FenwickTree(initial_list=test_list)
    assert fenwick.tree == [0, 3, 7, -2, 12, 3, 14, 5, 23, -9, -7, 4, -11]


if __name__ == "__main__":
    main()
