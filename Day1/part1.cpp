#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

int main() {
    std::ifstream infile("input");
    std::vector<int> v1 = {};
    std::vector<int> v2 = {};
    int a,b;
    while (infile >> a >> b) {
//        std::cout << a << " " << b << "\n";
        v1.push_back(a);
        v2.push_back(b);
    }
    std::sort(v1.begin(), v1.begin()+v1.size());
    std::sort(v2.begin(), v2.begin()+v2.size());
    int i;
    int distance = 0;
    for (i = 0; i < v1.size(); i++) {
        distance += abs(v2[i]-v1[i]);
    }
    std::cout << "Distance: " << distance << "\n";
}
