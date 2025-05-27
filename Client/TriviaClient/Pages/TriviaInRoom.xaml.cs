using Newtonsoft.Json;
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

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for InRoom.xaml
    /// </summary>
    public partial class TriviaInRoom : Page
    {
        private string _roomName;
        private int _maxPlayers;
        private int _numOfQuestions;
        private int _timePerQuestion;
        private bool _isAdmin;

        public TriviaInRoom(string roomName,int max,int num,int time,bool isAdmin)
        {
            InitializeComponent();

            _roomName = roomName;
            _maxPlayers = max;
            _numOfQuestions = num;
            _timePerQuestion = time;
            _isAdmin = isAdmin;
            Connected.Text = $"You are connected to room {_roomName}";

            SetupRoom();
        }


        void CloseRoomClick(object sender, RoutedEventArgs e)
        {
            // delete the room 
            this.NavigationService.Navigate(new Uri("Pages/TriviaJoinRoom.xaml", UriKind.Relative));
        }
        void StartGameClick(object sender, RoutedEventArgs e)
        {
            //start the game
        }
        void LeaveRoomClick(object sender, RoutedEventArgs e)
        {
            //remove from room 
            this.NavigationService.Navigate(new Uri("Pages/TriviaJoinRoom.xaml", UriKind.Relative));

        }
        private void SetupRoom()
        {

            App.m_communicator.Send(Serializer.GetRooms());
            string jsonString = App.m_communicator.Receive();
            RoomsResponse response = JsonConvert.DeserializeObject<RoomsResponse>(jsonString);


            Settings.Text = $"Max players: {_maxPlayers}  Number of questions: {_numOfQuestions}  Time per question: {_timePerQuestion}";

            // If admin, show the control buttons
            if (_isAdmin)
            {
                CloseRoom.Visibility = Visibility.Visible;
                StartGame.Visibility = Visibility.Visible;
            }
            else
            {
                LeaveRoom.Visibility = Visibility.Visible;
            }
        }

        // Call this to add users to the list
        public void AddUser(string username)
        {
            UsersListBox.Items.Add(new ListBoxItem
            {
                Content = username
            });
        }
    
    }
}
