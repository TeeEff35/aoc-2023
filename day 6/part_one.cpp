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

    std::vector<int> input_casy;
    input_casy.push_back(54);
    input_casy.push_back(81);
    input_casy.push_back(70);
    input_casy.push_back(88);

    std::vector<int> max_dis;
    max_dis.push_back(446);
    max_dis.push_back(1292);
    max_dis.push_back(1035);
    max_dis.push_back(1007);

    std::vector<int> pocet_moznosti_prekonania;
    for (int j = 0; j < input_casy.size(); j++) {
        std::vector<int> casy_na_kontrolu;
        for (int i = 0; i < input_casy.at(j); i++) {
            int distance = (input_casy.at(j)-i)*i;
            casy_na_kontrolu.push_back(distance);
        }

        int counter = 0;
        for (int cass : casy_na_kontrolu) {
            if (cass > max_dis.at(j)) {
                counter++;
            }
        }
        pocet_moznosti_prekonania.push_back(counter);
    }
    int vysledok = 1;
    for (int i : pocet_moznosti_prekonania) {
        vysledok *= i;
    }
    std::cout << vysledok;
}