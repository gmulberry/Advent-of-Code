% Advent of Code 2022
% Day 15
clear
close
clc

fprintf("Advent of Code 2022\nDay 15\n\nPart 1:\n");

% inputFile = fopen('input1.txt');
% rowNum = 10;
% searchSpace = 20;

inputFile = fopen('input.txt');
rowNum = 2000000;
searchSpace = 4000000;

input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);

% parse the input into lists of sensors and beacons
numSensors = 0;
sensors = zeros(numLines, 2);
beacons = zeros(numLines, 2);
manhattan = zeros(numLines, 1);
for i = 1:numLines
    line = lines{i};
    splitUp = strsplit(line,'=');
    numSensors = numSensors + 1;
    for j = 2:length(splitUp)-1
        if j == 2
            coords = strsplit(splitUp{j},',');
            sensors(numSensors,1) = str2double(coords{1});
        elseif j == 3
            coords = strsplit(splitUp{j},':');
            sensors(numSensors,2) = str2double(coords{1});
        elseif j == 4
            coords = strsplit(splitUp{j},',');
            beacons(numSensors,1) = str2double(coords{1});
            beacons(numSensors,2) = str2double(splitUp{5});
        end
    end
    manhattan(numSensors) = abs(beacons(numSensors, 1) - sensors(numSensors, 1)) + abs(beacons(numSensors, 2) - sensors(numSensors, 2));
end

minXknown = min([sensors(:,1); beacons(:,1)]);
maxXknown = max([sensors(:,1); beacons(:,1)]);
rangeXknown = maxXknown - minXknown + 1;
offXknown = 1 - minXknown;

minYknown = min([sensors(:,2); beacons(:,2)]);
maxYknown = max([sensors(:,2); beacons(:,2)]);
rangeYknown = maxYknown - minYknown + 1;
offYknown = 1 - minYknown; 

% rangeX may not be large enough. we have to consider the manhattan 
% distance of all of the sensors. 
maxMan = max(manhattan);
minX = minXknown - maxMan;
offX = 1 - minX;
maxX = maxXknown + maxMan;
rangeX = maxX - minX + 1;

% create an array that will act as the row we are interested in.
testRow = zeros(1,rangeX);

% for each position in our test row, check if it is in the manhattan range
% of any of the sensors.
numChecks = 0;
for x = minX:maxX
    for i = 1:numSensors
        man = manhattan(i);
        senseX = sensors(i, 1);
        senseY = sensors(i, 2);
        beacX = beacons(i, 1);
        beacY = beacons(i, 2);
        testMan = abs(senseX - x) + abs(senseY - rowNum);
        numChecks = numChecks + 1;
        if senseX == x && senseY == rowNum
            % cant be a beacon here, because there's a sensor
            testRow(x + offX) = 0;
            
        elseif beacX == x && beacY == rowNum
            % there is a beacon here
            testRow(x + offX) = 0;
            
        elseif testMan <= man
            % there can't be a beacon here
            testRow(x + offX) = 1;
        end
    end
end

fprintf("In the row where y=%d, there are %d positions where a beacon cannot be present.\n", rowNum, sum(testRow));
fprintf("It took %d comparisons.\n", numChecks);


fprintf("\nPart 2:\n");

figure 
hold on
for i = 1:numSensors
    man = manhattan(i);
    senseX = sensors(i, 1);
    senseY = sensors(i, 2);
    beacX = beacons(i, 1);
    beacY = beacons(i, 2);
    
    senseRange = [
        [senseX, senseY + man];
        [senseX + man, senseY];
        [senseX, senseY - man];
        [senseX - man, senseY];
        [senseX, senseY + man]];
    plot(senseRange(:,1), senseRange(:,2));
    
    %scatter(beacX, beacY, 'filled', 'r')
    scatter(senseX, senseY, 'filled', 'b')
end
searchRange = [
        [0, 0];
        [0, searchSpace];
        [searchSpace, searchSpace];
        [searchSpace, 0];
        [0, 0]];
plot(searchRange(:,1), searchRange(:,2),'k');

% search along the edges of the sensors' range.
overlaps = 1;
i = 1;
numCheck = 0;
while i <= numSensors && overlaps == 1
    
    man = manhattan(i);
    senseX = sensors(i, 1);
    senseY = sensors(i, 2);
    
    
    dir = 0;
    x = senseX - 1;
    y = senseY + man + 2;
    while dir < 4
        if dir == 0
            x = x + 1;
            y = y - 1;
            if y == senseY
                dir = dir + 1;
            end
        elseif dir == 1
            x = x - 1;
            y = y - 1;
            if x == senseX
                dir = dir + 1;
            end
        elseif dir == 2
            x = x - 1;
            y = y + 1;
            if y == senseY
                dir = dir + 1;
            end
        elseif dir == 3
            x = x + 1;
            y = y + 1;
            if x == senseX
                dir = dir + 1;
                break;
            end
        end
        
        if x >= 0 && x <= searchSpace && y >= 0 && y <= searchSpace
            % if we are inside of the valid search area then check this
            % location to see it it falls inside of another sensor's range
            numCheck = numCheck + 1;
            overlaps = 0;
            for j = 1:numSensors
                if i == j
                    % there is no point to check the same sensor we are checking.
                    continue;
                else
                    
                    testMan = manhattan(j);
                    testSenseX = sensors(j, 1);
                    testSenseY = sensors(j, 2);
                    
                    distToOtherSensor = abs(testSenseX - x) + abs(testSenseY - y);
                    
                    if distToOtherSensor <= testMan
                        overlaps = 1;
                        break;
                    end
                end
                
            end
            
            if overlaps == 0
                tuningFreq = uint64(x)*uint64(4000000) + uint64(y);
                fprintf("The beacon must be at x=%d , y=%d, it has tuning frequency: %d\n", x, y, tuningFreq);
                scatter(x, y, 'filled', 'r')
                break;
            end
        end
        
        if overlaps == 0
            break;
        end
        
    end
    
    i = i + 1;
end