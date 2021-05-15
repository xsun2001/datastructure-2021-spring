import random
n = 500000
res = ""
for _ in range(n):
    c = random.randint(0, 25)
    res = res + chr(ord('a')+c)
print(res)
