using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaCreateRoom.xaml
    /// </summary>
    public partial class TriviaCreateRoom : Page
    {
        private bool hasInputRoomName = false;
        private bool hasInputMaxPlayers = false;
        private bool hasInputQuestionCount = false;
        private bool hasInputAnswerTimeout = false;

        public TriviaCreateRoom()
        {
            InitializeComponent();
        }

        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));
        }

        void CreateRoomClick(object sender, RoutedEventArgs e)
        {   
            string roomName = RoomNameTextBox.Text;
            string maxPlayers = NumberOfPlayersTextBox.Text;
            string questionCount = NumberOfQuestionsTextBox.Text;
            string answerTimeout = TimePerQuestionTextBox.Text;
            if (string.IsNullOrEmpty(roomName) || !hasInputRoomName ||
                string.IsNullOrEmpty(maxPlayers) || !hasInputMaxPlayers ||
                string.IsNullOrEmpty(questionCount) || !hasInputQuestionCount ||
                string.IsNullOrEmpty(answerTimeout) || !hasInputAnswerTimeout)
            {
                App.ButtonErrorEvent(sender, e);
                return;
            }
            else if(int.TryParse(int.Parse(maxPlayers).ToString(), out _) == false ||
                    int.TryParse(int.Parse(questionCount).ToString(), out _) == false ||
                    int.TryParse(int.Parse(answerTimeout).ToString(), out _) == false)
            {
                ErrorBox.Text = "Please enter valid numbers for max players, question count, and answer timeout.";
                App.ButtonErrorEvent(sender, e);
                return;
            }
            App.m_communicator.Send(Serializer.CreateRoom(roomName, maxPlayers, questionCount, answerTimeout));

            string jsonString = App.m_communicator.Receive();
            Dictionary<string, string> response = JsonConvert.DeserializeObject<Dictionary<string, string>>(jsonString);
            
            if (response.ContainsKey("message"))
            {
                ErrorBox.Text = response["message"];
                return;
            }

            RoomData data = new RoomData
            {
                name = roomName,
                maxPlayers = int.Parse(maxPlayers),
                numOfquestionsInGame = int.Parse(questionCount),
                timePerQuestion = int.Parse(answerTimeout),
                id = int.Parse(response["status"])
            };


            TriviaInRoom roomPage = new TriviaInRoom(data, true);
            this.NavigationService.Navigate(roomPage);

        }

        public static RoomData GetRoomData(string roomName)
        {
            App.m_communicator.Send(Serializer.GetRooms());
            string jsonString = App.m_communicator.Receive();
            RoomsResponse response = JsonConvert.DeserializeObject<RoomsResponse>(jsonString);

            foreach(RoomData room in response.rooms)
            {
                if(room.name == roomName) return room;
            }

            return null;
        }

        private void RoomNameTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            hasInputRoomName = true;
            if (RoomNameTextBox.Text == "Room Name:")
            {
                RoomNameTextBox.Text = "";
                RoomNameTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                RoomNameTextBox.Padding = new Thickness(20, 0, 20, 0);
                RoomNameTextBox.FontSize = 35;
            }
        }

        private void NumberOfPlayersTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            hasInputMaxPlayers = true;
            if (NumberOfPlayersTextBox.Text == "Number Of Players:")
            {
                NumberOfPlayersTextBox.Text = "";
                NumberOfPlayersTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                NumberOfPlayersTextBox.Padding = new Thickness(20, 0, 20, 0);
                NumberOfPlayersTextBox.FontSize = 35;
            }
        }

        private void NumberOfQuestionsTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            hasInputQuestionCount = true;
            if (NumberOfQuestionsTextBox.Text == "Number Of Questions:")
            {
                NumberOfQuestionsTextBox.Text = "";
                NumberOfQuestionsTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                NumberOfQuestionsTextBox.Padding = new Thickness(20, 0, 20, 0);
                NumberOfQuestionsTextBox.FontSize = 35;
            }
        }

        private void TimePerQuestionTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            hasInputAnswerTimeout = true;
            if (TimePerQuestionTextBox.Text == "Time Per Question:")
            {
                TimePerQuestionTextBox.Text = "";
                TimePerQuestionTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                TimePerQuestionTextBox.Padding = new Thickness(20, 0, 20, 0);
                TimePerQuestionTextBox.FontSize = 35;
            }
        }
    }
}
