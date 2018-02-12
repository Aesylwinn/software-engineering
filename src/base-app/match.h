#ifndef MATCH_H
#define MATCH_H

#include <string>

/* Implemented by Yianni and Kyle */
class Match
{
public:
    Match();

    void confirm(std::string user);
    void cancel(std::string user);

private:

    void update();

    enum ConfirmState {
        CS_Confirmed,
        CS_Unsure,
        CS_Cancelled
    };

    struct Confirmation {
        std::string user;
        ConfirmState state;
    };

    Confirmation mConfirmations[2];
};

#endif // MATCH_H
