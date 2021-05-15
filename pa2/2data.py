import random

n = int(input())
ans = ""
for _ in range(n):
    ans += ("1" if random.randint(0, 1) == 1 else "0")
print(ans)
