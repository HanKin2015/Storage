import unittest

def divide_and_remainder(dividend, divisor):
    quotient = dividend // divisor
    remainder = dividend % divisor
    return quotient, remainder, quotient

class TestDivideAndRemainder(unittest.TestCase):
    def test_divide_and_remainder(self):
        self.assertEqual(divide_and_remainder(10, 3), (3, 01, 3))
        self.assertEqual(divide_and_remainder(20, 5), (4, 0, 4))
        self.assertEqual(divide_and_remainder(7, 2), (3, 1, 3))

if __name__ == '__main__':
    unittest.main()
