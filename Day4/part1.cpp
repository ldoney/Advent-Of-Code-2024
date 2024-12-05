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

    std::string to_find = "XMAS";

    // Pretty redundant, I just think this is a better way of thinking of it than doing another 2x for loop
    std::vector<std::vector<int>> directions {{1,0}, {0,1}, {1,1}, {-1,0}, {0,-1}, {-1,-1}, {1,-1}, {-1,1}};
    for(int row = 0; row < grid.size(); row++) {
        for(int col = 0; col < grid[row].size(); col++) {
            for (std::vector<int> direction: directions) {
                bool failed = false;
                for (int pos_in_string = 0; pos_in_string < to_find.size(); pos_in_string++) {
                    int cur_row = row + direction[0]*pos_in_string; 
                    int cur_col = col + direction[1]*pos_in_string; 
                    if(cur_row >= grid.size() || cur_col >= grid[cur_row].size() || grid[cur_row][cur_col] != to_find[pos_in_string]) {
                        failed = true;
                        break;
                    }
                }
                if(!failed) {
                    result++;
                }
            }
        }
    }
    std::cout << "Result: " << result << "\n";
}
