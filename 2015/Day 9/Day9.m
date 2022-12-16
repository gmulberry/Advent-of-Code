% Advent of Code 2015
% Day 9
clear
close
clc

fprintf("Advent of Code 2015\nDay 9\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,char('\n'));
numLines = length(lines);

distances = zeros(numLines);
locationNames = strings(numLines,1);
numLocs = 0;
for i = 1:numLines
    line = lines{i};
    lineLen = length(line);
    
    splitUp = strsplit(line, ' ');
    
    source = splitUp{1};
    dest = splitUp{3};
    dist = str2double(splitUp{5});
    
    sourceIdx = getLocationIdx(source, locationNames);
    if ~sourceIdx
        numLocs = numLocs + 1;
        locationNames(numLocs) = source;
        sourceIdx = numLocs;
    end
    
    destIdx = getLocationIdx(dest, locationNames);
    if ~destIdx
        numLocs = numLocs + 1;
        locationNames(numLocs) = dest;
        destIdx = numLocs;
    end
    
    distances(sourceIdx, destIdx) = dist;
end
distances = distances(1:numLocs,1:numLocs);
distances = distances + distances';

paths = perms(1:numLocs);
pathLengths = zeros(length(paths), 1);
for i = 1:length(paths)
    pathLen = 0;
    for j = 2:numLocs
        pathLen = pathLen + distances(paths(i,j-1),paths(i,j));
    end
    pathLengths(i) = pathLen;
end
shortestDistance = min(pathLengths);
fprintf("The shortest path between all places is %d\n", shortestDistance);

longestDistance = max(pathLengths);
fprintf("\nPart 2:\nThe longest path between all places is %d\n", longestDistance);


function idx = getLocationIdx(name, locationNames)
    idx = 0;
    
    for i = 1:length(locationNames)
        if strcmp(name, locationNames(i))
            idx = i;
            break;
        end
    end
end
