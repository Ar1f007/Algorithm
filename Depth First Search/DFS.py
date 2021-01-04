"""
            --------------------- Depth First Search(DFS) Implementation ---------------------
                            ------------------- Python 3.8 -------------------

"""
from collections import defaultdict
graph = defaultdict(list)               # defaultdict used because it doesn't show keyError


def dfs(explored, graph, node, d):
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
            dfs(explored, graph, neighbour, d+1)


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

    # set for keeping track of the explored nodes
    explored = set()

    # depth counting set. It will keep track of all the depths
    depth = []

    # assigned 0 to d, here d is like depth index
    # it will print depth value of the explored node
    d = 0

    # dfs called
    dfs(explored, graph, source, d)

    # max function returns the maximum value from the depth list
    # that is consists of different depth values
    print("\nMaximum Depth reached:", max(depth))