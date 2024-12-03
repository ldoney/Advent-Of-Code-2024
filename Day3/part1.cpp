#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

int main() {
    std::ifstream infile("input");
    std::string line;
    int result = 0;

    std::regex const exp{R"~(mul\((\d+)\,(\d+)\))~"};

    while(std::getline(infile, line)) {
        std::smatch m;

        auto words_begin = 
            std::sregex_iterator(line.begin(), line.end(), exp);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; i++) {
            std::smatch match = *i;
            std::cout << match.str() << ": ";
            std::cout << match.str(1) << "*" << match.str(2) << "\n";
            result += stoi(match.str(1))*stoi(match.str(2));
        }
    }
    infile.close();

    std::cout << "Result: " << result << "\n";
}
