#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;

struct coord
{
    int x;
    int y;
};

bool isOnPath(const coord &point, const std::vector<coord> &path)
{
    for (int i = 0; i < path.size(); i++)
        if (point.y == path[i].y && point.x == path[i].x)
            return true;
    return false;
}

bool isInside(const coord &point, const std::vector<coord> &vertices)
{
    // basically a ray tracing algorithm cobbled togehter from various sources
    int intersections = 0;
    double x = point.x + 0.5;
    double y = point.y + 0.5;

    for (int k = 0; k < vertices.size() - 1; k++)
    {
        double x1 = vertices[k].x;
        double y1 = vertices[k].y;
        double x2 = vertices[k + 1].x;
        double y2 = vertices[k + 1].y;
        if ((y < y1) != (y < y2) && x < (x1 + (((y - y1) / (y2 - y1)) * (x2 - x1))))
            intersections++;
    }
    return intersections % 2 == 1;
}

int main()
{
    std::cout << "AoC 2023 Day 10" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example3.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::string tiles;
    int height = 0;
    while (std::getline(file, line))
    {
        tiles += line;
        height++;
    }
    file.close();
    int width = line.length();

    coord startingPos;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            if (tiles[y * width + x] == 'S')
            {
                startingPos.x = x;
                startingPos.y = y;
                break;
                break;
            }

    coord currentPos = startingPos;
    coord previousPos = startingPos;
    int lastDir = 0;
    int steps = 0;
    bool atStartingPos = false;
    std::vector<coord> path;
    path.push_back(startingPos);
    while (!atStartingPos)
    {

        if (steps != 0 && currentPos.x == startingPos.x && currentPos.y == startingPos.y)
            atStartingPos = true;
        else
        {
            previousPos = currentPos;
            if (tiles[currentPos.y * width + currentPos.x] == 'S')
            {
                if (currentPos.x < width - 1 && (tiles[(currentPos.y) * width + (currentPos.x + 1)] == '-' ||
                                                 tiles[(currentPos.y) * width + (currentPos.x + 1)] == 'J' ||
                                                 tiles[(currentPos.y) * width + (currentPos.x + 1)] == '7'))
                {
                    currentPos.x += 1;
                    lastDir = EAST;
                }
                else if (currentPos.x > 0 && (tiles[(currentPos.y) * width + (currentPos.x - 1)] == '-' ||
                                              tiles[(currentPos.y) * width + (currentPos.x - 1)] == 'F' ||
                                              tiles[(currentPos.y) * width + (currentPos.x - 1)] == 'L'))
                {
                    currentPos.x -= 1;
                    lastDir = WEST;
                }
                else if (currentPos.y < height - 1 && (tiles[(currentPos.y + 1) * width + (currentPos.x)] == '|' ||
                                                       tiles[(currentPos.y + 1) * width + (currentPos.x)] == 'J' ||
                                                       tiles[(currentPos.y + 1) * width + (currentPos.x)] == 'L'))
                {
                    currentPos.y += 1;
                    lastDir = SOUTH;
                }
                else if (currentPos.y > 0 && (tiles[(currentPos.y - 1) * width + (currentPos.x)] == '|' ||
                                              tiles[(currentPos.y - 1) * width + (currentPos.x)] == '7' ||
                                              tiles[(currentPos.y - 1) * width + (currentPos.x)] == 'F'))
                {
                    currentPos.y -= 1;
                    lastDir = NORTH;
                }
                else
                    std::cout << "Error can't move!" << std::endl;
            }
            else if (lastDir == NORTH)
            {
                if (tiles[(currentPos.y) * width + (currentPos.x)] == '|')
                {
                    currentPos.y -= 1;
                    lastDir = NORTH;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == 'F')
                {
                    currentPos.x += 1;
                    lastDir = EAST;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == '7')
                {
                    currentPos.x -= 1;
                    lastDir = WEST;
                }
                else
                    std::cout << "Error can't move!" << std::endl;
            }
            else if (lastDir == EAST)
            {
                if (tiles[(currentPos.y) * width + (currentPos.x)] == '-')
                {
                    currentPos.x += 1;
                    lastDir = EAST;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == 'J')
                {
                    currentPos.y -= 1;
                    lastDir = NORTH;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == '7')
                {
                    currentPos.y += 1;
                    lastDir = SOUTH;
                }
                else
                    std::cout << "Error can't move!" << std::endl;
            }
            else if (lastDir == SOUTH)
            {
                if (tiles[(currentPos.y) * width + (currentPos.x)] == '|')
                {
                    currentPos.y += 1;
                    lastDir = SOUTH;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == 'L')
                {
                    currentPos.x += 1;
                    lastDir = EAST;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == 'J')
                {
                    currentPos.x -= 1;
                    lastDir = WEST;
                }
                else
                    std::cout << "Error can't move!" << std::endl;
            }
            else if (lastDir == WEST)
            {
                if (tiles[(currentPos.y) * width + (currentPos.x)] == '-')
                {
                    currentPos.x -= 1;
                    lastDir = WEST;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == 'L')
                {
                    currentPos.y -= 1;
                    lastDir = NORTH;
                }
                else if (tiles[(currentPos.y) * width + (currentPos.x)] == 'F')
                {
                    currentPos.y += 1;
                    lastDir = SOUTH;
                }
                else
                    std::cout << "Error can't move!" << std::endl;
            }
            else
                std::cout << "Error can't move!" << std::endl;

            path.push_back(currentPos);
            steps++;
        }
    }

    std::cout << "Part 1: " << steps / 2 << std::endl;

    // Part 2
    std::vector<coord> vertices;
    for (int i = 0; i < path.size(); i++)
        if (tiles[path[i].y * width + path[i].x] != '-' && tiles[path[i].y * width + path[i].x] != '|')
            vertices.push_back(path[i]);
    vertices.push_back(startingPos);

    coord point;
    int numInside = 0;
    for (point.y = 0; point.y < height; point.y++)
        for (point.x = 0; point.x < width; point.x++)
            if (!isOnPath(point, path) && isInside(point, vertices))
                numInside++;

    std::cout << "Part 2: " << numInside << std::endl;

    return 0;
}
