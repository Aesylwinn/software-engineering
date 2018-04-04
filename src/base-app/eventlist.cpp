/*Implemented by Jake*/

#include "eventlist.h"

namespace base{
    EventList::EventList(){}

    QVector<event> EventList::narrow(QVector<event> list, qint32 numEvents)
    {
        if (numEvents > list.size())
            numEvents = list.size();
        QVector<event> newList;
        qint32 index;
        do{
            index = qrand()% numEvents;
            if (!newList.contains(list[index]))
                    newList.push_back(list[index]);
        }while(newList.size() < numEvents);
        return newList;
    }
}
