import random
import sys

n = 1000000
m = 200
cards = [0] * (n+1)

print("{} {}".format(n, m))

for _ in range(m):
    op = random.choice(["H", "Q"])
    l = random.randint(1, n)
    r = random.randint(1, n)
    [l, r] = [min(l, r), max(l, r)]
    print("{} {} {}".format(op, l, r))
    if op == "H":
        for i in range(l, r+1):
            cards[i] = cards[i]+1
    elif op == "Q":
        ans = 0
        for i in range(l, r+1):
            ans += cards[i]
        print(ans, file=sys.stderr)
