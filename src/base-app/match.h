#ifndef BASE_MATCH_H
#define BASE_MATCH_H

#include <string>

namespace base {
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
}

#endif // MATCH_H
