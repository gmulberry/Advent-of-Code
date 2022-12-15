% Advent of Code 2022
% Day 9
clear
close
clc

fprintf("Advent of Code 2022\nDay 9\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);

numMoves = 0;
for i = 1:numLines
    line = lines{i};
    splitUp = strsplit(line, ' ');
    dir = splitUp{1};
    dist = str2double(splitUp{2});
    numMoves = numMoves + dist;
end

headPos = zeros(numMoves + 1, 2);
numMoves = 1;
for i = 1:numLines
    line = lines{i};
    splitUp = strsplit(line, ' ');
    dir = splitUp{1};
    dist = str2double(splitUp{2});
    
    if strcmp(dir, 'U')
        for j = 1:dist
            numMoves = numMoves + 1;
            headPos(numMoves, 1) = headPos(numMoves - 1, 1); % x
            headPos(numMoves, 2) = headPos(numMoves - 1, 2) + 1; % y
        end
    elseif strcmp(dir, 'D')
        for j = 1:dist
            numMoves = numMoves + 1;
            headPos(numMoves, 1) = headPos(numMoves - 1, 1); % x
            headPos(numMoves, 2) = headPos(numMoves - 1, 2) - 1; % y
        end
    elseif strcmp(dir, 'L')
        for j = 1:dist
            numMoves = numMoves + 1;
            headPos(numMoves, 1) = headPos(numMoves - 1, 1) - 1; % x
            headPos(numMoves, 2) = headPos(numMoves - 1, 2); % y
        end
    elseif strcmp(dir, 'R')
        for j = 1:dist
            numMoves = numMoves + 1;
            headPos(numMoves, 1) = headPos(numMoves - 1, 1) + 1; % x
            headPos(numMoves, 2) = headPos(numMoves - 1, 2); % y
        end
    end
    
end

plot(headPos(:,1), headPos(:,2));
tailPos = zeros(numMoves, 2);
for i = 2:numMoves
    headX = headPos(i, 1);
    headY = headPos(i, 2);
    
    distX = headX - tailPos(i - 1, 1);
    distY = headY - tailPos(i - 1, 2);
    
    if abs(distX) > 1 && abs(distY) > 1 || abs(distX) == 1 && abs(distY) > 1 || abs(distX) > 1 && abs(distY) == 1
        % then we need to move diagonally
        tailPos(i, 1) = tailPos(i - 1, 1) + sign(distX);
        tailPos(i, 2) = tailPos(i - 1, 2) + sign(distY);
    elseif abs(distX) > 1
        % only need to move in X direciton
        tailPos(i, 1) = tailPos(i - 1, 1) + sign(distX);
        tailPos(i, 2) = tailPos(i - 1, 2);
    elseif abs(distY) > 1
        % only need to move in Y direciton
        tailPos(i, 1) = tailPos(i - 1, 1);
        tailPos(i, 2) = tailPos(i - 1, 2) + sign(distY);
    else
        % otherwise we don't need to move at all
        tailPos(i, 1) = tailPos(i - 1, 1);
        tailPos(i, 2) = tailPos(i - 1, 2);
    end
end
hold on
plot(tailPos(:,1), tailPos(:,2));
%axis equal

numVisits = length(unique(tailPos, 'row'));
fprintf("The tail visits %d unique positions.\n", numVisits);


fprintf("\nPart 2:\n");

% For the second part we have to extend the length of the rope to 10. I am
% just going to put the same code into a loop, treating the head of each
% loop as the tail from the previous loop. For the first loop, I am
% assigning the input to the tailPos that I found in part 1. In part 1, the
% rope was two long, since I need it to be 10 long, I need to run the loop
% for part 2 8 times.

outputTail = tailPos;
for k = 1:8
    inputHead = outputTail;
    outputTail = zeros(numMoves, 2);
    for i = 2:numMoves
        distX = inputHead(i, 1) - outputTail(i - 1, 1);
        distY = inputHead(i, 2) - outputTail(i - 1, 2);
        
        if abs(distX) > 1 && abs(distY) > 1 || abs(distX) == 1 && abs(distY) > 1 || abs(distX) > 1 && abs(distY) == 1
            % then we need to move diagonally
            outputTail(i, 1) = outputTail(i - 1, 1) + sign(distX);
            outputTail(i, 2) = outputTail(i - 1, 2) + sign(distY);
        elseif abs(distX) > 1
            % only need to move in X direciton
            outputTail(i, 1) = outputTail(i - 1, 1) + sign(distX);
            outputTail(i, 2) = outputTail(i - 1, 2);
        elseif abs(distY) > 1
            % only need to move in Y direciton
            outputTail(i, 1) = outputTail(i - 1, 1);
            outputTail(i, 2) = outputTail(i - 1, 2) + sign(distY);
        else
            % otherwise we don't need to move at all
            outputTail(i, 1) = outputTail(i - 1, 1);
            outputTail(i, 2) = outputTail(i - 1, 2);
        end
    end
    plot(outputTail(:,1), outputTail(:,2));
end

numVisits = length(unique(outputTail, 'row'));
fprintf("The tail visits %d unique positions.\n", numVisits);

