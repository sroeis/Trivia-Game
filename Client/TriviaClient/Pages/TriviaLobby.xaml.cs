using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
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
using System.Windows.Threading;

namespace TriviaClient.Pages
{
    /// <summary>
    /// Interaction logic for TriviaLobby.xaml
    /// </summary>
    public partial class TriviaLobby : Page
    {
        private List<string> _currentAnswers = new List<string>();
        private int _questionIndex = 0;
        private int _score = 0;
        private int _totalQuestions = 0;
        private DispatcherTimer _timer;
        private int _timeRemaining = 0;
        private int MAX_TIME_PER_QUESTION = 0;

        public TriviaLobby(RoomData roomdata)
        {
            InitializeComponent();
            _totalQuestions = roomdata.numOfquestionsInGame;
            MAX_TIME_PER_QUESTION = roomdata.timePerQuestion;
            

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += Timer_Tick;
            FetchAndDisplayQuestion();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            _timeRemaining--;
            Timer.Text = $"Time left: {_timeRemaining}s";

            if (_timeRemaining <= 0)
            {
                _timer.Stop();
                SubmitAnswer(-1); // No answer selected
            }
        }

        private async void FetchAndDisplayQuestion()
        {
            App.m_communicator.Send(Serializer.getQuestion());
            string responseStr = App.m_communicator.Receive();


            if(_totalQuestions == _questionIndex-1)
            {
                System.Diagnostics.Debug.WriteLine("done with quesrtions getting results");

                NavigateToResults();
                return;
            }
            try
            {
                var response = JsonConvert.DeserializeObject<GetQuestionResponse>(responseStr);

                if (string.IsNullOrWhiteSpace(response.question))
                {
                    NavigateToResults();
                    return;
                }
                Question.Text = System.Net.WebUtility.HtmlDecode(response.question);                
                // Convert 2D array to list of strings
                _currentAnswers = response.answers.Select(answer => answer[1].ToString()).ToList();

                // Update buttons
                o1.Text = _currentAnswers[0];
                o2.Text = _currentAnswers[1];
                o3.Text = _currentAnswers[2];
                o4.Text = _currentAnswers[3];

                _questionIndex++;
                QuestionCount.Text = $"Question: {_questionIndex}/{_totalQuestions}";

                // Timer start
                _timeRemaining = MAX_TIME_PER_QUESTION;
                _timer.Start();
            }
            catch
            {
                ErrorBox.Text = "Error getting question.";
                System.Diagnostics.Debug.WriteLine("error caught getting results");

                NavigateToResults();
            }
        }

        private async void SubmitAnswer(int answerIndex)
        {
            _timer.Stop();
            
            App.m_communicator.Send(Serializer.submitAnswer((uint)answerIndex, (uint)(MAX_TIME_PER_QUESTION - _timeRemaining)));

            string responseStr = App.m_communicator.Receive();
            var response = JsonConvert.DeserializeObject<SubmitAnswerResponse>(responseStr);

            if (answerIndex == response.correctAnswerId)
                _score++;

            Score.Text = $"Score: {_score}/{_questionIndex}";

            await Task.Delay(800); // delay before next
            FetchAndDisplayQuestion();
        }

        private void NavigateToResults()
        {
            TriviaResults roomPage = new TriviaResults();
            this.NavigationService.Navigate(roomPage);
        }

        void ExitClick(object sender, RoutedEventArgs e)
        {
            App.m_communicator.Send(Serializer.LeaveGame());
            string responseStr = App.m_communicator.Receive();
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));
        }
        void Option1Click(object sender, RoutedEventArgs e) => SubmitAnswer(0);
        void Option2Click(object sender, RoutedEventArgs e) => SubmitAnswer(1);
        void Option3Click(object sender, RoutedEventArgs e) => SubmitAnswer(2);
        void Option4Click(object sender, RoutedEventArgs e) => SubmitAnswer(3);
    }
    public class GetQuestionResponse
    {
        public string question { get; set; }
        public List<List<object>> answers { get; set; }
    }

    public class SubmitAnswerResponse
    {
        public int correctAnswerId { get; set; }
    }
    public class GetGameResultsResponse
    {
        public uint status;
        public List<PlayerResults> results;
    };
    public class PlayerResults
    {
        public string username;
        public uint correctAnswerCount;
        public uint wrongAnswerCount;
        public uint averageAnswerTime;
    };

}
