
import unittest

RIGHT_P = ')'
LEFT_P = '('

class P:

    def __init__(self, count, index, par_type):
        self.count = count
        self.index = index
        self.par_type = par_type

    def from_left(self):
        return P(1, self.index, self.par_type)

    def from_right(self):
        return P(1, self.index+self.count-1, self.par_type)

    def __str__(self):
        return "(" + ",".join(map(str, [self.count, self.index, self.par_type])) + ")"

    def __repr__(self):
        return str(self)

def merge(left_list, right_p):
    add = []
    while right_p.count != 0:
        left_p = left_list.pop()
        m = min(left_p.count, right_p.count)
        add += [left_p.from_right(), right_p.from_right()]
        left_p.count -= m
        right_p.count -= m
        if left_p.count != 0: left_list.append(left_p)
    return add

def construct_par_list(ps):
    prev = None
    pars = []
    for i, p in enumerate(ps):
        if p == LEFT_P or p == RIGHT_P:
            if prev == p:
                pars[-1].count += 1
            else:
                pars.append(P(1, i, p))
        prev = p

    return pars

def reduce_pars(par_list):
    result = []
    left_list = []
    for p in par_list:
        if p.par_type == ')':
            result += merge(left_list, p)
        else: left_list.append(p)
    result.sort(key=lambda x: x.index)
    return result

def to_many_parenthesis(ps):
    par_list = construct_par_list(ps)
    needed_pars = reduce_pars(par_list)
    s = ""
    # so could pop them one by one
    needed_pars.reverse()
    for i, p in enumerate(ps):
        if p == LEFT_P or p == RIGHT_P:
            if needed_pars[-1].index == i:
                s += needed_pars.pop().par_type
        else:
            s += p
    return s


class TestToManyParenthesis(unittest.TestCase):

    def test_0(self):
        "((f)(ddefe((de)fef))f)(d)"
        s = "(((f)(ddefe(((de))fef))f))(((d)))"
        r = "((f)(ddefe((de)fef))f)(d)"
        s = to_many_parenthesis(s)
        self.assertEquals(s, r)

    def test_1(self):
        s = "()"
        r = "()"
        s = to_many_parenthesis(s)
        self.assertEquals(s, r)

    def test_2(self):
        s = "((((()))))"
        r = "()"
        s = to_many_parenthesis(s)
        self.assertEquals(s, r)

    def test_3(self):
        s = "(()(()(()(()()))))"
        r = "(()(()(()(()()))))"
        s = to_many_parenthesis(s)
        self.assertEquals(s, r)

    def test_4(self):
        s = "(((((((((((wfwe))))))(((((((((fefw))))))))(((((wf)))))))))))"
        r = "((wfwe)((fefw)(wf)))"
        s = to_many_parenthesis(s)
        self.assertEquals(s, r)

if __name__ == '__main__':
    unittest.main()
