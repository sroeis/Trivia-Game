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
using TriviaClient.Pages;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;
using System.Collections.ObjectModel;
using System.Security.RightsManagement;
using System.Windows.Threading;
using System.Threading;

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaJoinRoom.xaml
    /// </summary>
    public partial class TriviaJoinRoom : Page
    {
        DispatcherTimer timer = new DispatcherTimer();
        private bool isUpdatingRoomsList = false;

        public TriviaJoinRoom()
        {
            InitializeComponent();

            timer.Interval = TimeSpan.FromSeconds(3); // check every 5 seconds
            timer.Tick += Timer_Tick;
            timer.Start();

            Timer_Tick(null, null);

            this.Unloaded += TriviaJoinRoom_Unloaded;

        }


        private async void Timer_Tick(object sender, EventArgs e)
        {
            RoomsResponse rooms = await GetRoomsAsync();
            if(rooms == null)
            {
                return;
            }
            UpdateRoomList(rooms);
        }

        private async Task<RoomsResponse> GetRoomsAsync()
        {

            App.m_communicator.Send(Serializer.GetRooms());
            string jsonString = App.m_communicator.Receive();

            if (!jsonString.Contains("Rooms")) // crude check
            {
                return null;
            }

            RoomsResponse response = JsonConvert.DeserializeObject<RoomsResponse>(jsonString);
            if (!string.IsNullOrEmpty(response.message))
            {
                App.ShowError(ErrorBox);
            }
            return response;
        }

        private void UpdateRoomList(RoomsResponse response)
        {
            isUpdatingRoomsList = true;

            var selectedRoom = RoomsListBox.SelectedItem as RoomData;
            int? selectedRoomId = selectedRoom?.id;
            RoomsListBox.ItemsSource = response.rooms;

            // Try to restore the selection  
            if (selectedRoomId.HasValue && response.rooms != null)
            {
                var matchingRoom = response.rooms.FirstOrDefault(r => r.id == selectedRoomId.Value);
                if (matchingRoom != null)
                {
                    RoomsListBox.SelectedItem = matchingRoom;
                }
            }

            isUpdatingRoomsList = false;
        }


        private void RoomsListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (isUpdatingRoomsList) return;
            try
            {
                if (RoomsListBox.SelectedItem != null)
                {
                    PlayersPanel.Visibility = Visibility.Visible;
                    PlayersListBox.Items.Clear();

                    App.m_communicator.Send(Serializer.GetPlayersInRoom(((RoomData)RoomsListBox.SelectedItem).id));
                    string jsonString = App.m_communicator.Receive();
                    while (!jsonString.Contains("PlayersInRoom"))
                    {
                        jsonString = App.m_communicator.Receive();
                    }
                    PlayersResponse response = JsonConvert.DeserializeObject<PlayersResponse>(jsonString);
                    if (!string.IsNullOrEmpty(response.message))
                    {
                        ErrorBox.Text = response.message;
                        return;
                    }

                    PlayersListBox.ItemsSource = response.PlayersInRoom;
                }
                else
                {
                    PlayersPanel.Visibility = Visibility.Collapsed;
                }

            }
            catch (InvalidOperationException err)
            {

            }
        }
        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));
        }

        void RefreshClick(object sender, RoutedEventArgs e)
        {
            App.m_communicator.Send(Serializer.GetRooms());
            string jsonString = App.m_communicator.Receive();
            RoomsResponse response = JsonConvert.DeserializeObject<RoomsResponse>(jsonString);

            RoomsListBox.ItemsSource = response.rooms;

        }
        void JoinRoomClick(object sender, RoutedEventArgs e)
        {
            //check what room was selected
            if (RoomsListBox.SelectedItem is RoomData selectedRoom)
            {
                string roomName = selectedRoom.name;
                int max = selectedRoom.maxPlayers;
                int num = selectedRoom.numOfquestionsInGame;
                int time = selectedRoom.timePerQuestion;

                App.m_communicator.Send(Serializer.JoinRoom(selectedRoom.id));
                string jsonString = App.m_communicator.Receive();

                JoinRoomResponse response = JsonConvert.DeserializeObject<JoinRoomResponse>(jsonString);
                if (response.status != 200)
                {
                    ErrorBox.Text = "failed";
                    return;
                }
                else
                {
                    TriviaInRoom roomPage = new TriviaInRoom(selectedRoom, false);
                    this.NavigationService.Navigate(roomPage);
                }
            }
            else
            {
                ErrorBox.Text = "Please select a room first.";
            }

            ////for now delete after implementaion
            //var inRoomPage1 = new TriviaInRoom("hello");
            //this.NavigationService.Navigate(inRoomPage1);
        }

        private void TriviaJoinRoom_Unloaded(object sender, RoutedEventArgs e)
        {
            timer?.Stop();
            timer = null;
        }


    }

    public class PlayersResponse
    {
        public string message { get; set; } 
        public List<string> PlayersInRoom { get; set; }
    }
    public class JoinRoomResponse
    {
        public string message { get; set; }
        public uint status { get; set; } 
    }
    public class RoomsResponse
    {
        public string message { get; set; } 
        public List<RoomData> rooms { get; set; }
    }
    public class RoomData
    {
        public int id { get; set; }
        public string name { get; set; }
        public int maxPlayers { get; set; }
        public int numOfquestionsInGame { get; set; }
        public int timePerQuestion { get; set; }
        public int status { get; set; }


    }
}

