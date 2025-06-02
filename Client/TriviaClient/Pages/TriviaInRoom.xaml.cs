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
        private RoomData m_roomData;
        private bool m_isAdmin;
        public TriviaInRoom(RoomData room, bool isAdmin)
        {
            InitializeComponent();

            m_roomData = room;
            m_isAdmin = isAdmin;
            Connected.Text = $"You are connected to room {room.name}";

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


            Settings.Text = $"Max players: {m_roomData.maxPlayers}  Number of questions: {m_roomData.numOfquestionsInGame}  Time per question: {m_roomData.timePerQuestion}";

            // If admin, show the control buttons
            if (m_isAdmin)
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
