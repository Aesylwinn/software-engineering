#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QDate>
#include <QString>

#include "base-app_global.h"

namespace base {
    class BASEAPPSHARED_EXPORT UserProfile
    {
    public:
        UserProfile();

        QString getFirstName() const {
            return mFirstName;
        }

        QString getLastName() const {
            return mLastName;
        }

        QString getEmail() const {
            return mEmail;
        }

        QDate getBirthday() const {
            return mBirthday;
        }

        QString getGender() const {
            return mGender;
        }

        QString getBio() const {
            return mBio;
        }

        void setFirstName(QString name) {
            mFirstName = name;
        }

        void setLastName(QString name) {
            mLastName = name;
        }

        void setEmail(QString name) {
            mEmail = name;
        }

        void setBirthday(QDate date) {
            mBirthday = date;
        }

        void setGender(QString gender) {
            mGender = gender;
        }

        void setBio(QString bio) {
            mBio = bio;
        }

    private:
        QString mFirstName;
        QString mLastName;
        QString mEmail;
        QDate mBirthday;
        QString mGender;
        QString mBio;

        friend BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const UserProfile& profile);
        friend BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, UserProfile profile);
    };

    BASEAPPSHARED_EXPORT QDataStream& operator<<(QDataStream& ds, const UserProfile& profile);
    BASEAPPSHARED_EXPORT QDataStream& operator>>(QDataStream& ds, UserProfile profile);
}

#endif // USERPROFILE_H
