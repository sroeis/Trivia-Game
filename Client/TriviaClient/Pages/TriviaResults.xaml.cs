using Newtonsoft.Json;
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
    /// Interaction logic for TriviaResults.xaml
    /// </summary>
    public partial class TriviaResults : Page
    {

        public TriviaResults()
        {
            System.Diagnostics.Debug.WriteLine("got into results");

    
            InitializeComponent();
            Scores.Text = "Please wait for all Players to finish the game";
            Wait();
        }

        public async void Wait()
        {
            await Task.Delay(5000);
            App.m_communicator.Send(Serializer.getGameResults());
            string responseStr = App.m_communicator.Receive();
            GetGameResultsResponse response = JsonConvert.DeserializeObject<GetGameResultsResponse>(responseStr);
            if (response.status != 100)
            {
                Scores.Text = "Scores:";
                SetScores(response);
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("waiting more");

                Wait();
            }
            return;
        }
        public void SetScores(GetGameResultsResponse response)
        {
            foreach (PlayerResults player in response.results)
            {
                Scores.Inlines.Add(new Run(player.username + ":")
                {
                    FontSize = 35,
                    TextDecorations = TextDecorations.Underline
                });

                Scores.Inlines.Add(new Run($"\nWrong Answers: {player.wrongAnswerCount} Correct Answers: {player.correctAnswerCount} Average Answer Time: {player.averageAnswerTime}\n"));
            }
        }
    }
}
