#include <iostream>
#include <fstream>
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
//    v1.erase( unique( v1.begin(), v1.end() ), v1.end() );
    int i;
    int distance=0;
    int simscore = 0;
    for (i = 0; i < v1.size(); i++) {
        int count = std::count_if(v2.begin(), v2.end(), [v1,i](int x) { 
            return x == v1[i]; 
        });

        simscore += v1[i]*count;
    }
    std::cout << "Similarity Score: " << simscore << "\n";
}
