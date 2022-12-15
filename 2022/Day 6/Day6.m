% Advent of Code 2022
% Day 6
clear
close
clc

fprintf("Advent of Code 2022\nDay 6\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");

lengthNeeded = 4;
for i = lengthNeeded:length(input)
    buffer = input(i-(lengthNeeded-1):i);
    good = 1;
    for j = 1:lengthNeeded
        for k = 1:lengthNeeded
            if j ~= k && buffer(j) == buffer(k)
                good = 0;
            end
        end
    end
    if good
        fprintf("Good sequence at i = %d\n", i);
        break;
    end
end


fprintf("\nPart 2:\n")
lengthNeeded = 14;
for i = lengthNeeded:length(input)
    buffer = input(i-(lengthNeeded-1):i);
    good = 1;
    for j = 1:lengthNeeded
        for k = 1:lengthNeeded
            if j ~= k && buffer(j) == buffer(k)
                good = 0;
            end
        end
    end
    if good
        fprintf("Good sequence at i = %d\n", i);
        break;
    end
end
