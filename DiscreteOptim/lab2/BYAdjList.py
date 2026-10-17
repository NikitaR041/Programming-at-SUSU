class BYAdjList:
    def __init__(self, n = 0):
        self.n = n
        self.matrix = []

    def read_file(self, filename='example3.txt'):
        with open(filename, 'r') as f:
            lines = [line.strip() for line in f if line.strip()]
        self. n = int(lines[0])
        for line in lines[1:self.n+1]:
            parts = list(map(int, line.split()))
            k = parts[0]
            neigh = []
            for i in range(1, 1+2*k, 2):
                neigh.append((parts[i], parts[i+1]))
            self.matrix.append(neigh)
        return self.n, self.matrix
        
    # Конвертация в матрицу смежности
    def convert_in_adj_matrix(self):
        adj_matrix = [[0] * self.n for _ in range(self.n)]
        for i in range(self.n):
            for v, w in self.matrix[i]:
                adj_matrix[i][v-1] = w
        return self.n, adj_matrix

    # Конвертация в список ребер
    def convert_in_edges(self):
        edges = []
        for i in range(self.n):
            for v, w in self.matrix[i]:
                edges.append([i+1, v, w])
        return self.n, edges 

def save_adj_matrix_in_file(filename, n, adj_matrix):
    with open(filename, 'w') as f:
        f.write(f"{n}\n")
        for row in adj_matrix:
            f.write(" ".join(map(str, row)) + "\n")

def save_edges_to_file(filename, n, edges):
    with open(filename, 'w') as f:
        f.write(f"{n} {len(edges)}\n")  # N и количество рёбер
        for u, v, w in edges:
            f.write(f"{u} {v} {w}\n")

graph = BYAdjList()
# print(graph.read_file('example3.txt'))
size, m = graph.read_file('example3.txt')
print(size, m)

n, matrix = graph.convert_in_adj_matrix()
save_adj_matrix_in_file('example3_adj_m.txt', n, matrix)

n, edges = graph.convert_in_edges()
save_edges_to_file('example3_edges.txt', n, edges)
# n, a = graph.read_file('example3.txt')
# print(n, a)