"""
                ----------------- Iterative Deepening Search(IDS) Implementation -----------------
                             --------------------- Python 3.8 ----------------------

"""
from collections import defaultdict
graph = defaultdict(list)               # defaultdict used because it doesn't show keyError


def ids(explored, graph, node, d, limit):
    # checking if depth value is less than the limit
    if d <= limit:
        if node not in explored:

            # printing the explored node along with its depth
            print("Explored", node, "at depth", d)

            # adding visited node to the explored set
            explored.add(node)

            """
                Recursive method being implemented here
                # loop exploring the neighbour of the current node
            """
            for neighbour in graph[node]:
                ids(explored, graph, neighbour, d + 1, limit)


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

    limit = 0
    while limit <= 9:

        # set for keeping track of the explored nodes
        explored = set()

        # assigned 0 to d, here d is like depth index
        # it will print depth value of the explored node
        d = 0

        # print in depth limit order from 0 to 9
        print("\n\nWhen depth limit:", limit, "\n")
        ids(explored, graph, source, d, limit)
        limit += 1