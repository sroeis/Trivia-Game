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
using System.Windows.Threading;

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for InRoom.xaml
    /// </summary>
    public partial class TriviaInRoom : Page
    {
        private RoomData m_roomData;
        private bool m_isAdmin;
        DispatcherTimer timer = new DispatcherTimer();

        public TriviaInRoom(RoomData room, bool isAdmin)
        {
            InitializeComponent();

            m_roomData = room;
            m_isAdmin = isAdmin;
            Connected.Text = $"You are connected to room {room.name}";

            timer.Interval = TimeSpan.FromSeconds(5); // check every 5 seconds
            timer.Tick += Timer_Tick;
            timer.Start();

            Timer_Tick(null, null);

            SetupRoom();
        }


        private async void Timer_Tick(object sender, EventArgs e)
        {
            PlayersResponse users = await GetConnectedUsersAsync();
            UpdateUserList(users);
        }

        private async Task<PlayersResponse> GetConnectedUsersAsync()
        {
            App.m_communicator.Send(Serializer.GetPlayersInRoom(m_roomData.id));
            string jsonString = App.m_communicator.Receive();
            PlayersResponse response = JsonConvert.DeserializeObject<PlayersResponse>(jsonString);
            return response;
        }

        private void UpdateUserList(PlayersResponse users)
        {
            UsersListBox.ItemsSource = users.PlayersInRoom; 
        }
        void CloseRoomClick(object sender, RoutedEventArgs e)
        {
            // delete the room 
            App.m_communicator.Send(Serializer.CloseRoom());
            App.m_communicator.Receive();
            this.NavigationService.Navigate(new Uri("Pages/TriviaJoinRoom.xaml", UriKind.Relative));
        }
        void StartGameClick(object sender, RoutedEventArgs e)
        {
            //start the game
        }
        void LeaveRoomClick(object sender, RoutedEventArgs e)
        {
            //remove from room 
            App.m_communicator.Send(Serializer.CloseRoom());
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


    
    }
}
