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
        public TriviaResults(GetGameResultsResponse result)
        {
            InitializeComponent();
            foreach(PlayerResults player in result.results)
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
