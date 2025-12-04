#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

std::chrono::high_resolution_clock::time_point tickTime;
std::chrono::high_resolution_clock::time_point tockTime;

void static inline tick(){
    tickTime = std::chrono::high_resolution_clock::now();
}

void static inline tock(){
    tockTime = std::chrono::high_resolution_clock::now();
}

void static inline printMicroseconds() {
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tockTime - tickTime).count() << " us" << std::endl;
}

int main()
{
    std::cout << "AoC 2025 Day 3" << std::endl;
    std::string fileName = "input.txt";
    // std::string fileName = "example.txt";

    // read in the file
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::vector<int>> banks;
    while (std::getline(file, line))
    {
        std::vector<int> bank;
        for(auto c:line)
            bank.push_back(c-'0');
        
        banks.push_back(bank);
    }
    file.close();

    // Part 1
    tick();
    unsigned long long sum = 0;
    for (auto bank:banks){
        int max = 0;
        for (int first = 0; first < bank.size()-1; first++)
            for (int second = first + 1; second < bank.size(); second++)
            {
                int joltage = bank[first] * 10 + bank[second];
                max = joltage > max ? joltage : max;
            }
        sum += max;
    }
    tock();
    std::cout << "Part 1: " << sum << std::endl;
    printMicroseconds();

    // Part 2
    tick();
    sum = 0;
    for (auto bank:banks){
        int len = bank.size();
        unsigned long long max = 0;

        struct jolt{
            int position = -1;
            int value = 0;
        };

        jolt j;
        std::vector<jolt> jolts;
        jolts.reserve(12);
        for (int i = 0; i < 12; i ++){
            int startPos = 0;
            if (i > 0) startPos = jolts[i-1].position + 1;
            int endPos = len - (12 - i);
            max = 0;
            for (int n = endPos; n >= startPos; n--){
                if (bank[n] >= max){
                    max = bank[n];
                    j.value = max;
                    j.position = n;
                }
            }
            jolts[i] = j;
        }
        max = 0;
        for (int i = 0; i < 12; i ++)
            max = max * 10 + jolts[i].value;

        sum += max;
    }
    tock();
    std::cout << "Part 2: " << sum << std::endl;
    printMicroseconds();
    return 0;
}
