#include "match.h"

Match::Match()
{
    for (size_t i = 0; i < 2; ++i)
        mConfirmations[i] = { "NONE", CS_Unsure };
}

void Match::confirm(std::string user)
{
    for (size_t i = 0; i < 2; ++i) {
        if (mConfirmations[i].user == user)
            mConfirmations[i].state = CS_Confirmed;
    }
    update();
}

void Match::cancel(std::string user)
{
    for (size_t i = 0; i < 2; ++i) {
        if (mConfirmations[i].user == user)
            mConfirmations[i].state = CS_Cancelled;
    }
    update();
}

void Match::update()
{
    // TODO
}
