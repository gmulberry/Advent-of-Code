% Advent of Code 2022
% Day 14
clear
close
clc

fprintf("Advent of Code 2022\nDay 14\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);
map = [];
map(0+1,500) = 3; % the sand entry point
for i =1:numLines
    line = lines{i};
    
    splitUp = strsplit(line,' ');
    
    numNodes = 0;
    nodes = zeros(ceil(length(splitUp)/2), 2);
    for j = 1:2:length(splitUp)
        coords = strsplit(splitUp{j}, ',');
        numNodes = numNodes + 1;
        nodes(numNodes, 1) = str2double(coords{1});
        nodes(numNodes, 2) = str2double(coords{2});
    end
    
    for j = 2:numNodes
        start = nodes(j-1, :);
        stop = nodes(j, :);
        
        if start(1) ~= stop(1)
            y = start(2);
            for x = min(start(1), stop(1)):max(start(1), stop(1))
                map(y+1, x) = 1;
            end
        else
            x = start(1);
            for y = min(start(2), stop(2)):max(start(2), stop(2))
                map(y+1, x) = 1;
            end
        end
    end

end
fprintf("\n");

partOneMap = map;

% if any sand reaches this point, then it will fall into the abyss.
yMax = length(map(:,1))-1;

numSand = 0;
brokeOut = 0;
while brokeOut == 0
    
    oldMap = map;
    % create a new grain of sand at the starting position
    sand = [500,0];
    
    % move the sand until it settles
    settled = 0;
    while settled == 0
        map = oldMap;
        map(sand(2) + 1, sand(1)) = 2;
        
        showMapImg(map,numSand);
        
        % try to settle the sand
        if sand(2) + 1 + 1 < yMax+2
            if map(sand(2) + 1 + 1, sand(1)) == 0
                % if there is nothing below the sand, then it can fall
                sand(1) = sand(1);
                sand(2) = sand(2) + 1;
            elseif map(sand(2) + 1 + 1, sand(1)-1) == 0 
                % if there is something below the sand, then it cannot fall
                % straight down, so we also check if theres nothing down and
                % left.
                sand(1) = sand(1) - 1;
                sand(2) = sand(2) + 1;
            elseif map(sand(2) + 1 + 1, sand(1)+1) == 0 
                % if down, and down left are blocked, we check right
                sand(1) = sand(1) + 1;
                sand(2) = sand(2) + 1;
            else
                % if none of those happened, then we can settle
                settled = 1;
                numSand = numSand + 1;
            end
        else
            % if we tried to go lower, but exceed yMax, then we must have
            % broken out
            settled = 1;
            brokeOut = 1;
        end
    end
end
fprintf("%d grains of sand were able to settle before falling into the abyss.\n", numSand);

function showMapImg(map, numSand)
    xMax = length(map(1,:));
    yMax = length(map(:,1))-1;
    
    xMin = xMax;
    for y = 0:yMax
        for x = xMax:-1:1
            if map(y+1,x) ~= 0 && x < xMin
                xMin = x;
            end
        end
    end
    numLeftPad = numel(num2str(yMax));
    numTopPad = numel(num2str(xMax));
    
    % example of the desired output.
    
    %   4     5  5
    %   9     0  0
    %   4     0  3
    % 0 ......+...
    % 1 ..........
    % 2 ..........
    % 3 ..........
    % 4 ....#...##
    % 5 ....#...#.
    % 6 ..###...#.
    % 7 ........#.
    % 8 ........#.
    % 9 #########.
    

    frame = zeros(yMax,xMax-xMin,3);
    for y = 0:yMax
        frameY = y+1;
        for x = xMin:xMax
            frameX = x - xMin +1;
            if map(y+1,x) == 0
                %fprintf(".");
            elseif map(y+1,x) == 1
                frame(frameY,frameX,:) = [0.5,0.5,0.5];
            elseif map(y+1,x) == 2
                frame(frameY,frameX,:) = [0.8,0.8,0];
            elseif map(y+1,x) == 3
                frame(frameY,frameX,:) = [0,1,0];
            end
        end    

    end
    imshow(frame, 'InitialMagnification', 1100);
    numSand = num2str(numSand);
    title(numSand, 'FontSize', 12)
    drawnow();
    
end
