#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> strSplit(std::string in, char delimiter)
{
    std::vector<std::string> out;
    std::string temp = "";
    for (int idx = 0; idx < in.length(); idx++)
    {
        char c = in.at(idx);
        if (c == delimiter)
        {
            out.push_back(temp);
            temp = "";
        }
        else
            temp = temp + c;
    }
    out.push_back(temp);
    return out;
}

const int FIVE_OF_A_KIND = 7;
const int FOUR_OF_A_KIND = 6;
const int FULL_HOUSE = 5;
const int THREE_OF_A_KIND = 4;
const int TWO_PAIR = 3;
const int ONE_PAIR = 2;
const int HIGH_CARD = 1;

struct hand
{
    std::vector<int> cards;
    std::vector<int> cardsUnsorted;
    int bid;
    std::vector<int> uniqueCards;
    std::vector<int> sets;
    int handType;
};

bool isFirstHandBetter(const hand &hand1, const hand &hand2)
{
    if (hand1.handType != hand2.handType)
    {
        if (hand1.handType > hand2.handType)
            return true;
        else
            return false;
    }
    else
    {
        if (hand1.cardsUnsorted[0] != hand2.cardsUnsorted[0])
        {
            if (hand1.cardsUnsorted[0] > hand2.cardsUnsorted[0])
                return true;
            else
                return false;
        }
        else
        {
            if (hand1.cardsUnsorted[1] != hand2.cardsUnsorted[1])
            {

                if (hand1.cardsUnsorted[1] > hand2.cardsUnsorted[1])
                    return true;
                else
                    return false;
            }
            else
            {
                if (hand1.cardsUnsorted[2] != hand2.cardsUnsorted[2])
                {

                    if (hand1.cardsUnsorted[2] > hand2.cardsUnsorted[2])
                        return true;
                    else
                        return false;
                }
                else
                {
                    if (hand1.cardsUnsorted[3] != hand2.cardsUnsorted[3])
                    {

                        if (hand1.cardsUnsorted[3] > hand2.cardsUnsorted[3])
                            return true;
                        else
                            return false;
                    }
                    else
                    {
                        if (hand1.cardsUnsorted[4] != hand2.cardsUnsorted[4])
                        {

                            if (hand1.cardsUnsorted[4] > hand2.cardsUnsorted[4])
                                return true;
                            else
                                return false;
                        }
                        else
                        {
                            if (hand1.bid > hand2.bid)
                                return true;
                            else
                                return false;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    std::cout << "AoC 2023 Day 7" << std::endl;
    std::string fileName = "input.txt";

    // Part 1
    std::ifstream file(fileName);
    std::string line;
    std::string cardString;
    std::vector<hand> hands;
    while (std::getline(file, line))
    {
        hand h;
        h.handType = 0;
        std::vector<int> cards;
        std::vector<std::string> splitUp = strSplit(line, ' ');
        cardString = splitUp[0];
        int bid = stoi(splitUp[1]);
        h.bid = bid;

        for (int i = 0; i < cardString.length(); i++)
        {
            char c = cardString[i];
            if (c == 'A')
                cards.push_back(14);
            else if (c == 'K')
                cards.push_back(13);
            else if (c == 'Q')
                cards.push_back(12);
            else if (c == 'J')
                cards.push_back(11);
            else if (c == 'T')
                cards.push_back(10);
            else
                cards.push_back(atoi(&c));
        }
        h.cardsUnsorted = cards;
        sort(cards.begin(), cards.end());
        h.cards = cards;

        std::vector<int> uniqueCards = cards;
        uniqueCards.erase(unique(uniqueCards.begin(), uniqueCards.end()), uniqueCards.end());
        h.uniqueCards = uniqueCards;

        std::vector<int> sets;
        for (int i = 0; i < uniqueCards.size(); i++)
        {
            int numOfThatCard = 0;
            for (int j = 0; j < cards.size(); j++)
                if (cards[j] == uniqueCards[i])
                    numOfThatCard++;
            sets.push_back(numOfThatCard);
        }
        h.sets = sets;

        int numPairs = 0;
        int numTrips = 0;
        for (int i = 0; i < uniqueCards.size(); i++)
        {
            if (sets[i] == 2)
                numPairs++;
            else if (sets[i] == 3)
                numTrips++;
            else if (sets[i] == 4)
                h.handType = FOUR_OF_A_KIND;
            else if (sets[i] == 5)
                h.handType = FIVE_OF_A_KIND;
        }

        if (numTrips == 1)
        {
            if (numPairs == 0)
                h.handType = THREE_OF_A_KIND;
            else
                h.handType = FULL_HOUSE;
        }
        else if (numPairs == 2)
            h.handType = TWO_PAIR;
        else if (numPairs == 1)
            h.handType = ONE_PAIR;
        else if (h.handType == 0)
            h.handType = HIGH_CARD;

        hands.push_back(h);
    }
    file.close();

    for (int i = 0; i < hands.size() - 1; i++)
    {
        for (int j = 0; j < hands.size() - i - 1; j++)
        {
            if (isFirstHandBetter(hands[j], hands[j + 1]))
            {
                hand temp = hands[j];
                hands[j] = hands[j + 1];
                hands[j + 1] = temp;
            }
        }
    }
    unsigned long out = 0;
    for (int i = 0; i < hands.size(); i++)
        out += (i + 1) * hands[i].bid;

    std::cout << "Part 1: " << out << std::endl;

    // Part 2
    std::ifstream file2(fileName);
    hands.clear();
    while (std::getline(file2, line))
    {
        hand h;
        h.handType = 0;
        std::vector<int> cards;
        std::vector<std::string> splitUp = strSplit(line, ' ');
        cardString = splitUp[0];
        int bid = stoi(splitUp[1]);
        h.bid = bid;

        for (int i = 0; i < cardString.length(); i++)
        {
            char c = cardString[i];
            if (c == 'A')
                cards.push_back(14);
            else if (c == 'K')
                cards.push_back(13);
            else if (c == 'Q')
                cards.push_back(12);
            else if (c == 'J')
                cards.push_back(1);
            else if (c == 'T')
                cards.push_back(10);
            else
                cards.push_back(atoi(&c));
        }
        h.cardsUnsorted = cards;
        sort(cards.begin(), cards.end());
        h.cards = cards;

        std::vector<int> uniqueCards = cards;
        uniqueCards.erase(unique(uniqueCards.begin(), uniqueCards.end()), uniqueCards.end());
        h.uniqueCards = uniqueCards;

        std::vector<int> sets;
        int numJacks = 0;
        for (int i = 0; i < cards.size(); i++)
            if (cards[i] == 1)
                numJacks++;
        for (int i = 0; i < uniqueCards.size(); i++)
        {
            int numOfThatCard = 0;
            for (int j = 0; j < cards.size(); j++)
                if (cards[j] == uniqueCards[i] && cards[j] != 1)
                    numOfThatCard++;
            sets.push_back(numOfThatCard);
        }
        h.sets = sets;

        int numPairs = 0;
        int numTrips = 0;

        for (int i = 0; i < uniqueCards.size(); i++)
        {
            if (sets[i] == 2)
                numPairs++;
            else if (sets[i] == 3)
                numTrips++;
            else if (sets[i] == 4)
            {
                h.handType = FOUR_OF_A_KIND;
                if (numJacks == 1)
                    h.handType = FIVE_OF_A_KIND;
            }
            else if (sets[i] == 5)
                h.handType = FIVE_OF_A_KIND;
        }

        if (numTrips == 1)
        {
            if (numPairs == 0)
            {
                h.handType = THREE_OF_A_KIND;
                if (numJacks == 1)
                    h.handType = FOUR_OF_A_KIND;
                else if (numJacks == 2)
                    h.handType = FIVE_OF_A_KIND;
            }
            else
                h.handType = FULL_HOUSE;
        }
        else if (numPairs == 2)
        {
            h.handType = TWO_PAIR;
            if (numJacks == 1)
                h.handType = FULL_HOUSE;
        }
        else if (numPairs == 1)
        {
            h.handType = ONE_PAIR;
            if (numJacks == 1)
                h.handType = THREE_OF_A_KIND;
            else if (numJacks == 2)
                h.handType = FOUR_OF_A_KIND;
            else if (numJacks == 3)
                h.handType = FIVE_OF_A_KIND;
        }
        else if (h.handType == 0)
        {
            h.handType = HIGH_CARD;
            if (numJacks == 1)
                h.handType = ONE_PAIR;
            else if (numJacks == 2)
                h.handType = THREE_OF_A_KIND;
            else if (numJacks == 3)
                h.handType = FOUR_OF_A_KIND;
            else if (numJacks == 4)
                h.handType = FIVE_OF_A_KIND;
            else if (numJacks == 5)
                h.handType = FIVE_OF_A_KIND;
        }
        hands.push_back(h);
    }
    file2.close();

    for (int i = 0; i < hands.size() - 1; i++)
        for (int j = 0; j < hands.size() - i - 1; j++)
            if (isFirstHandBetter(hands[j], hands[j + 1]))
            {
                hand temp = hands[j];
                hands[j] = hands[j + 1];
                hands[j + 1] = temp;
            }

    out = 0;
    for (int i = 0; i < hands.size(); i++)
        out += (i + 1) * hands[i].bid;

    std::cout << "Part 2: " << out << std::endl;
    return 0;
}