#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

bool is_good(std::vector<int> update, std::map<int, std::vector<int>> rules) {
    for(int i = 0; i < update.size(); i++) {
        std::vector<int> rule = rules[update[i]];
        for(int j = i+1; j < update.size(); j++) {
            if(std::find(rule.begin(), rule.end(), update[j]) != rule.end()) {
                return false;
            }
        }
    }
    return true;
}
void print_update(std::vector<int> update) {
    for(int x : update) {
        std::cout << x << ",";
    }
}

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
    std::vector<std::vector<int>> bad_updates = {};
    // At this point, we have our rules... let's start applying them
    while(std::getline(infile, line)) {
        std::vector<int> update;
        std::stringstream stream(line);
        while (stream.good()) {
            std::string substr;
            getline(stream, substr, ',');
            update.push_back(stoi(substr));
        }
        if (is_good(update, rules)) {
            // From part 1 
            // result += update[update.size()/2];
        } else {
            bad_updates.push_back(update);
        }
    }
    infile.close();

    for (std::vector<int> bad_update : bad_updates) {
        std::cout << "Before: ";
        print_update(bad_update);
        std::cout << "\n";
        while(!is_good(bad_update, rules)) {
            for(int i = 0; i < bad_update.size(); i++) {
                std::vector<int> rule = rules[bad_update[i]];
                for(int j = i+1; j < bad_update.size(); j++) {
                    if(std::find(rule.begin(), rule.end(), bad_update[j]) != rule.end()) {
                        // Bad page found, swap!
                        int temp = bad_update[j];
                        bad_update[j] = bad_update[i];
                        bad_update[i] = temp;
                    }
                }
            }
        }
        result += bad_update[bad_update.size()/2];
        std::cout << "After: ";
        print_update(bad_update);
        std::cout << "\n";
    }

    std::cout << "Result: " << result << "\n";
}

