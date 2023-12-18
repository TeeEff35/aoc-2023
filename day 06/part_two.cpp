#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

int main (int argc, char* argv[]) {  
    /*
    Time:        54     81     70     88
    Distance:   446   1292   1035   1007
    */

    std::vector<long long> input_casy;
    input_casy.push_back(54817088);

    std::vector<long long> max_dis;
    max_dis.push_back(446129210351007);

    std::vector<long long> pocet_moznosti_prekonania;
    for (long long j = 0; j < input_casy.size(); j++) {
        std::vector<long long> casy_na_kontrolu;
        for (long long i = 0; i < input_casy.at(j); i++) {
            long long distance = (input_casy.at(j)-i)*i;
            casy_na_kontrolu.push_back(distance);
        }

        long long counter = 0;
        for (long long cass : casy_na_kontrolu) {
            if (cass > max_dis.at(j)) {
                counter++;
            }
        }
        pocet_moznosti_prekonania.push_back(counter);
    }
    long long vysledok = 1;
    for (long long i : pocet_moznosti_prekonania) {
        vysledok *= i;
    }
    std::cout << vysledok;
}