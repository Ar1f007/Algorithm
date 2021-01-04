"""
            --------------------- Depth Limited Search(DLS) Implementation ---------------------
                            ------------------ Python 3.8 ----------------------

"""
from collections import defaultdict
graph = defaultdict(list)               # defaultdict used because it doesn't show keyError


def dls(explored, graph, node, d, limit):
    # checking if depth value is less than the limit
    if d <= limit:
        if node not in explored:

            # appending depth value to the depth list
            depth.append(d)

            # printing the explored node along with its depth
            print("Explored", node, "at depth", d)

            # adding visited node to the explored set
            explored.add(node)

            """
                Recursive method being implemented here
                # loop exploring the neighbour of the current node
            """
            for neighbour in graph[node]:
                dls(explored, graph, neighbour, d + 1, limit)


if __name__ == '__main__':
    # taking input for node and edges
    node, edge = map(int, input().split())
    i = 0
    while i < edge:
        i += 1
        a, b = map(int, input().split())

        # graph adjacency list
        # a connects b and b connects a
        graph[a].append(b)
        graph[b].append(a)

    # source input taken
    source = int(input())

    # depth limit input
    limit = int(input())

    # set for keeping track of the explored nodes
    explored = set()

    # depth counting set. It will keep track of all the depths
    depth = []

    # assigned 0 to d, here d is like depth index
    # it will print depth value of the explored node
    d = 0

    # dls called
    dls(explored, graph, source, d, limit)

    # max function returns the maximum value from the depth list
    # that is consists of different depth values
    print("\nMaximum Depth reached:", max(depth))