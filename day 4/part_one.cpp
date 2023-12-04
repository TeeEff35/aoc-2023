#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

bool je_cislo(char);
std::vector<int> extract_numbers(std::string line);

int main (int argc, char* argv[]) {
    std::string line;
    std::string splited;
    std::ifstream file_input("input.txt");

    

    int points_sum = 0;

    while (getline (file_input, line)) 
    {
        std::vector<int> vyherne_cisla;
        std::vector<int> cisla_na_porovnanie;
        std::stringstream cisla(line);

        getline(cisla, splited, ':');
        getline(cisla, splited, ':');

        //vyherne
        std::stringstream vyherne_cisla_s(splited);
        getline(vyherne_cisla_s, splited, '|');
        vyherne_cisla = extract_numbers(splited);
        

        //na porovnanie
        getline(vyherne_cisla_s, splited, '|');
        cisla_na_porovnanie = extract_numbers(splited);
        
        int counter = 0;
        for (int cislo_vyherne : vyherne_cisla) {
            for (int cislo_porovnat : cisla_na_porovnanie) {
                if (cislo_vyherne == cislo_porovnat) {
                    counter = counter == 0 ? 1 : counter*2;
                }
            }
        }

        points_sum += counter;
    }
    std::cout << points_sum << std::endl;
    file_input.close();
}

bool je_cislo(char znak) {
    if ( (int) znak >= 48 && (int) znak  <= 57) {
        return true;
    } else {
        return false;
    }
}

std::vector<int> extract_numbers(std::string line) {
    std::vector<int> cisla;
    for (int i = 0; i < line.length(); i++) {
            std::string cislo = "";
            if (je_cislo(line.at(i))) {
                cislo += line.at(i);
                if (i+1 < line.length()) {
                    cislo = je_cislo(line.at(i + 1)) ? cislo + line.at(i + 1) : cislo;
                    i++;
                }
                cisla.push_back(stoi(cislo));
            }
        }
    return cisla;
}