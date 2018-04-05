#include "userprofile.h"

namespace base {
    UserProfile::UserProfile()
    {
    }

    BASEAPPSHARED_EXPORT bool operator==(const UserProfile& a, const UserProfile& b) {
        return
            a.getFirstName() == b.getFirstName() &&
            a.getLastName() == b.getLastName() &&
            a.getEmail() == b.getEmail() &&
            a.getBirthday() == b.getBirthday() &&
            a.getGender() == b.getGender() &&
            a.getBio() == b.getBio() &&
            a.getUserId() == b.getUserId();
    }

    BASEAPPSHARED_EXPORT bool operator!=(const UserProfile& a, const UserProfile& b) {
        return !(a == b);
    }

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream &ds, const UserProfile &profile)
    {
        ds << profile.getFirstName() << profile.getLastName();
        ds << profile.getEmail();
        ds << profile.getBirthday();
        ds << profile.getGender();
        ds << profile.getBio();
        ds << profile.getUserId();

        return ds;
    }

    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream &ds, UserProfile& profile)
    {
        QString str;
        QDate date;
        qint64 val;

        ds >> str; profile.setFirstName(str);
        ds >> str; profile.setLastName(str);
        ds >> str; profile.setEmail(str);
        ds >> date; profile.setBirthday(date);
        ds >> str; profile.setGender(str);
        ds >> str; profile.setBio(str);
        ds >> val; profile.setUserId(val);

        return ds;
    }
}
