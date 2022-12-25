% Advent of Code 2022
% Day 25
clear
close
clc

fprintf("Advent of Code 2022\nDay 25\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');
numLines = length(lines);

decimal = zeros(numLines, 1);
for i = 1:numLines
    line = lines{i};
    decimal(i) = toDecimal(line);
end
tot = sum(decimal);
snafu = toSNAFU(tot);
fprintf("You must supply %s to Bob's console\n", snafu);

function dec = toDecimal(str)
    dec = 0;
    for i = length(str):-1:1
        c = str(i);
        base = 5;
        mult = base^(length(str)-(i));
        val = 0;
        if c == '2'
            val = 2 * mult;
        elseif c == '1'
            val = 1 * mult;
        elseif c == '0'
            val = 0 * mult;
        elseif c == '-'
            val = -1 * mult;
        elseif c == '='
            val = -2 * mult;
        end
        dec = dec + val;
    end
end

function str = toSNAFU(dec)
    base = 5;
    numDigits = ceil(log(abs(dec))/log(base));

    if numDigits == 0
        numDigits = 1;
    end

    str = '';
    for i = 1:numDigits
        str = [str,'2'];
    end

    test = toDecimal(str);
    for i = 1:numDigits
        c = str(i);
        while test > dec && c ~= '='
            % go down in this digit
            c = str(i);
            if c == '2'
                c = '1';
            elseif c == '1'
                c = '0';
            elseif c == '0'
                c = '-';
            elseif c == '-'
                c = '=';
            elseif c == '='
                c = '2';
            end
            str(i) = c;
            test = toDecimal(str);
        end

        if test < dec
            % go back up in this digit
            c = str(i);
            if c == '2'
                c = '=';
            elseif c == '1'
                c = '2';
            elseif c == '0'
                c = '1';
            elseif c == '-'
                c = '0';
            elseif c == '='
                c = '-';
            end
            str(i) = c;
            test = toDecimal(str);
        end
    end

    if str(1) == '0' && dec ~= 0
        str = str(2:end);
    end
end