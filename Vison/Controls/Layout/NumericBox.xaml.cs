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

namespace Vison.Controls.Layout
{
    /// <summary>
    /// Interaction logic for NumericBoxSlider.xaml
    /// </summary>
    public partial class NumericBox : UserControl
    {
        private float _value;

        public NumericBox()
        {
            InitializeComponent();

            _value = 0;

            Box.TextChanged += (sender, e) =>
            {
                
            };
        }
    }
}
