% Advent of Code 2022
% Day 23
clear
close
clc

fprintf("Advent of Code 2022\nDay 23\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');
numLines = length(lines);

numRounds = 10;

% pad the map with the number of rounds + 1 since the farthest an elf can
% ever travel in 10 rounds is 10 away from where he is now.
map = zeros(numLines + 2*(numRounds+1), length(lines{1}) + 2*(numRounds+1));

for i = 1:numLines
    line = lines{i};
    for j = 1:length(line)
        if line(j) == '.'
            map(i+numRounds, j+numRounds) = 0;
        elseif line(j) == '#'
            map(i+numRounds, j+numRounds) = 1;
        end
    end
end
startMap = map;
% fprintf("== Initial State ==\n")
% printMap(map)

order = 1;

for round = 1:numRounds
    proposals = zeros(length(map(:, 1)),length(map(1, :)));
    for x = 2:length(map(1, :))-1
        for y = 2:length(map(:, 1))-1
            if map(y, x) == 1 
                propose = proposeDirection(map, x, y, order);
                proposals(y + propose(1), x + propose(2)) = proposals(y + propose(1), x + propose(2)) + 1;
            end
        end
    end
    
    newMap = zeros(numLines + 2*(numRounds+1), length(lines{1}) + 2*(numRounds+1));
    
    for x = 2:length(map(1, :))-1
        for y = 2:length(map(:, 1))-1
            if map(y, x) == 1
                propose = proposeDirection(map, x, y, order);
                if proposals(y + propose(1), x + propose(2)) == 1
                    % only mark the new map if only one elf is proposing to
                    % move there
                    newMap(y + propose(1), x + propose(2)) = 1;
                else
                    % otherwise, the elf stays in its current location
                    newMap(y, x) = 1;
                end
            end
        end
    end
    
    map = newMap;
  
%     fprintf("\n== End of Round %d ==\n", round)
%     printMap(map)
    
    if order < 4
        order = order + 1;
    else
        order = 1;
    end
end

[minX, maxX, minY, maxY] = getExtents(map);
trimmed = map(minY:maxY, minX:maxX);

%printMap(trimmed)

numEmpty = sum(sum(trimmed == 0));
fprintf("The number of empty ground tiles is %d\n", numEmpty);


% For part 2, we don't know how many rounds it will take. Since I have a
% method for extracting the trimmed map, I am just going to use the trimmed
% map with 0's around the border from now on. This will perform the same
% function as padding the map by the number of rounds + 1 that I did in
% part 1.

% now trim the map and add a 0 around all the edges
[minX, maxX, minY, maxY] = getExtents(map);
trimmed = map(minY:maxY, minX:maxX);
map = zeros(length(trimmed(:,1))+2, length(trimmed(1,:)) + 2);
map(2:end-1,2:end-1) = trimmed;

numSame = 0;
while numSame ~= numel(map)
    round = round + 1;
    proposals = zeros(length(map(:, 1)),length(map(1, :)));
    for x = 2:length(map(1, :))-1
        for y = 2:length(map(:, 1))-1
            if map(y, x) == 1 
                propose = proposeDirection(map, x, y, order);
                proposals(y + propose(1), x + propose(2)) = proposals(y + propose(1), x + propose(2)) + 1;
            end
        end
    end
    
    newMap = zeros(length(map(:,1)), length(map(1,:)));
    
    for x = 2:length(map(1, :))-1
        for y = 2:length(map(:, 1))-1
            if map(y, x) == 1
                propose = proposeDirection(map, x, y, order);
                if proposals(y + propose(1), x + propose(2)) == 1
                    % only mark the new map if only one elf is proposing to
                    % move there
                    newMap(y + propose(1), x + propose(2)) = 1;
                else
                    % otherwise, the elf stays in its current location
                    newMap(y, x) = 1;
                end
            end
        end
    end
    
    same = map == newMap;
    numSame = sum(sum(same));
    
    map = newMap;
    
    % now trim the map and add a 0 around all the edges
    [minX, maxX, minY, maxY] = getExtents(map);
    trimmed = map(minY:maxY, minX:maxX);
    map = zeros(length(trimmed(:,1))+2, length(trimmed(1,:)) + 2);
    map(2:end-1,2:end-1) = trimmed;
  
%    fprintf("\n== End of Round %d ==\n", round)
%    printMap(map)
    
    if order < 4
        order = order + 1;
    else
        order = 1;
    end
end

fprintf("\nPart 2:\nThe last round where no elves moved was round %d\n", round);
%printMap(map)

function [minX, maxX, minY, maxY] = getExtents(map)
    minX = 0;
    for x = 1:length(map(1, :))
        for y = 1:length(map(:, 1))
            if map(y, x) == 1
                minX = x;
                break;
            end
        end
        if minX ~= 0
            break;
        end
    end

    maxX = 0;
    for x = length(map(1, :)):-1:1
        for y = 1:length(map(:, 1))
            if map(y, x) == 1
                maxX = x;
                break;
            end
        end
        if maxX ~= 0
            break;
        end
    end

    minY = 0;
    for y = 1:length(map(:, 1))
        for x = 1:length(map(1, :))
            if map(y, x) == 1
                minY = y;
                break;
            end
        end
        if minY ~= 0
            break;
        end
    end

    maxY = 0;
    for y = length(map(:, 1)):-1:1
        for x = 1:length(map(1, :))
            if map(y, x) == 1
                maxY = y;
                break;
            end
        end
        if maxY ~= 0
            break;
        end
    end
end

function propose = proposeDirection(map, x, y, order)
    propose = [0, 0];
    if sum(sum(map(y-1:y+1, x-1:x+1))) > 1
        if order == 1
            if ~map(y-1, x-1) && ~map(y-1, x) && ~map(y-1, x+1)
                % move North
                propose = [-1, 0];
            elseif ~map(y+1, x-1) && ~map(y+1, x) && ~map(y+1, x+1)
                % move South
                propose = [1, 0];
            elseif ~map(y-1, x-1) && ~map(y, x-1) && ~map(y+1, x-1)
                % move West
                propose = [0, -1];
            elseif ~map(y-1, x+1) && ~map(y, x+1) && ~map(y+1, x+1)
                % move East
                propose = [0, 1];
            end
        elseif order == 2
            if ~map(y+1, x-1) && ~map(y+1, x) && ~map(y+1, x+1)
                % move South
                propose = [1, 0];
            elseif ~map(y-1, x-1) && ~map(y, x-1) && ~map(y+1, x-1)
                % move West
                propose = [0, -1];
            elseif ~map(y-1, x+1) && ~map(y, x+1) && ~map(y+1, x+1)
                % move East
                propose = [0, 1];
            elseif ~map(y-1, x-1) && ~map(y-1, x) && ~map(y-1, x+1)
                % move North
                propose = [-1, 0];
            end
        elseif order == 3
            if ~map(y-1, x-1) && ~map(y, x-1) && ~map(y+1, x-1)
                % move West
                propose = [0, -1];
            elseif ~map(y-1, x+1) && ~map(y, x+1) && ~map(y+1, x+1)
                % move East
                propose = [0, 1];
            elseif ~map(y-1, x-1) && ~map(y-1, x) && ~map(y-1, x+1)
                % move North
                propose = [-1, 0];
            elseif ~map(y+1, x-1) && ~map(y+1, x) && ~map(y+1, x+1)
                % move South
                propose = [1, 0];
            end
        elseif order == 4
            if ~map(y-1, x+1) && ~map(y, x+1) && ~map(y+1, x+1)
                % move East
                propose = [0, 1];
            elseif ~map(y-1, x-1) && ~map(y-1, x) && ~map(y-1, x+1)
                % move North
                propose = [-1, 0];
            elseif ~map(y+1, x-1) && ~map(y+1, x) && ~map(y+1, x+1)
                % move South
                propose = [1, 0];
            elseif ~map(y-1, x-1) && ~map(y, x-1) && ~map(y+1, x-1)
                % move West
                propose = [0, -1];
            end
        end
    end
end

function printMap(map)
    for i = 1:length(map(:,1))
        for j = 1:length(map(1,:))
            if map(i,j) == 0
                fprintf(".")
            elseif map(i,j) == 1
                fprintf("#");
            elseif map(i,j) == 2
                fprintf("S");
            elseif map(i,j) == 3
                fprintf(">");
            elseif map(i,j) == 4
                fprintf("V");
            elseif map(i,j) == 5
                fprintf("<");
            elseif map(i,j) == 6
                fprintf("^");
            elseif map(i,j) == 7
                fprintf("E");
            elseif map(i,j) == 10
                fprintf("C");
            else
                fprintf(" ");
            end
        end
        fprintf("\n");
    end
end
