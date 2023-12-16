#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

typedef struct 
{
    std::vector<long long> starting_sequence;
    std::vector<std::vector<long long>> derived_sequences;
}Sequence;

std::vector<long long> get_numbers(std::string);
std::vector<long long> derive_sequence(std::vector<long long>);
bool is_all_zero(std::vector<long long> seq);

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    long long total = 0;
    std::vector<Sequence> sequences;

    while (getline (file_input, line)) 
    {
        Sequence temp;
        temp.starting_sequence = get_numbers(line);
        sequences.push_back(temp);
    }

    for (Sequence &sequence : sequences) {
        std::vector<long long> temp_seq;
        sequence.derived_sequences.push_back(sequence.starting_sequence);

        temp_seq = derive_sequence(sequence.starting_sequence);
        sequence.derived_sequences.push_back(temp_seq);

        while (!is_all_zero(temp_seq)) {
            temp_seq = derive_sequence(temp_seq);
            sequence.derived_sequences.push_back(temp_seq);
        }

        long long num_of_sequences = sequence.derived_sequences.size();
        long long previous_num = sequence.derived_sequences.at(num_of_sequences - 2).at(0);

        long long num_to_add;
        for (int i = (num_of_sequences - 3); i >= 0; i--) {
            long long size_of_sequence = sequence.derived_sequences.at(i).size();
            num_to_add = sequence.derived_sequences.at(i).at(size_of_sequence-1) + previous_num;

            sequence.derived_sequences.at(i).push_back(num_to_add);
            previous_num = num_to_add;
        }
        total += previous_num;
    }
    
    std::cout << total;
}

std::vector<long long> get_numbers(std::string line) {
    std::string cislo = "";
    std::vector<long long> sequence;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line.at(i)) || line.at(i) == '-') {
            cislo += line.at(i);
        }
        if (line.at(i) == ' ' || i == line.length()-1) {
            if(cislo != ""){
                sequence.push_back((stoll(cislo, nullptr, 10)));
            }
            cislo = "";
        }
    }
    return sequence;
}

std::vector<long long> derive_sequence(std::vector<long long> seq) {
    long long difference;
    std::vector<long long> new_seq;
    for (int i = 0; i < seq.size(); i++) {
        if (i == seq.size()-1) break;
        difference = seq.at(i+1) - seq.at(i);
        new_seq.push_back(difference);
    }
    return new_seq;
}

bool is_all_zero(std::vector<long long> seq) {
    for (long long num : seq) {
        if (num != 0) {
            return false;
        }
    }
    return true;
}
