import numpy as np
import tqdm as td
class RECEiVE_CIRCLE:
    def __init__(self,size):
        self.map = np.zeros([size,size])
        self.size = size

    def receive_circle(self,xtx,ytx,arg,map,map_line):
        l = np.max(map_line)
        for x in td.tqdm(range(self.size)):
            for y in range(self.size):
                d = np.sqrt((xtx-x)**2+(ytx-y)**2)
                r = (d*arg)/2
                # if r>10:
                #     r = 10
                power = np.zeros([int(l+1)])
                dis = np.zeros([int(l+1)])
                for x0 in range(round(2*r)):
                    for y0 in range(round(2*r)):
                        
                        if (x-(x+x0-round(r)))**2 + (y-(y+y0-round(r)))**2 < r**2 and 0<=(x+x0-round(r))<self.size and 0<=(y+y0-round(r))<self.size :
                            id = int(map_line[x+x0-round(r),y+y0-round(r)])
                            d1 = (x-(x+x0-round(r)))**2 + (y-(y+y0-round(r)))**2
                            if map[x+x0-round(r),y+y0-round(r)] == 0:
                                continue
                            elif map[x+x0-round(r),y+y0-round(r)] != 0 and power[id] == 0:
                                power[id] = map[x+x0-round(r),y+y0-round(r)]
                                dis[id] = d1
                            elif map[x+x0-round(r),y+y0-round(r)] != 0 and power[id] != 0:
                                if dis[id] >= d1:
                                    continue
                                elif dis[id] < d1:
                                    power[id] = map[x+x0-round(r),y+y0-round(r)]
                                dis[id] = d1
                for i in range(int(l+1)):
                    self.map[x,y] += power[i]


# import numpy as np
# from tqdm import tqdm

# class RECEiVE_CIRCLE:
#     def __init__(self):
#         self.map_power = np.zeros([100, 100])

#     def receive_circle(self, xtx, ytx, arg, map_power, map_line):
#         for x in tqdm(range(100)):
#             for y in range(100):
#                 d = np.sqrt((xtx - x)**2 + (ytx - y)**2)
#                 r = (d * arg) / 2

#                 # 計算に必要な座標の範囲を事前に計算
#                 x_range = np.arange(max(0, x - r), min(100, x + r + 1))
#                 y_range = np.arange(max(0, y - r), min(100, y + r + 1))

#                 for x0 in x_range:
#                     for y0 in y_range:
#                         distance_squared = (x - (x + x0 - round(r)))**2 + (y - (y + y0 - round(r)))**2

#                         if distance_squared < r**2 and (x + x0 - round(r))>0 and (y + y0 - round(r))>0:
#                             power_val = map_power[x + x0 - round(r), y + y0 - round(r)]
#                             line_val = map_line[x + x0 - round(r), y + y0 - round(r)]
#                             distance = np.sqrt(distance_squared)

#                             # 重複しているかを判定
#                             duplicate_index = np.where(line_val == map_line[x_range, y_range])

#                             if len(duplicate_index[0]) > 0:
#                                 memo = duplicate_index[0][0]
#                                 if distance < np.sqrt((x - (x + x0 - round(r)))**2 + (y - (y + y0 - round(r)))**2):
#                                     power_val = map_power[x + x0 - round(r), y + y0 - round(r)]
#                                     distance = np.sqrt((x - (x + x0 - round(r)))**2 + (y - (y + y0 - round(r)))**2)
#                                 else:
#                                     power_val = map_power[x + x0 - round(r), y + y0 - round(r)]
#                                     distance = np.sqrt((x - (x + x0 - round(r)))**2 + (y - (y + y0 - round(r)))**2)

#                             else:
#                                 map_line[x_range, y_range] = line_val
#                                 power_val = map_power[x + x0 - round(r), y + y0 - round(r)]
#                                 distance = np.sqrt(distance_squared)

#                             self.map_power[x, y] += power_val

