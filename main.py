class Solution:
    def longestDecomposition(self, text: str) -> int:
        self.memo = {}

        def dp(start, end):
            pair = (start, end)
            if pair in self.memo:
                return self.memo[pair]

            if start == end:
                return 1

            score = 1
            sub_string_distance = 0
            while start + sub_string_distance < end - sub_string_distance:
                if text[start: start + sub_string_distance+1] == text[end - sub_string_distance: end + 1]:
                    print(text[start: start + sub_string_distance])
                    new_start = start + sub_string_distance + 1
                    new_end = end - sub_string_distance - 1
                    score = max(score, 2 + dp(new_start, new_end))
                sub_string_distance += 1

            self.memo[pair] = score
            return score

        return dp(0, len(text) - 1)


def main():
    x = Solution()
    print(x.longestDecomposition("aaa"))


if __name__ == "__main__":
    main()
