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
    /// Interaction logic for TriviaCreateRoom.xaml
    /// </summary>
    public partial class TriviaCreateRoom : Page
    {
        public TriviaCreateRoom()
        {
            InitializeComponent();
        }

        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("TriviaHome.xaml", UriKind.Relative));
        }

        void CreateRoomClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));
        }

        private void RoomNameTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
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
