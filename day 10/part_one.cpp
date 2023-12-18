#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

std::map<std::string, std::pair<int, int>> look_up_table = {{"hore|", std::pair<int, int>(-1, 0)}, {"dole|", std::pair<int, int>(1, 0)},
                                                            {"vlavo-", std::pair<int, int>(0, -1)}, {"vpravo-", std::pair<int, int>(0, 1)},
                                                            {"doleL", std::pair<int, int>(1, 1)}, {"vlavoL", std::pair<int, int>(-1, -1)},
                                                            {"vpravoJ", std::pair<int, int>(-1, 1)}, {"doleJ", std::pair<int, int>(1, -1)},
                                                            {"vpravo7", std::pair<int, int>(1, 1)}, {"hore7", std::pair<int, int>(-1, -1)},
                                                            {"vlavoF", std::pair<int, int>(1, -1)}, {"horeF", std::pair<int, int>(-1, 1)}};

typedef struct 
{
    int first;
    int second;
    long pocet_krokov = 0;
    bool finished = false;
    int last_first;
    int last_second;
    char character;
}Pozicia;


Pozicia najdi_start(std::vector<std::string>);
void make_move(std::vector<Pozicia> &pozicie, std::vector<std::string>);
bool all_finished(std::vector<Pozicia>);
void skontroluj_poziciu(Pozicia &pozicia, std::vector<std::string>);
std::vector<Pozicia> najdi_nove_cesty(Pozicia pozicia, std::vector<std::string> labyrint);


int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    long total = 0;
    std::vector<std::string> labyrint;
    std::vector<Pozicia> pozicie;


    while (getline (file_input, line)) 
    {
        labyrint.push_back(line);
    }

    pozicie.push_back(najdi_start(labyrint));


    Pozicia start_test = najdi_start(labyrint);
    
    std::vector<Pozicia> nove_cesty = najdi_nove_cesty(start_test, labyrint);
    
    int i = 0;
    while (!all_finished(nove_cesty)) {
        std::vector<Pozicia> new_cesty;
        for (Pozicia pozicia  : nove_cesty) {
            if (pozicia.finished) continue;    
            std::vector<Pozicia> temp = najdi_nove_cesty(pozicia, labyrint);
            new_cesty.insert(new_cesty.end(), temp.begin(), temp.end());
        }
        for (Pozicia &pozicia : new_cesty) {
            skontroluj_poziciu(pozicia, labyrint);
        }

        nove_cesty = new_cesty;
    }
    for (Pozicia &pozicia : nove_cesty) {
            skontroluj_poziciu(pozicia, labyrint);
            total = std::max(pozicia.pocet_krokov, total);
        }

    total = (total - 1)/2 + 1;
    std::cout << "najdalej: " << total;
}

std::vector<Pozicia> najdi_nove_cesty(Pozicia pozicia, std::vector<std::string> labyrint) {
    std::vector<Pozicia> nove_cesty;
    std::map<std::string, std::pair<int, int>> table = {{"dole", std::pair<int, int>(1, 0)},
                                                        {"hore", std::pair<int, int>(-1, 0)},
                                                        {"vlavo", std::pair<int, int>(0, -1)},
                                                        {"vpravo", std::pair<int, int>(0, 1)}};
    
    for (auto i : table) {
        if (pozicia.character == '-' && (i.first == "dole" || i.first == "hore") ) {
            continue;
        }
        if (pozicia.character == '|' && (i.first == "vpravo" || i.first == "vlavo") ) {
            continue;
        }
        if (pozicia.character == 'L' && (i.first == "dole" || i.first == "vlavo") ) {
            continue;
        }
        if (pozicia.character == 'J' && (i.first == "vpravo" || i.first == "dole") ) {
            continue;
        }
        if (pozicia.character == '7' && (i.first == "vpravo" || i.first == "hore") ) {
            continue;
        }
        if (pozicia.character == 'F' && (i.first == "vlavo" || i.first == "hore") ) {
            continue;
        }


        int prva_pos = pozicia.first + i.second.first;
        int druha_pos = pozicia.second + i.second.second;

        if (prva_pos < 0 || druha_pos < 0 || prva_pos >= labyrint.size() || druha_pos >= labyrint.size()) {
            continue;
        }

        std::string legalna_cesta = i.first + labyrint.at(prva_pos).at(druha_pos);
        auto it = look_up_table.find(legalna_cesta);
        

        if (it != look_up_table.end()) {
            Pozicia nova_pozicia;

            char znak = labyrint.at(prva_pos).at(druha_pos);

            

            if (znak == '-' || znak == '|') {
                nova_pozicia.last_first  = pozicia.first;
                nova_pozicia.last_second = pozicia.second;
                nova_pozicia.pocet_krokov = pozicia.pocet_krokov + 1;
            } else {
                nova_pozicia.last_first = prva_pos;
                nova_pozicia.last_second = druha_pos;
                nova_pozicia.pocet_krokov = pozicia.pocet_krokov + 2;
            }
            nova_pozicia.first =  pozicia.first + it->second.first;
            nova_pozicia.second = pozicia.second + it->second.second;

            if (nova_pozicia.first == pozicia.last_first && nova_pozicia.second == pozicia.last_second) {
                continue;
            } else if ((znak != '-' && znak != '|') && nova_pozicia.last_first == pozicia.last_first && nova_pozicia.last_second == pozicia.last_second) {
                continue;
            }

            nova_pozicia.character =  labyrint.at(nova_pozicia.first).at(nova_pozicia.second);
            nove_cesty.push_back(nova_pozicia);

        }
    }
    if (nove_cesty.size() <= 0) {
        pozicia.finished = true;
        nove_cesty.push_back(pozicia);
    }
    return nove_cesty;
}

Pozicia najdi_start(std::vector<std::string> labyrint) {
    for (int i = 0; i < labyrint.size(); i++) {
        for (int j = 0; j < labyrint.at(i).size(); j++) {
            if (labyrint.at(i).at(j) == 'S') {
                Pozicia pozicia;
                pozicia.first = i;
                pozicia.second = j;
                pozicia.last_first = i;
                pozicia.last_second = j;
                return pozicia;
            }
        }
    }
}

bool all_finished(std::vector<Pozicia> pozicie) {
    for (Pozicia pozicia : pozicie) {
        if (!pozicia.finished) {
            return false;
        }
    }
    return true;
}

void skontroluj_poziciu(Pozicia &pozicia, std::vector<std::string> labyrint) {
    if (labyrint.at(pozicia.first).at(pozicia.second) == 'S') {
        pozicia.finished = true;
        if ((pozicia.pocet_krokov % 2) != 0) {
            pozicia.pocet_krokov = ((pozicia.pocet_krokov - 1) / 2) + 1;
        } else {
            pozicia.pocet_krokov /= 2;
        }
    } else if (labyrint.at(pozicia.first).at(pozicia.second) == '.') {
        pozicia.finished = true;
    }

}