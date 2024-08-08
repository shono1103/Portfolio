import numpy as np

class EXPAND_RAY:
    def __init__(self,f,ram,k_0,size) :
        # 
        self.alpha = 0.1
        self.size = size
        self.f = f
        self.ram = ram
        self.k_0 = k_0
        self.x_p = 0
        self.y_p = 0
        self.vec_x = 0
        self.vec_y = 0
        self.d = 0
        self.map_power = np.zeros([size,size])
        self.normal_vec = 0
        self.wall = 0
        self.x_wall = 0
        self.y_wall = 0
        self.r = []
        self.d_before = 0
        self.map_line = np.zeros([size,size])
        self.map_line2 = np.zeros([size,size])
        # 波長
        self.ram = 3.0*(10**8)/f
        # 導電率
        self.map_ray_real = np.zeros([size,size])
        self.map_ray_imag = np.zeros([size,size])

        # 複素屈折率
        self.bump = False


    def expand_ray(self,map,ray_vec,id):
        for k in range(1000):
            x = self.x_p + (k+1)*ray_vec[0]
            y = self.y_p + (k+1)*ray_vec[1]
            
            # 画像の端
            if round(x) < 0 or round(x) >= self.size-1:
                
                self.wall =False
                break
            elif round(y) < 0 or round(y) >= self.size-1:
                self.wall =False
                break
            elif map[round(x),round(y)] != 0:
                self.x_wall = x
                self.y_wall = y
                self.wall = True
                self.d_before += 0.05*np.sqrt((x - self.x_p)**2 + (y-self.y_p)**2)
                if map[round(x),round(y)] == 1:
                    self.material = [5.31, 0.0326, 0.8095]
                    
                elif map[round(x),round(y)] == 2:
                    self.material = [2.94, 0.0116, 0.7076]
                    
                elif map[round(x),round(y)] == 3:
                    self.material = [6.27, 0.0043, 1.1925]
                    

                # 反射面での法線導出
                if map[round(self.x_wall+1),round(self.y_wall)]==1 and map[round(self.x_wall-1),round(self.y_wall)]==1:
                    if self.y_wall < (self.y_p + (k-1)*ray_vec[1]):
                        self.vec_x = 0 
                        self.vec_y = 1
                    if self.y_wall > (self.y_p + (k-1)*ray_vec[1]):
                        self.vec_x = 0
                        self.vec_y = -1
                    
                elif map[round(self.x_wall),round(self.y_wall+1)]==1 and map[round(self.x_wall),round(self.y_wall-1)]==1:
                    if self.x_wall < (self.x_p + (k-1)*ray_vec[0]):
                        self.vec_x = 1
                        self.vec_y = 0
                    if self.x_wall > (self.x_p + (k-1)*ray_vec[0]):
                        self.vec_x = -1 
                        self.vec_y = 0
                
                self.normal_vec = [self.vec_x,self.vec_y]
                self.normal_vec = np.array(self.normal_vec)
                
                # self.normal_vec = np.linalg.norm (self.normal_vec)

                break
            
            self.map_line[round(x),round(y)] = id
            self.map_line2[round(x),round(y)] = 1
            # 電力計算
            self.d = self.d_before + self.alpha*np.sqrt((x - self.x_p)**2 + (y-self.y_p)**2)
            
            # 受信電力導出
            if self.map_ray_real[round(x),round(y)] == 0:
                self.map_ray_real[round(x),round(y)] = np.sqrt(120*np.pi/(4*np.pi))*(np.cos(self.k_0*self.d))/(self.d)
                if self.bump == True :
                    for i in range(len(self.r)):
                        self.map_ray_real[round(x),round(y)] *= self.r[i]
            else:
                continue
            if self.map_ray_imag[round(x),round(y)] == 0:
                self.map_ray_imag[round(x),round(y)] = -np.sqrt(120*np.pi/(4*np.pi))*np.sin(self.k_0*self.d)/(self.d)
                if self.bump == True :
                    for i in range(len(self.r)):
                        self.map_ray_imag[round(x),round(y)] *= self.r[i]
            else:
                continue
            
            # a = (map_ray_real + 1j*map_ray_imag)
            # if self.bump == True :
            #     for i in range(len(self.r)):
            #         a *= self.r[i]
            # power = np.abs(a)**2
            
            # if self.map_power[round(x),round(y)] == 0:
            #     self.map_power[round(x),round(y)] = power
            # else :
            #     continue


    # def make_normal_vec(self):
    #     self.normal_vec = [self.vec_x,self.vec_y]
    #     self.normal_vec = np.array(self.normal_vec)
    #     self.normal_vec = np.linalg.norm (self.normal_vec)
    
