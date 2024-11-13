import matplotlib.pyplot as plt
import numpy as np

# Load the data from the file
data = np.loadtxt("perf.dat", skiprows=1)

# Split the data into separate arrays for each column
size = data[:, 0]
mallocmemset_time = data[:, 1]
calloc_time = data[:, 2]

# Create the plot
plt.figure(figsize=(8, 6))
plt.plot(size, mallocmemset_time, label='malloc/memset', marker='o')
plt.loglog(size, calloc_time, label='calloc', marker='s')

# Set title and labels
plt.title('Time taken for different memory allocation functions')
plt.xlabel('Size (bytes)')
plt.ylabel('Time (seconds)')

# Add legend
plt.legend()

# Show grid lines
plt.grid(True)

# Display the plot
plt.show()
