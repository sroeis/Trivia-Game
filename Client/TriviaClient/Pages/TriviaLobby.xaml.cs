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
    /// Interaction logic for TriviaLobby.xaml
    /// </summary>
    public partial class TriviaLobby : Page
    {
        public TriviaLobby()
        {
            InitializeComponent();
        }

        void ExitClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("TriviaHome.xaml", UriKind.Relative));
        }
        void Option1Click(object sender, RoutedEventArgs e)
        {

        }
        void Option2Click(object sender, RoutedEventArgs e)
        {

        }
        void Option3Click(object sender, RoutedEventArgs e)
        {

        }
        void Option4Click(object sender, RoutedEventArgs e)
        {

        }

    }

}
