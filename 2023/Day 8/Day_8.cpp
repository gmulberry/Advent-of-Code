#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

struct node
{
    std::string name;
    std::string left;
    std::string right;
};

int findNode(std::string nodeName, const std::vector<node> &nodes)
{
    int nodeNum = 0;
    while (nodeNum < nodes.size())
    {
        if (nodes[nodeNum].name == nodeName)
            break;

        nodeNum++;
    }
    return nodeNum;
}

int main()
{
    std::cout << "AoC 2023 Day 8" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::vector<node> nodes;
    std::string directions;
    std::getline(file, directions);
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::vector<std::string> splitUp = strSplit(line, ' ');
        node n;
        n.name = splitUp[0];
        std::string temp = "";
        for (int i = 1; i < 4; i++)
            temp += splitUp[2][i];
        n.left = temp;
        temp = "";
        for (int i = 0; i < 3; i++)
            temp += splitUp[3][i];
        n.right = temp;
        nodes.push_back(n);
    }
    file.close();

    int directionIdx = 0;
    int nodePos = 0;
    bool found = false;
    std::string lookingFor = "AAA";
    int steps = -1;
    while (!found)
    {
        nodePos = findNode(lookingFor, nodes);

        if (directions[directionIdx] == 'R')
            lookingFor = nodes[nodePos].right;
        else
            lookingFor = nodes[nodePos].left;

        if (directionIdx < directions.length() - 1)
            directionIdx++;
        else
            directionIdx = 0;

        if (nodes[nodePos].name == "ZZZ")
            found = true;

        steps++;
    }

    std::cout << "Part 1: " << steps << std::endl;
    return 0;
}
