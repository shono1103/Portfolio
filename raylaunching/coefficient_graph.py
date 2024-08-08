import numpy as np
import csv
from matplotlib import pyplot as plt

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

def cul_n(material,air,cond,f):
    w = 2*np.pi*f
    n = np.sqrt((material[0]-1j*cond/w)/(air[0]))
    return n


material = [5.31,0.0326,0.8095]
air = [1,0,0]
f = 2*10**9
c = 3*10**8
ram = c/f
delta_h = 0.1
k_0 = 2*np.pi/ram

r_real = []
r_img = []
t_real = []
t_img = []


for i in range(90):
    theta = (i/180)*np.pi
    s = np.sin(theta)
    c = np.cos(theta)
    cond = cul_cond(material,f)
    n = cul_n(material,air,cond,f)
    r_1 = cul_r(ram,delta_h,n,s,c)
    r_r = r_1.real
    r_i = r_1.imag
    r_real.append(r_r)
    print(r_r)
    r_img.append(r_i)
    t_1 = cul_t(ram,delta_h,n,s,c,k_0)
    t_r = t_1.real
    print(t_r)
    t_i = t_1.imag
    t_real.append(t_r)
    t_img.append(t_i)


x = list(range(90))
y1 = r_real
y2 =r_img


# グラフの描画
plt.plot(x, y1,label = "real")
plt.plot(x, y2,label = "imag")
plt.legend()
plt.show()

x = list(range(90))
y1 = t_real
y2 = t_img

plt.plot(x, y1,label = "real")
plt.plot(x, y2,label = "imag")
plt.legend()
plt.show()