#include <iostream>
#include <vector>
#include <bitset>

struct Index {
    int m;
    int n;
};

void p_matrix(std::vector<std::vector<int>> A) {
    for (std::vector m: A) {
        for (int n: m)
            std::cout << n << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::bitset<400> replace(std::vector<std::vector<int>> &matrix, Index from, Index to, std::bitset<400> visited) {
    int s = matrix.size();
    int i = from.n + s*from.m;

    if (visited[i]) {
        return visited;
    } else {
        int to_copy = matrix[from.m][from.n];
        visited.flip(i);
        visited = replace(matrix, (struct Index){to.m, to.n}, (struct Index){to.n, s-to.m-1}, visited);
        matrix[to.m][to.n] = to_copy;
    }
    return visited;
}

int main() {
    // std::vector<std::vector<int>> matrix = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    std::vector<std::vector<int>> matrix = {
        {16,49,27,12,54,13, 2,69, 8},
        {17,33,47,50,41, 8,17,10,31},
        {29,30,20,39,59,25,21,79,35},
        {24,42,75,71,75,60,18, 7,35},
        {48,26,24,58,60,75,25,30,36},
        {50,49,48, 1,14,14,22,71,75},
        {48,28, 9, 3,69,68,15,61,63},
        {76,-1, 6,31,49,50,73,43,30},
        {68,69,62,24,39,47, 8,57,78}
    };
    // std::vector<std::vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9}};
    int s = matrix.size();
    p_matrix(matrix);
    
    std::bitset<400> visited;
    for (int m = 0; m < s; m++) {
        for (int n = 0; n < s; n++) {
            visited = replace(matrix, (struct Index){m,n}, (struct Index){n,s-m-1}, visited);
        }
    }
    p_matrix(matrix);

    return 0;
}
