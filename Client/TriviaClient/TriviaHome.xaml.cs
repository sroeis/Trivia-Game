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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for TriviaHome.xaml
    /// </summary>
    public partial class TriviaHome : Page
    {
        public TriviaHome()
        {
            InitializeComponent();
        }

        void SignInClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaSignin.xaml",UriKind.Relative));
        }
        void SignUpClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaSignup.xaml", UriKind.Relative));
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
