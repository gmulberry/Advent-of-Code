#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::vector<std::string> strSplit(std::string in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (int idx = 0; idx < in.length(); idx++)
    {
        char c = in.at(idx);
        if (c == delimiter)
        {
            out.push_back(temp);
            temp = "";
        }
        else
            temp = temp + c;
    }
    out.push_back(temp);
    return out;
}

struct range
{
    long srcStart;
    long dstStart;
    long rn;
};

long map(const long &in, const std::vector<range> &map)
{
    long out = -1;
    for (int j = 0; j < map.size(); j++)
        if (in >= map[j].srcStart && in <= (map[j].srcStart + map[j].rn))
        {
            out = map[j].dstStart + (in - map[j].srcStart);
            break;
        }

    if (out == -1)
        out = in;
    return out;
}

void parseMap(std::ifstream &file, std::vector<range> &map)
{
    std::string line;
    std::vector<std::string> splitUp;
    while (std::getline(file, line))
    {
        if (line == "")
            break;
        splitUp = strSplit(line, ' ');
        range rn;
        rn.dstStart = stol(splitUp[0]);
        rn.srcStart = stol(splitUp[1]);
        rn.rn = stol(splitUp[2]);
        map.push_back(rn);
    }
}

int main()
{
    std::cout << "AoC 2023 Day 5" << std::endl;
    // Part 1
    std::ifstream file("input.txt");
    // std::ifstream file("example.txt");
    std::string line;
    std::vector<unsigned long> seeds;
    std::vector<range> seed2soil, soil2fert, fert2wat, wat2lght, lght2temp, temp2humd, humd2loc;

    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp;
        splitUp = strSplit(line, ' ');

        if (splitUp[0] == "seeds:")
            for (int i = 1; i < splitUp.size(); i++)
                seeds.push_back(stol(splitUp[i]));

        if (line == "seed-to-soil map:")
            parseMap(file, seed2soil);

        if (line == "soil-to-fertilizer map:")
            parseMap(file, soil2fert);

        if (line == "fertilizer-to-water map:")
            parseMap(file, fert2wat);

        if (line == "water-to-light map:")
            parseMap(file, wat2lght);

        if (line == "light-to-temperature map:")
            parseMap(file, lght2temp);

        if (line == "temperature-to-humidity map:")
            parseMap(file, temp2humd);

        if (line == "humidity-to-location map:")
            parseMap(file, humd2loc);
    }
    file.close();

    long min = -1;
    for (int i = 0; i < seeds.size(); i++)
    {
        long temp = map(map(map(map(map(map(map(seeds[i], seed2soil), soil2fert), fert2wat), wat2lght), lght2temp), temp2humd), humd2loc);
        if (min == -1)
            min = temp;
        else if (temp < min)
            min = temp;
    }
    std::cout << "Part 1: " << min << std::endl;

    // Part 2
    min = -1;
    for (int i = 0; i < seeds.size(); i += 2)
    {
        for (long j = seeds[i]; j < seeds[i] + seeds[i + 1]; j++)
        {
            long temp = map(map(map(map(map(map(map(j, seed2soil), soil2fert), fert2wat), wat2lght), lght2temp), temp2humd), humd2loc);
            if (min == -1)
                min = temp;
            else if (temp < min)
                min = temp;
        }
    }
    std::cout << "Part 2: " << min << std::endl;
}