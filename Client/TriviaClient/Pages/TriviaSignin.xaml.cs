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
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for TriviaSignin.xaml
    /// </summary>
    public partial class TriviaSignin : Page
    {
        private bool hasInputUsername = false;
        private bool hasInputPassword = false;

        public TriviaSignin()
        {
            InitializeComponent();
        }

        void BackClick(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("TriviaHome.xaml", UriKind.Relative));
        }

        void SignInClick(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordTextBox.Text;
            
            
            if(!hasInputUsername || !hasInputPassword || string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
            {
                App.ButtonErrorEvent(sender, e);
                return;
            }
            App.m_communicator.Send(Serializer.Signin(username, password));

            if(App.ShowError(ErrorBox))
            {
                App.ButtonErrorEvent(sender, e);
                return;
            }

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
    }
}
