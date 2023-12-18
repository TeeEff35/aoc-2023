#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

enum hand_type {five_kind, four_kind, full_house, three_kind, two_pair, pair, high_card};

typedef struct
{
    std::string cards;
    int bid;
    hand_type type_of_hand;
    int rank;
}Hand;

int daj_number(char znak);

struct CompareByCards {
    bool operator()(const Hand& a, const Hand& b) const {
        for (size_t i = 0; i < a.cards.size(); ++i) {
            if (daj_number(a.cards[i]) < daj_number(b.cards[i])) {
                return true;
            } else if (daj_number(a.cards[i]) > daj_number(b.cards[i])) {
                return false;
            }
        }
        return false; 
    }
};

hand_type zisti_typ(Hand);
std::vector<Hand> sort_card(std::vector<Hand>);
std::string get_hand_type(hand_type);

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    int total = 0;
    std::vector<std::vector<Hand>> all_hands;
    std::vector<Hand> five_kind;
    std::vector<Hand> four_kind;
    std::vector<Hand> full_house;
    std::vector<Hand> three_kind;
    std::vector<Hand> two_pair;
    std::vector<Hand> pair;
    std::vector<Hand> high_card;

    while (getline (file_input, line)) 
    {
        Hand temp_hand;
        std::string temp_cards;
        int temp_bid;
        
        int space = line.find(" ");

        temp_cards = line.substr(0, space);
        temp_bid = stoi(line.substr(space + 1, -1));

        temp_hand.cards = temp_cards;
        temp_hand.bid = temp_bid;
        temp_hand.type_of_hand = zisti_typ(temp_hand);

        switch (temp_hand.type_of_hand)
        {
            case hand_type::five_kind:
                five_kind.push_back(temp_hand);
                break;
            case hand_type::four_kind:
                four_kind.push_back(temp_hand);
                break;
            case hand_type::full_house:
                full_house.push_back(temp_hand);
                break;
            case hand_type::three_kind:
                three_kind.push_back(temp_hand);
                break;
            case hand_type::two_pair:
                two_pair.push_back(temp_hand);
                break;
            case hand_type::pair:
                pair.push_back(temp_hand);
                break;
            case hand_type::high_card:
                high_card.push_back(temp_hand);
                break;
            default:
                break;
        }
        
    }
    
    five_kind = sort_card(five_kind);
    four_kind = sort_card(four_kind);
    full_house = sort_card(full_house);
    three_kind = sort_card(three_kind);
    two_pair = sort_card(two_pair);
    pair = sort_card(pair);
    high_card = sort_card(high_card);

    all_hands.push_back(high_card);
    all_hands.push_back(pair);
    all_hands.push_back(two_pair);
    all_hands.push_back(three_kind);
    all_hands.push_back(full_house);
    all_hands.push_back(four_kind);
    all_hands.push_back(five_kind);
    
    int rank = 1;
    for (std::vector<Hand> hands : all_hands) {
        for (Hand hand : hands) {
            total += hand.bid * rank;
            rank++;
        }
    }
    std::cout << "total: " << total;
}

hand_type zisti_typ(Hand hand) {
    int cards_count[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int five_count = 0;
    int four_count = 0;
    int three_count = 0;
    int two_count = 0;
    int j_count = 0;

    for (int i = 0; i < hand.cards.size(); i++) {
        int da_number = daj_number(hand.cards.at(i)) - 1;
        cards_count[da_number]++;
    }

    for (int i = 0; i < 14; i++) {
        if(i == 0) {
            j_count = cards_count[0];
            
        }
        switch (cards_count[i])
        {
        case 5:
            five_count++;
            break;
        case 4:
            four_count++;
            break;
        case 3:
            three_count++;
            break;
        case 2:
            two_count++;
            break;
        default:
            break;
        }
    }
    
    
    if (j_count == 4) {
        five_count++;
    } else if (j_count == 3 && !two_count) {
        four_count++;
    } else if (j_count == 3 && two_count) {
        five_count++;
    } else if (j_count == 2 && three_count) {
        five_count++;
    } else if (j_count == 2 && two_count == 2) {
        four_count++;
    } else if (j_count == 2) {
        three_count++;
        two_count = 0;
    } else if (j_count == 1 && two_count == 1) {
        three_count++;
        two_count = 0;
    } else if (j_count == 1 && two_count == 2) {
        three_count++;
    } else if (j_count == 1 && three_count) {
        four_count++;
    } else if (j_count == 1 && four_count) {
        five_count++;
    } else if (j_count == 1) {
        two_count++;
    } 

    if (five_count) {
        return hand_type::five_kind;
    } else if (four_count) {
        return hand_type::four_kind;
    } else if (three_count && two_count) {
        return hand_type::full_house;
    } else if (three_count) {
        return hand_type::three_kind;
    } else if (two_count == 2) {
        return hand_type::two_pair;
    } else if (two_count == 1) {
        return hand_type::pair;
    } else {
        return high_card;
    }
}

std::vector<Hand> sort_card(std::vector<Hand> hands) {
    std::sort(hands.begin(), hands.end(), CompareByCards());
    return hands;
}

int daj_number(char znak) {
    if (isdigit(znak)) {
        return znak - '0';
    } else {
        switch (znak)
        {
        case 'T':
            return 10;
            break;
        case 'J':
            return 1;
            break;
        case 'Q':
            return 12;
            break;
        case 'K':
            return 13;
            break;
        case 'A':
            return 14;
            break;
        default:
            break;
        }
    }
}