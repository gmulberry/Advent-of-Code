% Advent of Code 2022
% Day 7
clear 
close 
clc

fprintf("Advent of Code 2022\nDay 7\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');
numLines = length(lines);

global outStr;
outStr = '';

numLS = 0;
numCD = 0;
global fileSystem;
fileSystem = struct;
fileSystem.type = 'dir'; 
fileSystem.numSubDirs = nan;
fileSystem.dirSize = nan;
path = strings(100,1);
path(1) = 'root';
pathIdx = 1;
i = 1;
while i <= length(lines)
    line = lines{i};
    if line(3:4) == 'cd'
        numCD = numCD + 1;
        if line(6) == '/'
            % return to root
            while pathIdx > 1
               path(pathIdx) = '';
               pathIdx = pathIdx - 1;
            end
            
        elseif line (6:7) == '..'
            % return to previous directory
            if pathIdx == 1
                % we can't go back anymore than the root...
            else
                path(pathIdx) = '';
                pathIdx = pathIdx - 1;
            end
        else
            % get the rest of the desired directory
            splitUp = strsplit(line, ' ');
            newDir = splitUp{end};
            newDir = strsplit(newDir, char(13));
            newDir = newDir{1};
            % go to the new directory
            pathIdx = pathIdx + 1;
            path(pathIdx) = newDir;
            
        end
    elseif line(3:4) == 'ls'
        numLS = numLS + 1;
        % the next lines will be lists of contents in the current directory
        % this will continue until the first line where the first character
        % is a $.
        fileSize = [];
        fileName = strings();
        numItems = 1;
        doneListing = 0;
        i = i + 1;
        while doneListing == 0
            contents = struct;
            contents.type = 'dir';
            contents.dirSize = nan;
            tempLine = lines{i};
            if tempLine(1) == '$'
                doneListing = 1;
                i = i - 1;
                break;
            else
                % parse the line item
                splitUp = strsplit(tempLine, ' ');
                if strcmp(splitUp{1}, "dir") 
                    fileSize(numItems) = 0;
                else 
                    fileSize(numItems) = str2double(splitUp{1});
                end
                tempName = strsplit(splitUp{2}, char(13));
                tempName = tempName{1};
                fileName(numItems) = tempName;
                numItems = numItems + 1;
            end
            
            if i == numLines
                doneListing = 1;
                i = i - 1;
                break;
            else
                i = i + 1;
            end
        end
        % create the contents payload
        numFilesInThisDir = 0;
        
        numSubDirs = 0;
        for j = 1:numItems-1
            if fileSize(j) == 0
                % for directories, create and empty struct with the
                % matching name of the directory
                contents.(fileName(j)) = struct;
                numSubDirs = numSubDirs + 1;
            else
                numFilesInThisDir = numFilesInThisDir + 1;
                fullName = strsplit(fileName(j),'.');
                if length(fullName) == 1
                    % not all files have extensions
                    nameOnly = fullName{1};
                    file = struct;
                    file.fileType = '';
                    file.fileSize = fileSize(j);
                    contents.(nameOnly) = file;
                    contents.(nameOnly).type = 'file';
                else
                    nameOnly = fullName{1};
                    fileType = fullName{2};
                    file = struct;
                    file.fileType = fileType;
                    file.fileSize = fileSize(j);
                    nameStr = [nameOnly, fileType];
                    contents.(nameStr) = file;
                    contents.(nameStr).type = 'file';
                end
                
            end
        end
        
        if numSubDirs > 0
            contents.dirSize = nan;
        end
        contents.numSubDirs = numSubDirs;
        
        % find the current directory position
        pathStr = 'root';
        if pathIdx > 1
            for j = 2:pathIdx
                lookingFor = path(j);
                pathStr = strcat(pathStr,'.');
                pathStr = strcat(pathStr,lookingFor);
            end
        end
       
        spl = regexp(pathStr,'\.','split');
        fileSystem = setfield(fileSystem, spl{:}, contents);
        if pathIdx == 1
           fileSystem.root.type = 'dir'; 
           fileSystem.root.numSubDirs = nan; 
        end
    end
    i = i + 1;
end
printStruct(fileSystem, 0);

fprintf("The output reversed is:\n")
lines = strsplit(outStr, '\n');
numLines = length(lines);
numTabs = 1;

totSum = 0;
sizeLim = 100000;
runningSize = zeros(10,1);
for i = numLines-1:-1:1
    line = lines{i};
    lineLen = length(line);
    oldTabs = numTabs;
    
    size = strsplit(line, '=');
    size = strsplit(size{end}, ')');
    size = str2double(size{1});
    
    if isnan(size)
        numTabs = 1;
        while line(numTabs) == char(9)
            numTabs = numTabs + 1;
        end
        numTabs = numTabs - 1;
        refNumTabs = numTabs;
        j = i+1;
        runSum = 0;
        numTabs = refNumTabs + 1; % to enter the loop the first time
        while numTabs > refNumTabs && j < numLines
            tempLine = lines{j};
            lineLen = length(tempLine);
            
            numTabs = 1;
            while tempLine(numTabs) == char(9)
                numTabs = numTabs + 1;
            end
            numTabs = numTabs - 1;
            
            if numTabs == refNumTabs + 1
                size = strsplit(tempLine, '=');
                size = strsplit(size{end}, ')');
                size = str2double(size{1});
                runSum = runSum + size;
            end
            
            j = j + 1;
        end
        line2 = strsplit(line, '=');
        line2 = line2{1};
        line2 = sprintf("%s=%d)", line2, runSum);
        fprintf("%s\n", line2);
        lines{i} = char(line2);
    else
        fprintf("%s\n", line);
    end
    
    % if the line is a dir
    line = lines{i};
    type = strsplit(line, '(');
    type = type{2};
    type = strsplit(type,' ');
    type = type{1};
    if strcmp(type, 'dir')
        % check the size
        size = strsplit(line, '=');
        size = strsplit(size{end}, ')');
        size = str2double(size{1});
        if size <= sizeLim
           totSum = totSum + size; 
        end
    end
    
end

fprintf("\n The size of all directories less than %d is %d.\n", sizeLim, totSum);


fprintf("\nPart 2:\n")

size = strsplit(lines{1}, '=');
size = strsplit(size{end}, ')');
rootSize = str2double(size{1});

totSize = 70000000;
neededSize = 30000000;
unusedSize = totSize-rootSize;
targetDirSize = neededSize - unusedSize;
dirToDelete = '';
dirToDeleteSize = 0;
sizeList = zeros(numLines,1);

for i = 1:numLines-1
    line = lines{i};
    lineLen = length(line);
    oldTabs = numTabs;
    
    % if the line is a dir
    line = lines{i};
    type = strsplit(line, '(');
    type = type{2};
    type = strsplit(type,' ');
    type = type{1};
    
    % check the size
    size = strsplit(line, '=');
    size = strsplit(size{end}, ')');
    size = str2double(size{1});
    sizeList(i) = size;
    if strcmp(type, 'dir')
        if size >= targetDirSize
           if dirToDeleteSize == 0
                dirToDeleteSize = size;
                dirToDelete = strsplit(line, ' ');
                dirToDelete = dirToDelete{2};
           elseif size < dirToDeleteSize
                dirToDeleteSize = size;
                dirToDelete = strsplit(line, ' ');
                dirToDelete = dirToDelete{2};
                fprintf("%s\n",line);
           end
        end
    end
end

sizeList = sort(sizeList);

fprintf("\nThe dir to delete that will free up %d bytes is %s with size %d.\n", targetDirSize, dirToDelete, dirToDeleteSize);

function returnVal = fixDirSize(input)
    fieldNames = fields(input);
    numFields = length(fieldNames);
    dirSum = 0;
    for i = 1:numFields
        condition = ~(strcmp(fieldNames{i}, 'type') || strcmp(fieldNames{i}, 'dirSize') || strcmp(fieldNames{i}, 'numSubDirs'));
        if condition
            try
                dirSize = input.(fieldNames{i}).dirSize;
            catch
                dirSize = input.(fieldNames{i}).fileSize;
            end
            dirSum = dirSum + dirSize;
        end
    end
    returnVal = dirSum;
end

function numTabs = printStruct(input, numTabs)
    global outStr;
    fieldNames = fields(input);
    numFields = length(fieldNames);

    if strcmp(input.type, 'file')
        if ~isempty(input.fileType)
            fprintf(".%s", input.fileType);
            outStr =  strcat(outStr, sprintf(".%s", input.fileType));
        end
        if ~isempty(input.fileSize)
            fprintf(" (file, size=");
            outStr =  strcat(outStr, sprintf(" (file, size="));
            fprintf("%d)\n", input.fileSize);
            outStr =  strcat(outStr, sprintf("%d)\n", input.fileSize));
        end
    else
        for i = 1:numFields
            fieldContents = input.(fieldNames{i});
            if isstruct(fieldContents)
                for j = 1 : numTabs
                    fprintf("\t");
                    outStr =  strcat(outStr, sprintf("\t"));
                end
                fprintf("- %s", fieldNames{i});
                outStr =  strcat(outStr, sprintf("- %s", fieldNames{i}));
                printStruct(fieldContents, numTabs);
            else
                if strcmp(fieldNames{i}, 'type')
                    fprintf(" (dir size=%d)\n", input.dirSize);
                    outStr =  strcat(outStr, sprintf(" (dir size=%d)\n", input.dirSize));
                    if isnan(input.dirSize)
                        newSize = fixDirSize(input);
                        input.dirSize = newSize;
                    end
                    numTabs = numTabs + 1;
                end
            end
        end
    end
end

function numTabs = printStructonly(input, numTabs)
    fieldNames = fields(input);
    numFields = length(fieldNames);
    
    if strcmp(input.type, 'file')
        if ~isempty(input.fileType)
            fprintf(".%s", input.fileType);
        end
        
        if ~isempty(input.fileSize)
            fprintf(" (file, size=");
            fprintf("%d)\n", input.fileSize);
        end
    else
        for i = 1:numFields
            fieldContents = input.(fieldNames{i});
            if isstruct(fieldContents)
                for j = 1 : numTabs
                    fprintf("\t");
                end
                fprintf("- %s", fieldNames{i});
                
                printStruct(fieldContents, numTabs);
                
            else
                fprintf(" (dir)\n");
                numTabs = numTabs + 1;
            end
        end
    end
end

