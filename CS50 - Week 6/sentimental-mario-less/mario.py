# TODO
from cs50 import get_int

# Prompt user for the pyramide's height:
while True:
    height = get_int("Height: ")
    if 0 < height < 9:
        break

width = 1
space = height - 1

for x in range(height):
    print(space * " ", end="")
    space = space - 1
    for y in range(width):
        print("#", end="")
    width = width + 1
    print()

