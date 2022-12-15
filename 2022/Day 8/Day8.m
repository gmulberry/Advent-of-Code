% Advent of Code 2022
% Day 8
clear
close
clc

fprintf("Advent of Code 2022\nDay 8\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);

trees = zeros(numLines);

for i = 1:numLines
    line = lines{i};
    lineLen = length(line);
    for j = 1:numLines
        trees(i,j) = str2double(line(j));
    end
end

numVisible = 0;
for y = 1:numLines % y direction
    for x = 1:numLines % x direction
        targetTree = trees(y,x);
        if x == 1 || x == numLines || y == 1 || y == numLines
            % always visible on the edges
            isVisible = 1;
        else
            % check from the left
            visLeft = 1;
            for xx = x-1:-1:1
                if trees(y,xx) >= targetTree
                    visLeft = 0;
                end
            end
            
            % check from the right
            visRight = 1;
            for xx = x+1:numLines
                if trees(y,xx) >= targetTree
                    visRight = 0;
                end
            end
            
            % check from the top
            visTop = 1;
            for yy = y-1:-1:1
                if trees(yy,x) >= targetTree
                    visTop = 0;
                end
            end
            
            % check from below
            visBot = 1;
            for yy = y+1:numLines
                if trees(yy,x) >= targetTree
                    visBot = 0;
                end
            end
            
            isVisible = max([visLeft, visRight, visTop, visBot]);
            
        end
        numVisible = numVisible + isVisible;
    end
end

fprintf("The number of visible trees is %d\n", numVisible);


fprintf("\nPart 2:\n",numVisible);
scenicScores = zeros(numLines);
for y = 1:numLines % y direction
    for x = 1:numLines % x direction
        targetTree = trees(y,x);
        
        if x == 1 || x == numLines || y == 1 || y == numLines
            % always visible on the edges
            scenicScore = 0;
        else
            % check from the left
            visLeft = 1;
            for xx = x-1:-1:1
                if trees(y,xx) >= targetTree  || xx == 1
                    break;
                else
                    visLeft = visLeft + 1;
                end
            end
            
            % check from the right
            visRight = 1;
            for xx = x+1:numLines
                if trees(y,xx) >= targetTree || xx == numLines
                    break;
                else
                    visRight = visRight + 1;
                end
            end
            
            % check from the top
            visTop = 1;
            for yy = y-1:-1:1
                if trees(yy,x) >= targetTree  || yy == 1
                    break;
                else
                    visTop = visTop + 1;
                end
            end
            
            % check from below
            visBot = 1;
            for yy = y+1:numLines
                if trees(yy,x) >= targetTree  || yy == numLines
                    break;
                else
                    visBot = visBot + 1;
                end
            end
        end
        
        scenicScore = visLeft * visRight * visTop * visBot;
        scenicScores(y,x) = scenicScore;
    end
end
higestScore = max(max(scenicScores));
fprintf("The highest scenic score is %d\n", higestScore);




