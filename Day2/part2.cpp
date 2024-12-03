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
        bool all_safe = false;
        for(int skip = 0; skip < line.size(); skip++) {
            std::vector<int> line_copy = {};
            std::copy(line.begin(), line.end(), std::back_inserter(line_copy));
            line_copy.erase(line_copy.begin() + skip);
            bool safe = true;
            bool increasing = line_copy[1] > line_copy[0];
            for(int i = 0; i < line_copy.size()-1; i++) {
                int dist = abs(line_copy[i] - line_copy[i+1]);
                if (!(dist >= 1 && dist <= 3)) {
                    safe = false;
                    break;
                }
                if (increasing && line_copy[i+1] < line_copy[i]) {
                    safe = false;
                    break;
                }
                if (!increasing && line_copy[i+1] > line_copy[i]) {
                    safe = false;
                    break;
                }
            }
            if (safe) {
                all_safe = true;
                break;
            }
        }
        if (all_safe) {
            safe_count++;
        }
    }
    std::cout << "Safe count: " << safe_count << "\n";
}
