% Advent of Code 2015
% Day 10

clear
close
clc

fprintf("Advent of Code 2015\nDay 10\n\nPart 1:\n");

input = '3113322113';
outStr = '';
for numLoops = 1:40
    if numLoops == 1
        in = input;
    else
        in = outStr;
        outStr = '';
    end
    numTimes = 1;
    for i = 2:length(in)
        if in(i) == in(i-1)
            numTimes = numTimes + 1;
        else
            outStr = [outStr, num2str(numTimes)];
            outStr = [outStr, in(i-1)];
            numTimes = 1;
        end
    end
    if in(end) ~= in(end-1)
        outStr = [outStr, num2str(1)];
        outStr = [outStr, in(end)];
    end
end
fprintf("The length of the resulting string is %d\n", length(outStr));


% do it 10 more times
for numLoops = 1:10
    in = outStr;
    outStr = '';
    numTimes = 1;
    for i = 2:length(in)
        if in(i) == in(i-1)
            numTimes = numTimes + 1;
        else
            outStr = [outStr, num2str(numTimes)];
            outStr = [outStr, in(i-1)];
            numTimes = 1;
        end
    end
    if in(end) ~= in(end-1)
        outStr = [outStr, num2str(1)];
        outStr = [outStr, in(end)];
    end
end
fprintf("\nPart 2:\nThe length of the resulting string is %d\n", length(outStr));