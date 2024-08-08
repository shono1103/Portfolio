import numpy as np
import matplotlib.pyplot as plt


map = np.zeros([500,500])


#id 1:concrete, 2:plasterboard, 3:wood, 4:glass, 0:air
#外壁
map[0:3,] = 1
map[498:500,] = 1
map[0:500,0:3] = 1
map[0:500,498:500] = 1
#glass
map[0:3,50:100] = 3
map[0:3,200:300] = 3
map[150:250,0:3] = 3
map[400:450,0:3] = 3
map[150:250,498:500] = 3
map[400:450,498:500] = 3






#内壁
map[99:100,3:150] = 1
map[99:100,350:498] = 1

map[199:200,150:350] = 1

map[349:350,3:150] = 1
map[349:350,350:498] = 1


map[50:100,149:150] = 1
map[150:250,149:150] = 1
map[300:450,149:150] = 1

map[50:100,349:350] = 1
map[150:250,349:350] = 1
map[300:450,349:350] = 1



root = './map'
No = '04_'
ray = str(20)

np.savetxt(root + No + ray +'.txt',map,fmt="%d",delimiter=' ')
plt.imshow(map,cmap='Greys')
plt.show()