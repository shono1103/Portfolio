import numpy as np

class MAKE_ROW:
    def __init__(self,data1,data2):
        self.r_max = data1
        self.t_max = data2

    def permutations(self,iterable, permutation=[]):
        if not iterable: 
            yield permutation
            pass
        for i in [iterable.index(i) for i in set(iterable)]:
            yield from self.permutations(iterable[:i] + iterable[i+1:], permutation + [iterable[i]])

    def make_row(self):
        node = []
        # 要素のリスト
        for i in range (self.r_max):
            node.append(0)
        for j in range(self.t_max):
            node.append(1)
        # print(node)
        # 順列の生成
        pattern = list(self.permutations(node))
        # print(list(pattern))
        pattern = np.array(pattern)
        # print(pattern)
        return pattern
