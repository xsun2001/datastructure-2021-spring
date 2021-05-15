if __name__ == "__main__":
    n = 1
    m = 500000
    input = open("input.txt", "w")
    output = open("output.txt", "w")

    for i in range(n):
        if i % 2 == 0:
            input.write("A")
        else:
            input.write("B")
    input.write("\n{}\n".format(m))
    for i in range(m):
        if i % 2 == 0:
            input.write("0 B\n")
        else:
            input.write("0 A\n")
    input.write("0 C\n")
