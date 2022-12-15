% Advent of Code 2022
% Day 5
clear
close
clc

fprintf("Advent of Code 2022\nDay 5\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

startLine = 0;
for i = 1:length(lines)
    line = lines{i};
    % check for a carriage return ( '\r' = char(13) )
    if strcmp(line, char(13))
        initialStack = lines(1:i-1);
        startLine = i + 1;
        break;
    end
end

%fprintf("The starting stack:\n")
for i = 1:length(initialStack)
    line = initialStack{i};
    %fprintf("%s", line);
end

numStacks = str2double(line(end-2));

% initialize the stacks array
maxHeight = 100;
stacks = char(ones(numStacks, maxHeight)*' ');
for stackNum = 1:numStacks
    j = 1;
    for i = length(initialStack)-1:-1:1
        line = initialStack{i};
        stacks(stackNum, j) = line((stackNum-1)*4 + 2);
        j = j + 1;
    end
end

% follow the instructions
for i = startLine:length(lines)
    line = lines{i};
    splitUp = strsplit(line, ' ');
    numToMove = str2double(splitUp{2});
    source = str2double(splitUp{4});
    dest = str2double(splitUp{6});
    
    while numToMove > 0
        % pick up a container and remove it from the source stack.
        for j = maxHeight:-1:1
            container = stacks(source, j);
            if ~strcmp(container, ' ')
                %fprintf("%s\n",container);
                stacks(source, j) = ' ';
                break;
            end
        end
        
        % put the container in the destination stack
        for j = 1:maxHeight
            onStack = stacks(dest, j);
            if strcmp(onStack, ' ')
                stacks(dest, j) = container;
                break;
            end
        end
        numToMove = numToMove - 1;
    end
end

topOfStack = char(ones(1,numStacks) * ' ');
for i = 1:numStacks
    for j = maxHeight:-1:1
        container = stacks(i, j);
        if ~strcmp(container, ' ')
            topOfStack(i) = container;
            break;
        end
    end
end

fprintf("The containers at the top of the stacks are: %s\n", topOfStack);

fprintf("\nPart 2:\n");

% initialize the stacks array
maxHeight = 100;
stacks = char(ones(numStacks, maxHeight)*' ');
for stackNum = 1:numStacks
    j = 1;
    for i = length(initialStack)-1:-1:1
        line = initialStack{i};
        stacks(stackNum, j) = line((stackNum-1)*4 + 2);
        j = j + 1;
    end
end

% follow the instructions
for i = startLine:length(lines)
    line = lines{i};
    splitUp = strsplit(line, ' ');
    numToMove = str2double(splitUp{2});
    source = str2double(splitUp{4});
    dest = str2double(splitUp{6});
    
    
    % pick up a container and remove it from the source stack.
    for j = maxHeight:-1:1
        container = stacks(source, j);
        if ~strcmp(container, ' ')
            %fprintf("%s\n",container);
            container = stacks(source, j-numToMove+1:j);
            for k = j-numToMove+1:j
                stacks(source, k) = ' ';
            end
            break;
        end
    end
    
    % put the container in the destination stack
    for j = 1:maxHeight
        onStack = stacks(dest, j);
        if strcmp(onStack, ' ')
            n = 1;
            for k = j:j+numToMove-1
                stacks(dest, k) = container(n);
                n = n + 1;
            end
            break;
        end
    end
end

topOfStack = char(ones(1,numStacks) * ' ');
for i = 1:numStacks
    for j = maxHeight:-1:1
        container = stacks(i, j);
        if ~strcmp(container, ' ')
            topOfStack(i) = container;
            break;
        end
    end
end
fprintf("The containers at the top of the stacks are: %s\n", topOfStack);





