% Advent of Code 2015
% Day 3
clear
close
clc

fprintf("Advent of Code 2015\nDay 3\n\nPart 1:\n");

inputFile = fopen('input.txt');
input = fscanf(inputFile, "%c");

coordinates = zeros(length(input)+1, 2);
numHouses = 1;

i = 2;
while i <= length(input) + 1
    if input(i-1) == '^'
        coordinates(i,1) = coordinates(i-1, 1) + 1;
        coordinates(i,2) = coordinates(i-1, 2);
    elseif input(i-1) == 'v'
        coordinates(i,1) = coordinates(i-1, 1) - 1;
        coordinates(i,2) = coordinates(i-1, 2);
    elseif input(i-1) == '>'
        coordinates(i,1) = coordinates(i-1, 1);
        coordinates(i,2) = coordinates(i-1, 2) + 1;
    elseif input(i-1) == '<'
        coordinates(i,1) = coordinates(i-1, 1);
        coordinates(i,2) = coordinates(i-1, 2) - 1;
    end
    
    beenBefore = 0;
    j = i-1;
    while j > 0
        if coordinates(i,1) == coordinates(j,1) && coordinates(i,2) == coordinates(j,2)
            beenBefore = 1;
            break;
        end
        j = j - 1;
    end
    if beenBefore == 0
        numHouses = numHouses + 1;
    end
    
    i = i + 1;
end
% plot santa's path
plot(coordinates(:,1), coordinates(:,2))
fprintf("Santa delivered %d presents to %d unique houses.\n", length(input), numHouses);

santa = zeros(length(input)/2, 2);
roboSanta = zeros(length(input)/2, 2);
santaI = 2;
roboI = 2;
numHouses = 1;

i = 2;
while i <= length(input) + 1
    if mod(i-1,2) == 1 % on the first command, santa moves first, then every other time
        if input(i-1) == '^'
            santa(santaI,1) = santa(santaI-1, 1) + 1;
            santa(santaI,2) = santa(santaI-1, 2);
        elseif input(i-1) == 'v'
            santa(santaI,1) = santa(santaI-1, 1) - 1;
            santa(santaI,2) = santa(santaI-1, 2);
        elseif input(i-1) == '>'
            santa(santaI,1) = santa(santaI-1, 1);
            santa(santaI,2) = santa(santaI-1, 2) + 1;
        elseif input(i-1) == '<'
            santa(santaI,1) = santa(santaI-1, 1);
            santa(santaI,2) = santa(santaI-1, 2) - 1;
        end
        coordinates(i,1) = santa(santaI,1);
        coordinates(i,2) = santa(santaI,2);
        santaI = santaI + 1;
    else
        if input(i-1) == '^'
            roboSanta(roboI,1) = roboSanta(roboI-1, 1) + 1;
            roboSanta(roboI,2) = roboSanta(roboI-1, 2);
        elseif input(i-1) == 'v'
            roboSanta(roboI,1) = roboSanta(roboI-1, 1) - 1;
            roboSanta(roboI,2) = roboSanta(roboI-1, 2);
        elseif input(i-1) == '>'
            roboSanta(roboI,1) = roboSanta(roboI-1, 1);
            roboSanta(roboI,2) = roboSanta(roboI-1, 2) + 1;
        elseif input(i-1) == '<'
            roboSanta(roboI,1) = roboSanta(roboI-1, 1);
            roboSanta(roboI,2) = roboSanta(roboI-1, 2) - 1;
        end
        coordinates(i,1) = roboSanta(roboI,1);
        coordinates(i,2) = roboSanta(roboI,2);
        roboI = roboI + 1;
    end
    
    beenBefore = 0;
    j = i-1;
    while j > 0
        if coordinates(i,1) == coordinates(j,1) && coordinates(i,2) == coordinates(j,2)
            beenBefore = 1;
            break;
        end
        j = j - 1;
    end
    if beenBefore == 0
        numHouses = numHouses + 1;
    end
    
    i = i + 1;
end

figure
% plot santa's path
plot(santa(:,1), santa(:,2))
hold on
%plot robo-santa's path
plot(roboSanta(:,1), roboSanta(:,2))

fprintf("\nPart 2:\nSanta and Robo-Santa each delivered %d presents to %d unique houses.\n", length(input)/2, numHouses);


