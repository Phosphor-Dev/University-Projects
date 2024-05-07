from collections import deque
 
def bfs_shortest_path(graph, start):
    # Create a queue and add the starting vertex to it
    queue = deque([start])
     
    # Create an array to keep track of the distances from the starting vertex to all other vertices
    distances = [float('inf')] * len(graph)
    distances[start] = 0
     
    # Create a set to keep track of visited vertices
    visited = set()
     
    # Perform BFS
    while queue:
        # Dequeue the next vertex
        vertex = queue.popleft()
        visited.add(vertex)
         
        # Update the distances of neighbors
        for neighbor in graph[vertex]:
            if neighbor not in visited:
                distances[neighbor] = distances[vertex] + 1
                queue.append(neighbor)
     
    return distances
 
 
# Example graph: unweighted, directed graph with 5 vertices
# Vertices are represented by integers 0 through 4
# Edges: (0, 1), (0, 2), (1, 2), (1, 3), (2, 3), (3, 4)
 
graph = [[1, 2], [2, 3], [3], [4], []]
 
start_vertex = 0
distances = bfs_shortest_path(graph, start_vertex)
 
print(distances)  # Output: [0, 1, 1, 2, 3]