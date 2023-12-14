#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> processMap(const std::vector<std::string> &map)
{
    std::vector<int> notes;
    int width = map[0].length();
    int height = map.size();

    for (int x = 0; x < width - 1; x++)
    {
        bool symmetric = true;
        std::string col1;
        std::string col2;
        for (int y = 0; y < height; y++)
        {
            col1 += map[y][x];
            col2 += map[y][x + 1];
        }
        if (col1 == col2)
        {
            for (int offset = 1; offset < width; offset++)
            {
                col1 = "";
                col2 = "";
                if (x - offset < 0 || x + offset + 1 >= width)
                    break;
                for (int y = 0; y < height; y++)
                {
                    col1 += map[y][x - offset];
                    col2 += map[y][x + offset + 1];
                }
                if (col1 != col2)
                {
                    symmetric = false;
                    break;
                }
            }
        }
        else
            symmetric = false;

        if (symmetric == true)
            notes.push_back(x + 1);
    }

    for (int y = 0; y < height - 1; y++)
    {
        bool symmetric = true;
        std::string row1 = map[y];
        std::string row2 = map[y + 1];

        if (row1 == row2)
        {
            for (int offset = 1; offset < width; offset++)
            {
                if (y - offset < 0 || y + offset + 1 >= height)
                    break;

                row1 = map[y - offset];
                row2 = map[y + offset + 1];
                if (row1 != row2)
                {
                    symmetric = false;
                    break;
                }
            }
        }
        else
            symmetric = false;

        if (symmetric == true)
            notes.push_back(100 * (y + 1));
    }

    return notes;
}

int processMapPart2(const std::vector<std::string> &mapIn)
{
    int part1Notes = processMap(mapIn)[0];
    int notes = 0;
    int width = mapIn[0].length();
    int height = mapIn.size();
    std::vector<std::string> map;
    std::vector<int> notesList;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            map = mapIn;
            if (map[j].at(i) == '.')
                map[j].at(i) = '#';
            else
                map[j].at(i) = '.';

            std::vector<int> notesTemp;
            notesTemp = processMap(map);
            for (int k = 0; k < notesTemp.size(); k++)
                notesList.push_back(notesTemp[k]);
        }
    }

    sort(notesList.begin(), notesList.end());
    notesList.erase(unique(notesList.begin(), notesList.end()), notesList.end());

    for (int i = 0; i < notesList.size(); i++)
        if (notesList[i] != part1Notes)
            return notesList[i];

    return part1Notes;
}

int main()
{
    std::cout << "AoC 2023 Day 13" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1 & 2
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> lines;
    int out = 0;
    int out2 = 0;
    while (std::getline(file, line))
    {
        if (line == "")
        {
            out += processMap(lines)[0];
            out2 += processMapPart2(lines);
            lines.clear();
        }
        else
            lines.push_back(line);
    }
    out += processMap(lines)[0];
    out2 += processMapPart2(lines);
    file.close();

    std::cout << "Part 1: " << out << std::endl;
    std::cout << "Part 2: " << out2 << std::endl;

    return 0;
}
