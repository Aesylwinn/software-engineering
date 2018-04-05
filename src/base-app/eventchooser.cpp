/*Implemented by Jake*/

#include "eventchooser.h"

namespace base{
    EventChooser::EventChooser(){}

    QVector<Event> EventChooser::narrow(QVector<Event> list, qint32 numEvents)
    {
        if (numEvents > list.size())
            numEvents = list.size();
        QVector<Event> newList;
        qint32 index;
        do{
            index = qrand()% numEvents;
            if (!newList.contains(list[index]))
                    newList.push_back(list[index]);
        }while(newList.size() < numEvents);
        return newList;
    }
}
