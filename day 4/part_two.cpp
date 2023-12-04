#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

bool je_cislo(char);
std::vector<int> extract_numbers(std::string line);
int extract_card_number(std::string);

int main (int argc, char* argv[]) {
    std::string line;
    std::string splited;
    std::ifstream file_input("input.txt");

    int instances_sum = 0;
    std::vector<int> instances;
    instances.push_back(1); // instancia 1 katry 1
 
    while (getline (file_input, line)) 
    {
        std::vector<int> vyherne_cisla;
        std::vector<int> cisla_na_porovnanie;
        std::stringstream cisla(line);

        getline(cisla, splited, ':');
        int momenentalne_cislo_karty = extract_card_number(splited);

        if (instances.size() < momenentalne_cislo_karty) {
            instances.push_back(1);
        } else if (instances.size() != 1) {
            instances.at(momenentalne_cislo_karty - 1) += 1;
        }

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
                    counter++;
                }
            }
        }

        int cislo = instances.at(momenentalne_cislo_karty-1);
        for (int j = 0 ; j < cislo; j++) {
            for (int i = 0; i < counter; i++) {
                if (instances.size() < momenentalne_cislo_karty + i + 1) {
                    instances.push_back(1);
                    continue;
                }
                instances.at(momenentalne_cislo_karty + i) += 1;
            }
        }

        
    }
    for (int cislo : instances) {
        instances_sum += cislo;
    }
    std::cout << instances_sum << std::endl;
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

int extract_card_number(std::string line) {
    std::string number;
    for (int i = 0 ; i < line.length(); i++) {
        if (je_cislo(line.at(i))) {
            number += line.at(i);
        }
    }

    
    return stoi(number);
}