namespace TriviaClient.Requests
{
    public class CreateRoomRequest
    {
        public string RoomName { get; set; }
        public int MaxPlayers { get; set; }
        public int QuestionCount { get; set; }
        public int AnswerTimeout { get; set; }
    }
} 