#include <iostream>
#include <fstream>
#include <string>
#include <vector>
struct coord
{
    int x;
    int y;
};

int main()
{
    std::cout << "AoC 2023 Day 11" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::string mapNonExpanded;
    int height = 0;
    while (std::getline(file, line))
    {
        mapNonExpanded += line;
        height++;
    }
    file.close();
    int width = line.length();

    std::vector<int> emptyCols;
    std::vector<int> emptyRows;

    bool isEmpty = true;
    for (int y = 0; y < height; y++)
    {
        isEmpty = true;
        for (int x = 0; x < width; x++)
            if (mapNonExpanded[y * width + x] == '#')
            {
                isEmpty = false;
                break;
            }
        if (isEmpty)
            emptyRows.push_back(y);
    }
    for (int x = 0; x < width; x++)
    {
        isEmpty = true;
        for (int y = 0; y < height; y++)
            if (mapNonExpanded[y * width + x] == '#')
            {
                isEmpty = false;
                break;
            }
        if (isEmpty)
            emptyCols.push_back(x);
    }

    std::vector<coord> galaxies;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            if (mapNonExpanded[y * width + x] == '#')
            {
                coord c;
                c.x = x;
                c.y = y;
                galaxies.push_back(c);
            }

    unsigned long out = 0;
    for (int galaxy1 = 0; galaxy1 < galaxies.size() - 1; galaxy1++)
        for (int galaxy2 = galaxy1 + 1; galaxy2 < galaxies.size(); galaxy2++)
        {
            int minX = (galaxies[galaxy1].x < galaxies[galaxy2].x) ? galaxies[galaxy1].x : galaxies[galaxy2].x;
            int maxX = (galaxies[galaxy1].x > galaxies[galaxy2].x) ? galaxies[galaxy1].x : galaxies[galaxy2].x;
            int minY = (galaxies[galaxy1].y < galaxies[galaxy2].y) ? galaxies[galaxy1].y : galaxies[galaxy2].y;
            int maxY = (galaxies[galaxy1].y > galaxies[galaxy2].y) ? galaxies[galaxy1].y : galaxies[galaxy2].y;

            int numEmptyCols = 0;
            for (int i = 0; i < emptyCols.size(); i++)
                if (emptyCols[i] > minX && emptyCols[i] < maxX)
                    numEmptyCols++;

            int numEmptyRows = 0;
            for (int i = 0; i < emptyRows.size(); i++)
                if (emptyRows[i] > minY && emptyRows[i] < maxY)
                    numEmptyRows++;

            out += (maxX - minX + numEmptyCols) + (maxY - minY + numEmptyRows);
        }

    std::cout << "Part 1: " << out << std::endl;

    // Part 2
    out = 0;
    for (int galaxy1 = 0; galaxy1 < galaxies.size() - 1; galaxy1++)
        for (int galaxy2 = galaxy1 + 1; galaxy2 < galaxies.size(); galaxy2++)
        {
            int minX = (galaxies[galaxy1].x < galaxies[galaxy2].x) ? galaxies[galaxy1].x : galaxies[galaxy2].x;
            int maxX = (galaxies[galaxy1].x > galaxies[galaxy2].x) ? galaxies[galaxy1].x : galaxies[galaxy2].x;
            int minY = (galaxies[galaxy1].y < galaxies[galaxy2].y) ? galaxies[galaxy1].y : galaxies[galaxy2].y;
            int maxY = (galaxies[galaxy1].y > galaxies[galaxy2].y) ? galaxies[galaxy1].y : galaxies[galaxy2].y;

            int numEmptyCols = 0;
            for (int i = 0; i < emptyCols.size(); i++)
                if (emptyCols[i] > minX && emptyCols[i] < maxX)
                    numEmptyCols++;

            int numEmptyRows = 0;
            for (int i = 0; i < emptyRows.size(); i++)
                if (emptyRows[i] > minY && emptyRows[i] < maxY)
                    numEmptyRows++;

            out += (maxX - minX + numEmptyCols * 999999) + (maxY - minY + numEmptyRows * 999999);
        }

    std::cout << "Part 2: " << out << std::endl;

    return 0;
}
