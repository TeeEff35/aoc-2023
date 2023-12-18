#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <numeric>

typedef struct 
{
    std::string node_name;
    std::string left_path;
    std::string righ_path;
    int steps_for_ghost_move = 0;
}Node;

Node extract_node(std::string);
int find_node_pos(std::vector<Node>, std::string);
std::vector<Node> ghost_move(std::vector<Node>, std::vector<Node>, std::string);
long long najdi_nsn(std::vector<Node>);

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    std::string instructions = "";
    std::vector<Node> all_nodes;
    std::vector<Node> starting_nodes;

    int position = 0;

    getline (file_input, line);
    while (line != "") 
    {
        instructions += line;
        getline (file_input, line);
    }

    while (getline (file_input, line)) 
    {
        Node temp;
        temp = extract_node(line);
        if (temp.node_name.at(2) == 'A') {
            starting_nodes.push_back(temp);
        }
        position++;
        all_nodes.push_back(temp);
    }

    int step_counter = 1;
    starting_nodes = ghost_move(starting_nodes, all_nodes, instructions);

    for (Node node : starting_nodes) {
        std::cout << "pocet krokov: " << node.steps_for_ghost_move << std::endl;
    }


    std::cout << najdi_nsn(starting_nodes) << std::endl;

}

Node extract_node(std::string info) {
    Node node;
    int pos;
    std::string split;
    while (info.find(" ") != std::string::npos) {
        pos = info.find(" ");
        info.erase(pos, 1);
    }
    pos = info.find("(");
    info.erase(pos, 1);
    pos = info.find(")");
    info.erase(pos, 1);

    std::stringstream splited(info);
    getline (splited, split, '=');
    node.node_name = split;
    getline (splited, split, '=');

    std::stringstream splitedd(split);
    getline (splitedd, split, ',');
    node.left_path = split;
    getline (splitedd, split, ',');
    node.righ_path = split;

    return node;
}

int find_node_pos(std::vector<Node> all_nodes, std::string name) {
    int counter = 0;

    for (Node node : all_nodes) {
        if (node.node_name == name) {
            return counter;
        } else {
            counter++;
        }
    }
    return 0;
}

std::vector<Node> ghost_move(std::vector<Node> nodes_to_change, std::vector<Node> all_nodes, std::string instructions) {
    int pos;
    for (Node &node : nodes_to_change) {
        std::string current_node = node.node_name;
        while (current_node.at(2) != 'Z') {
            for (int i = 0; i < instructions.size(); i++) {
                switch (instructions.at(i))
                {
                    case 'L':
                        pos = find_node_pos(all_nodes, current_node);
                        current_node = all_nodes.at(pos).left_path;
                        node.steps_for_ghost_move++;
                        break;
                    case 'R':
                        pos = find_node_pos(all_nodes, current_node);
                        current_node = all_nodes.at(pos).righ_path;
                        node.steps_for_ghost_move++;
                        break;
                    default:
                        break;
                }
                if (current_node.at(2) == 'Z') {
                    break;
                }
            }
        }
    }

    return nodes_to_change;
}

long long najdi_nsn(std::vector<Node> nodes) {
    std::vector<long long> lcm;
    std::vector<long long> help;
    for (Node node : nodes) {
        lcm.push_back(node.steps_for_ghost_move);
    }
    long long fr, sc;
    while (lcm.size() != 1) {
        for (int i = 0; i < lcm.size(); i++) {
            if (i <= lcm.size()-2) {
                fr = lcm.at(i);
                sc = lcm.at(i+1);
                i = i+1;
            } else {
                fr = lcm.at(i);
                sc = lcm.at(i-1);
            }
            help.push_back(std::lcm(fr, sc));
        }
        lcm = help;
        help.clear();
    }
    return lcm.at(0);
}