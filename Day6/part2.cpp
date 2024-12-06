#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#define MAX_CROSSES 1000
enum OBJECT{GUARD, OBSTRUCTION, EMPTY, VISITED};
enum DIRECTION{RIGHT, LEFT, UP, DOWN};

DIRECTION char_to_direction(char c) {
    switch(c) {
        case '^': return UP;
        case '>': return RIGHT;
        case '<': return DOWN;
        case 'v': return LEFT;
        // Should never happen...
        default: return UP;
    }
}

OBJECT get_type_from_char(char c) {
    if (c == '^' || c == '>' || c == '<' || c == 'v') {
        return GUARD;
    } else if (c == '#') {
        return OBSTRUCTION;
    } else if (c == '.') {
        return EMPTY;
    } else if (c == 'X') {
        return VISITED;
    }
    return EMPTY;
}

char get_char_from_type(OBJECT o, DIRECTION d) {
    switch(o) {
        case GUARD: switch(d) {
            case UP: return '^';
            case LEFT: return '<';
            case DOWN: return 'v';
            case RIGHT: return '>';
        }
        case OBSTRUCTION: return '#';
        case EMPTY: return '.';
        case VISITED: return 'X';
    }
    return EMPTY;
}

void print_map(std::vector<std::vector<OBJECT>> map, DIRECTION direction) {
    for(std::vector<OBJECT> line: map) {
        for(OBJECT entry : line) {
            std::cout << get_char_from_type(entry, direction);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::ifstream infile("input");
    std::string line;
    std::vector<std::vector<OBJECT>> original_map{};
    int result = 0;

    int row_counter = 0;
    int original_pos_row = 0, original_pos_col = 0;
    DIRECTION original_direction;

    while(std::getline(infile, line)) {
        std::vector<OBJECT> lineTypes = {};
        for(int i = 0; i < line.length(); i++) {
            char c = line[i];
            OBJECT type = get_type_from_char(c);
            if(type == GUARD) {
                original_pos_row = row_counter;
                original_pos_col = i;
                original_direction = char_to_direction(c);
            }
            lineTypes.push_back(type);
        }
        original_map.push_back(lineTypes);
        row_counter++;
    }
    infile.close();

    for(int paradox_row = 0; paradox_row < original_map.size(); paradox_row++) {
        for(int paradox_col = 0; paradox_col < original_map[0].size(); paradox_col++) {
            if(original_map[paradox_row][paradox_col] != EMPTY) {
                continue;
            }
//            std::cout << paradox_row << " " << paradox_col << "\n";
            std::vector<std::vector<OBJECT>> map = original_map;
            int pos_row = original_pos_row, pos_col = original_pos_col;
            DIRECTION direction = original_direction;
            bool is_time_loop = true;

            map[paradox_row][paradox_col] = OBSTRUCTION;
            int suspected_loop_row = 0;
            int suspected_loop_col = 0;
            int crosses = 0;
            while(crosses < MAX_CROSSES) {
//                print_map(map, direction);
                int new_pos_row = pos_row;
                int new_pos_col = pos_col;
                switch(direction) {
                    case UP: new_pos_row -= 1; break;
                    case DOWN: new_pos_row += 1; break;
                    case LEFT: new_pos_col -= 1; break;
                    case RIGHT: new_pos_col += 1; break;
                }
                if(!(new_pos_row < map.size() && new_pos_row >= 0 && 
                new_pos_col >= 0 && new_pos_col < map[0].size())) {
                    is_time_loop = false;
                    break;
                }
                if (map[new_pos_row][new_pos_col] == OBSTRUCTION) {
                    switch(direction) {
                        case UP: direction = RIGHT; break;
                        case RIGHT: direction = DOWN; break;
                        case DOWN: direction = LEFT; break;
                        case LEFT: direction = UP; break;
                    }
                } else {
                    if(map[new_pos_row][new_pos_col] == VISITED) {
                        crosses++;
                    }
                    map[pos_row][pos_col] = VISITED;
                    map[new_pos_row][new_pos_col] = GUARD;
                    pos_row = new_pos_row;
                    pos_col = new_pos_col;
                }
            }
            if(is_time_loop) {
                result++;
            }
        }
    }

    std::cout << "Result: " << result << "\n";
}
