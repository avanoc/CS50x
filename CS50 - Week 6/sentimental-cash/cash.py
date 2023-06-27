# TODO
from cs50 import get_float
import sys

# Keep prompting user for a non-negative float number:
while True:
    owed = get_float("Change owed: ")
    if owed > 0:
        break

# Initialize coins count:
coins = 0

# Calculate the minimum ammount of coins needed to give change
while owed - 0.25 >= 0:
    coins = coins + 1
    owed = round(owed - 0.25, 2)
while owed - 0.1 >= 0:
    coins = coins + 1
    owed = round(owed - 0.1, 2)
while owed - 0.05 >= 0:
    coins = coins + 1
    owed = round(owed - 0.05, 2)
while owed - 0.01 >= 0:
    coins = coins + 1
    owed = round(owed - 0.01, 2)

# Print the result
print(coins)

sys.exit()