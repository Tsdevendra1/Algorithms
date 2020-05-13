# https://indepth.dev/the-simple-math-behind-decimal-binary-conversion-algorithms/


def binary_to_decimal(number: str) -> int:
    total = 0
    for letter in number:
        total = 2 * total + int(letter)
    return total


def decimal_to_binary(number: int) -> str:
    current_quotient = number

    binary_string = ''
    while current_quotient != 0:
        binary_string += str(current_quotient % 2)
        current_quotient = current_quotient // 2

    return binary_string[::-1]


if __name__ == "__main__":
    assert binary_to_decimal('1100') == 12
    assert decimal_to_binary(12) == '1100'
