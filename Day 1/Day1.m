% Advent of Code 2015
% Day 1
clear
close
clc

fprintf("Advent of Code 2015\nDay 1\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");

floor = 0;
i = 1;
while i <= length(input)
    instruction = input(i);
    
    if instruction == '('
        floor = floor + 1;
    end
    if instruction == ')'
        floor = floor - 1;
    end
    i = i + 1;
end
fprintf("Santa ended on floor %d\n", floor);


floor = 0;
i = 1;
while i <= length(input)
    instruction = input(i);
    
    if instruction == '('
        floor = floor + 1;
    end
    if instruction == ')'
        floor = floor - 1;
    end
    if floor == -1
        break;
    end
    i = i + 1;
end
fprintf("\nPart 2:\nSanta entered the basement on character %d\n", i);

