#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>

// Geez... I had to do a lot to make these integers fit in...

std::ostream&
operator<<( std::ostream& dest, __uint128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}
__uint128_t stou(std::string s) {
    const char *p = s.c_str();
    __uint128_t val = 0;

    while (*p >= '0' && *p <= '9') {
        val = (10 * val) + (*p - '0');
        p++;
    }
    return val;
}

std::string uint128ToString(const __uint128_t& value) {
    static const char* charmap = "0123456789";
    std::string result;
    result.reserve( 40 );
    __uint128_t helper = value;

    do {
        result += charmap[ helper % 10 ];
        helper /= 10;
    } while ( helper );
    std::reverse( result.begin(), result.end() );
    return result;
}

__uint128_t shift_left_base_3(__uint128_t x, int times) {
    for(int i = 0; i < times; i++) {
        x *= 3;
    }
    return x;
}

__uint128_t shift_right_base_3(__uint128_t x, int times) {
    for(int i = 0; i < times; i++) {
        x /= 3;
    }
    return x;
}

__uint128_t powu(__uint128_t x, __uint128_t y) {
    __uint128_t result = 1;
    for(int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}

__uint128_t concatenate(__uint128_t x, __uint128_t y) {
    return stou(uint128ToString(x) + uint128ToString(y));
//    return x * (powu(10,ceil(log10(y)))) + y;
}

int main() {
    std::ifstream infile("input");
    std::string line;
    __uint128_t result = 0;
    
    std::regex const exp{R"~(^(\d+):(.*)$)~"};

    while(std::getline(infile, line)) {
        std::smatch m;

        auto words_begin = 
            std::sregex_iterator(line.begin(), line.end(), exp);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; i++) {
            std::smatch match = *i;
            __uint128_t to_check_against = stou(match.str(1));

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
            __uint128_t combinations = shift_left_base_3(1, NUM_INPUTS);

            for(unsigned int q = 0; q < combinations; q++) {
                __uint128_t last_result = int_list[0];
//                std::cout << last_result;
                int index = 0;
                for(int w = NUM_INPUTS -1; w > -1; w--) {
                    index++;
                    int type = shift_right_base_3(q, w) % 3;
                    if(type == 0) {
//                        std::cout << " * ";
                        last_result = last_result * int_list[index];    
                    } else if (type == 1){
//                        std::cout << " + ";
                        last_result = last_result + int_list[index];    
                    } else if (type == 2) {
//                        std::cout << " || ";
                        last_result = concatenate(last_result, int_list[index]); 
                    }
//                    std::cout << int_list[index];
                    if(last_result > to_check_against)
                        break;
                }
//                std::cout << " = " << last_result << " ? " << to_check_against << "\n";
                if (last_result == to_check_against) {
//                    std::cout << "Found!\n";
                    result += to_check_against;
                    break;
                } 
            }
        }
    }
    infile.close();

    std::cout << "Result: " << result << "\n";
}

