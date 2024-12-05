#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

int main() {
    std::ifstream infile("input");
    std::string line;
    std::vector<std::vector<char>> grid = {};
    int result = 0;

    while(std::getline(infile, line)) {
        std::vector<char> new_line(line.begin(), line.end());
        grid.push_back(new_line);
    }
    infile.close();

    std::string to_find = "MAS";
    std::string to_find_reverse = std::string(to_find.rbegin(), to_find.rend());

    // Pretty redundant, I just think this is a better way of thinking of it than doing another 2x for loop
    std::vector<std::vector<int>> directions {{1,1}, {-1,1}};
    for(int row = 1; row < grid.size()-1; row++) {
        for(int col = 1; col < grid[row].size()-1; col++) {
            if (grid[row][col] == 'A') {
                bool bad_entry = false;
                
                for(std::vector<int> direction : directions) {
                    std::vector<char> found = {grid[row - direction[0]][col - direction[1]], grid[row][col], grid[row + direction[0]][col + direction[1]]};
                    std::string s(found.begin(), found.end());
                    std::cout << s << "\n";
                    if(!(s == to_find || s == to_find_reverse)) {
                        bad_entry = true;
                    }
                }
                if(!bad_entry) {
                    result++;
                }
            }
        }
    }
    std::cout << "Result: " << result << "\n";
}

