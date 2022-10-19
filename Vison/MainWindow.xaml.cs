using System.Windows;
using System.Windows.Media;

namespace Vison
{
    internal struct ViewportParams
    {
        public int Size => Stride * Height;
        public int Stride => Width * Format.BitsPerPixel / 8;

        public int Width;
        public int Height;
        public PixelFormat Format;
        public int Dpi;
    }

    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            var op = System.Reflection.Emit.OpCodes.Add;
        }
    }
}
