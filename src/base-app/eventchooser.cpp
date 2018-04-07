/*Implemented by Jake and Kyle*/

#include "eventchooser.h"

namespace base{
    EventChooser::EventChooser(){}

    QVector<Event> EventChooser::narrow(QVector<QString> interests, QVector<Event> list, qint32 numEvents)
    {
        //check to see if requested number is too large
        if (numEvents > list.size()) {
            numEvents = list.size();
        }

        QVector<Event> matches;
        QVector<Event> random;
        QVector<Event> output;

        qint32 index;

        //populate lists
        for (int i = 0; i < list.size(); i++){
            if (interests.contains(list[i].getCategory()))
                matches.push_back(list[i]);
            else
                random.push_back(list[i]);
        }

        //checking for enough matches/random to populate the final list
        int numMatches = numEvents * 7 / 10;
        int numRandom = numEvents - numMatches;
        if (numMatches > matches.size()){
            numRandom += numMatches - matches.size();
            numMatches = numEvents - numRandom;
        }
        if (numRandom > random.size()){
            numMatches += numRandom - random.size();
            numRandom = numEvents - numMatches;
        }

        //fill 70% of final list with matches
        while(output.size() < numMatches && !matches.isEmpty()){
            index = qrand() % matches.size();
            output.push_back(matches[index]);
            matches.remove(index);
        }
        //fill the rest with random events
        while(output.size() < numEvents && !random.isEmpty()){
            index = qrand() % random.size();
            output.push_back(random[index]);
            random.remove(index);
        }
        return output;
    }
}
