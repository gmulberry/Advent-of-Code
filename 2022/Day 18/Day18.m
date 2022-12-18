% Advent of Code 2022
% Day 18
clear
close
clc 

fprintf("Advent of Code 2022\nDay 18\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

numCubes = length(lines);
% columns are x, y, z, freeEdges
cubes = zeros(numCubes, 4);

for i = 1:numCubes
    line = lines{i};
    splitUp = strsplit(line, ',');
    cubes(i,1:3) = str2double(splitUp);
end
for i = 1:numCubes
    freeEdges = 6;
    connectionsFound = 0;
    j = 1;
    while connectionsFound < 6 && j <= numCubes
        dist = findDist(cubes(i,1:3), cubes(j,1:3));
        if dist == 1
            freeEdges = freeEdges - 1;
        end
        j = j + 1;
    end
    cubes(i,4) = freeEdges;
end
surfaceArea = sum(cubes(:,4));
fprintf("The surface area is %d\n", surfaceArea);


% For part 2, we have to remove the interior surface area. My approach will
% be to determine all of the completely enclosed points, assemble them into
% a new array, and then determine the surface area of that array using the
% same method as from part 1. Subtracting this surface area from the answer
% from part 1 should result in the exterior surface area.

minX = min(cubes(:, 1));
maxX = max(cubes(:, 1));
minY = min(cubes(:, 2));
maxY = max(cubes(:, 2));
minZ = min(cubes(:, 3));
maxZ = max(cubes(:, 3));

numAirByMult = ((maxX-minX+1) * (maxY-minY+1) * (maxZ-minZ+1)) - numCubes;
air = zeros(numAirByMult, 4);
numAir = 0;
for z = minZ:maxZ
    for y = minY:maxY
        for x = minX:maxX
            isAir = ~isACube(cubes, x, y, z);
            if isAir
                % if the point is air, store its coordinates
                numAir = numAir + 1;
                air(numAir,1:3) = [x,y,z];
                
                if x == minX || y == minY || z == minZ || x == maxX || y == maxY || z == maxX
                    % if it is along the outside, set the last element to 1
                    air(numAir,4) = 1;
                end

            end
        end
    end
end

% Flood fill the space from the outside
numOutside = sum(air(:,4));
oldNumOutside = 0;
while oldNumOutside ~= numOutside
    oldNumOutside = numOutside;
    for i = 1:numAir
        if air(i,4) == 0
            for j = 1:numAir
                if i ~= j && air(j,4) == 1
                    dist = findDist(air(i,1:3), air(j,1:3));
                    if dist == 1
                        air(i,4) = 1;
                    end
                end
            end
        end
    end
    numOutside = sum(air(:,4));
end

% Now we have found all of the air that is on the outside.
% We can use this to make an array of just air that is on the inside
% instead.
airPockets = [];
numAirPockets = 0;
for i = 1:numAir
    if air(i,4) == 0
        numAirPockets = numAirPockets + 1;
        airPockets(numAirPockets,:) = air(i,1:3);
    end
end

% Now determine the surface area of all of the air pockets
for i = 1:numAirPockets
    freeEdges = 6;
    connectionsFound = 0;
    j = 1;
    while connectionsFound < 6 && j <= numAirPockets
        dist = findDist(airPockets(i,1:3), airPockets(j,1:3));
        if dist == 1
            freeEdges = freeEdges - 1;
        end
        j = j + 1;
    end
    airPockets(i,4) = freeEdges;
end
extSurfaceArea = surfaceArea - sum(airPockets(:,4));
fprintf("\nPart 2:\nThe exterior surface area is %d\n", extSurfaceArea);

scatter3(cubes(:,1),cubes(:,2),cubes(:,3),'filled')
hold on
scatter3(airPockets(:,1),airPockets(:,2),airPockets(:,3),'filled')

function dist = findDist(a, b)
    len = length(a);
    cumSquares = 0;
    for i = 1:len
        cumSquares = cumSquares + (a(i)-b(i))^2;
    end
    dist = sqrt(cumSquares);
end
function isCube = isACube(cubes, x, y, z)
    isCube = 0;
    for i = 1:length(cubes)
        cube = cubes(i,:);
        if cube(1) == x && cube(2) == y && cube(3) == z
            isCube = 1;
            return;
        end
    end
end
