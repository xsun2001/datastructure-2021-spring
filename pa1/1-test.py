import random

input = open("1.in", "w");
output = open("1.out", "w");
n = 500
input.write(str(n) + "\n")
for _ in range(n):
    a = random.getrandbits(5000)
    b = random.getrandbits(5000)
    input.write(str(a) + " " + str(b) + "\n")
    r = a*b
    output.write(str(r) + "\n")
input.close()
output.close()
