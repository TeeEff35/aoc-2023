#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    int cal_values_sum = 0;

    while (getline (file_input, line)) 
    {
        char first_digit = 'x';
        char last_digit = 'x';
        int number = 0;
        int dlzka_stringu = line.length();

        
        for (int i = 0; i < dlzka_stringu; i++)
        {
            if (last_digit != 'x' && first_digit != 'x') {
                number = first_digit + last_digit;
            }

            if ((int) line.at(i) >= 0 && (int) line.at(i) <= 57 && first_digit == 'x' )  {
                first_digit = line.at(i);
            }

            if ((int) line.at(dlzka_stringu - i - 1) >= 0 && (int) line.at(dlzka_stringu - i - 1) <= 57 && last_digit == 'x') {
                last_digit = line.at(dlzka_stringu - i - 1);
            }
        }
        std::string vysledne_cislo_s = std::string(1, first_digit) + last_digit;
        number = stoi(vysledne_cislo_s);
        cal_values_sum += number; 
    }
    std::cout << cal_values_sum << std::endl;

}