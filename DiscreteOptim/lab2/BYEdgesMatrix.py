class BYEdgesMatrix:
    def __init__(self, n = 0, m = 0): 
        self.n = n
        self.m = m
        self.matrix = []

    def read_file(self, filename='example2.txt'):
        with open(filename, 'r') as f:
            lines = [line.strip() for line in f if line.strip()]
        self.n, self.m = map(int, lines[0].split())
        self.matrix = [[int(x) for x in line.split()] for line in lines[1:self.m + 1]]
        return self.n, self.m, self.matrix

    # Конвертация в матрицу смежности
    def convert_in_adj_matrix(self):
        adj_matrix = [[0] * self.n for _ in range(self.n)]
        for elem in self.matrix:
            u, v, w = elem[0], elem[1], elem[2]
            adj_matrix[u-1][v-1] = w
        return self.n, adj_matrix

    # Конвертация в список смежности
    def convert_in_adj_l(self):
        adj_list = [[] for _ in range(self.n)]
        for edge in self.matrix:
            u, v, w = edge[0], edge[1], edge[2]
            adj_list[u-1].append((v, w))
        return self.n, adj_list

def save_adj_matrix_in_file(filename, n, adj_matrix):
    with open(filename, 'w') as f:
        f.write(f"{n}\n")
        for row in adj_matrix:
            f.write(" ".join(map(str, row)) + "\n")

def save_adj_l_in_file(filename, n, adj_l):
    with open(filename, 'w') as f:
        f.write(f"{n}\n")
        for neigh in adj_l:
            row = [str(len(neigh))]
            for v, w in neigh:
                row.extend([str(v), str(w)])
            f.write(" ".join(row)+'\n')

graph = BYEdgesMatrix()
size_n, size_m, m = graph.read_file('example2.txt')
print(size_n, size_m, m)

n, adj_m = graph.convert_in_adj_matrix()
# print(n, adj_m)
save_adj_matrix_in_file("example2_adj_matrix.txt", n, adj_m)

n, adj_l = graph.convert_in_adj_l()
save_adj_l_in_file("example2_adj_l.txt", n, adj_l)
# print(n, adj_l)

# save_edges_to_file('example1_edges.txt', n, edges)
# tmp = graph.read_file('example2.txt')
# print(tmp)
# n, m, matrix = graph.read_file('example2.txt')    
# print(n, m, matrix)
