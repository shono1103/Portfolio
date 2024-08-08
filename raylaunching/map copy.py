import numpy as np
import matplotlib.pyplot as plt


map = np.zeros([200,200])


#id 1:concrete, 2:plasterboard, 3:wood, 4:glass, 0:air
#外壁

a = 1
b = 199
c = 50
d = 150

map[a,a:b-1] = 1
map[b-1,a:b-1] = 1
map[a:b-1,a] = 1
map[a:b-1,b-1] = 1
map[c,c:d] = 1
map[d,c:d] = 1
map[c:d,c] = 1
map[c:d,d] = 1

root = './map'
No = '05'

np.savetxt(root + No + '.txt',map,fmt="%d",delimiter=' ')
plt.imshow(map,cmap='Greys')
plt.show()