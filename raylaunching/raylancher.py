import numpy as np
import matplotlib.pyplot as plt
from root_row import MAKE_ROW
from expand_ray import EXPAND_RAY
from make_vec import MAKE_VEC
from recieve_circle import RECEiVE_CIRCLE
import tqdm as td

def make_ray_vec(arg):

    if 0 <= arg and arg <= np.pi/2 :
        ray_vec = [1, np.tan(arg),0]
    elif np.pi/2 < arg and arg <= np.pi:
        ray_vec = [-1, -np.tan(arg),0]
    elif np.pi < arg and arg <= (3/2)*np.pi:
        ray_vec = [-1, -np.tan(arg),0]
    elif (3/2)*np.pi < arg and arg < 2*np.pi:
        ray_vec = [1, np.tan(arg),0]

    ray_vec = np.array(ray_vec)
    ray_vec = ray_vec/np.linalg.norm(ray_vec)
    return ray_vec



def make_ray_vec(arg):

    if 0 <= arg and arg <= np.pi/2 :
        ray_vec = [1, np.tan(arg)]
    elif np.pi/2 < arg and arg <= np.pi:
        ray_vec = [-1, -np.tan(arg)]
    elif np.pi < arg and arg <= (3/2)*np.pi:
        ray_vec = [-1, -np.tan(arg)]
    elif (3/2)*np.pi < arg and arg < 2*np.pi:
        ray_vec = [1, np.tan(arg)]
    ray_vec = np.array(ray_vec)
    ray_vec = ray_vec/np.linalg.norm(ray_vec)
    return ray_vec

def cul_r(ram,d_h,n,sin,cos):
    d_x = 0
    r_a_mat = 0
    r_mat = 0
    a = n**2-sin**2
    d_x = (2*np.pi/ram)*(d_h)*(np.sqrt(a))
    r_a_mat = (cos-np.sqrt(n**2-sin**2))/(cos+np.sqrt(n**2-sin**2))
    r_mat = (r_a_mat*(1-np.cos(2*d_x)+1j*np.sin(2*d_x)))/(1-r_a_mat**2*(np.cos(2*d_x)-1j*np.sin(2*d_x)))
    return r_mat

def cul_t(ram,d_h,n,sin,cos,k_0):
    a = n**2-sin**2
    d_x = (2*np.pi/ram)*(d_h)*(np.sqrt(a))
    r_a_mat = (cos-np.sqrt(n**2-sin**2))/(cos+np.sqrt(n**2-sin**2))
    t_mat = ((1-r_a_mat**2)*(np.cos(d_x-k_0*d_h*cos)-1j*np.sin(d_x-k_0*d_h*cos)))/(1-r_a_mat**2*(np.cos(2*d_x)-1j*np.sin(2*d_x)))
    return t_mat
    

def cul_cond(material,f):
    cond = material[1]*f**material[2]
    return cond

def cul_n(material,air,cond,w):
    n = np.sqrt((material[0]-1j*cond/w)/(air[0]))
    return n

air = [1, 0, 0]


# 周波数[Hz]
f = 2.0*(10**9)
w = 2*np.pi*f
# 光速
c = 3.0*(10**8)
# 波長
ram = c/f
# 波数
k_0 = 2*np.pi/ram
# 壁厚
d_h = 0.2

# 送信機の位置
(xtx, ytx) = (100, 200)
# 光線の本数
ray_num = 30

# 光線方向ベクトル作成
arg = 2*np.pi/ray_num

ref_max = 5
trans_max = 4
ref_num = 0
trans_num = 0

row = MAKE_ROW(ref_max,trans_max)
pattern = row.make_row()
pattern_shape = list(np.shape(pattern))




map_power = 0
root = './map_loss'

path ='./map'
No ='02'
ray_n = str(ray_num)
ref = str(ref_max)
tran = str(trans_max)
xtx_l = str(xtx)
ytx_l = str(ytx)

map = np.loadtxt(path + No + '.txt')
map_size = np.shape(map)
print(map_size)
size = int(map_size[0])
print(size)
plt.imshow(map,cmap='Greys')
plt.show()

id = 1
mv = MAKE_VEC()
ex = EXPAND_RAY(f,ram,k_0,size)
for num in td.tqdm(range(ray_num)):
    ex.r = []
    ray_vec = make_ray_vec(num*arg)
    i = 0
    j = 0
    # print(pattern[i,j])
    ex.bump = False
    ex.x_p = xtx
    ex.y_p = ytx
    ex.d_before = 0
    id += 1
    ex.expand_ray(map,ray_vec,id)
    
    
    x_wall = ex.x_wall
    y_wall = ex.y_wall
    

    nor_vec = ex.normal_vec
    material = ex.material
    d_before = ex.d_before
    x_wall_first = ex.x_wall
    y_wall_first = ex.y_wall
    nor_vec_first = ex.normal_vec
    ray_vec_first = ray_vec
    wall_first =ex.wall
    mt_first = material
    d_before_first = d_before

    for i in range(pattern_shape[0]):
        mv.ray_vec = ray_vec_first
        mv.nor_vec = nor_vec_first
        mv.x_wall = x_wall_first
        mv.y_wall = y_wall_first
        ex.wall = wall_first
        ex.material = mt_first
        ex.d_before = d_before_first
        ex.r = []
        ex.bump = False
        id +=1


        for j in range(pattern_shape[1]):
            if ex.wall == True:
                cos = np.dot(-ray_vec,ex.normal_vec)/(np.linalg.norm(ray_vec)*np.linalg.norm(ex.normal_vec))
                sin = np.sqrt(1-cos**2)
                cond = cul_cond(material,f)
                n = cul_n(material,air,cond,w)
                if pattern[i,j] == 0:
                    ex.r.append(cul_r(ram,d_h,n,sin,cos))
                    ex.bump = True
                    mv.make_ref_vec()
                    ray_vec = mv.ref_vec
                    ex.x_p= mv.x_wall
                    ex.y_p = mv.y_wall
                    ex.expand_ray(map,ray_vec,id)
                    id += 1
                elif pattern[i,j] == 1:
                    ex.r.append(cul_t(ram,d_h,n,sin,cos,k_0))
                    ex.bump = True
                    mv.make_trans_vec()
                    ray_vec = mv.trans_vec
                    mv.avoid_wall(map)
                    ex.x_p = mv.x_trans
                    ex.y_p = mv.y_trans
                    ex.expand_ray(map,ray_vec,id)
                    id += 1
            elif ex.wall == False:
                break
            x_wall = ex.x_wall
            y_wall = ex.y_wall
            nor_vec = ex.normal_vec
            mv.ray_vec = ray_vec
            mv.nor_vec = nor_vec
            mv.x_wall = x_wall
            mv.y_wall = y_wall
            
    
    
    # plt.imshow(ex.map_line2,cmap='Greys')
    # plt.colorbar()
    # # ,cmap='Greys'
    # plt.show()
    # ex.map_line2 = np.zeros([size,size])

ex.map_ray_real[xtx,ytx] = np.sqrt(120*np.pi/(4*np.pi))

map_comp = ex.map_ray_real + 1j*ex.map_ray_imag
# rc_real = RECEiVE_CIRCLE(size)
# rc_img = RECEiVE_CIRCLE(size)
# rc_real.receive_circle(xtx,ytx,arg,ex.map_ray_real,ex.map_line)
# rc_img.receive_circle(xtx,ytx,arg,ex.map_ray_imag,ex.map_line)
rc =RECEiVE_CIRCLE(size)
rc.receive_circle(xtx,ytx,arg,map_comp,ex.map_line)

map_a = (ram/np.sqrt(4*120*np.pi))*rc.map

# map_a = (ram/np.sqrt(4*120*np.pi))*(rc_real.map+1j*rc_img.map)

map_power = abs(map_a)**2

map_loss = 10*np.log10(10/map_power)

# for x in range(size):
#     for y in range(size):
#         if map_loss[x,y]>120:
#             map_loss[x,y] = []

# for x in range(size):
#     for y in range(size):
#         if map_loss[x,y] < 90:
#             map_loss[x,y] = 90





plt.imshow(map_power,cmap='Greys')
plt.colorbar()
# ,cmap='Greys'
plt.show()

np.savetxt( root + '_' +No + '_' + ray_n + '_' + ref + '_' + tran + '_' + xtx_l + '_' + ytx_l+'.txt', map_loss ,fmt="%f",delimiter=' ')
plt.imshow(map_loss,cmap='Greys')
plt.show()

plt.imshow(map_loss)
plt.colorbar()
# ,cmap='Greys'
plt.show()

