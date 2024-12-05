#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

int main() {
    std::ifstream infile("input");
    std::string line;
    std::vector<std::tuple<int,int>> rules_raw{};
    int result = 0;

    std::regex const rule_exp{R"~(^(\d+)\|(\d+)$)~"};

    while(std::getline(infile, line)) {
        std::smatch match;
        if (regex_search(line, match, rule_exp)) {
            rules_raw.push_back(std::tuple<int,int>{stoi(match.str(1)), stoi(match.str(2))});
        } else {
            break;
        }
    }
    std::map<int,std::vector<int>> rules {};
    for (std::tuple<int,int> rule : rules_raw) {
        int pre = std::get<0>(rule);
        int post = std::get<1>(rule);
        if(rules.count(post) == 0) {
            rules[post] = {};
        }
        rules[post].push_back(pre);
    }
    // At this point, we have our rules... let's start applying them
    while(std::getline(infile, line)) {
        std::vector<int> updates;
        std::stringstream stream(line);
        while (stream.good()) {
            std::string substr;
            getline(stream, substr, ',');
            updates.push_back(stoi(substr));
        }
        bool good = true;
        for(int i = 0; i < updates.size(); i++) {
            std::vector<int> rule = rules[updates[i]];
            for(int j = i+1; j < updates.size(); j++) {
                if(std::find(rule.begin(), rule.end(), updates[j]) != rule.end()) {
                    good = false;
                    break;
                }
            }
            if (!good)
                break;
        }
        if (good) {
            result += updates[updates.size()/2];
        } else {

        }
    }
    infile.close();

    std::cout << "Result: " << result << "\n";
}
