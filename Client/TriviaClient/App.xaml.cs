using System.Configuration;
using System.Data;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Threading;
using Newtonsoft.Json;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static Communicator m_communicator { get; } = new Communicator();

        public static void ButtonErrorEvent(object sender, RoutedEventArgs e)
        {
            ((Button)sender).Background = new SolidColorBrush(Colors.Red);
            DispatcherTimer timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(0.5);
            timer.Tick += (s, args) =>
            {

                ((Button)sender).Background = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#3baaa3"));
                timer.Stop();
            };
            timer.Start();
        }

    }

    public class DarkerColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is Color color)
            {
                // You can adjust the darkening factor as needed (e.g., 0.7 for 70% brightness)
                double darkenFactor = 0.8;
                return Color.FromRgb((byte)(color.R * darkenFactor),
                                     (byte)(color.G * darkenFactor),
                                     (byte)(color.B * darkenFactor));
            }
            return value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }


    }

    
}
