#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

int myFunc(const std::vector<int>& arr) {
    int count = 0;
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const int SIZE = 10000;
    std::vector<int> arr(SIZE);

   std::srand(std::time(nullptr));
   
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (std::rand() % 100000) + 1;
    }
    auto start = std::chrono::high_resolution_clock::now();
    int c = myFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> finish = end - start;
    std::cout << "Количество дубликатов в массиве: " << c << std::endl;
    std::cout << "Время работы алгоритма на C++: " << finish.count() << " миллисекунд" << std::endl;

    return 0;
}