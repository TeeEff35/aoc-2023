#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

bool je_cislo(char);
bool nieje_cislo(char);
bool je_symbol(char);

std::vector<int> zisti_pozicie_symbolov(std::string line);
std::map<int, int> zisti_pozicie_cisel(std::string line);

std::vector<int> pozri_hore_dole(std::map<int, int> mapa_cisla, std::vector<int> znaky, std::string line);
std::vector<int> pozri_dole(std::map<int, int> mapa_cisla, std::vector<int> znaky,  std::string line);
std::vector<int> pozri_vedla(std::map<int, int> mapa_cisla, std::string line, int pos);

int algoritmus(std::string line_before, std::string line_now, std::string line_ahead);

int main (int argc, char* argv[]) {
    std::string line_before = "";
    std::string line_now = "";
    std::string line_ahead = "";

    std::ifstream file_input("input.txt");

    int part_sum = 0;
    
    while (getline (file_input, line_ahead)) 
    {     
        part_sum += algoritmus(line_before, line_now, line_ahead);
        line_before = line_now;
        line_now = line_ahead;
    }
    part_sum += algoritmus(line_before, line_now, "");
    
  std::cout << part_sum;
}

std::vector<int> zisti_pozicie_symbolov(std::string line) {
    std::vector<int> znaky;
    for (int i = 0; i < line.length(); i++) {
        if (je_symbol(line.at(i))) {
            znaky.push_back(i);
        }
    }
    return znaky;
}

std::map<int, int> zisti_pozicie_cisel(std::string line) {
    std::map<int, int> mapa;
    
    for (int i = 0; i < line.length(); i++) {
        int start;
        int stop;
        if (je_cislo(line.at(i))) {
            start = i;
            int temp = start;
            while (temp != line.length() && je_cislo(line.at(temp))) {
                temp++;
            }
                stop = temp - 1;
                
        mapa.insert(std::pair<int, int>(start, stop));
        i = stop;
        }
    }
    return mapa;
}

bool je_cislo(char znak) {
    if ( (int) znak >= 48 && (int) znak  <= 57) {
        return true;
    } else {
        return false;
    }
}

bool nieje_cislo(char znak) {
    if ( (int) znak >= 48 && (int) znak <= 57) {
        return false;
    } else {
        return true;
    }
}

bool je_symbol(char znak) {
    return ((int) znak == 42) ? true : false;
}

std::vector<int> pozri_hore_dole(std::map<int, int> mapa_cisla, std::vector<int> znaky_pozicie, std::string line) {
    std::vector<int> cisla;
    std::string cislo = ""; 

    for (int pozicia : znaky_pozicie) {
        for (std::map<int, int>::iterator it = mapa_cisla.begin(); it != mapa_cisla.end(); ++it)
        {
            if (pozicia >= it->first - 1 && pozicia <= it->second + 1) {
                for (int i = it->first; i <= it->second; i++) {
                    cislo += line.at(i);
                }
                
                cisla.push_back(stoi(cislo));
                cislo = "";
            }
        }
    }

    return cisla;
}
std::vector<int> pozri_vedla(std::map<int, int> mapa_cisla, std::string line, int pos) {
    std::vector<int> cisla;
    std::string cislo;
    for (std::map<int, int>::iterator it = mapa_cisla.begin(); it != mapa_cisla.end(); ++it)
    {
        if ((it->first-1 == pos) || 
            (it->second+1 == pos)) 
        {
            
            for (int i = it->first; i <= it->second; i++) {
                cislo += line.at(i);
            }
            
            cisla.push_back(stoi(cislo));
            cislo = "";
        }
    }
    return cisla;
}

int algoritmus(std::string line_before, std::string line_now, std::string line_ahead) {
    std::vector<int> znaky = zisti_pozicie_symbolov(line_now);
    
    
    std::map<int, int> cisla_before = zisti_pozicie_cisel(line_before);
    std::map<int, int> cisla_now = zisti_pozicie_cisel(line_now);
    std::map<int, int> cisla_ahead = zisti_pozicie_cisel(line_ahead);
    std::vector<int>::iterator ip;
    int sum = 0;
    for (int znak_pos : znaky) {
        std::vector<int> validne_cisla;
        std::vector<int> temp_vec;
        std::vector<int> xd;
        xd.push_back(znak_pos);

        temp_vec = pozri_hore_dole(cisla_before, xd, line_before);
        
        validne_cisla.insert(validne_cisla.end(), temp_vec.begin(), temp_vec.end());

        temp_vec = pozri_hore_dole(cisla_ahead, xd, line_ahead);
        
        validne_cisla.insert(validne_cisla.end(), temp_vec.begin(), temp_vec.end());

        temp_vec = pozri_vedla(cisla_now, line_now, znak_pos);
        
        validne_cisla.insert(validne_cisla.end(), temp_vec.begin(), temp_vec.end());

        
        ip = std::unique(validne_cisla.begin(), validne_cisla.end());
        validne_cisla.resize(std::distance(validne_cisla.begin(), ip));
        
        if (validne_cisla.size() == 2) {
            sum += validne_cisla.at(0) *  validne_cisla.at(1);
            //std::cout << "valid 1: " << validne_cisla.at(0) << "  valid 2: " << validne_cisla.at(1) << "\n";
        }
    }
    
    return sum;

}