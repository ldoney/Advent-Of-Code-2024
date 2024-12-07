#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

unsigned long long stou(std::string const & str, size_t * idx = 0, int base = 10) {
    unsigned long long result = std::stoul(str, idx, base);
    if (result > std::numeric_limits<unsigned long long>::max()) {
        throw std::out_of_range("stou");
    }
    return result;
}

int main() {
    std::ifstream infile("sample_input");
    std::string line;
    unsigned long long result = 0;
    
    std::regex const exp{R"~(^(\d+):(.*)$)~"};

    while(std::getline(infile, line)) {
        std::smatch m;

        auto words_begin = 
            std::sregex_iterator(line.begin(), line.end(), exp);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; i++) {
            std::smatch match = *i;
//            std::cout << match.str(1) << "\n";
            unsigned long long to_check_against = stou(match.str(1));

            std::stringstream stream(match.str(2));
            std::vector<int> int_list = {};
            while(true) {
                unsigned int n;
                stream >> n;
                if(!stream)
                    break;
                int_list.push_back(n);
            }
            unsigned int num_spaces = int_list.size() - 1;

            const unsigned int NUM_INPUTS = num_spaces;
            unsigned int combinations = 1 << NUM_INPUTS;

            for(unsigned int q = 0; q < combinations; q++) {
                unsigned long long last_result = int_list[0];
                std::cout << last_result;
                int index = 0;
                for(int w = NUM_INPUTS -1; w > -1; w--) {
                    index++;
                    bool multiply = (q >> w) & 1;
                    if(multiply) {
                        std::cout << " * ";
                        last_result = last_result * int_list[index];    
                    } else {
                        std::cout << " + ";
                        last_result = last_result + int_list[index];    
                    }
                    std::cout << int_list[index];
                    if(last_result > to_check_against)
                        break;
                }
                std::cout << " = " << last_result << "\n";
                if (last_result == to_check_against) {
                    std::cout << "Found!\n";
                    result += to_check_against;
                    break;
                } 
            }
        }
    }
    infile.close();

    std::cout << "Result: " << result << "\n";
}
