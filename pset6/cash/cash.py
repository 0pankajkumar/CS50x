# Importing cs50 library.
from cs50 import get_float

# A do while type of loop to get input.
while True:
    f1 = get_float("O hai! How much change is owed?")
    if (f1 > 0):
        break

# Converting into cents.
f1 *= 100
f = f1

count = 0

while (f >= 25):
    f = f - 25
    count += 1

while (f >= 10):
    f = f - 10
    count += 1

while (f >= 5):
    f = f - 5
    count += 1

while (f >= 1):
    f = f - 1
    count += 1

print(count)
