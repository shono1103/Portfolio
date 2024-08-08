import numpy as np
import matplotlib.pyplot as plt


map = np.zeros([500,500])


#id 1:concrete, 2:plasterboard, 3:wood, 4:glass, 0:air
#外壁
map[1:3,1:499] = 1
map[498:499,1:499] = 1
map[1:499,1:3] = 1
map[1:499,498:499] = 1
#glass
map[1:3,50:150] = 3
map[1:3,250:300] = 3
map[1:3,400:450] = 3
map[498:499,50:150] = 3
map[498:499,200:300] = 3
map[498:499,350:450] = 3
map[498:499,50:150] = 3
map[200:300,1:3] = 3
map[350:400,1:3] = 3
map[150:200,498:499] = 3
map[250:300,498:499] = 3
map[350:450,498:499] = 3





#内壁
map[149:150,3:50] = 2
map[149:150,100:250] = 2
map[149:150,300:498] = 2

map[99:100,200:250] = 2
map[99:100,300:400] = 2
map[99:100,450:498] = 2

map[249:250,350:498] = 2
map[349:350,350:498] = 2

map[3:100,199:200] = 2
map[3:100,349:350] = 2
map[200:250,349:350] = 2
map[300:350,349:350] = 2
map[400:498,349:350] = 2



root = './map'
No = '02'

np.savetxt(root + No + '.txt',map,fmt="%f",delimiter=' ')
plt.imshow(map,cmap='Greys')
plt.show()