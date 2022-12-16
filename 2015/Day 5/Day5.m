% Advent of Code 2015
% Day 5
clear
close
clc

fprintf("Advent of Code 2015\nDay 5\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");
lines = strsplit(input,'\n');

numNice = 0;
i = 1;
while i <= length(lines)
    line = lines{i};
    nice = 1;
    
    % look for vowels
    numVowels = 0;
    vowels = ['a', 'e', 'i', 'o', 'u'];
    for j = 1:length(vowels)
        lookFor = vowels(j);
        for k = 1:length(line)
            if line(k) == lookFor
                numVowels = numVowels + 1;
            end
        end
    end
    if numVowels < 3
        nice = 0;
    end
    
    hasDouble = 0;
    for j = 1:length(line)-1
        lookFor = strcat(line(j), line(j));
        for k = 1:length(line)-1
            if strcmp(lookFor, line(k:k+1))
                hasDouble = 1;
                break;
            end
        end
    end
    if hasDouble == 0
        nice = 0;
    end
    
    hasNaughtyCombo = 0;
    naughtyCombos = ["ab", "cd", "pq", "xy"];
    for j = 1:length(naughtyCombos)
        lookFor = naughtyCombos(j);
        for k = 1:length(line)-1
            if strcmp(lookFor, line(k:k+1))
                hasNaughtyCombo = 1;
                break;
            end
        end
    end
    if hasNaughtyCombo == 1
        nice = 0;
    end
    
    if nice == 1
        numNice = numNice + 1;
    end
    i = i + 1;
end
fprintf("Out of %d strings, %d are nice.\n", length(lines), numNice);


numNice = 0;
i = 1;
while i <= length(lines)
    line = lines{i};
    nice = 1;
    
    hasRepeatPair = 0;
    for j = 1:length(line)-3
        lookFor = strcat(line(j), line(j+1));
        for n = j+2:length(line)-1
            if strcmp(lookFor, line(n:n+1))
                hasRepeatPair = 1;
                break;
            end
        end
    end
    if hasRepeatPair == 0
        nice = 0;
    end
    
    hasDoubleWithGap = 0;
    for j = 1:length(line)-2
        if line(j) == line(j+2)
            hasDoubleWithGap = 1;
            break;
        end
    end
    if hasDoubleWithGap == 0
        nice = 0;
    end
    
    if nice == 1
        numNice = numNice + 1;
    end
    i = i + 1;
end
fprintf("\nPart 2:\nOut of %d strings, %d are nice.\n", length(lines), numNice);
