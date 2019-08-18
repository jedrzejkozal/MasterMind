import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse
from matplotlib.collections import PatchCollection
import numpy as np

num2col = {
    0:  "beige",
    1:  "red",
    2:  "green",
    3:  "purple",
    4:  "turquoise",
    5:  "gray",
    6:  "blue",
    7:  "yellow",
    8:  "black",
}

fig, ax = plt.subplots()


def plot_sequence(colors, y=0.5, y_radius=0.04):
    for i in range(6):
        e = Ellipse((2.0*i+1, y), 2.0, y_radius,
                    color=colors[i], linewidth=0.8)
        e.set_edgecolor("black")
        ax.add_artist(e)


def plot_sequences(sequences):
    for colors, y in zip(sequences, np.arange(len(sequences)*0.08, 0, -0.08)):
        plot_sequence(colors, y=y, y_radius=0.08)


def sequence_to_colors(sequence):
    colors = []
    for e in sequence:
        colors.append(num2col[e])
    return colors


def sequences_to_colors(sequences):
    colors = []
    for sequence in sequences:
        colors.append(sequence_to_colors(sequence))
    return colors


sequence_to_guess = [5, 8, 4, 7, 0, 4]
plot_sequence(sequence_to_colors(sequence_to_guess))

plt.xlim(-1, 13)
plt.ylim(0.4, 0.6)

plt.axis('off')
fig.savefig('sequence_to_guess.png')


fig, ax = plt.subplots()
fig.set_size_inches(15.5, 20.5, forward=True)

"""
sequence to guess = 584704
genetic algorithm sequence = 586348
genetic algorithm sequence = 046322
genetic algorithm sequence = 180047
genetic algorithm sequence = 471848
genetic algorithm sequence = 588784
genetic algorithm sequence = 588514
genetic algorithm sequence = 587704
genetic algorithm sequence = 584704
fitnessValue = -2
"""

sequences = [
    [5, 8, 6, 3, 4, 8],
    [0, 4, 6, 3, 2, 2],
    [1, 8, 0, 0, 4, 7],
    [4, 7, 1, 8, 4, 8],
    [5, 8, 8, 7, 8, 4],
    [5, 8, 8, 5, 1, 4],
    [5, 8, 7, 7, 0, 4],
    [5, 8, 4, 7, 0, 4],
]
plot_sequences(sequences_to_colors(sequences))

plt.xlim(-1, 13)
plt.ylim(0.0, 0.7)

plt.axis('off')
fig.savefig('guesses.png')
plt.show()
