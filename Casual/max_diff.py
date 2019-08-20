# Find maximum difference between two elements in array
# such that i < j and a[i] < a[j]: [1,6,4,10,3,0,-10] => 10 - 1 = 9 is an answer even though maximum difference without condition would be 10 - (-10)

import unittest

def max_diff(arr):
    min_el = arr[0]
    res = -1
    for a in arr[1:]:
        diff = a - min_el
        if res < diff:
            res = diff
        min_el = min(a, min_el)
    if res <= 0: res = -1
    return res



class TestMaxDiff(unittest.TestCase):

    def test_0(self):
        arr = [1,6,4,10,3,0,-10]
        res = max_diff(arr)
        self.assertEquals(res, 9)


if __name__ == '__main__':
    unittest.main()

