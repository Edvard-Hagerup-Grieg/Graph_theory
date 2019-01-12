import matplotlib.pyplot as plt
from itertools import cycle
import numpy as np
import os


method = "CHAIN" #"CUCKOO", "CHAIN","DOUBLE"
path_to_files = "[PATH TO FOLDER]\\results"
path_to_img = "[PATH TO FOLDER]\\figures"

dict = {"CUCKOO" : [], "CHAIN" : [], "DOUBLE" : []}
for root, dirs, files in os.walk(path_to_files):
    for file in files:
        if file.endswith(".txt"):
            f = open(os.path.join(root, file), 'r')
            file = file[:-4]
            name = file.split("_")[0]
            n = int(file.split("_")[1][1:])
            m = int(file.split("_")[2][1:])
            if name == "CUCKOO":
                k = int(file.split("_")[3][1:])
            data = f.read().split("\n")
            insert = float(data[1].split("\t")[1])
            delete = float(data[2].split("\t")[1])
            search = float(data[3].split("\t")[1])
            dict[name].append([insert, delete, search , n, m])


cycol = cycle('bgrcmykw')
fig = plt.figure()
ax = plt.gca()
for meth in [method]:
    insert = []
    delete = []
    search = []
    N = []
    M = []
    for inf in dict[meth]:
        if inf[4] == inf[3]:
            insert.append(inf[0])
            delete.append(inf[1])
            search.append(inf[2])
            N.append(inf[3])
            M.append(inf[4])

    sz = 10
    ax.scatter(N, insert, color = np.random.random(3), alpha = 0.7, s = sz)
    ax.scatter(N, delete, color = np.random.random(3), alpha = 0.7, s = sz)
    ax.scatter(N, search, color = np.random.random(3), alpha = 0.7, s = sz)

#plt.title(method)
ax.set_xscale('log')
plt.ylim(0.0, 0.0005)
plt.ylabel('time')
plt.xlabel('N')
plt.legend([method+'_insert',method+'_delete',method+'_search'], loc='upper right')
#plt.show()
plt.savefig(path_to_img+method+"_N==M"+".png")