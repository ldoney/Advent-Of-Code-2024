#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

void print_map(std::vector<std::vector<char>> map) {
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[0].size(); j++) {
            std::cout << map[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    std::ifstream infile("sample_input");
    std::string line;
    std::vector<std::vector<char>> map_default{};
    int result = 0;

    int row_counter = 0;
    int pos_row = 0, pos_col = 0;
    std::vector<char> channels = {};

    while(std::getline(infile, line)) {
        std::vector<char> lineChars = {};
        for(int i = 0; i < line.length(); i++) {
            if(std::find(channels.begin(), channels.end(), line[i]) == channels.end() && line[i] != '.')
                channels.push_back(line[i]);
            lineChars.push_back(line[i]);
        }
        map_default.push_back(lineChars);
        row_counter++;
    }
    infile.close();

//    for(char c: channels) {std::cout << c << " ";}
//    std::cout << "\n";
    int map_size_rows = map_default.size();
    int map_size_cols = map_default[0].size();

    std::map<char, std::vector<std::vector<char>>> channels_map = {};
    for (char c: channels) {
        std::vector<std::vector<char>> map = map_default;
        for(int i = 0; i < map_size_rows; i++) {
            for(int j = 0; j < map_size_cols; j++) {
                if(map[i][j] != c)
                    map[i][j] = '.';
            }
        }
        channels_map[c] = map;
    }
    std::vector<std::pair<int,int>> global_positions = {};
    for (auto &[channel, map] : channels_map) {
        std::cout << "Channel " << channel << ": \n";
        print_map(map);
        std::vector<std::pair<int,int>> positions = {};
        for(int i = 0; i < map_size_rows; i++) {
            for(int j = 0; j < map_size_cols; j++) {
                if(map[i][j] == channel) {
                    positions.push_back(std::pair<int,int>{i,j});
                }
            }
        }

        for(int i = 0; i < positions.size(); i++) {
            std::cout << "i: " << std::get<0>(positions[i]) << ", " << std::get<1>(positions[i]) << "\n";
            for(int j = 0; j < positions.size(); j++) {
                std::cout << "j: " <<std::get<0>(positions[j]) << ", " << std::get<1>(positions[j]) << "\n";
                if(i == j) continue;
                std::pair<int, int> relative_distance {
                    std::get<0>(positions[i]) - std::get<0>(positions[j]), 
                    std::get<1>(positions[i]) - std::get<1>(positions[j])
                };
                std::cout << "Relative distance: " << std::get<0>(relative_distance) << ", " << std::get<1>(relative_distance) << "\n";

                int new_row = std::get<0>(positions[i]) + std::get<0>(relative_distance);
                int new_col = std::get<1>(positions[i]) + std::get<1>(relative_distance);
                std::pair<int, int> new_pair = {new_row, new_col};
                std::cout << "New pos: " << new_row << ", " << new_col << "\n";
                if(new_row < 0 || new_col < 0 || new_row >= map_size_rows || new_col >= map_size_cols)
                    continue;
                if(find_if(global_positions.begin(), global_positions.end(), [&new_pair](const std::pair<int, int> &arg) {return arg.first == new_pair.first && arg.second == new_pair.second;}) == global_positions.end())
                    global_positions.push_back(std::pair<int,int> {new_row, new_col});
            }
        }
        std::cout << "\n";
        print_map(map);
    }

    std::cout << "Result: " << global_positions.size() << "\n";
}

