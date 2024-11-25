import matplotlib.pyplot as plt
import time

with open("./time.dat", "r") as f:
    tdata = f.read().split("\n")
    data = []
    for d in tdata:
        print(d)
        tmp = d.split(" ")
        if len(tmp) != 2:
            continue
        data.append([int(tmp[0]), float(tmp[1])])

print(data)


# Plotting the result
plt.loglog([x[0] for x in data], [x[1] for x in data], marker='o')
plt.title('Duration of Fibonacci Sequence Calculation')
plt.xlabel('N (Fibonacci index)')
plt.ylabel('Duration (Seconds)')
plt.grid(True)
plt.show()
