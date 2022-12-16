% Advent of Code 2015
% Day 4
clear 
close 
clc
% I'm using DataHash version 1.7.1 (12 KB) by Jan from Mathworks file
% exchange to implement the MD5 hash.

% note that the part 1 solution is 282749

fprintf("Advent of Code 2015\nDay 4\n\nPart 1:\n");

key = "yzbqklnj";
%count = 0;
count = 282748; % use this so I don't have to wait for part one to finish
goodHash = 0;
while goodHash == 0
    count = count + 1;
    data = strcat(key, num2str(count));
    hash = DataHash(data, 'ascii');
    
    goodHash = 1;
    for i = 1:5
        if hash(i) ~= '0'
            goodHash = 0;
            break;
        end
    end
end

fprintf("Santa's number to get an AdventCoin with a secret key of %s is %d\n", key, count);
fprintf("The MD5 Hash of %s is %s\n", data, hash);

% the first hash that has 6 zeros would have already been detected if we
% it had occured for a count already, so I can just keep the count the same
% and keep going from there.

% for reference, the solution for part 2 is 9962624, uncomment below to
% start right before it
count = 9962623;

goodHash = 0;
while goodHash == 0
    count = count + 1;
    data = strcat(key, num2str(count));
    hash = DataHash(data, 'ascii');
    
    goodHash = 1;
    for i = 1:6
        if hash(i) ~= '0'
            goodHash = 0;
            break;
        end
    end
end

fprintf("\nPart 2:\nSanta's number to get an AdventCoin with a secret key of %s is %d\n", key, count);
fprintf("The MD5 Hash with 6 0's of %s is %s\n", data, hash);

