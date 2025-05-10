using System.Configuration;
using System.Data;
using System.Globalization;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {

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
