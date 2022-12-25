% Advent of Code 2022
% Day 24
clear
close
clc

fprintf("Advent of Code 2022\nDay 24\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');
height = length(lines);
width = length(lines{1});

map = zeros(height, width);
stepsToCheck = 1000;
steps = inf(stepsToCheck, height, width);
currentStep = 0;
startPoint = [0,0];
endPoint = [0,0];

for i = 1:height
    line = lines{i};
    for j = 1:width
        if i == 1 && line(j) == '.'
            map(i,j) = 2;
            currentStep = currentStep + 1;
            steps(currentStep, i, j) = 0;
            startPoint = [i, j];
        elseif i == height && line(j) == '.'
            map(i,j) = 7;
            endPoint = [i, j];
        elseif line(j) == '#'
            map(i, j) = 1;
        elseif line(j) == '>'
            map(i, j) = 3;
        elseif line(j) == 'v'
            map(i, j) = 4;
        elseif line(j) == '<'
            map(i, j) = 5;
        elseif line(j) == '^'
            map(i, j) = 6;
        end
    end
end
startMap = map;
% fprintf("== Initial State ==\n")
% printMap(map);

emptyMap = startMap;
emptyMap(2:height - 1, 2:width - 1) = zeros(height - 2, width - 2);

% extract the blizzards
numBlizzards = 0;
for i = 1:height
    for j = 1:width
        if map(i, j) >= 3 && map(i, j) <= 6
            numBlizzards = numBlizzards + 1;
            blizzards(numBlizzards, 1) = i;
            blizzards(numBlizzards, 2) = j;
            blizzards(numBlizzards, 3) = map(i,j);
        end
    end
end

minute = -1;
while map(endPoint(1),endPoint(2)) == 7
    minute = minute + 1;
    
    % reconstruct the map based on the blizzards
    % printMap(map);
    % fprintf("\n== Empty Map ==\n")
    % printMap(map);
    map = emptyMap;
    
    if minute ~=0
        % move the blizzards
        for i = 1:numBlizzards
            if blizzards(i, 3) == 3 % >
                if blizzards(i, 2) + 1 <= width - 1
                    blizzards(i, 2) = blizzards(i, 2) + 1;
                else
                    blizzards(i, 2) = 2;
                end
            elseif blizzards(i, 3) == 4 % V
                if blizzards(i, 1) + 1 <= height - 1
                    blizzards(i, 1) = blizzards(i, 1) + 1;
                else
                    blizzards(i, 1) = 2;
                end
            elseif blizzards(i, 3) == 5 % <
                if blizzards(i, 2) - 1 >= 2
                    blizzards(i, 2) = blizzards(i, 2) - 1;
                else
                    blizzards(i, 2) = width - 1;
                end
            elseif blizzards(i, 3) == 6 % ^
                if blizzards(i, 1) - 1 >= 2
                    blizzards(i, 1) = blizzards(i, 1) - 1;
                else
                    blizzards(i, 1) = height - 1;
                end
            end
            
            % place the blizzards on the map
            if map(blizzards(i, 1), blizzards(i, 2)) ~= 0
                map(blizzards(i, 1), blizzards(i, 2)) = 8; % *
            else
                map(blizzards(i, 1), blizzards(i, 2)) = blizzards(i, 3);
            end
        end
    end
    % fprintf("\n== Minute %d ==\n", minute)
    % printMap(map);
    
    % now that we have the new blizzard positions, we can check the adjacent
    % points to see if they are open.
    
    currentStep = currentStep + 1;
    for i = 1:height
        for j = 1:width
            if map(i, j) == 0
                if ~isinf(steps(currentStep-1, i, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i, j-1))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i, j+1))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i-1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i+1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                
            elseif map(i, j) == 2
                steps(currentStep, i, j) = currentStep-1;
                
            elseif map(i, j) == 7
                if ~isinf(steps(currentStep-1, i-1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
            end
            
            if ~isinf(steps(currentStep, i, j))
                map(i,j) = 9;
            end
        end
    end
    
%     step = reshape(steps(currentStep,:,:), height,width);
%     printStep(step)
    
%     fprintf("\n== Minute %d ==\n", minute);
%     printMap(map);
end
fprintf("You reach the endpoint on move %d\n", minute)
% answer is 322

% For part 2, we need to know the total time to go from the start to the
% end, back to the start, and then back to the end. The blizzards need to
% remain in the same place but now we are just continuing back to the
% begining.
fprintf("\nPart 2\n");

trip1 = minute;

stepsToCheck = 1000;
steps = inf(stepsToCheck, height, width);
currentStep = 1;

% swap the start and the end
temp = endPoint;
endPoint = startPoint;
startPoint = temp;

reverseMap = map;
reverseMap(2:height - 1, 2:width - 1) = zeros(height - 2, width - 2);
reverseMap(startPoint(1), startPoint(2)) = 2;
reverseMap(endPoint(1), endPoint(2)) = 7;
steps(currentStep, i, j) = 0;
map = reverseMap;
%printMap(reverseMap);

minute = -1;
while map(endPoint(1),endPoint(2)) == 7
    minute = minute + 1;
    map = reverseMap; % now the reverse map
    if minute ~=0
        % move the blizzards
        for i = 1:numBlizzards
            if blizzards(i, 3) == 3 % >
                if blizzards(i, 2) + 1 <= width - 1
                    blizzards(i, 2) = blizzards(i, 2) + 1;
                else
                    blizzards(i, 2) = 2;
                end
            elseif blizzards(i, 3) == 4 % V
                if blizzards(i, 1) + 1 <= height - 1
                    blizzards(i, 1) = blizzards(i, 1) + 1;
                else
                    blizzards(i, 1) = 2;
                end
            elseif blizzards(i, 3) == 5 % <
                if blizzards(i, 2) - 1 >= 2
                    blizzards(i, 2) = blizzards(i, 2) - 1;
                else
                    blizzards(i, 2) = width - 1;
                end
            elseif blizzards(i, 3) == 6 % ^
                if blizzards(i, 1) - 1 >= 2
                    blizzards(i, 1) = blizzards(i, 1) - 1;
                else
                    blizzards(i, 1) = height - 1;
                end
            end
            
            % place the blizzards on the map
            if map(blizzards(i, 1), blizzards(i, 2)) ~= 0
                map(blizzards(i, 1), blizzards(i, 2)) = 8; % *
            else
                map(blizzards(i, 1), blizzards(i, 2)) = blizzards(i, 3);
            end
        end
    end
    
    currentStep = currentStep + 1;
    for i = 1:height
        for j = 1:width
            if map(i, j) == 0
                if ~isinf(steps(currentStep-1, i, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i, j-1))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i, j+1))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i-1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i+1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                
            elseif map(i, j) == 2
                steps(currentStep, i, j) = currentStep-1;
                
            elseif map(i, j) == 7
                if ~isinf(steps(currentStep-1, i+1, j)) % now i+1
                    steps(currentStep, i, j) = currentStep-1;
                end
            end
            
            if ~isinf(steps(currentStep, i, j))
                map(i,j) = 9;
            end
        end
    end
end
trip2 = minute;

stepsToCheck = 1000;
steps = inf(stepsToCheck, height, width);
currentStep = 1;

% swap the start and the end back
temp = endPoint;
endPoint = startPoint;
startPoint = temp;

steps(currentStep, i, j) = 0;
map = emptyMap;
%printMap(emptyMap);

minute = -1;
while map(endPoint(1),endPoint(2)) == 7
    minute = minute + 1;
    
    map = emptyMap; % back to the empty map
    
    if minute ~=0
        % move the blizzards
        for i = 1:numBlizzards
            if blizzards(i, 3) == 3 % >
                if blizzards(i, 2) + 1 <= width - 1
                    blizzards(i, 2) = blizzards(i, 2) + 1;
                else
                    blizzards(i, 2) = 2;
                end
            elseif blizzards(i, 3) == 4 % V
                if blizzards(i, 1) + 1 <= height - 1
                    blizzards(i, 1) = blizzards(i, 1) + 1;
                else
                    blizzards(i, 1) = 2;
                end
            elseif blizzards(i, 3) == 5 % <
                if blizzards(i, 2) - 1 >= 2
                    blizzards(i, 2) = blizzards(i, 2) - 1;
                else
                    blizzards(i, 2) = width - 1;
                end
            elseif blizzards(i, 3) == 6 % ^
                if blizzards(i, 1) - 1 >= 2
                    blizzards(i, 1) = blizzards(i, 1) - 1;
                else
                    blizzards(i, 1) = height - 1;
                end
            end
            
            % place the blizzards on the map
            if map(blizzards(i, 1), blizzards(i, 2)) ~= 0
                map(blizzards(i, 1), blizzards(i, 2)) = 8; % *
            else
                map(blizzards(i, 1), blizzards(i, 2)) = blizzards(i, 3);
            end
        end
    end
    
    currentStep = currentStep + 1;
    for i = 1:height
        for j = 1:width
            if map(i, j) == 0
                if ~isinf(steps(currentStep-1, i, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i, j-1))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i, j+1))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i-1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                if ~isinf(steps(currentStep-1, i+1, j))
                    steps(currentStep, i, j) = currentStep-1;
                end
                
            elseif map(i, j) == 2
                steps(currentStep, i, j) = currentStep-1;
                
            elseif map(i, j) == 7
                if ~isinf(steps(currentStep-1, i-1, j)) % back to - 1
                    steps(currentStep, i, j) = currentStep-1;
                end
            end
            
            if ~isinf(steps(currentStep, i, j))
                map(i,j) = 9;
            end
        end
    end
end
trip3 = minute;

roundTrip = trip1 + trip2 + trip3;

fprintf("The full round trip time is %d\n", roundTrip);
% answer is 974


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
                fprintf("v");
            elseif map(i,j) == 5
                fprintf("<");
            elseif map(i,j) == 6
                fprintf("^");
            elseif map(i,j) == 7
                fprintf("E");
            elseif map(i,j) == 8
                fprintf("*");
            elseif map(i,j) == 9
                fprintf("X");
            else
                fprintf(" ");
            end
        end
        fprintf("\n");
    end
end

function printStep(map)
    for i = 1:length(map(:,1))
        for j = 1:length(map(1,:))
            if isinf(map(i,j))
                fprintf(".")
            else
                fprintf("X");
            end
        end
        fprintf("\n");
    end
end
