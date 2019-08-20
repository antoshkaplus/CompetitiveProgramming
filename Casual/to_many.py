
import unittest

RIGHT_P = ')'
LEFT_P = '('

def is_par(p):
    return p == RIGHT_P or p == LEFT_P

# removes excessive pars
# return new current index
def roll(st, i, ps):
    # has to watch out for last element
    while i < len(ps) and st:
        p = ps[i]
        if p == RIGHT_P and st[-1] == LEFT_P:
            st.pop()
            i += 1
        else: break
    return i


def to_many_parenthesis(ps):
    res = ""
    st = []
    i = 0
    while i < len(ps):
        p = ps[i]
        if p == RIGHT_P:
            r = RIGHT_P
            while True:
                s = st.pop()
                r += s
                if s == LEFT_P:
                    break

            i = roll(st, i+1, ps)
            st.append(r)

        else:
            st.append(p)
            i += 1

    return "".join(map(lambda x: x[::-1], st))



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