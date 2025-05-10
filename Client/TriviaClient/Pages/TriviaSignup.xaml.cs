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
    /// Interaction logic for TriviaSignup.xaml
    /// </summary>
    public partial class TriviaSignup : Page
    {
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
            this.NavigationService.Navigate(new Uri("Pages/TriviaLoggedIn.xaml", UriKind.Relative));

        }


        private void UsernameTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            if (UsernameTextBox.Text == "Username:")
            {
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
                EmailTextBox.Text = "";
                EmailTextBox.VerticalContentAlignment = VerticalAlignment.Center;
                EmailTextBox.Padding = new Thickness(20, 0, 20, 0);
                EmailTextBox.FontSize = 35;
            }
        }

    }
}
