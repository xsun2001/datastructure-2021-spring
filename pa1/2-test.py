import random

input_file = open("2.in", "w")
output_file = open("2.out", "w")

n = 100
xl = list(range(1, n+1))
yl = list(range(1, n+1))
x = list(range(1, n+1))
y = list(range(1, n+1))
input_file.write(str(n) + "\n")
random.shuffle(xl)
random.shuffle(yl)
for i in xl:
    input_file.write(str(i) + " ")
input_file.write("\n")
for i in yl:
    input_file.write(str(i) + " ")
input_file.write("\n")

m = 1
input_file.write(str(m)+"\n")
for _ in range(m):
    px = random.randint(1, n)
    py = random.randint(1, n)
    input_file.write(str(px) + " " + str(py) + "\n")
    res = n
    for i in range(n):
        qx = (i + 1) / (py/px + 1)
        if qx > px:
            res = i
            break
    output_file.write(str(res) + "\n")

input_file.close()
output_file.close()
