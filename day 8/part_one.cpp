#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

typedef struct 
{
    std::string node_name;
    std::string left_path;
    std::string righ_path;
}Node;

Node extract_node(std::string);
int find_node_pos(std::vector<Node>, std::string name);

int main (int argc, char* argv[]) {
    std::string line;
    std::ifstream file_input("input.txt");

    std::string instructions = "";
    std::vector<Node> nodes;
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
        nodes.push_back(temp);
    }

    std::string starting_node = "AAA";
    std::string final_node = "ZZZ";
    std::string current_node = starting_node;

    int step_counter = 1;
    while (current_node != final_node) {
        for (int i = 0; i < instructions.size(); i++) {
            int pos = find_node_pos(nodes, current_node);

            switch (instructions.at(i))
            {
            case 'R':
                current_node = nodes.at(pos).righ_path;
                break;
            case 'L':
                current_node = nodes.at(pos).left_path;
                break;
            default:
                break;
            }
            if (current_node == final_node) {
                break;
            } else {
                step_counter++;
            }
        }
    }
    std::cout << "pocet krokov: " << step_counter << std::endl;

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

int find_node_pos(std::vector<Node> nodes, std::string name) {
    int counter = 0;

    for (Node node : nodes) {
        if (node.node_name == name) {
            return counter;
        } else {
            counter++;
        }
    }
    return 0;
}