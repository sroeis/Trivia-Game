using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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
    /// Interaction logic for TriviaSignup.xaml
    /// </summary>
    public partial class TriviaSignup : Page
    {
        private bool hasInputUsername = false;
        private bool hasInputPassword = false;
        private bool hasInputEmail = false;

        public TriviaSignup()
        {
            InitializeComponent();
        }
        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("TriviaHome.xaml", UriKind.Relative));
        }

        void SignUpClick(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordTextBox.Text;
            string email = EmailTextBox.Text;

            Regex emailRegex = new Regex(@"^[^@\s]+@[^@\s]+\.[^@\s]+$");
            if (!hasInputUsername || !hasInputPassword || !hasInputEmail || !emailRegex.IsMatch(email) || string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                App.ButtonErrorEvent(sender, e);
                return;
            }
            App.m_communicator.Send(Serializer.Signup(username, password, email));

            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));

        }


        private void UsernameTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (UsernameTextBox.Text == "Username:")
            {
                hasInputUsername = true;
                UsernameTextBox.Text = "";
                UsernameTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                UsernameTextBox.Padding = new Thickness(20, 0, 20, 0); // Center padding
                UsernameTextBox.FontSize = 35;
            }
        }

        private void PasswordTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (PasswordTextBox.Text == "Password:")
            {
                hasInputPassword = true;
                PasswordTextBox.Text = "";
                PasswordTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                PasswordTextBox.Padding = new Thickness(20, 0, 20, 0);
                PasswordTextBox.FontSize = 35;
            }
        }  
        private void EmailTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (EmailTextBox.Text == "Email:")
            {
                hasInputEmail = true;
                EmailTextBox.Text = "";
                EmailTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                EmailTextBox.Padding = new Thickness(20, 0, 20, 0);
                EmailTextBox.FontSize = 35;
            }
        }

    }
}
