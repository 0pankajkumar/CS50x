from cs50 import get_int  # To obtain better input

# To get valid input from user
while True:
    n = get_int("Height: ")
    if (n >= 0 and n <= 23):
        break

for i in range(0, n):     # printing main loop
    for j in range(n - i - 2, -1, -1): # printing spaces
        print(" ", end = "")
    for k in range(0, i + 2):   # printing the hashes
        print("#", end="")
    print() # printing newline

# End of program
