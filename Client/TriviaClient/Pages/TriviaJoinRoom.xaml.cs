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

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaJoinRoom.xaml
    /// </summary>
    public partial class TriviaJoinRoom : Page
    {
        private ObservableCollection<RoomData> m_rooms;
        public TriviaJoinRoom()
        {
            InitializeComponent();
            App.m_communicator.Send(Serializer.GetRooms());
            string jsonString = App.m_communicator.Receive();
            RoomsResponse response = JsonConvert.DeserializeObject<RoomsResponse>(jsonString);
            if (string.IsNullOrEmpty(response.message))
            {
                ErrorBox.Text = response.message + "\nPlease press the refresh button to try again.";
                return;
            }
            m_rooms = response.rooms;
            RoomsListBox.ItemsSource = m_rooms;
        }

        private void RoomsListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (RoomsListBox.SelectedItem != null)
            {
                PlayersPanel.Visibility = Visibility.Visible;
                PlayersListBox.Items.Clear();
                
                App.m_communicator.Send(Serializer.GetPlayersInRoom(((RoomData)RoomsListBox.SelectedItem).id));
                string jsonString = App.m_communicator.Receive();
                PlayersResponse response = JsonConvert.DeserializeObject<PlayersResponse>(jsonString);
                if (string.IsNullOrEmpty(response.message))
                {
                    ErrorBox.Text = response.message;
                    return;
                }

                PlayersListBox.ItemsSource = response.players;
            }
            else
            {
                PlayersPanel.Visibility = Visibility.Collapsed;
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
            
            m_rooms = response.rooms;
        }
        void JoinRoomClick(object sender, RoutedEventArgs e)
        {
            //check what room was selected
            if (RoomsListBox.SelectedItem is RoomData selectedRoom)
            {
                string roomName = selectedRoom.name;
                App.m_communicator.Send(Serializer.JoinRoom(selectedRoom.id));
                if (App.ShowError(ErrorBox))
                    return;
                //add user to the room here

                var inRoomPage = new TriviaInRoom(roomName);
                this.NavigationService.Navigate(inRoomPage);
            }
            else
            {
                ErrorBox.Text = "Please select a room first.";
            }

            ////for now delete after implementaion
            //var inRoomPage1 = new TriviaInRoom("hello");
            //this.NavigationService.Navigate(inRoomPage1);
        }

    }

    public class PlayersResponse
    {
        public string message { get; set; } //for Error response
        public List<string> players { get; set; }
    }
        public class RoomsResponse
    {
        public string message { get; set; } //for Error response
        public ObservableCollection<RoomData> rooms { get; set; }
    }
    public class RoomData
    {
        public int id;
        public string name;
        public int maxPlayers;
        public int numOfquestionsInGame;
        public int timePerQuestion;
        public int status;

    }

}

