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
using static System.Formats.Asn1.AsnWriter;
using System.Xml.Linq;
using Newtonsoft.Json;


namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaHighScores.xaml
    /// </summary>
    public partial class TriviaHighScores : Page
    {
        public TriviaHighScores()
        {
            InitializeComponent();

            App.m_communicator.Send(Serializer.GetHighScore());
            string jsonString = App.m_communicator.Receive();
            Players response = JsonConvert.DeserializeObject<Players>(jsonString);
            if (!string.IsNullOrEmpty(response.message))
            {
                ErrorBox.Text = response.message;
                return;
            }
            HighScoresListBox.ItemsSource = response.statistics;

        }
        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));
        }

    }

    public class Players
    {
        public string message { get; set; }
        public List<string> statistics { get; set; }
    }
}
