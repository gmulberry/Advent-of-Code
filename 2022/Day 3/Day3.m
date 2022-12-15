% Advent of Code 2022
% Day 3
clear
close
clc

fprintf("Advent of Code 2022\nDay 3\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

totPriority = 0;

for i = 1:length(lines)
    line = lines{i};
    if line(end)+0 == 13
        line = line(1:end-1);
    end
    numItems = length(line);
    comp1 = line(1:(numItems/2));
    comp2 = line((numItems/2)+1:end);
    
    for j = 1:length(comp1)
        for k = 1:length(comp2)
            if (comp1(j) == comp2(k))
                itemInBoth = comp1(j);
            end
        end
    end
    
    priority = itemInBoth-64;
    if priority <= 26
        priority = priority + 26;
    elseif priority > 26
        priority = priority - 32;
    end
    
    totPriority = totPriority + priority;
    
end
fprintf("The total priority of the misplaced items is %d\n", totPriority);

totPriority = 0;
for i = 1:3:length(lines)
    elf1 = lines{i};
    if elf1(end)+0 == 13
        elf1 = elf1(1:end-1);
    end
    
    elf2 = lines{i+1};
    if elf2(end)+0 == 13
        elf2 = elf2(1:end-1);
    end
    
    elf3 = lines{i+2};
    if elf3(end)+0 == 13
        elf3 = elf3(1:end-1);
    end
    
    for j = 1:length(elf1)
        for k = 1:length(elf2)
            for l = 1:length(elf3)
                if (elf1(j) == elf2(k) && elf1(j) == elf3(l) && elf2(k) == elf3(l))
                    badge = elf1(j);
                end
            end
        end
    end
    
    priority = badge-64;
    if priority <= 26
        priority = priority + 26;
    elseif priority > 26
        priority = priority - 32;
    end
    
    totPriority = totPriority + priority;
end

fprintf("\nPart 2:\nThe total priority of the groups' badges is %d\n", totPriority);
