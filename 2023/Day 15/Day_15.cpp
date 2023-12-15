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

int getHash(const std::string &in)
{
    int out = 0;
    for (int i = 0; i < in.length(); i++)
    {
        out += in[i];
        out *= 17;
        out %= 256;
    }
    return out;
}

struct lens
{
    std::string label;
    int focalLength;
};

void printBoxes(const std::vector<std::vector<lens>> &boxes)
{
    for (int boxNum = 0; boxNum < 256; boxNum++)
        if (boxes[boxNum].size() != 0)
        {
            std::cout << "box: " << boxNum << " lenses: ";
            for (int lensNum = 0; lensNum < boxes[boxNum].size(); lensNum++)
                std::cout << "[" << boxes[boxNum][lensNum].label << " " << boxes[boxNum][lensNum].focalLength << "] ";

            std::cout << std::endl;
        }
}

int main()
{
    std::cout << "AoC 2023 Day 15" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::getline(file, line);
    file.close();
    std::vector<std::string> steps = strSplit(line, ',');
    int out = 0;
    for (int i = 0; i < steps.size(); i++)
        out += getHash(steps[i]);

    std::cout << "Part 1: " << out << std::endl;

    // Part 2
    std::vector<std::vector<lens>> boxes;
    for (int i = 0; i < 256; i++)
    {
        std::vector<lens> temp;
        boxes.push_back(temp);
    }

    for (int i = 0; i < steps.size(); i++)
    {
        std::string label = "";
        int j = 0;
        do
        {
            label += steps[i][j];
            j++;
        } while (steps[i][j] >= 'a' && steps[i][j] <= 'z');
        int boxNum = getHash(label);
        char instruction = steps[i][j];
        int focalLength = 0;
        if (instruction == '=')
        {
            focalLength = atoi(&steps[i][j + 1]);
            bool replacedALens = false;
            for (int lensNum = 0; lensNum < boxes[boxNum].size(); lensNum++)
                if (boxes[boxNum][lensNum].label == label)
                {
                    boxes[boxNum][lensNum].focalLength = focalLength;
                    replacedALens = true;
                }

            if (!replacedALens)
            {
                lens newLens;
                newLens.label = label;
                newLens.focalLength = focalLength;
                boxes[boxNum].push_back(newLens);
            }
        }
        else
        {
            std::vector<lens> tempLenses;
            for (int lensNum = 0; lensNum < boxes[boxNum].size(); lensNum++)
                if (boxes[boxNum][lensNum].label != label)
                {
                    tempLenses.push_back(boxes[boxNum][lensNum]);
                }

            boxes[boxNum] = tempLenses;
        }
    }

    out = 0;
    for (int boxNum = 0; boxNum < 256; boxNum++)
        for (int lensNum = 0; lensNum < boxes[boxNum].size(); lensNum++)
        {
            int focusingPower = 1;
            focusingPower *= (boxNum + 1);
            focusingPower *= (lensNum + 1);
            focusingPower *= boxes[boxNum][lensNum].focalLength;
            out += focusingPower;
        }

    std::cout << "Part 2: " << out << std::endl;
    return 0;
}
