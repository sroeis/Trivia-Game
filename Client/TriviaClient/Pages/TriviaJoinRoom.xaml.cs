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

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaJoinRoom.xaml
    /// </summary>
    public partial class TriviaJoinRoom : Page
    {
        public TriviaJoinRoom()
        {
            InitializeComponent();
            App.m_communicator.Send(Serializer.GetRooms());
            string jsonString = App.m_communicator.Receive();
            RoomsResponse response = JsonConvert.DeserializeObject<RoomsResponse>(jsonString);
            if (!string.IsNullOrEmpty(response.message))
            {
                ErrorBox.Text = response.message + "\nPlease press the refresh button to try again.";
                return;
            }
            RoomsListBox.ItemsSource = response.rooms;
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
                //string jsonString = App.m_communicator.Receive();

                if (App.ShowError(ErrorBox))
                    return;
                //add user to the room here


                TriviaInRoom roomPage = new TriviaInRoom(selectedRoom, true);
                this.NavigationService.Navigate(roomPage);
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
        public List<string> PlayersInRoom { get; set; }
    }
    public class RoomsResponse
    {
        public string message { get; set; } //for Error response
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

