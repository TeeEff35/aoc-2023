#include <iostream>
#include <string>
#include <fstream>


int prve_string_cislo_pozicia(std::string);
std::string prve_string_cislo(std::string);

int posledne_string_cislo_pozicia(std::string);
std::string posledne_string_cislo(std::string);

std::string find_first_number(std::string);
std::string find_last_number(std::string);

bool je_cislo(char);

std::string valid_numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");


    int cal_values_sum = 0;
    
    while (getline (file_input, line)) 
    {
        std::string first_digit = "x";
        std::string last_digit = "x";
        int number = 0;

        first_digit = find_first_number(line);
        last_digit = find_last_number(line);

        std::string vysledne_cislo_s =  first_digit + last_digit;
        number = stoi(vysledne_cislo_s);
        cal_values_sum += number; 
    }
    
    
    std::cout << cal_values_sum << std::endl;
}


std::string find_first_number(std::string line) {
    for (int i = 0; i < line.length(); i++)
        {
            if (prve_string_cislo_pozicia(line) == i) 
            {
                return prve_string_cislo(line);
            } else if (je_cislo(line.at(i))) 
            {
                return std::string(1,line.at(i));
            }
        }
}

std::string find_last_number(std::string line) {
    int dlzka = line.length() - 1;
    for (int i = dlzka; i >= 0; i--)
        {
            if (posledne_string_cislo_pozicia(line) == i) 
            {
                return posledne_string_cislo(line);
            } else if (je_cislo(line.at(i))) 
            {
                return std::string(1,line.at(i));
            }
        }
}

bool je_cislo(char znak) {
    if ( (int) znak >= 0 && (int) znak  <= 57) {
        return true;
    } else {
        return false;
    }
}

int prve_string_cislo_pozicia(std::string line) {
    int mapa[10] = {INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX};

    for (int i = 0; i < 10; i++) {
        if (line.find(valid_numbers[i]) != std::string::npos) {
            mapa[i] = line.find(valid_numbers[i]);
        }  
    }
    int smallest = INT16_MAX;
    for (int i = 0; i < 10; i++) {
        if (mapa[i] < smallest) {
            smallest = mapa[i];
        }
    }
    return smallest;

}

std::string prve_string_cislo(std::string line) {
    int mapa[10] = {INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX};

    for (int i = 0; i < 10; i++) {
        if (line.find(valid_numbers[i]) != std::string::npos) {
            mapa[i] = line.find(valid_numbers[i]);
        }  
    }
    int smallest = INT16_MAX;
    int position_of_first_number = 0;
    for (int i = 0; i < 10; i++) {
        if (mapa[i] < smallest) {
            smallest = mapa[i];
            position_of_first_number = i;
        }
    }
    return mapa[position_of_first_number] == INT16_MAX ? "" : std::to_string(position_of_first_number);

}

int posledne_string_cislo_pozicia(std::string line) {
    int mapa[10] = {INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN};

    for (int i = 0; i < 10; i++) {
        int start = 0;
        while (line.find(valid_numbers[i], start) != std::string::npos)
        {
            mapa[i] = line.find(valid_numbers[i], start);
            start = line.find(valid_numbers[i], start) + 1 ;
        }  
    }
    int highest = INT16_MIN;
    for (int i = 0; i < 10; i++) {
        if (mapa[i] > highest) {
            highest = mapa[i];
        }
    }
    return highest;

}

std::string posledne_string_cislo(std::string line) {
    int mapa[10] = {INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN};

    for (int i = 0; i < 10; i++) {
        int start = 0;
        while (line.find(valid_numbers[i], start) != std::string::npos)
        {
            mapa[i] = line.find(valid_numbers[i], start);
            start = line.find(valid_numbers[i], start) + 1;
        }   
    }
    int highest = INT16_MIN;
    int position_of_last_number = 0;
    for (int i = 0; i < 10; i++) {
        if (mapa[i] > highest) {
            highest = mapa[i];
            position_of_last_number = i;
        }
    }
    
    return mapa[position_of_last_number] == INT16_MIN ? "" : std::to_string(position_of_last_number);

}