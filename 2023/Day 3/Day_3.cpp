#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct symbol
{
    char sym;
    int x;
    int y;
};

struct number
{
    int num;
    int numLength;
    int x;
    int y;
    int isTouchingSymbol = false;
};

int main()
{
    std::cout << "AoC 2023 Day 3" << std::endl;
    // Part 1
    std::ifstream file("input.txt");
    // std::ifstream file("example.txt");
    std::string line;
    unsigned int out = 0;
    bool failed = false;
    std::vector<std::string> lines;
    std::vector<symbol> symbols;
    std::vector<number> numbers;
    int y = 0;
    while (std::getline(file, line))
    {
        int numLength = 0;
        int num = 0;
        int numX = 0;
        int numY = 0;
        for (int x = 0; x < line.length(); x++)
        {
            char c = line.at(x);
            if (c >= '0' && c <= '9')
            {
                if (numLength == 0)
                {
                    numX = x;
                    numY = y;
                }
                numLength++;
                num = num * 10 + c - '0';
            }
            else
            {
                if (c != '.')
                {
                    symbol s;
                    s.sym = c;
                    s.x = x;
                    s.y = y;
                    symbols.push_back(s);
                }
                if (numLength != 0)
                {
                    number n;
                    n.num = num;
                    n.numLength = numLength;
                    n.x = x - 1;
                    n.y = y;
                    numbers.push_back(n);
                    numLength = 0;
                    num = 0;
                }
            }
        }
        if (numLength != 0) // number could be at the end of a line too
        {
            number n;
            n.num = num;
            n.numLength = numLength;
            n.x = line.length() - 1;
            n.y = y;
            numbers.push_back(n);
            numLength = 0;
            num = 0;
        }
        y++;
        lines.push_back(line);
    }
    file.close();
    for (int i = 0; i < numbers.size(); i++)
    {
        for (int s = 0; s < symbols.size(); s++)
        {
            if (symbols[s].y >= numbers[i].y - 1 && symbols[s].y <= numbers[i].y + 1 && symbols[s].x >= numbers[i].x - numbers[i].numLength && symbols[s].x <= numbers[i].x + 1)
                numbers[i].isTouchingSymbol = true;
        }
        if (numbers[i].isTouchingSymbol)
            out += numbers[i].num;
    }
    std::cout << "Part 1: " << out << std::endl;

    // Part 2
    out = 0;
    for (int s = 0; s < symbols.size(); s++)
    {
        int gearRatio = 0;
        int numTouching = 0;
        for (int i = 0; i < numbers.size(); i++)
        {
            if (symbols[s].sym == '*' && symbols[s].y >= numbers[i].y - 1 && symbols[s].y <= numbers[i].y + 1 && symbols[s].x >= numbers[i].x - numbers[i].numLength && symbols[s].x <= numbers[i].x + 1)
            {
                // touching the gear
                numTouching++;
                if (gearRatio == 0)
                    gearRatio = numbers[i].num;
                else
                    gearRatio *= numbers[i].num;
            }
        }
        if (numTouching == 2)
            out += gearRatio;
    }
    std::cout << "Part 2: " << out << std::endl;