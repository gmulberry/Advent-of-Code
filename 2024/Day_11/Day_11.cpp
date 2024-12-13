#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

struct stone
{
    std::string engraving = "";
    unsigned long long numTimes = 0;

    unsigned long long toNum()
    {
        return stoull(engraving);
    }

    int numDigits()
    {
        return engraving.length();
    }
};

std::vector<std::string> strSplit(const std::string &in, const char &delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (char c : in)
    {
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

void addToList(std::vector<stone> &stones, stone s, unsigned long long numTimes)
{
    for (unsigned long long n = 0; n < numTimes; n++)
    {
        bool alreadyInList = false;
        int i;
        for (i = 0; i < stones.size(); i++)
        {
            if (s.engraving == stones.at(i).engraving)
            {
                alreadyInList = true;
                break;
            }
        }

        if (alreadyInList)
            stones.at(i).numTimes++;
        else
            stones.push_back(s);
    }
}

std::string rmZeros(std::string str)
{
    size_t pos = str.find_first_not_of('0');
    str = (pos == std::string::npos) ? "0" : str.substr(pos);
    return str;
}

std::string toStringNoZeros(unsigned long long in)
{
    std::string str = std::to_string(in);
    return rmZeros(str);
}

int main()
{
    std::cout << "AoC 2024 Day 11" << std::endl;
    std::string fileName = "Day_11/input.txt";
    // std::string fileName = "Day_11/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    std::vector<std::string> splitUp = strSplit(line, ' ');
    file.close();

    // Part 1
    std::vector<stone> stones;

    // create the list of stones
    for (auto st : splitUp)
    {
        stone s;
        s.engraving = st;
        s.numTimes = 1;
        addToList(stones, s, 1);
    }

    for (int numBlinks = 0; numBlinks < 25; numBlinks++)
    {
        std::vector<stone> newStones;
        newStones.reserve(10000);
        for (stone st : stones)
        {
            unsigned long long engraving = st.toNum();
            if (engraving == 0)
            {
                stone s;
                s.engraving = toStringNoZeros(1);
                s.numTimes = 1;
                addToList(newStones, s, st.numTimes);
            }
            else if (st.numDigits() % 2 == 0)
            {
                std::string firstHalf = st.engraving.substr(0, st.numDigits() / 2);
                std::string secondHalf = st.engraving.substr(st.numDigits() / 2, st.numDigits() / 2);

                stone s;
                s.engraving = rmZeros(firstHalf);
                s.numTimes = 1;
                addToList(newStones, s, st.numTimes);

                s.engraving = rmZeros(secondHalf);
                addToList(newStones, s, st.numTimes);
            }
            else
            {
                unsigned long long temp = engraving * 2024;
                stone s;
                s.engraving = toStringNoZeros(temp);
                s.numTimes = 1;
                addToList(newStones, s, st.numTimes);
            }
        }
        stones = newStones;
        unsigned long long numStones = 0;
        for (auto st : stones)
            numStones += st.numTimes;
    }

    unsigned long long numStones = 0;
    for (auto st : stones)
        numStones += st.numTimes;
    std::cout << "Part 1: " << numStones << std::endl;

    // Part 2
    int numPossible = 0;
    std::cout << "Part 2: " << "Not implemented yet!" << std::endl;
    // 31116819518 too low
    return 0;
}