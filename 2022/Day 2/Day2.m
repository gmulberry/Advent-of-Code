% Advent of Code 2022
% Day 2
clear
close
clc

%input = sprintf("A Y\nB X\nC Z");

fprintf("Advent of Code 2022\nDay 2\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

score = 0;
for i = 1:length(lines)
    line = string(strsplit(lines{i},' '));
    if line(2) == 'X' % rock
        score = score + 1;
        if line(1) == 'A' % rock
            score = score + 3;
        elseif line(1) == 'C' % scissors
            score = score + 6;
        end
    elseif line(2) == 'Y' % paper
        score = score + 2;
        if line(1) == 'B' % paper
            score = score + 3;
        elseif line(1) == 'A' % rock
            score = score + 6;
        end
    elseif line(2) == 'Z' % scissors
        score = score + 3;
        if line(1) == 'C' % scissors
            score = score + 3;
        elseif line(1) == 'B' % paper
            score = score + 6;
        end
    end
end
fprintf("If you follow the strategy, you end with %d points.\n", score);


score = 0;
for i = 1:length(lines)
    line = string(strsplit(lines{i},' '));
    if line(2) == 'X' % lose
        if line(1) == 'A' % rock
            score = score + 3; % scissors
        elseif line(1) == 'B' % paper
            score = score + 1; % rock
        elseif line(1) == 'C' % scissors
            score = score + 2; % paper
        end
    elseif line(2) == 'Y' % draw
        score = score + 3;
        if line(1) == 'A' % rock
            score = score + 1; % rock
        elseif line(1) == 'B' % paper
            score = score + 2; % paper
        elseif line(1) == 'C' % scissors
            score = score + 3; % scissors
        end
    elseif line(2) == 'Z' % win
        score = score + 6;
        if line(1) == 'A' % rock
            score = score + 2; % paper
        elseif line(1) == 'B' % paper
            score = score + 3; % scissors
        elseif line(1) == 'C' % scissors
            score = score + 1; % rock
        end
    end
end
fprintf("\nPart 2:\nIf you follow the ultra top secret strategy, you end with %d points.\n", score);
