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
        }

        private void RoomsListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (RoomsListBox.SelectedItem != null)
            {
                PlayersPanel.Visibility = Visibility.Visible;
                PlayersListBox.Items.Clear();
                //add like a way to get the players
                //its like this: PlayersListBox.Items.Add(new ListBoxItem { Content = "user1234 whatever" });
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
            //get the room available from the server
            // add them to the screen
            //its like this: RoomsListBox.Items.Add(new ListBoxItem { Content = "room_name whatever" });

        }
        void JoinRoomClick(object sender, RoutedEventArgs e)
        {
            //check what room was selected
            if (RoomsListBox.SelectedItem is ListBoxItem selectedItem)
            {
                string roomName = selectedItem.Content.ToString();


                //add user to the room here

                var inRoomPage = new TriviaInRoom(roomName);
                this.NavigationService.Navigate(inRoomPage);
            }
            else
            {
                MessageBox.Show("Please select a room first.");
            }

            //for now delete after implementaion
            var inRoomPage1 = new TriviaInRoom("hello");
            this.NavigationService.Navigate(inRoomPage1);
        }

    }

}

