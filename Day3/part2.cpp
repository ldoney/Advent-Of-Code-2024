#include <fstream>
#include <string>
#include <bits/stdc++.h>

int main() {
    std::ifstream infile("input");
    std::string line;
    int result = 0;

    bool doit = true;
    std::regex const exp{R"~(do\(\)|don\'t\(\)|mul\((\d+)\,(\d+)\))~"};

    while(std::getline(infile, line)) {
        std::smatch m;

        auto words_begin = 
            std::sregex_iterator(line.begin(), line.end(), exp);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; i++) {
            std::smatch match = *i;
            std::cout << match.str(0) << "\n";
            if(match.str(0) == "do()") {
                doit = true;
                std::cout << "DO" << "\n";
            } else if(match.str(0) == "don't()") {
                doit = false;
                std::cout << "DON'T" << "\n";
            } else {
                std::cout << match.str() << (doit ? "" : " (REJECT) ") << ": ";
                std::cout << match.str(1) << "*" << match.str(2) << "\n";
                if(doit) {
                    result += stoi(match.str(1))*stoi(match.str(2));
                }
          }
        }
    }
    infile.close();

    std::cout << "Result: " << result << "\n";
}

