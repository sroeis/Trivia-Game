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
        SIGNUP_CODE,
        ERROR_CODE,
        LOGOUT_CODE,
        GET_ROOMS_CODE,
        JOIN_ROOM_CODE,
        CREATE_ROOM_CODE,
        GET_PLAYERS_IN_ROOM_CODE,
        GET_HIGH_SCORE_CODE,
        GET_PERSONAL_STATS_CODE,
        CLOSE_ROOM_CODE,
        START_GAME_CODE,
        GET_ROOM_STATE_CODE,
        LEAVE_ROOM_CODE
    };
}