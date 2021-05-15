import random


def randChar(maxChar):
    return random.randint(ord('A'), ord(maxChar))


def genSeq(n, maxChar='Z'):
    lastc = 0
    lastn = 0
    seq = []
    for _ in range(n):
        c = randChar(maxChar)
        while c == lastc and lastn == 2:
            c = randChar(maxChar)
        if lastc == c:
            lastn = lastn+1
        else:
            lastc = c
            lastn = 1
        seq.append(chr(c))
    return seq


def genOp(seq, maxChar='Z'):
    return (
        random.randint(0, len(seq)),
        chr(randChar(maxChar))
    )


def eliminate(seq, rank):
    ok = False
    while not ok:
        i = rank
        l = len(seq)
        ok = True
        while i < l:
            j = i
            ele = seq[i]
            while j < l:
                if ele != seq[j]:
                    break
                j = j+1
            if j-i >= 3:
                for _ in range(j-i):
                    del seq[i]
                ok = False
                break
            i = i+1


def printSeq(file, seq):
    file.write("".join(seq))
    file.write("\n")


if __name__ == "__main__":
    n = int(input())
    m = int(input())
    input = open("input.txt", "w")
    middle = open("middle.txt", "w")
    output = open("output.txt", "w")
    mc = 'Z'

    seq = genSeq(n, mc)
    printSeq(input, seq)
    input.write(str(m)+"\n")
    for _ in range(m):
        op = genOp(seq, mc)
        input.write("{} {}\n".format(op[0], op[1]))
        if op[0] == len(seq):
            seq.append(op[1])
        else:
            seq.insert(op[0], op[1])
        eliminate(seq, op[0])
        printSeq(middle, seq)
    printSeq(output, seq)

    input.close()
    middle.close()
    output.close()
