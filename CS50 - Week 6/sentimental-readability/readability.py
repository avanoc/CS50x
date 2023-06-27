# TODO

from cs50 import get_string

# Prompt user for text:
text = get_string("Text: ")

# Set initial count parameters:
letters = 0
words = 1
sentences = 0

# Calculate how many letters, words and sentences there are:
for x in range(len(text)):
    if text[x].isalpha():
        letters = letters + 1
    elif text[x] == " ":
        words = words + 1
    elif text[x] == '.' or text[x] == '?' or text[x] == '!':
        sentences = sentences + 1

# Calculate Coleman-Liau index:
L = letters * 100 / words
S = sentences * 100 / words
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print result:
if index <= 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")