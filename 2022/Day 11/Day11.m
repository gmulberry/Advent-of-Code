% Advent of Code 2022
% Day 11
clear
close
clc

fprintf("Advent of Code 2022\nDay 11\n\nPart 1:\n");

inputFile = fopen("input.txt");
input = fscanf(inputFile, "%c");
lines = strsplit(input, '\n');

% load the data for the monkeys from the input file
monkeys = struct();
i = 1;
monkeyIdx = 0;
while i <= length(lines)
    line = lines{i};
    splitUp = strsplit(line, ' ');
    
    if strcmp(splitUp{1}, 'Monkey')
        temp = splitUp{2};
        temp = strsplit(temp, ':');
        monkeyIdx = str2double(temp{1});
        monkey.name = monkeyIdx;
        monkeyIdx = monkeyIdx + 1;
        monkeys(monkeyIdx).Monkey = monkey;
        i = i + 1;
    elseif strcmp(splitUp{2}, 'Starting')
        monkey = monkeys(monkeyIdx).Monkey;
        numItems = length(splitUp) - 3;
        
        items = zeros(numItems,1);
        for j = 1:numItems
            temp = strsplit(splitUp{3+j}, ',');
            items(j) = str2double(temp{1});
        end
        monkey.items = items;
        
        monkeys(monkeyIdx).Monkey = monkey;
        i = i + 1;
    elseif strcmp(splitUp{2}, 'Operation:')
        monkey = monkeys(monkeyIdx).Monkey;
        
        op = splitUp{end-1};
        monkey.op = op;
        temp = splitUp{end};
        if strcmp(temp, 'old')
            amt = 9999;
        else
            amt = str2double(splitUp{end});
        end
        monkey.amt = amt;
        
        monkeys(monkeyIdx).Monkey = monkey;
        i = i + 1;
        
    elseif strcmp(splitUp{2}, 'Test:')
        monkey = monkeys(monkeyIdx).Monkey;
        
        testDivisor = str2double(splitUp{end});
        monkey.testDivisor = testDivisor;
        
        monkeys(monkeyIdx).Monkey = monkey;
        i = i + 1;
    elseif strcmp(splitUp{3}, 'true:')
        monkey = monkeys(monkeyIdx).Monkey;
        
        trueMonkey = str2double(splitUp{end});
        monkey.trueMonkey = trueMonkey;
        
        monkeys(monkeyIdx).Monkey = monkey;
        i = i + 1;
        
    elseif strcmp(splitUp{3}, 'false:')
        monkey = monkeys(monkeyIdx).Monkey;
        
        falseMonkey = str2double(splitUp{end});
        monkey.falseMonkey = falseMonkey;
        
        monkeys(monkeyIdx).Monkey = monkey;
        i = i + 1;
        
    else
        i = i + 1;
    end
end
numMonkeys = length(monkeys);

lcm = 1;
for i = 1:numMonkeys
    monkey = monkeys(i).Monkey;
    monkey.timesInspected = 0;
    monkeys(i).Monkey = monkey;
    lcm = lcm * monkey.testDivisor;
end
initialMonkeys = monkeys;

for round = 1:20
    % perform a round of monkey business
    
    fprintf("Round %d:\n", round);
    
    for i = 1:numMonkeys
        monkey = monkeys(i).Monkey;
        fprintf("\t");
        fprintf("Monkey %d:\n", monkey.name);
        
        numItems = length(monkey.items);
        if numItems > 0
            for itemNum = 1:numItems
                worryLev = monkey.items(itemNum);
                fprintf("\t\tMonkey inspects an item with a worry level of %d.\n", worryLev);
                monkey.timesInspected = monkey.timesInspected + 1;
                
                amt = monkey.amt;
                if amt == 9999
                    amt = worryLev;
                end
                if strcmp(monkey.op, '+')
                    newWorryLev = worryLev + amt;
                    fprintf("\t\t\tWorry level increases by %d to %d.\n", amt, newWorryLev);
                    
                elseif strcmp(monkey.op, '*')
                    newWorryLev = worryLev * amt;
                    fprintf("\t\t\tWorry level is multiplied by %d to %d.\n", amt, newWorryLev);
                end
                
                newWorryLev = floor(newWorryLev/3);
                fprintf("\t\t\tMonkey gets bored with item. Worry level is divided by 3 to %d.\n", newWorryLev);
                
                testResult = mod(newWorryLev, monkey.testDivisor);
                
                if testResult == 0
                    fprintf("\t\t\tCurrent worry level is divisible by %d.\n", monkey.testDivisor);
                    fprintf("\t\t\tItem with worry level %d is thrown to monkey %d.\n", newWorryLev, monkey.trueMonkey);
                    destMonkey = monkey.trueMonkey;
                else
                    fprintf("\t\t\tCurrent worry level is not divisible by %d.\n", monkey.testDivisor);
                    fprintf("\t\t\tItem with worry level %d is thrown to monkey %d.\n", newWorryLev, monkey.falseMonkey);
                    destMonkey = monkey.falseMonkey;
                end
                
                % throw the item to the destination monkey's inventory
                for k = 1:length(monkeys)
                    if monkeys(k).Monkey.name == destMonkey
                        items = monkeys(k).Monkey.items;
                        items = [items; newWorryLev];
                        monkeys(k).Monkey.items = items;
                        break;
                    end
                end
            end
            % the monkey always throws all his items
            monkey.items = [];
        else
            fprintf("\t\tMonkey has no items\n");
        end
        
        monkeys(i).Monkey = monkey;
    end
    
    fprintf("\nAfter round %d, the monkeys are holding items with these worry levels:\n", round);
    for i = 1:numMonkeys
        monkey = monkeys(i).Monkey;
        fprintf("\t");
        fprintf("Monkey %d: ", monkey.name);
        
        numItems = length(monkey.items);
        if numItems > 0
            for itemNum = 1:numItems
                worryLev = monkey.items(itemNum);
                fprintf("%d", worryLev);
                if itemNum ~= numItems
                    fprintf(", ");
                end
            end
        end
        fprintf("\n");
    end
    fprintf("\n");
end

inspects = zeros(numMonkeys, 1);
fprintf("\nAfter %d rounds:\n", round);
for i = 1:numMonkeys
    monkey = monkeys(i).Monkey;
    fprintf("Monkey %d inspected items %d times.\n", monkey.name, monkey.timesInspected);
    inspects(i) = monkey.timesInspected;
end
inspects = sort(inspects);

totalMonkeyBusiness = inspects(end) * inspects(end-1);
fprintf("\nThe level of monkey business is %d.\n", totalMonkeyBusiness);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf("\n\nPart 2:\n")
monkeys = initialMonkeys;
for round = 1:10000
    % perform a round of monkey business
    for i = 1:numMonkeys
        monkey = monkeys(i).Monkey;
        
        numItems = length(monkey.items);
        if numItems > 0
            for itemNum = 1:numItems
                worryLev = monkey.items(itemNum);
                monkey.timesInspected = monkey.timesInspected + 1;
                
                amt = monkey.amt;
                if amt == 9999
                    amt = worryLev;
                end
                if strcmp(monkey.op, '+')
                    newWorryLev = worryLev + amt;
                elseif strcmp(monkey.op, '*')
                    newWorryLev = worryLev * amt;
                end
                
                testResult = mod(newWorryLev, monkey.testDivisor);
                newWorryLev = mod(newWorryLev, lcm);
                if testResult == 0
                    destMonkey = monkey.trueMonkey;
                else
                    destMonkey = monkey.falseMonkey;
                end
                
                % throw the item to the destination monkey's inventory
                for k = 1:length(monkeys)
                    if monkeys(k).Monkey.name == destMonkey
                        items = monkeys(k).Monkey.items;
                        items = [items; newWorryLev];
                        monkeys(k).Monkey.items = items;
                        break;
                    end
                end
                
            end
            
            % the monkey always throws all his items
            monkey.items = [];
        end
        monkeys(i).Monkey = monkey;
    end
    if mod(round, 1000) == 0 || round == 1 || round == 20
        fprintf("\n== After round %d ==\n", round);
        for i = 1:numMonkeys
            monkey = monkeys(i).Monkey;
            fprintf("Monkey %d inspected items %d times.\n", monkey.name, monkey.timesInspected);
        end
    end
end

inspects = zeros(numMonkeys, 1);
for i = 1:numMonkeys
    monkey = monkeys(i).Monkey;
    inspects(i) = monkey.timesInspected;
end
inspects = sort(inspects);

totalMonkeyBusiness = inspects(end) * inspects(end-1);
fprintf("\nThe level of monkey business is %d.\n", totalMonkeyBusiness);




