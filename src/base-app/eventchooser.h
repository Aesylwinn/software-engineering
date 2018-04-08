
/*Chooses a random list of a certain number of events given a list of events*/

#ifndef EVENTCHOOSER_H
#define EVENTCHOOSER_H

#include "event.h"
#include "base-app_global.h"
#include <QVector>

namespace base{
    /*Implemented by Jake and Kyle */
    class BASEAPPSHARED_EXPORT EventChooser
    {
    public:
        EventChooser();
        QVector<Event> narrow(QVector<QString> interests, QVector<Event> list, qint32 numEvents);
    private:
    };
}
#endif // EVENTLIST_H
