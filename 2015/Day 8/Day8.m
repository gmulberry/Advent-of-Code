% Advent of Code 2015
% Day 8
clear
close
clc

fprintf("Advent of Code 2015\nDay 8\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,char('\n'));
numLines = length(lines);
totMem = 0;
totStr = 0;

numSlash = 0;
numQuote = 0;
numHex = 0;
numStart_StopQuotes = 0;

for i = 1:numLines
    line = lines{i};
    numMemChars = length(line);
    lineLen = length(line);
    
    j = 1;
    escapedLine = char();
    while j <= lineLen
        if line(j) == char('\')
            if line(j + 1) == char('\')
                escapedLine = strcat(escapedLine,  char('?'));
                j = j + 1;
                numSlash = numSlash + 1;
            elseif line(j + 1) == char('"')
                escapedLine = strcat(escapedLine,  char('?'));
                j = j + 1;
                numQuote = numQuote + 1;
            elseif line(j + 1) == char('x')
                code = line(j: j + 3);
                escapedLine = strcat(escapedLine,  char('?'));
                j = j + 3;
                numHex = numHex + 1;
            end
        elseif line(j) == char('"')
            % dont escape the quote, but don't add to the string.
            numStart_StopQuotes = numStart_StopQuotes + 1;
        else
            escapedLine = [escapedLine,  line(j)];
        end
        j = j + 1;
    end
    numStrChars = length(escapedLine);
    
    totMem = totMem + numMemChars;
    totStr = totStr + numStrChars;
end


difference = totMem - totStr;
fprintf("The difference between the number of chars in memory vs. in the strings is %d\n", difference);
% answer: 1371


inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,char('\n'));
numLines = length(lines);
totMem = 0;
totStr = 0;

for i = 1:numLines
    line = lines{i};
    numMemChars = length(line);
    lineLen = length(line);
    
    j = 1;
    escapedLine = char('"');
    while j <= lineLen
        if line(j) == char('"')
            escapedLine = [escapedLine,  sprintf('\\\"')];
        elseif line(j) == char('\')
            escapedLine = [escapedLine,  sprintf('\\\\')];
        else
            escapedLine = [escapedLine,  line(j)];
        end
        j = j + 1;
    end
    escapedLine = [escapedLine,  char('"')];
    numStrChars = length(escapedLine);
    
    totMem = totMem + numMemChars;
    totStr = totStr + numStrChars;
end

difference =  totStr - totMem;
fprintf("\nPart 2:\nThe difference between the number of chars in the strings vs. in the code is %d\n", difference);
% answer: 2117


