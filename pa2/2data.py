import random
n = int(input())
for _ in range(n):
    print("1" if random.randint(0, 1) == 1 else "0", end="")
print()