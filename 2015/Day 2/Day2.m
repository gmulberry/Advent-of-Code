% Advent of Code 2015
% Day 2
clear 
close 
clc

fprintf("Advent of Code 2015\nDay 2\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');

i = 1;
totPaper = 0;
while i <= length(lines)
    line = lines{i};
    dims = sscanf(line,'%dx%dx%d');
    side1 = dims(1) * dims(2);
    side2 = dims(2) * dims(3);
    side3 = dims(1) * dims(3);
    surfaceArea = 2 * side1 + 2 * side2 + 2 * side3;
    extra = min([side1, side2, side3]);
    paperNeeded = surfaceArea + extra;
    totPaper = totPaper + paperNeeded;

    i = i + 1;
end
fprintf("The elves need %d square feet of wrapping paper.\n", totPaper);

i = 1;
totRibbon = 0;
while i <= length(lines)
    line = lines{i};
    dims = sscanf(line,'%dx%dx%d');
    side1 = 2*dims(1) + 2*dims(2);
    side2 = 2*dims(2) + 2*dims(3);
    side3 = 2*dims(1) + 2*dims(3);
    bow = dims(1) * dims(2) * dims(3);
    wrap = min([side1, side2, side3]);
    ribbonNeeded = wrap + bow;
    totRibbon = totRibbon + ribbonNeeded;

    i = i + 1;
end
fprintf("\nPart 2:\nThe elves need %d feet of ribbon.\n", totRibbon);
