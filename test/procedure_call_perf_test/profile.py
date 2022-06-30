import os
import matplotlib.pyplot as plt
import subprocess

x = []
y = []
print("testing lower1")
os.system("gcc lower.c -g -Og -o lower")
p = subprocess.run("./lower", capture_output=True)
data = p.stdout.decode().strip().split("\n")
data = [[float(n) for n in str.split(" ")] for str in data]
print(data)
for i in data:
    x.append(i[0])
    y.append(i[1])

fig, ax = plt.subplots()
ax.plot(x, y)

x = []
y = []
os.system("gcc lower.c -g -Og -D OPTIMIZED_LOWER -o lower")
print("testing lower2")
p = subprocess.run("./lower", capture_output=True)
data = p.stdout.decode().strip().split("\n")
data = [[float(n) for n in str.split(" ")] for str in data]
print(data)
for i in data:
    x.append(i[0])
    y.append(i[1])

ax.plot(x, y)

plt.show()

"""
Observed expected behaviour. (i.e. the execution time of `lower` function is proportional to n^2)

Note: the text read need to be converted to float.. I was pretty strange at the first time why I plotted a stright line (though it is obvious Y axis' tick locations are not linear), then I wasted half an hour to debug it...
"""
