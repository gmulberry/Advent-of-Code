% Advent of Code 2022
% Day 10
clear
close
clc

fprintf("Advent of Code 2022\nDay 10\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

numContained = 0;
cycle = 0;
X = 1;
subCycles = 0;
i = 1;
while i <= length(lines)
    line = lines{i};
    splitUp = strsplit(line, ' ');
    instruction = splitUp{1};
    cycle = cycle + 1;
    
    if strcmp(instruction, 'noop')
        subCycles = 0;
        i = i + 1;
    elseif strcmp(instruction, 'addx')
        arg = str2double(splitUp{2});
        if subCycles == 0
            subCycles = 1;
        elseif subCycles == 1
            subCycles = 0;
            X = X + arg;
            i = i + 1;
        end
    end
    
    % store the values
    Xs(cycle) = X;
end

check = [20, 60, 100, 140, 180, 220];
totStrength = 0;
for i = 1:length(check)
    totStrength = totStrength + Xs(check(i)-1)*check(i);
end
fprintf("The total strength is %d\n", totStrength);

fprintf("\nPart 2:\nThe CRT looks like this:\n")

xPos = 0;
width = 3;
fprintf("#");
for i = 1:length(Xs)
    xPos = mod(i-1, 40);
    
    if xPos == 39
        fprintf("\n#");
        
    else
        if Xs(i) >= xPos && Xs(i) < xPos + width
            fprintf("#");
        else
            fprintf(".");
        end
    end
end
