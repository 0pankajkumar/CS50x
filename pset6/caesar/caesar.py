from cs50 import get_string
from sys import argv

script, first = argv

a = int(argv[1])
s = get_string("plaintext: ")
lum = len(s)
result = ""

for i in range(0, lum):
    char = s[i]

    # Encrypt uppercase characters
    if(char.isupper()):
        result += chr((ord(char) + a - 65) % 26 + 65)

    # Encrypt lowercase characters
    else:
        result += chr((ord(char) + a - 97) % 26 + 97)

print("ciphertext: ", result)

