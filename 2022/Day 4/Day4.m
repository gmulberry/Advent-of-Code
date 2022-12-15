% Advent of Code 2022
% Day 4

clear
close
clc

fprintf("Advent of Code 2022\nDay 4\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

numContained = 0;
for i = 1:length(lines)
    line = string(strsplit(lines{i},','));
    elf1 = str2double(strsplit(line{1},'-'));
    elf2 = str2double(strsplit(line{2},'-'));
    
    if elf1(1) >= elf2(1) && elf1(2) <= elf2(2) || elf2(1) >= elf1(1) && elf2(2) <= elf1(2)
        numContained = numContained + 1;
    end
    
end
fprintf("There are %d completely overlapping pairs\n",numContained);


numOverlap = 0;
for i = 1:length(lines)
    overlaps = 0;
    line = string(strsplit(lines{i},','));
    elf1 = str2double(strsplit(line{1},'-'));
    elf2 = str2double(strsplit(line{2},'-'));
    for j = elf1(1):elf1(2)
        for k = elf2(1):elf2(2)
            if j == k
                overlaps = 1;
            end
        end
    end
    
    if overlaps == 1
        numOverlap = numOverlap + 1;
    end
    
end
fprintf("\nPart 2:\n");
fprintf("There are %d partially overlapping pairs\n", numOverlap);