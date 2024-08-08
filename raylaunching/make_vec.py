import numpy as np
class MAKE_VEC:
    def __init__(self):
        self.x_wall = 0
        self.y_wall = 0
        self.x_trans = 0
        self.y_trans = 0
        self.trans_vec = 0
        self.ray_vec = 0
        self.ref_vec = 0
        self.nor_vec = 0

    def make_trans_vec(self):
        self.trans_vec = self.ray_vec
    
    def avoid_wall(self,map):
        self.x_trans = self.x_wall + self.trans_vec[0]
        self.y_trans = self.y_wall + self.trans_vec[1]
        for i in range(10):
            if map[round(self.x_trans),round(self.y_trans)] != 0:
                self.x_trans += self.trans_vec[0]
                self.y_trans += self.trans_vec[1]
            elif map[round(self.x_trans),round(self.y_trans)] != 0:
                break
        return self.x_trans, self.y_trans
    
    def make_ref_vec(self):
        self.ref_vec= self.ray_vec - 2*(np.dot(self.nor_vec,self.ray_vec))*self.nor_vec