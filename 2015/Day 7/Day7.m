% Advent of Code 2015
% Day 7
clear
close
clc

fprintf("Advent of Code 2015\nDay 7\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');

global numWires;
global numUsedWires;
global wires;
global names;
numWires = length(lines);
numUsedWires = 0;
wires = uint16(zeros(numWires,1));
names = strings(numWires,1);
badlines = zeros(length(lines), 1);
numBad = 1;
numLoops = 0;
while numBad ~= 0
    for i = 1:length(lines)
        try
            line = lines{i};
            splitUp = strsplit(line, " -> ");
            temp = strsplit(splitUp{1}, ' ');
            
            dest = splitUp{2};
            
            if ~isnan(str2double(splitUp{1}))
                constant = uint16(str2double(splitUp{1}));
                % load a constant
                writeResult(constant, dest);
            else
                if length(temp) == 1
                    writeResult(getInput(temp), dest);
                end
                if length(temp) == 2
                    if strcmp(temp{1}, "NOT")
                        argA = getInput(temp{2});
                        argB = bin2dec('1111111111111111');
                        result = bitxor(argA, argB);
                        writeResult(result, dest);
                    end
                end
                if length(temp) == 3
                    if ~isnan(str2double(temp{1}))
                        argA = uint16(str2double(temp{1}));
                        if ~isreal(argA)
                            argA = uint16(getInput(temp{1}));
                        end
                    else
                        argA = uint16(getInput(temp{1}));
                    end
                    if ~isnan(str2double(temp{3}))
                        argB = uint16(str2double(temp{3}));
                        if ~isreal(argB)
                            argB = uint16(getInput(temp{3}));
                        end
                    else
                        argB = uint16(getInput(temp{3}));
                    end
                    
                    if strcmp(temp{2}, "AND")
                        result = bitand(argA, argB);
                        writeResult(result, dest);
                    elseif strcmp(temp{2}, "OR")
                        result = bitor(argA, argB);
                        writeResult(result, dest);
                    elseif strcmp(temp{2}, "LSHIFT")
                        result = bitshift(argA, argB);
                        writeResult(result, dest);
                    elseif strcmp(temp{2}, "RSHIFT")
                        result = bitshift(argA, -int16(argB));
                        writeResult(result, dest);
                    end
                    %fprintf("%s\nA: %s\nB: %s\nR: %s\n", temp{2}, dec2bin(argA), dec2bin(argB), dec2bin(result));
                end
            end
            
            badlines(i) = 0;
            
        catch err
            badlines(i) = 1;
        end
    end
    numLoops = numLoops + 1;
    numBad = sum(badlines);
    fprintf("loop %d numBad %d\n", numLoops, numBad);
end

fprintf("The value in wire a is %d\n", getInput("a"));


% now we need to override wire b to this result.
part1Result = getInput("a");

% if you comment out everything above this line to just run part 2, then
% uncomment the line below since part 2 relies on the answer from part 1.
% part1Result = 3176;

fprintf("\nPart 2:\n");

numWires = length(lines);
numUsedWires = 0;
wires = uint16(zeros(numWires,1));
names = strings(numWires,1);
badlines = zeros(length(lines), 1);
numBad = 1;
numLoops = 0;
while numBad ~= 0
    for i = 1:length(lines)
        try
            line = lines{i};
            splitUp = strsplit(line, " -> ");
            temp = strsplit(splitUp{1}, ' ');
            
            dest = splitUp{2};

            if strcmp(dest, "b")
                writeResult(part1Result, dest);
            else
            
            if ~isnan(str2double(splitUp{1}))
                constant = uint16(str2double(splitUp{1}));
                % load a constant
                writeResult(constant, dest);
            else
                if length(temp) == 1
                    writeResult(getInput(temp), dest);
                end
                if length(temp) == 2
                    if strcmp(temp{1}, "NOT")
                        argA = getInput(temp{2});
                        argB = bin2dec('1111111111111111');
                        result = bitxor(argA, argB);
                        writeResult(result, dest);
                    end
                end
                if length(temp) == 3
                    if ~isnan(str2double(temp{1}))
                        argA = uint16(str2double(temp{1}));
                        if ~isreal(argA)
                            argA = uint16(getInput(temp{1}));
                        end
                    else
                        argA = uint16(getInput(temp{1}));
                    end
                    if ~isnan(str2double(temp{3}))
                        argB = uint16(str2double(temp{3}));
                        if ~isreal(argB)
                            argB = uint16(getInput(temp{3}));
                        end
                    else
                        argB = uint16(getInput(temp{3}));
                    end
                    
                    if strcmp(temp{2}, "AND")
                        result = bitand(argA, argB);
                        writeResult(result, dest);
                    elseif strcmp(temp{2}, "OR")
                        result = bitor(argA, argB);
                        writeResult(result, dest);
                    elseif strcmp(temp{2}, "LSHIFT")
                        result = bitshift(argA, argB);
                        writeResult(result, dest);
                    elseif strcmp(temp{2}, "RSHIFT")
                        result = bitshift(argA, -int16(argB));
                        writeResult(result, dest);
                    end
                    %fprintf("%s\nA: %s\nB: %s\nR: %s\n", temp{2}, dec2bin(argA), dec2bin(argB), dec2bin(result));
                end
            end
            
            end
            badlines(i) = 0;
            
        catch err
            badlines(i) = 1;
        end
    end
    numLoops = numLoops + 1;
    numBad = sum(badlines);
    fprintf("loop %d numBad %d\n", numLoops, numBad);
end

fprintf("The value in wire a is %d\n", getInput("a"));


function in = getInput(name)
    global numUsedWires;
    global wires;
    global names;
    for j = 1:numUsedWires
        if strcmp(names(j), name)
            in = uint16(wires(j));
        end
    end
    if (numUsedWires == 0)
        in = nan;
    end
end

function result = writeResult(result, dest)
    global numWires;
    global numUsedWires;
    global wires;
    global names;
    found = 0;
    for j = 1:numWires
        if strcmp(names(j), dest)
            wires(j) = result;
            found = 1;
        end
    end
    if found == 0
        numUsedWires = numUsedWires + 1;
        wires(numUsedWires) = result;
        names(numUsedWires) = dest;
    end
end