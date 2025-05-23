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

        public TriviaInRoom(string roomName)
        {
            InitializeComponent();

            _roomName = roomName;
            SetupRoom();
        }

        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaJoinRoom.xaml", UriKind.Relative));
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
            //use _roomName to get the data of the room
            //bool isAdmin;
            //string roomName;
            //int maxPlayers;
            //int numQuestions;
            //int timePerQuestion;

            Connected.Text = $"You are connected to room {_roomName}";

            //Settings.Text = $"Max players: {maxPlayers}  Number of questions: {numQuestions}  Time per question: {timePerQuestion}";

            // If admin, show the control buttons
            //if (isAdmin)
            //{
            //    CloseRoom.Visibility = Visibility.Visible;
            //    StartGame.Visibility = Visibility.Visible;
            //}
            //else
            //{
            //    LeaveRoom.Visibility = Visibility.Visible;
            //}
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
