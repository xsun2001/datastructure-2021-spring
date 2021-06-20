from random import randint

n = int(input())
k = int(input())
print("{} {}".format(n, k))


def generateArray():
    arr = []
    for i in range(n):
        x = randint(1, 2 * n)
        arr.append(x)
        print(str(x), end=" ")
    print()
    return arr


a = generateArray()
b = generateArray()
c = generateArray()

t = []
l = min(n, k)
for x in range(l):
    for y in range(l):
        for z in range(l):
            t.append(a[x] + b[y] + c[z])
t = sorted(t)
# for x in t:
#     print(str(x), end=" ")
# print()
print("{}".format(t[k - 1]))
