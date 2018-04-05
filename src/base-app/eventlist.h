/*Implemented by Jake*/
/*Chooses a random list of a certain number of events given a list of events*/

#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "event.h"
#include "base-app_global.h"
#include <QVector>

namespace base{
    class BASEAPPSHARED_EXPORT EventList
    {
    public:
        EventList();
        QVector<event> narrow(QVector<event> list, qint32 numEvents);
    private:
    };
}
#endif // EVENTLIST_H
