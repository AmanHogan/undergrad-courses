import numpy as np
import matplotlib.pyplot as plt

# Sample data and plot
x_ticks = [0, 0.3050, 0.6100, 0.9150, 1.2200, 1.5250, 1.8299, 2.1350, 2.4400, 2.7450, 3.0500, 3.3550, 3.6600, 3.9650, 4.2700, 4.575, 4.8800]
y_ticks = [0, 0.3050, 0.6100, 0.9150, 1.2200, 1.5250, 1.8299, 2.1350, 2.4400, 2.7450, 3.0500]

fig, ax = plt.subplots(figsize=(10,6))

ax.set_xticks(x_ticks)
ax.set_yticks(y_ticks)

# Enabling grid lines:
ax.grid()

plt.show() 



