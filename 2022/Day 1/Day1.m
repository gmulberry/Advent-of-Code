% Advent of Code 2022
% Day 1
clear 
close 
clc

fprintf("Advent of Code 2022\nDay 1\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");

lines = strsplit(input, '\n');

i = 1;
totCal = 0;
maxCal = 0;
numElves = 0;
while i <= length(lines)
    line = lines{i};
    len = length(line);
    if len > 1
        lineVal = str2double(line);
        totCal = totCal + lineVal;
    else
        numElves = numElves + 1;
        elf(numElves) = totCal;
        maxCal = max(totCal,maxCal);
        totCal = 0;
    end    
    i = i + 1;
end
fprintf("There are %d elves, the most calories being carried is: %d\n", numElves, maxCal);

elf = sort(elf);
topThree = sum(elf(numElves - 2: numElves));

fprintf("\nPart 2:\n");
fprintf("The top three elves are carrying %d, %d, and %d calories.\n", elf(numElves), elf(numElves - 1), elf(numElves - 2));
fprintf("The total carried by the top 3 elves is %d\n", topThree);
