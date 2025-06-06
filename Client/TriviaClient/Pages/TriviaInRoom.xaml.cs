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
            Settings.Text = $"Max players: {m_roomData.maxPlayers}  Number of questions: {m_roomData.numOfquestionsInGame}  Time per question: {m_roomData.timePerQuestion}";
            SetupRoom();


            timer.Interval = TimeSpan.FromSeconds(3); // check every 3 seconds
            timer.Tick += Timer_Tick;
            timer.Start();

            Timer_Tick(null, null);

            this.Unloaded += TriviaInRoom_Unloaded;

        }

        private void TriviaInRoom_Unloaded(object sender, RoutedEventArgs e)
        {
            timer?.Stop();
            timer = null;
        }

        private async void Timer_Tick(object sender, EventArgs e)
        {
            try
            {
                GetRoomStateResponse users = await GetConnectedUsersAsync();
                UpdateUserList(users);
            }
            catch (Exception ex)
            {
                // Handle any exceptions that occur during the update
                MessageBox.Show($"An error occurred while updating the user list: {ex.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private async Task<GetRoomStateResponse> GetConnectedUsersAsync()
        {
            App.m_communicator.Send(Serializer.GetRoomState());
            string jsonString = App.m_communicator.Receive();
            GetRoomStateResponse response = JsonConvert.DeserializeObject<GetRoomStateResponse>(jsonString);
            return response;
        }

        private void UpdateUserList(GetRoomStateResponse users)
        {
            if (users?.players != null)
                UsersListBox.ItemsSource = users.players;
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
            App.m_communicator.Send(Serializer.StartGame());
            this.NavigationService.Navigate(new Uri("Pages/TriviaLobby.xaml", UriKind.Relative));
        }
        void LeaveRoomClick(object sender, RoutedEventArgs e)
        {
            //remove from room 
            App.m_communicator.Send(Serializer.CloseRoom());
            this.NavigationService.Navigate(new Uri("Pages/TriviaJoinRoom.xaml", UriKind.Relative));

        }
        private void SetupRoom()
        {
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

    public class GetRoomStateResponse
    {
        public uint status { get; set; }
        public bool hasGameBegun { get; set; }
        public List<string> players { get; set; }
        public uint questionCount { get; set; }
        public long answerTimeout { get; set; }
    }
}
