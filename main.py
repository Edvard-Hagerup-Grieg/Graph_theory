import matplotlib.pyplot as plt
import os
import numpy as np
from itertools import cycle


path_to_files = "C:\\Users\\donte_000\\Downloads\\Telegram Desktop\\hash"
path_to_img = "c:/Program Files/Mozilla Firefox/firefox.exe"
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
            #print(insert)
            #if name == "CUCKOO":
            dict[name].append([insert, delete, search , n, m])
cycol = cycle('bgrcmykw')
name = "CHAIN"
for meth in ["CHAIN" ]:#"CUCKOO", "CHAIN","DOUBLE"
    insert = []
    delete = []
    search = []
    N = []
    M = []
    for inf in dict[meth]:
        if inf[3] == inf[4]:
            insert.append(inf[0])
            delete.append(inf[1])
            search.append(inf[2])
            N.append(inf[3])
            M.append(inf[4])

    #plt.axes((0, 1000, 0, 0.001))
    plt.semilogx(N, insert, color = np.random.random(3), alpha = 0.7)
    plt.semilogx(N, delete, color = np.random.random(3), alpha = 0.7)
    plt.semilogx(N, search, color = np.random.random(3), alpha = 0.7)
#plt.title(name)
plt.xlim(0, 1000)
#plt.ylim(0,0.00001)
plt.ylabel('time')
plt.xlabel('N')
#'CUCKOO_insert','CUCKOO_delete','CUCKOO_search','CHAIN_insert','CHAIN_delete','CHAIN_search','DOUBLE_insert','DOUBLE_delete','DOUBLE_search'
plt.legend(['CHAIN_insert','CHAIN_delete','CHAIN_search'], loc='upper right')
#plt.show()
plt.savefig(name+"N==M"+".png")
#plt.clf()

