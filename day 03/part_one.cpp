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
std::vector<int> pozri_vedla(std::map<int, int> mapa_cisla, std::string line);

int algoritmus(std::string line_before, std::string line_now, std::string line_ahead);

int main (int argc, char* argv[]) {
    std::string line_before = "";
    std::string line_now = "";
    std::string line_ahead = "";

    std::ifstream file_input("input.txt");

    long long part_sum = 0;
    
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
    return (nieje_cislo(znak) && (int) znak != 46) ? true : false;
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
std::vector<int> pozri_vedla(std::map<int, int> mapa_cisla, std::string line) {
    std::vector<int> cisla;
    std::string cislo;
    for (std::map<int, int>::iterator it = mapa_cisla.begin(); it != mapa_cisla.end(); ++it)
    {
        if ((it->first-1 >= 0 && je_symbol(line.at(it->first-1))) || 
            (it->second+1 < line.length() && je_symbol(line.at(it->second+1)))) 
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
    std::vector<int> znaky_before;
        std::vector<int> validne_cisla;
        std::vector<int> temp_vec;
        
        std::vector<int>::iterator ip;   
        if (line_now == "") {
            line_now = line_ahead;
            return 0;
        }


        //line before 
        if (line_before != "") znaky_before = zisti_pozicie_symbolov(line_before);

        //line now
        std::map<int, int> mapa_pozicii_cisel = zisti_pozicie_cisel(line_now); // start stop
        
        //line ahead
        std::vector<int> znaky_after = zisti_pozicie_symbolov(line_ahead);

        temp_vec = pozri_hore_dole(mapa_pozicii_cisel, znaky_before, line_now);
        for (int cisla : temp_vec) {
            std::cout << "horne cisla: " << cisla << std::endl;
        }
        validne_cisla.insert(validne_cisla.end(), temp_vec.begin(), temp_vec.end());

        temp_vec = pozri_hore_dole(mapa_pozicii_cisel, znaky_after, line_now);
        for (int cisla : temp_vec) {
            std::cout << "dolne cisla: " << cisla << std::endl;
        }
        validne_cisla.insert(validne_cisla.end(), temp_vec.begin(), temp_vec.end());

        temp_vec = pozri_vedla(mapa_pozicii_cisel, line_now);
        for (int cisla : temp_vec) {
            std::cout << "vedla cisla: " << cisla << std::endl;
        }
        validne_cisla.insert(validne_cisla.end(), temp_vec.begin(), temp_vec.end());

        
        ip = std::unique(validne_cisla.begin(), validne_cisla.end());
        validne_cisla.resize(std::distance(validne_cisla.begin(), ip));

        int sumicka = 0;
        for (int cislo : validne_cisla) {
            sumicka += cislo;
        }
        return sumicka;
}