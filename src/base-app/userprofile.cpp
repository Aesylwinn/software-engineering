#include "userprofile.h"

namespace base {
    UserProfile::UserProfile()
    {
    }

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream &ds, const UserProfile &profile)
    {
        ds << profile.getFirstName() << profile.getLastName();
        ds << profile.getEmail();
        ds << profile.getBirthday();
        ds << profile.getGender();
        ds << profile.getBio();

        return ds;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream &ds, UserProfile profile)
    {
        QString str;
        QDate date;

        ds >> str; profile.setFirstName(str);
        ds >> str; profile.setLastName(str);
        ds >> str; profile.setEmail(str);
        ds >> date; profile.setBirthday(date);
        ds >> str; profile.setGender(str);
        ds >> str; profile.setBio(str);

        return ds;
    }
}
