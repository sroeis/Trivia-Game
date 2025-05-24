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
using Newtonsoft.Json;

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaMyStatus.xaml
    /// </summary>
    public partial class TriviaMyStatus : Page
    {
        public TriviaMyStatus()
        {
            InitializeComponent();
            App.m_communicator.Send(Serializer.GetPersonalStats());
            string jsonString = App.m_communicator.Receive();

            PersonalStatsResp response = JsonConvert.DeserializeObject<PersonalStatsResp>(jsonString);

            foreach (string stat in response.stats)
            {
                Performances.Text += stat + "\n";
            }
        }
        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));
        }

    }

    public class PersonalStatsResp
    {
        public int status { get; set; }
        public List<string> stats { get; set; } // <format explanation of stat>: <stat>



    }
}
