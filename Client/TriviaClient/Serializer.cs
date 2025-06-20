using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using TriviaClient.Requests;
using Buffer = System.Collections.Generic.List<byte>;

namespace TriviaClient
{
    class Serializer
    {
        public static Buffer Signin(string username, string password)
        {
            Dictionary<string, string> data = new Dictionary<string, string>()
            {
                { "username", username},
                { "password", password }
            };

            string jsonString = JsonConvert.SerializeObject(data);
            return Serialize((byte)CODES.LOGIN_CODE, jsonString);
        }

        public static Buffer Signup(string username, string password, string email)
        {
            Dictionary<string, string> data = new Dictionary<string, string>()
            {
                { "username", username},
                { "password", password },
                { "email", email }
            };

            string jsonString = JsonConvert.SerializeObject(data);
            return Serialize((byte)CODES.SIGNUP_CODE, jsonString);
        }

        public static Buffer CreateRoom(string roomName, string maxPlayers, string questionCount, string answerTimeout)
        {
            Dictionary<string, string> data = new Dictionary<string, string>()
            {
                { "roomName", roomName},
                { "maxPlayers", maxPlayers },
                { "questionCount", questionCount },
                { "answerTimeout", answerTimeout }
            };

            string jsonString = JsonConvert.SerializeObject(data);
            return Serialize((byte)CODES.CREATE_ROOM_CODE, jsonString);
        }

        public static Buffer GetRooms()
        {
            return Serialize((byte)CODES.GET_ROOMS_CODE);
        }
        public static Buffer Logout()
        {
            return Serialize((byte)CODES.LOGOUT_CODE);
        }

        public static Buffer JoinRoom(int roomId)
        {
            Dictionary<string, int> data = new Dictionary<string, int>()
            {
                { "roomId", roomId}
            };

            string jsonString = JsonConvert.SerializeObject(data);
            return Serialize((byte)CODES.JOIN_ROOM_CODE, jsonString);
        }

        public static Buffer GetPersonalStats()
        {
            return Serialize((byte)CODES.GET_PERSONAL_STATS_CODE);
        }
        public static Buffer GetHighScore()
        {
            return Serialize((byte)CODES.GET_HIGH_SCORE_CODE);
        }

        public static Buffer GetPlayersInRoom(int roomId)
        {
            Dictionary<string, int> data = new Dictionary<string, int>()
            {
                { "roomId", roomId}
            };

            string jsonString = JsonConvert.SerializeObject(data);
            return Serialize((byte)CODES.GET_PLAYERS_IN_ROOM_CODE, jsonString);
        }
        public static Buffer CloseRoom()
        {
            return Serialize((byte)CODES.CLOSE_ROOM_CODE);
        }
        internal static Buffer LeaveRoom()
        {
            return Serialize((byte)CODES.LEAVE_ROOM_CODE);
        }
        internal static Buffer StartGame()
        {
            return Serialize((byte)CODES.START_GAME_CODE);
        }
        internal static Buffer GetRoomState()
        {
            return Serialize((byte)CODES.GET_ROOM_STATE_CODE);
        }
        internal static Buffer LeaveGame()
        {
            return Serialize((byte)CODES.LEAVE_GAME_CODE);
        }
        internal static Buffer getGameResults()
        {
            return Serialize((byte)CODES.GET_GAME_RESULTS_CODE);
        }
        internal static Buffer submitAnswer(uint answerID, uint timeTaken)
        {
            Dictionary<string, uint> data = new Dictionary<string, uint>()
            {
                { "answerId", answerID},
                { "timeTaken", timeTaken }
            };

            string jsonString = JsonConvert.SerializeObject(data);
            return Serialize((byte)CODES.SUBMIT_ANSWER_CODE, jsonString);
        }
        internal static Buffer getQuestion()
        {
            return Serialize((byte)CODES.GET_QUESTION_CODE);
        }


        public static Buffer Serialize(byte code, string jsonString = " ")
        {
            Buffer msg = new Buffer();
            msg.Add(code);

            msg.AddRange(BitConverter.GetBytes(jsonString.Length));

            msg.AddRange(Encoding.ASCII.GetBytes(jsonString));

            return msg;
        }

    }


}
