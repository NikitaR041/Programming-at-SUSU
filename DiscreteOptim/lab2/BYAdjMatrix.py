class BYAdjMatrix:
    def __init__(self, n = 0):
        self.n = n
        self.matrix = []

    def read_file(self, filename='example1.txt'):
        with open(filename, 'r') as f:
            lines = [line.strip() for line in f if line.strip()]
        self.n = int(lines[0])
        self.matrix = [[int(x) for x in line.split()] for line in lines[1:self.n + 1]]
        return self.n, self.matrix
    # Конвертация в список рёбер 
    def convert_in_edges(self):
        edges = []
        for i in range(self.n):
            for j in range(self.n):
                if self.matrix[i][j] != 0:
                    edges.append([i + 1, j + 1, self.matrix[i][j]])
        return self.n, edges

    # Конвертация в список смежности
    def convert_in_adj_l(self):
        adj_list = []
        for i in range(self.n):
            neigh = []
            for j in range(self.n):
                if self.matrix[i][j] != 0:
                    neigh.append((j + 1, self.matrix[i][j]))
            adj_list.append(neigh)
        return self.n, adj_list

def save_edges_to_file(filename, n, edges):
    with open(filename, 'w') as f:
        f.write(f"{n} {len(edges)}\n")  
        for u, v, w in edges:
            f.write(f"{u} {v} {w}\n")

def save_adj_to_file(filename, n, adj_list):
    with open(filename, 'w') as f:
        f.write(f"{n}\n")
        for neigh in adj_list:
            row = [str(len(neigh))]  
            for v, w in neigh:
                row.extend([str(v), str(w)])  
            f.write(" ".join(row) + "\n")


graph = BYAdjMatrix()
size, m = graph.read_file('example1.txt')
print(size, m)
# n, matrix = graph.read_file('example1.txt')
# print(n, matrix)
# write_file() # Почему не рабтает - отключи комментарии в блоке кода выше

n, edges = graph.convert_in_edges()
save_edges_to_file('example1_edges.txt', n, edges)

n, adj = graph.convert_in_adj_l()
save_adj_to_file('example1_adj.txt', n, adj)

