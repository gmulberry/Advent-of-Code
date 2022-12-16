% Advent of Code 2015
% Day 6
clear
close
clc

fprintf("Advent of Code 2015\nDay 6\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');

lights = zeros(1000,1000);

for i = 1:length(lines)
    line = lines{i};
    splitUp = strsplit(line, ',');
    temp = strsplit(splitUp{1}, ' ');
    
    if length(temp) == 3 % turn on or off
        if strcmp(temp{2}, "on")
            command = 1; % turn on the range
        else
            command = 0; % tuen off the range
        end
    else
        command = 2; % toggle the range
    end
    
    startX = str2double(temp{end});
    temp = strsplit(splitUp{2}, ' ');
    startY = str2double(temp{1});
    stopX = str2double(temp{3});
    temp = strsplit(splitUp{2}, ' ');
    stopY = str2double(splitUp{3});
    
    for j = startX-1:stopX-1
        for k = startY-1:stopY-1
            if command == 0
                lights(j, k) = 0;
            elseif command == 1
                lights(j, k) = 1;
            else
                lights(j,k) = ~lights(j,k);
            end
        end
    end
    
end
numOn = sum(sum(lights));
fprintf("There are %d lights on\n", numOn);


lights = zeros(1000,1000);

for i =1:length(lines)
    line = lines{i};
    splitUp = strsplit(line, ',');
    temp = strsplit(splitUp{1}, ' ');
    
    if length(temp) == 3 % turn on or off
        if strcmp(temp{2}, "on")
            command = 1; % turn on the range
        else
            command = 0; % tuen off the range
        end
    else
        command = 2; % toggle the range
    end
    
    startX = str2double(temp{end});
    temp = strsplit(splitUp{2}, ' ');
    startY = str2double(temp{1});
    stopX = str2double(temp{3});
    temp = strsplit(splitUp{2}, ' ');
    stopY = str2double(splitUp{3});
    
    for j = startX-1:stopX-1
        for k = startY-1:stopY-1
            if command == 1
                lights(j, k) = lights(j, k) + 1;
            elseif command == 0
                lights(j, k) = lights(j, k) - 1;
                if lights(j, k) < 0
                    lights(j, k) = 0;
                end
            else
                lights(j,k) = lights(j,k) + 2;
            end
        end
    end
    
end
numOn = sum(sum(lights));
fprintf("\nPart 2:\nThe total brightness of the lights is %d\n", numOn);
