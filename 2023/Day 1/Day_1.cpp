#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::cout << "AoC 2023 Day 1" << std::endl;

    // Part 1
    std::ifstream file("input.txt");
    // std::ifstream file("example.txt");
    std::string line;
    unsigned int out = 0;
    while (std::getline(file, line))
    {
        std::vector<int> digits;
        for (int i = 0; i < line.length(); i++)
        {
            char c = line.at(i);
            if (c >= '0' && c <= '9')
                digits.push_back(c - 48);
        }
        out += (digits.front() * 10 + digits.back());
    }
    std::cout << "Part 1: " << out << std::endl;
    file.close();

    // Part 2
    std::ifstream file2("input.txt");
    // std::ifstream file2("example 2.txt");
    out = 0;
    while (std::getline(file2, line))
    {
        std::string newLine;
        std::cout << "line: " << line << std::endl;
        int idx = 0;
        while (line.length() > 0)
        {
            if (line.find("one") == 0)
            {
                newLine.push_back('1');
                line.erase(0, 3);
                if (line.find("ight") == 0)
                    line = 'e' + line;
            }
            else if (line.find("two") == 0)
            {
                newLine.push_back('2');
                line.erase(0, 3);
                if (line.find("ne") == 0)
                    line = 'o' + line;
            }
            else if (line.find("three") == 0)
            {
                newLine.push_back('3');
                line.erase(0, 5);
                if (line.find("ight") == 0)
                    line = 'e' + line;
            }
            else if (line.find("four") == 0)
            {
                newLine.push_back('4');
                line.erase(0, 4);
            }
            else if (line.find("five") == 0)
            {
                newLine.push_back('5');
                line.erase(0, 4);
                if (line.find("ight") == 0)
                    line = 'e' + line;
            }
            else if (line.find("six") == 0)
            {
                newLine.push_back('6');
                line.erase(0, 3);
            }
            else if (line.find("seven") == 0)
            {
                newLine.push_back('7');
                line.erase(0, 5);
            }
            else if (line.find("eight") == 0)
            {
                newLine.push_back('8');
                line.erase(0, 5);
                if (line.find("wo") == 0)
                    line = 't' + line;
                if (line.find("hree") == 0)
                    line = 't' + line;
            }
            else if (line.find("nine") == 0)
            {
                newLine.push_back('9');
                line.erase(0, 4);
                if (line.find("ight") == 0)
                    line = 'e' + line;
            }
            else
            {
                newLine.push_back(line.at(0));
                line.erase(0, 1);
            }
        }
        line = newLine;

        std::vector<int> digits;
        for (int i = 0; i < line.length(); i++)
        {
            char c = line.at(i);
            if (c >= '0' && c <= '9')
                digits.push_back(c - 48);
        }
        out += (digits.front() * 10 + digits.back());
    }
    std::cout << "Part 2: " << out << std::endl;
    file2.close();

    return 0;
}
