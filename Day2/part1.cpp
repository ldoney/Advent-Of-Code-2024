#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

int main() {
    std::ifstream infile("input");
    std::vector<std::vector<int>> vectors;

    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        std::vector<int> new_vec;
        int v;
        while (ss >> v) {
            new_vec.push_back(v);
        }
        vectors.push_back(new_vec);
    }
    infile.close();

    int safe_count = 0;
    for(std::vector<int> line : vectors) {
        bool safe = true;
        bool increasing = line[1] > line[0];
        for(int i = 0; i < line.size()-1; i++) {
            int dist = abs(line[i] - line[i+1]);
            if (!(dist >= 1 && dist <= 3)) {
                safe = false;
                break;
            }
            if (increasing && line[i+1] < line[i]) {
                safe = false;
                break;
            }
            if (!increasing && line[i+1] > line[i]) {
                safe = false;
                break;
            }
        }
        if (!safe) {
            continue;
        }
        safe_count++;
    }
    std::cout << "Safe count: " << safe_count << "\n";
}
