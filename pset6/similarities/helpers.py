from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    x = ""
    y = ""
    list1 = []
    list2 = []
    list3 = []

    for i in a:
        if i != '\n':
            x += str(i)
        else:
            list1.append(x)
            x =""
    list1.append(x)

    for j in b:
        if j != '\n':
            y += str(j)
        else:
            list2.append(y)
            y = ""
    list2.append(y)

    list2 = set(list2)
    list1 = set(list1)

    return list1.intersection(list2)


def sentences(a, b):
    """Return sentences in both a and b"""

    list1 = sent_tokenize(a)
    list2 = sent_tokenize(b)

    return set(list1).intersection(set(list2))

def butherize(string,n):
    list1 = []
    i = 0
    str_len = len(string)
    while ((i + n) <= str_len):
        list1.append(string[i:(i+n)])
        i += 1
    return list1

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    list2 = butherize(a,n)
    list3 = butherize(b,n)

    return set(list2).intersection(set(list3))
