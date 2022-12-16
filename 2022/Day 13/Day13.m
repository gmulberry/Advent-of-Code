% Advent of Code 2022
% Day 13
clear
close
clc

fprintf("Advent of Code 2022\nDay 13\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);

packet1 = struct;
packet2 = struct;
packetNum = 0;
pairNum = 1;
numPairs = 1;
goodPairs = [];
i = 1;
while i < numLines
    packet1 = lines{i};
    packet1 = packet1(1:end-1);
    packet2 = lines{i+1};
    packet2 = packet2(1:end-1);
    
    fprintf("== Pair %d ==\n", pairNum);
    [numTabs, done] = compare(packet1, packet2, 0, 0);
    
    if done == 1
        goodPairs = [goodPairs, pairNum];
    end
    
    fprintf("\n");
    pairNum = pairNum + 1;
    numPairs = numPairs + 1;
    i = i + 3;
end

fprintf("There are %d good pairs and the sum of their indices is %d\n", length(goodPairs), sum(goodPairs));


fprintf("\nPart 2:\n")
% now we actually have to sort the packets, as well as insert the "divider"
% packets into the mix. I am just going to do the loop however many times
% it takes to sort it because I'm lazy.
dividerPackets = [sprintf("[[2]]\n"); sprintf("[[6]]\n")];
outLines = dividerPackets;
numOutLines = 2;
for i = 1:numLines
    if ~strcmp(lines{i}, char(13))
        numOutLines = numOutLines + 1;
        outLines(numOutLines) = lines{i};
    end
end

numLines = length(outLines);
numUnsorted = numLines;
while numUnsorted > 0
    numUnsorted = 0;
    
    for i = 1:numLines-1
        packet1 = outLines(i);
        packet1 = char(packet1);
        packet1 = packet1(1:end-1);
        packet2 = outLines(i+1);
        packet2 = char(packet2);
        packet2 = packet2(1:end-1);
        [numTabs, done] = compareNoPrint(packet1, packet2, 0, 0);
        
        if done == 1
            % if they're in the right order do nothing
        else
            % if they aren't in the right order, sort them.
            
            temp = outLines(i);
            outLines(i) = outLines(i+1);
            outLines(i+1) = temp;
            numUnsorted = numUnsorted + 1;
        end
    end
    fprintf("%d\n", numUnsorted);
end

dividerIndex = [0,0];
for i = 1:numLines
    if strcmp(outLines(i), dividerPackets(1))
        dividerIndex(1) = i;
    elseif strcmp(outLines(i), dividerPackets(2))
        dividerIndex(2) = i;
    end
end
decoderKey = dividerIndex(1)*dividerIndex(2);
fprintf("The decoder key is: %d\n", decoderKey);


function [numTabs, result] = compare(left, right, numTabs, result)
    left = char(left);  
    right = char(right);
    
    for i = 1:numTabs
        fprintf("\t");
    end
    if result
        return; 
    else
        fprintf("- Compare %s vs %s\n", left, right);
        leftElements = getElements(left);
        rightElements = getElements(right);
        numLeft = length(leftElements);
        numRight = length(rightElements);
        
        % check if they are both lists
        leftIsList = 0;
        rightIsList = 0;
        if left(1) == '['
            leftIsList = 1;
        end
        if right(1) == '['
            rightIsList = 1;
        end
        if leftIsList && rightIsList
            % if they are both lists
            
            % check to see if the list is empty
            if strcmp(leftElements(1), "")
                numLeft = 0;
                i = 0;
            end
            if strcmp(rightElements(1), "")
                numRight = 0;
                i = 0;
            end
            
            % then we start comparing element by element.
            numTabs = numTabs + 1;
            if numLeft ~= 0 && numRight ~= 0
                for i = 1:min([numLeft,numRight])
                    [numTabs, result] = compare(leftElements(i), rightElements(i), numTabs, result);   
                end
            end
            if result 
                % if the comparison has a result there is no need to check
                % if one of the lists ran out of items
            elseif i ~= max([numLeft,numRight])
                for i = 1:numTabs
                    fprintf("\t");
                end
                if numLeft < numRight
                    result = 1;
                    fprintf("- Left side ran out of items, so inputs are in the right order\n");
                elseif numLeft > numRight
                    result = 2;
                    fprintf("- Right side ran out of items, so inputs are not in the right order\n");
                end
            end
            numTabs = numTabs - 1;
        elseif ~leftIsList && ~rightIsList
            % if they are both ints
            leftAsNum = str2double(left);
            rightAsNum = str2double(right);
            
            if leftAsNum < rightAsNum
                result = 1; % right order
                for i = 1:numTabs+1
                    fprintf("\t");
                end
                fprintf("- Left side is smaller, so inputs are in the right order\n");
            elseif leftAsNum > rightAsNum
                result = 2; % wrong order
                for i = 1:numTabs+1
                    fprintf("\t");
                end
                fprintf("- Right side is smaller, so inputs are not in the right order\n");
            else 
                result = 0; % the same, keep checking
            end
        else
            for i = 1:numTabs+1
                fprintf("\t");
            end
            
            fprintf("- Mixed types; convert ");
            if ~leftIsList
                fprintf("left to [%s]", left);
                left = ['[', left, ']'];
            end
            if ~rightIsList
                fprintf("right to [%s]", right);
                right = ['[', right, ']'];
            end
            fprintf(" and retry comparison\n");
            
            numTabs = numTabs + 1;
            [numTabs, result] = compare(left, right, numTabs, result);
            numTabs = numTabs - 1;
        end
    end
end

function [numTabs, result] = compareNoPrint(left, right, numTabs, result)
    left = char(left);  
    right = char(right);
    
    if result
        return; 
    else
        leftElements = getElements(left);
        rightElements = getElements(right);
        numLeft = length(leftElements);
        numRight = length(rightElements);
        
        % check if they are both lists
        leftIsList = 0;
        rightIsList = 0;
        if left(1) == '['
            leftIsList = 1;
        end
        if right(1) == '['
            rightIsList = 1;
        end
        if leftIsList && rightIsList
            % if they are both lists
            
            % check to see if the list is empty
            if strcmp(leftElements(1), "")
                numLeft = 0;
                i = 0;
            end
            if strcmp(rightElements(1), "")
                numRight = 0;
                i = 0;
            end
            
            % then we start comparing element by element.
            numTabs = numTabs + 1;
            if numLeft ~= 0 && numRight ~= 0
                for i = 1:min([numLeft,numRight])
                    [numTabs, result] = compareNoPrint(leftElements(i), rightElements(i), numTabs, result);   
                end
            end
            if result 
                % if the comparison has a result there is no need to check
                % if one of the lists ran out of items
            elseif i ~= max([numLeft,numRight])
                
                if numLeft < numRight
                    result = 1;
                elseif numLeft > numRight
                    result = 2;
                end
            end
            numTabs = numTabs - 1;
        elseif ~leftIsList && ~rightIsList
            % if they are both ints
            leftAsNum = str2double(left);
            rightAsNum = str2double(right);
            
            if leftAsNum < rightAsNum
                result = 1; % right order
            elseif leftAsNum > rightAsNum
                result = 2; % wrong order
            else 
                result = 0; % the same, keep checking
            end
        else
            if ~leftIsList
                left = ['[', left, ']'];
            end
            if ~rightIsList
                right = ['[', right, ']'];
            end
            
            numTabs = numTabs + 1;
            [numTabs, result] = compareNoPrint(left, right, numTabs, result);
            numTabs = numTabs - 1;
        end
    end
end

function elements = getElements(in)
    tempStr = '';
    elements = strings;
    numElements = 0;
    nestLev = 0;
    for i = 2:length(in)
        if (in(i) == ',' && nestLev == 0)|| i == length(in)
            numElements = numElements + 1;
            elements(numElements) = tempStr;
            tempStr = '';
        else
            if in(i) == '['
                nestLev = nestLev + 1;
            elseif in(i) == ']'
                nestLev = nestLev - 1;
            end
            tempStr = [tempStr, in(i)];
        end
    end
end

