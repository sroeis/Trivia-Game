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
    /// Interaction logic for TriviaLoggedIn.xaml
    /// </summary>
    public partial class TriviaLoggedIn : Page
    {
        public TriviaLoggedIn()
        {
            InitializeComponent();
        }

        void SignOutClick(object sender, RoutedEventArgs e)
        {
            App.m_communicator.Send(Serializer.Logout());

            if (App.ShowError(ErrorBox))
            {
                App.ButtonErrorEvent(sender, e);
                return;
            }
            this.NavigationService.Navigate(new Uri("../TriviaHome.xaml", UriKind.Relative));
        }
        void JoinRoomClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaJoinRoom.xaml", UriKind.Relative));
        }
        void CreateRoomClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaCreateRoom.xaml", UriKind.Relative));
        }
        void MyStatusClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaMyStatus.xaml", UriKind.Relative));
        }

        void HighScoresClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaHighScores.xaml", UriKind.Relative));
        }
    }
}
