#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

std::vector<long long> get_numbers(std::string line);
long long find_in_map(long long number, std::vector<long long> map);

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    std::vector<long long> seeds;

    long long lowest_location = LONG_LONG_MAX;

    getline (file_input, line);
    seeds = get_numbers(line);

    for (long long seed : seeds) {
        long long location = seed;
        bool found = false;
        while (getline (file_input, line)) 
        {
            if (line == "" || !isdigit(line.at(0))) {
                found = false;
                continue;
            }
        
            std::vector<long long> map = get_numbers(line);

            if (find_in_map(location, map) != 0 && !found) {
                location = find_in_map(location, map);
                found = true;
            }

        }
        std::cout << "seed end: " << location << std::endl;
        file_input.clear();
        file_input.seekg(0);
        lowest_location = location < lowest_location ? location : lowest_location;
    }
    std::cout << lowest_location << std::endl;
    
}

std::vector<long long> get_numbers(std::string line) {
    std::string cislo = "";
    std::vector<long long> seeds;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line.at(i))) {
            cislo += line.at(i);
        }
        if (line.at(i) == ' ' || i == line.length()-1) {
            if(cislo != "")seeds.push_back(stoll(cislo, nullptr, 10));
            cislo = "";
        }
    }
    return seeds;
}

long long find_in_map(long long number, std::vector<long long> map) {
    // 0 14 42
    // 49
    if (number >= map.at(1) && number <= map.at(2) + map.at(1) - 1) {
       return  number -= (map.at(1) - map.at(0));
      
    }
    return 0;
}