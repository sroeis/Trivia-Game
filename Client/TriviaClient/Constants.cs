using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{

    public enum CODES
    {
        LOGIN_CODE = 1,
        SIGNUP_CODE = 2,
        ERROR_CODE = 3,
        LOGOUT_CODE = 4,
        GET_ROOMS_CODE = 5,
        JOIN_ROOM_CODE = 6,
        CREATE_ROOM_CODE = 7,
        GET_PLAYERS_IN_ROOM_CODE = 8,
        GET_HIGH_SCORE_CODE = 9,
        GET_PERSONAL_STATS_CODE = 10
    };
}