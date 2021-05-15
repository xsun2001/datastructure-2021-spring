import random

n = 10
m = 10
tree = []


def genTree():
    edges = []
    inTree = []
    for _ in range(n*n//2):
        u = random.randint(1, n)
        v = random.randint(1, n)
        edge = [u, v] if u <= v else [v, u]
        edges.append(edge)

    def dfs(idx):
        for edge in edges:
            if idx == edge[0]:
                if not inTree[edge[1]]:
                    inTree[edge[1]] = True
                    tree[idx].append(edge[1])
                    dfs(edge[1])

    for _ in range(n+1):
        tree.append([])
        inTree.append(False)
    inTree[1] = True
    dfs(1)

    for i in range(1, n+1):
        if not inTree[i]:
            inTree[i] = True
            tree[1].append(i)


def printInt(x):
    print("{}".format(x), end=" ")


printInt(n)
printInt(m)
print()

genTree()
for i in range(1, len(tree)):
    printInt(len(tree[i]))
    for child in tree[i]:
        printInt(child)
    print()


def genPath():
    k = random.randint(1, 20)
    printInt(k)
    for _ in range(k):
        printInt(random.randint(1, 10))
    print()


for _ in range(m):
    op = random.randint(0, 2)
    printInt(op)
    print()
    if op == 0:
        genPath()
        genPath()
        print("0")
    else:
        genPath()
