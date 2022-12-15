% Advent of Code 2022
% Day 12
clear
close
clc

fprintf("Advent of Code 2022\nDay 12\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);

map = zeros(numLines, length(lines{1})-1);
startPos = [0, 0, 0];
endPos = [0, 0, 26];

for y = 1:numLines
    line = lines{y};
    line = line(1:end-1);
    for x = 1:length(line)
        height = line(x);
        if height == 'S'
            map(y, x) = 0;
            startPos(1:2) = [x, y];
        elseif height == 'E'
            map(y, x) = 26;
            endPos(1:2) = [x, y];
        else
            map(y, x) = height - 97;
        end
    end
end

surf(map)
hold on

scatter3(startPos(1), startPos(2), startPos(3), 'filled')
scatter3(endPos(1), endPos(2), endPos(3), 'filled')
xlabel('x')
ylabel('y')
zlabel('z')

maxX = length(map(1,:));
maxY = length(map(:,1));
dists = ones(maxY, maxX) * inf;
oldDists = dists;
dists(endPos(2), endPos(1)) = 0;

numSteps = 0;

while ~isequal(oldDists, dists)
    oldDists = dists;
    for x = 1:maxX
        for y = 1:maxY
            z = map(y, x);
            
            if isinf(dists(y,x))
                % check the 4 directions around my current position to see if any of
                % them have a connection to the end
                north = inf;
                south = inf;
                east = inf;
                west = inf;
                
                if y ~= maxY
                    % check north
                    testX = x;
                    testY = y + 1;
                    if map(testY, testX) <= z+1
                        % going to the north is possible
                        if ~isinf(dists(testY, testX))
                            north = dists(testY, testX)+1;
                        end
                    end
                end
                if y ~= 1
                    % check south
                    testX = x;
                    testY = y - 1;
                    if map(testY, testX) <= z+1
                        % going to the south is possible
                        if ~isinf(dists(testY, testX))
                            south = dists(testY, testX)+1;
                        end
                    end
                end
                if x ~= maxX
                    % check east
                    testX = x + 1;
                    testY = y;
                    if map(testY, testX) <= z+1
                        % going to the east is possible
                        if ~isinf(dists(testY, testX))
                            east = dists(testY, testX)+1;
                        end
                    end
                end
                if x ~= 1
                    % check west
                    testX = x - 1;
                    testY = y;
                    if map(testY, testX) <= z+1
                        % going to the west is possible
                        if ~isinf(dists(testY, testX))
                            west = dists(testY, testX)+1;
                        end
                    end
                end
                dists(y,x) = min([north, south, east, west]);
            end
        end
    end
    numSteps = numSteps + 1;
end
shortestPath = dists(startPos(2), startPos(1));
fprintf("The shortest path to the summit is %d.\n", shortestPath);

% find a possible path
path = zeros(numSteps, 3);

x = startPos(1);
y = startPos(2);
path(1,:) = [x, y, map(y,x)];
for step = 2:shortestPath+1
    dist = dists(y,x);
    
    if y ~= maxY
        % check north
        testX = x;
        testY = y + 1;
        if dists(testY, testX) == dist - 1
            % going to the north is possible
            x = testX;
            y = testY;
        end
    end
    if y ~= 1
        % check south
        testX = x;
        testY = y - 1;
        if dists(testY, testX) == dist - 1
            % going to the south is possible
            x = testX;
            y = testY;
        end
    end
    if x ~= maxX
        % check east
        testX = x + 1;
        testY = y;
        if dists(testY, testX) == dist - 1
            % going to the east is possible
            x = testX;
            y = testY;
        end
    end
    if x ~= 1
        % check west
        testX = x - 1;
        testY = y;
        if dists(testY, testX) == dist - 1
            % going to the west is possible
            x = testX;
            y = testY;
        end
    end
    path(step, :) = [x, y, map(y,x)];
end

xCoords = path(:, 1);
yCoords = path(:, 2);
zCoords = path(:, 3);
plot3(xCoords, yCoords, zCoords, 'LineWidth', 1, 'color','r');

% part 2
minAnyA = inf;
for x = 1:maxX
    for y = 1:maxY
        if map(y,x) == 0
            dist = dists(y, x);
            minAnyA = min(minAnyA, dist);
        end
    end
end
fprintf("\nPart 2:\nThe shortest path to the summit from any lowest starting point is %d.\n", minAnyA);

