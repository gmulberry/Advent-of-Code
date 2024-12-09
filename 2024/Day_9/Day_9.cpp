#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int EMPTY_BLOCK = -1;

struct fileInfo
{
    int loc = 0;
    int size = 0;
};

void printBlocks(const std::vector<int> &blocks)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks.at(i) != EMPTY_BLOCK)
            std::cout << blocks.at(i);
        else
            std::cout << '.';
    }
    std::cout << std::endl;
}

std::vector<int> constructBlocks(const std::string &diskMap)
{
    std::vector<int> blocks;
    int fileID = 0;
    for (int i = 0; i < diskMap.length(); i += 2)
    {
        int blockSize = diskMap.at(i) - '0';
        int emptySize = (i != diskMap.length() - 1) ? diskMap.at(i + 1) - '0' : 0;
        for (int n = 0; n < blockSize; n++)
            blocks.push_back(fileID);

        for (int n = 0; n < emptySize; n++)
            blocks.push_back(EMPTY_BLOCK);

        fileID++;
    }
    return blocks;
}

unsigned long long check(const std::vector<int> &blocks)
{
    unsigned long long checksum = 0;
    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks.at(i) != EMPTY_BLOCK)
        {
            checksum += blocks.at(i) * i;
        }
    }
    return checksum;
}

fileInfo findFile(const std::vector<int> &blocks, const int id, const int start)
{
    fileInfo f;
    f.size = 1;
    for (f.loc = start; f.loc < blocks.size(); f.loc++)
        if (blocks.at(f.loc) == id)
            break;

    for (int i = f.loc + 1; i < blocks.size(); i++)
    {
        if (blocks.at(i) == id)
            f.size++;
        else
            break;
    }

    return f;
}

int main()
{
    std::cout << "AoC 2024 Day 9" << std::endl;
     std::string fileName = "Day_9/input.txt";
    //std::string fileName = "Day_9/example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string diskMap;
    std::getline(file, diskMap);
    file.close();

    // Part 1
    std::vector<int> blocks = constructBlocks(diskMap);
    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks.at(i) == EMPTY_BLOCK)
        {
            int j;
            for (j = blocks.size() - 1; j > i; j--)
                if (blocks.at(j) != EMPTY_BLOCK)
                    break;

            if (j == i)
                break;

            int temp = blocks.at(i);
            blocks.at(i) = blocks.at(j);
            blocks.at(j) = temp;
        }
    }
    std::cout << "Part 1: " << check(blocks) << std::endl;

    // Part 2
    blocks = constructBlocks(diskMap);
    int maxFileID = blocks.at(blocks.size() - 1);
    for (int fileID = maxFileID; fileID >= 0; fileID--)
    {
        fileInfo f = findFile(blocks, fileID, 0);
        fileInfo e = findFile(blocks, EMPTY_BLOCK, 0);
        while (e.size < f.size && e.loc < blocks.size())
            e = findFile(blocks, EMPTY_BLOCK, e.loc + e.size);

        if (e.loc < blocks.size() && e.loc < f.loc)
        {
            for (int i = e.loc; i < e.loc + f.size; i++)
                blocks.at(i) = fileID;

            for (int i = f.loc; i < f.loc + f.size; i++)
                blocks.at(i) = EMPTY_BLOCK;
        }
    }
    std::cout << "Part 2: " << check(blocks) << std::endl;
    return 0;
}