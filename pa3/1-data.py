from random import randint

n = int(input())
k = int(input())
a = []

print("{} {}".format(n, k))
for i in range(n):
    x = randint(0, 2 ** 64)
    print("{:064b}".format(x))
    a.append(x)

for i in range(n):
    l = max(0, i - k - 1)
    r = min(n, i + k + 2)
    maxv = 0
    maxi = 0
    for j in range(l, r):
        if maxv < (a[i] ^ a[j]):
            maxv = a[i] ^ a[j]
            maxi = j
    print("{}".format(maxi))
