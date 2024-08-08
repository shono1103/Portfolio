import numpy as np
import matplotlib.pyplot as plt

#レイローンチングmapと屋内形状map
map_ray = np.zeros([500,500])
map = np.zeros([500,500])

#屋内形状
map[1,1:498] = 1
map[498,1:498] = 1
map[1:498,498] = 1
map[1:498,1] = 1

#ダイアド反射係数
# 動作周波数
f = 2.0*10**6
# 角周波数
w = 2*np.pi*f
# 導電率導出
phy_air = 0
c_wood = 0.0047
d_wood = 1.0718
phy_wood = c_wood*f**d_wood

# 比誘電率
ep_air = 1.0
ep_wood = 5.0

# 比透磁率
u_air = 1.0
u_wood = 1.0

# 比複素屈折率
n_air_wood = np.sqrt(u_wood/u_air)*np.sqrt((ep_wood-1j*phy_wood/w)/(ep_air-1j*phy_air/w))



# 送信点
(xtx, ytx) = (50, 50)
# 反射回数・透過回数
ref_num = 5
tran_num = 5
# 送信電力
pt = 1

# 周波数[Hz]
f = 2.0*(10**9)
# 光速
c = 3.0*(10**8)
# 波長
ram = c/f
# 波数
k = 2*np.pi/ram
# 自由空間の誘電率
ep0 = (1/(36*np.pi))*10**(-9)
# 自由空間の透磁率
u0 = 4*np.pi*10**(-7)
# 自由空間の固有インピーダンス
z0 = np.sqrt(u0/ep0)
# 初期電界
e0 = np.sqrt(pt*z0/4*np.pi)
# レイの数
num_ray = 10
# 角度計算
arg = 2*np.pi/num_ray
ray_vec = [1, np.tan(arg),0]
ray_vec = np.array(ray_vec)
ray_vec = ray_vec/np.linalg.norm(ray_vec)
# 送信機との距離
r = 0

# レイの発射
for i in range (1000):
    # 光線出射
    x = xtx + i*ray_vec[0]
    y = ytx + i*ray_vec[1]
    
    # 画像の端
    if x >= 499:
        print('範囲外')
        break
    
    # 壁検出
    elif map[int(x),int(y)] == 1:
        x_ref = x
        y_ref = y
        # 反射面での法線導出
        if map[int(x_ref+1),int(y_ref)]==1 and map[int(x_ref-1),int(y_ref)]==1:
            if x_ref < (xtx + (i-1)*ray_vec[0]):
                vec_x = 0 
                vec_y = 1
            if x_ref > (xtx + (i-1)*ray_vec[0]):
                vec_x = 0
                vec_y = -1
        elif map[int(x_ref),int(y_ref+1)]==1 and map[int(x_ref),int(y_ref-1)]==1:
            if y_ref < (ytx + (i-1)*ray_vec[1]):
                vec_x = 1
                vec_y = 0
            if y_ref > (ytx + (i-1)*ray_vec[1]):
                vec_x = -1 
                vec_y = 0
        elif map[int(x_ref+1),int(y_ref)]==1 and map[int(x_ref),int(y_ref+1)]==1:
            vec_x = 1/np.sqrt(2)
            vec_y = 1/np.sqrt(2)
        elif map[int(x_ref+1),int(y_ref)]==1 and map[int(x_ref),int(y_ref-1)]==1:
            vec_x = 1/np.sqrt(2)
            vec_y = -1/np.sqrt(2)
        elif map[int(x_ref-1),int(y_ref)]==1 and map[int(x_ref),int(y_ref+1)]==1:
            vec_x = -1/np.sqrt(2)
            vec_y = 1/np.sqrt(2)
        elif map[int(x_ref-1),int(y_ref)]==1 and map[int(x_ref),int(y_ref-1)]==1:
            vec_x = -1/np.sqrt(2)
            vec_y = -1/np.sqrt(2)
        nor_vec = [vec_x,vec_y,0]
        nor_vec = np.array(nor_vec)
        break
    
    r = np.sqrt((x - xtx)**2 + (y-ytx)**2)
    print(e0*np.exp(-1.j*k*r)/r)
    # 電磁波割り当て
    map_ray[int(x),int(y)] = e0*np.exp(-1.j*k*r)/r

memo_ray_e = e0*np.exp(-1.j*k*r)/r

# 反射方向の単位ベクトル導出
ray_vec_2 = ray_vec - 2*(np.dot(nor_vec,ray_vec))*nor_vec

# 法線と入射レイのなす角の導出
theta = np.arccos(np.dot(ray_vec,nor_vec)/(np.abs(ray_vec)*np.abs(nor_vec)))
print(np.cross(nor_vec,ray_vec))
# ダイアド反射係数
u_vec_in_11 = np.cross(nor_vec,ray_vec)/np.abs(np.cross(nor_vec,ray_vec))
u_vec_in_1_ = np.cross(ray_vec,u_vec_in_11)
u_vec_r_11 = np.cross(nor_vec,ray_vec_2)/np.abs(np.cross(nor_vec,ray_vec_2))
u_vec_r_1_ = np.cross(ray_vec_2,u_vec_r_11)

r_1__1 = (u_wood*np.cos(theta) - u_air*np.sqrt(n_air_wood**2-np.sin(theta)**2))/(u_wood*np.cos(theta) + u_air*np.sqrt(n_air_wood**2-np.sin(theta)**2))
r_11_1 = (u_air*n_air_wood**2*np.cos(theta) - u_wood*np.sqrt(n_air_wood**2-np.sin(theta)**2))/(u_air*n_air_wood**2*np.cos(theta) + u_wood*np.sqrt(n_air_wood**2-np.sin(theta)**2))

ref = r_1__1*u_vec_in_1_*u_vec_r_1_ + r_11_1*u_vec_in_11*u_vec_r_11
e_r = memo_ray_e*np.dot(ray_vec,ref)
# for k in range(3):
# 反射後のレイの出射
for j in range (499):
        x = x_ref + (j+1)*ray_vec_2[0]
        y = y_ref + (j+1)*ray_vec_2[1]
        if j==0:
            map_ray[int(x),int(y)] = 1
            continue
        if x >= 499:
            break
        elif map[int(x),int(y)] == 1:
            x_ref = x
            y_ref = y
        # 反射面での法線導出
            if map[int(x_ref+1),int(y_ref)]==1 and map[int(x_ref-1),int(y_ref)]==1:
                if x_ref < (xtx + (i-1)*ray_vec[0]):
                    vec_x = 0 
                    vec_y = 1
                if x_ref > (xtx + (i-1)*ray_vec[0]):
                    vec_x = 0
                    vec_y = -1
            elif map[int(x_ref),int(y_ref+1)]==1 and map[int(x_ref),int(y_ref-1)]==1:
                if y_ref < (ytx + (i-1)*ray_vec[1]):
                    vec_x = 1
                    vec_y = 0
                if y_ref > (ytx + (i-1)*ray_vec[1]):
                    vec_x = -1 
                    vec_y = 0
            elif map[int(x_ref+1),int(y_ref)]==1 and map[int(x_ref),int(y_ref+1)]==1:
                vec_x = 1/np.sqrt(2)
                vec_y = 1/np.sqrt(2)
            elif map[int(x_ref+1),int(y_ref)]==1 and map[int(x_ref),int(y_ref-1)]==1:
                vec_x = 1/np.sqrt(2)
                vec_y = -1/np.sqrt(2)
            elif map[int(x_ref-1),int(y_ref)]==1 and map[int(x_ref),int(y_ref+1)]==1:
                vec_x = -1/np.sqrt(2)
                vec_y = 1/np.sqrt(2)
            elif map[int(x_ref-1),int(y_ref)]==1 and map[int(x_ref),int(y_ref-1)]==1:
                vec_x = -1/np.sqrt(2)
                vec_y = -1/np.sqrt(2)
            nor_vec = [vec_x,vec_y]
            nor_vec = np.array(nor_vec)
            break

        r = np.sqrt((x - x_ref)**2 + (y-y_ref)**2)
        
        map_ray[int(x),int(y)] = abs(e_r)*np.exp(-1.j*k*r)/r
    
    # ray_vec = ray_vec_2
    # ray_vec_2 = ray_vec - 2*(np.dot(nor_vec,ray_vec))*nor_vec

# map_ray = np.abs(map_ray*(ram/np.sqrt(4*np.pi*z0)))**2

plt.imshow(map_ray,cmap='Greys')
plt.show()
