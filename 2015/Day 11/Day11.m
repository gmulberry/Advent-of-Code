% Advent of Code 2015
% Day 11
clear
close
clc

fprintf("Advent of Code 2015\nDay 11\n\nPart 1:\n");

oldPass = 'cqjxjnds';

password = oldPass;
invalid = 1;
while invalid
    
    % increment the password

    for i = 8:-1:1
        if password(i)+0 < char('z')+0
            password(i) = password(i)+1;
            break;
        else 
            password(i) = char('a');
        end
    end
    
    invalid = 0;
    
    % check for a straight
    hasStraight = 0;
    for i = 1:5
        startChar = password(i) + 0;
        if startChar <= 'x' + 0 && password(i + 1) + 0 == startChar + 1 && password(i + 2)+ 0 == startChar + 2
            hasStraight = 1;
            break;
        end
    end
    
    % check for i, o, or l
    hasIllegalLetter = 0;
    for i = 1:8
        if password(i) == 'i' || password(i) == 'o' || password(i) == 'l'
            hasIllegalLetter = 1;
            break;
        end
    end
    
    % check for two pairs
    numPairs = 0;
    for i = 1:5
        startChar = password(i) + 0;
        if startChar == password(i + 1) + 0
            numPairs = numPairs + 1;
            break;
        end
    end
    for i = i+2:7
        startChar = password(i) + 0;
        if startChar == password(i + 1) + 0
            numPairs = numPairs + 1;
            break;
        end
    end
    
    % determine if invalid
    if ~hasStraight || hasIllegalLetter || numPairs < 2
       invalid = 1; 
    end
end
fprintf("Santa's new password should be %s\n", password);


fprintf("\nPart 2:\n");
invalid = 1;
while invalid
    
    % increment the password

    for i = 8:-1:1
        if password(i)+0 < char('z')+0
            password(i) = password(i)+1;
            break;
        else 
            password(i) = char('a');
        end
    end
    
    invalid = 0;
    
    % check for a straight
    hasStraight = 0;
    for i = 1:5
        startChar = password(i) + 0;
        if startChar <= 'x' + 0 && password(i + 1) + 0 == startChar + 1 && password(i + 2)+ 0 == startChar + 2
            hasStraight = 1;
            break;
        end
    end
    
    % check for i, o, or l
    hasIllegalLetter = 0;
    for i = 1:8
        if password(i) == 'i' || password(i) == 'o' || password(i) == 'l'
            hasIllegalLetter = 1;
            break;
        end
    end
    
    % check for two pairs
    numPairs = 0;
    for i = 1:5
        startChar = password(i) + 0;
        if startChar == password(i + 1) + 0
            numPairs = numPairs + 1;
            break;
        end
    end
    for i = i+2:7
        startChar = password(i) + 0;
        if startChar == password(i + 1) + 0
            numPairs = numPairs + 1;
            break;
        end
    end
    
    % determine if invalid
    if ~hasStraight || hasIllegalLetter || numPairs < 2
       invalid = 1; 
    end
end
fprintf("Santa's new new password should be %s\n", password);
