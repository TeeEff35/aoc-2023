#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>

typedef struct
{
    long long start_range;
    long long end_range;
    bool found = false;
}Range;

std::vector<long long> get_numbers(std::string line);
long long find_in_map(long long number, std::vector<long long> map);
std::vector<long long> daj_vyhovujuci_range(std::vector<long long> map);
std::vector<Range> find_range_in_map(Range range, std::vector<long long> map);
std::vector<Range> najdi_range(std::vector<Range>, std::vector<std::vector<long long>> mapy);
Range preloz_range(Range range, std::vector<long long> mapa);

int main (int argc, char* argv[]) {

    auto start = std::chrono::high_resolution_clock::now();

    std::string line;
    std::ifstream file_input("input.txt");

    std::vector<long long> seeds;
    std::vector<std::vector<long long>> mapy;
    long long lowest_location = LONG_LONG_MAX;

    getline (file_input, line);
    seeds = get_numbers(line);

    while (getline (file_input, line)) 
    {
        if (line == "" || !isdigit(line.at(0))) {
            mapy.push_back(std::vector<long long> {0,0,0});
            continue;
        }else{
            std::vector<long long> map = get_numbers(line);
            mapy.push_back(map);
        }
    }
    mapy.push_back({0,0,0});

    for (int i = 0; i <= seeds.size()/2; i += 2) {
        Range starting_range;
        starting_range.start_range = seeds.at(i);
        starting_range.end_range = seeds.at(i) + seeds.at(i + 1) - 1;

        std::vector<Range> ranges;
        ranges.push_back(starting_range);
        std::vector<std::vector<long long>> mapy_na_preklad;

        int help_counter = 0;
        for (std::vector<long long> mapa : mapy) {
            help_counter++;
            if (mapa.at(2) == 0 && mapy_na_preklad.size() == 0) {
                continue;
            } else if (mapa.at(2) == 0 && mapy_na_preklad.size()) {
                ranges = najdi_range(ranges, mapy_na_preklad);
                mapy_na_preklad.clear();
                continue;
            }
           
            mapy_na_preklad.push_back(mapa);
        }
        for (Range range : ranges) {
            lowest_location = std::min(range.start_range, lowest_location);
        }
        ranges.clear();
    }

    std::cout << "najmensia lokacia: " << lowest_location << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Program bežal " << duration.count() << " sekúnd." << std::endl;
}

std::vector<long long> get_numbers(std::string line) {
    std::string cislo = "";
    std::vector<long long> seeds;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line.at(i))) {
            cislo += line.at(i);
        }
        if (line.at(i) == ' ' || i == line.length()-1) {
            if(cislo != "")seeds.push_back(stoll(cislo, nullptr, 10));
            cislo = "";
        }
    }
    return seeds;
}

long long find_in_map(long long number, std::vector<long long> map) {
    if (number >= map.at(1) && number <= map.at(2) + map.at(1) - 1) {
       return  number -= (map.at(1) - map.at(0));     
    }
    return number;
}

std::vector<long long> daj_vyhovujuci_range(std::vector<long long> map){
    std::vector<long long> vyhovujuci_range;
    vyhovujuci_range.push_back(map.at(1));
    vyhovujuci_range.push_back(map.at(1) + map.at(2) - 1);
    return vyhovujuci_range;
}

std::vector<Range> find_range_in_map(Range range, std::vector<long long> map) {
    std::vector<Range> new_ranges;
    Range temp_range;
    
    //spolocny rozsah
    std::vector<long long> rozsah_z_mapy = daj_vyhovujuci_range(map);
    long long min_hodnota_spolocnej_casti = std::max(range.start_range, rozsah_z_mapy.at(0));
    long long max_hodnota_spolocnej_casti = std::min(range.end_range, rozsah_z_mapy.at(1));

    if (min_hodnota_spolocnej_casti <= max_hodnota_spolocnej_casti) {
        temp_range.start_range = min_hodnota_spolocnej_casti;
        temp_range.end_range = max_hodnota_spolocnej_casti;
        temp_range.found = true;
        new_ranges.push_back(temp_range);
    } else {
        new_ranges.push_back(range);
        return new_ranges; 
    }

    //ostatne rozsahy
    long long min_horny_rozsah = min_hodnota_spolocnej_casti == range.start_range ? min_hodnota_spolocnej_casti : min_hodnota_spolocnej_casti - 1;
    long long max_dolny_rozsah = max_hodnota_spolocnej_casti == range.end_range ? max_hodnota_spolocnej_casti : max_hodnota_spolocnej_casti + 1;

    temp_range.start_range = range.start_range;
    temp_range.end_range = min_horny_rozsah;
    temp_range.found = false;
    if (temp_range.start_range != temp_range.end_range) {
        new_ranges.push_back(temp_range);
    }

    temp_range.start_range = max_dolny_rozsah;
    temp_range.end_range = range.end_range;
    temp_range.found = false;
    if (temp_range.start_range != temp_range.end_range) {
        new_ranges.push_back(temp_range);
    }
    return new_ranges;
}

std::vector<Range> najdi_range(std::vector<Range> starting_ranges, std::vector<std::vector<long long>> mapy) {
    std::vector<Range> final_ranges;
    std::vector<Range> temp_ranges;
    std::vector<Range> nevyhovujuce_ranges = starting_ranges;
    std::vector<Range> helper;
    bool found_range = false; 

    for (std::vector<long long> mapa : mapy) {
        while (true) {
            for (Range range : nevyhovujuce_ranges) {
                temp_ranges = find_range_in_map(range, mapa);
                for (int i = 0; i < temp_ranges.size(); i++) {
                     if (temp_ranges.at(i).found) {
                        Range prelozeny_range = preloz_range(temp_ranges.at(i), mapa);
                        final_ranges.push_back(prelozeny_range);  
                        for (int j = i+1; j < temp_ranges.size() - i; j++) {
                            helper.push_back(temp_ranges.at(j));
                        }
                        break;
                    } else {
                        helper.push_back(range);
                    }
                }
                if (found_range) {
                    found_range = false;
                    break;
                }
            }
            nevyhovujuce_ranges = helper;
            helper.clear();
            break;
        }
    }

    final_ranges.insert(final_ranges.end(), nevyhovujuce_ranges.begin(), nevyhovujuce_ranges.end());
    return final_ranges;
}

Range preloz_range(Range range, std::vector<long long> mapa) {
    Range prelozeny_range;
    prelozeny_range.start_range = find_in_map(range.start_range, mapa);
    prelozeny_range.end_range =  find_in_map(range.end_range, mapa);
    return prelozeny_range;
}