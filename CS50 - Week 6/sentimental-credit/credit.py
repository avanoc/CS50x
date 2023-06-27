# TODO
from cs50 import get_string

# Prompt user for a credit card number:
while True:
    number = get_string("Number: ")
    if number.isdigit():
        break

# Check if number corresponds to AMEX card:
if len(number) == 15:
    if number[0] == '3' and number[1] == '4' or number[1] == '7':
        print("AMEX\n")
# Check if number corresponds to MC card:
elif len(number) == 16:
    if number[0] == '5' and 1 <= int(number[1]) <= 5:
        print("MASTERCARD\n")
# Check if number corresponds to VISA card:
    elif number[0] == '4':
        print("VISA\n")
elif len(number) == 13:
    if number[0] == '4':
        print("VISA\n")
# The number doesn't correspond to any card:
else:
    print("INVALID\n")
