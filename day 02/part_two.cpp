#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    std::map<std::string, int> bag;
    bag["red"] = 12;
    bag["green"] = 13;
    bag["blue"] = 14;

    std::string farby[] = {"red", "green", "blue"};

    int total_sum = 0;
    int game_id = 0;

    std::string splited_part;
    
    while (getline (file_input, line)) 
    {
        int mapa_minimalnych_kociek[] = {1,1,1}; // red,green,blue

        std::stringstream split_to_two(line);
        getline(split_to_two, splited_part, ':');
        getline(split_to_two, splited_part, ':'); // druha cast LINE

        for (int i = 0; i < splited_part.length(); i++) {
            if(splited_part.at(i) == ' ') {
                splited_part.erase(i, 1);
            }
        }
        std::stringstream split_games(splited_part);
        while (getline(split_games, splited_part, ';')) {
            std::stringstream tah(splited_part);
            while (getline(tah, splited_part, ',')) {
                for (int i = 0; i < 3; i++) {
                    if (splited_part.find(farby[i]) != std::string::npos) {
                        splited_part.erase(splited_part.find(farby[i]), farby[i].length());
                        if (mapa_minimalnych_kociek[i] < stoi(splited_part)) {
                            mapa_minimalnych_kociek[i] = stoi(splited_part);
                        }
                    }
                }
            }   
        }
       
            int sum_mapa = 0;
            sum_mapa = mapa_minimalnych_kociek[0] * mapa_minimalnych_kociek[1] * mapa_minimalnych_kociek[2];
            total_sum += sum_mapa;
        
    }
    std::cout << total_sum << std::endl;
    
}
