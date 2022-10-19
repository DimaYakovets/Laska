using System.Windows;
using System.Numerics;
using System.Diagnostics;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media.Imaging;

using Vector = System.Windows.Vector;


namespace Vison.Controls.Layout
{
    public partial class ViewPort : UserControl
    {
        public Image Image => Display;

        private bool _grab;
        private bool _over;
        private Point _base;
        private Vector2 _start;
        private float _scale;

        private readonly float _step;

        private WriteableBitmap _bitmap;

        public ViewPort()
        {
            InitializeComponent();

            _scale = 1;
            _step = 0.2f;
        }

        public void SetEditorContext()
        {
        }

        internal void Init(ref ViewportParams viewport)
        {
            _bitmap = new WriteableBitmap(viewport.Width, viewport.Height, viewport.Dpi, viewport.Dpi, viewport.Format, null);

            Image.Source = _bitmap;
        }

        public unsafe void Update()
        {
            _bitmap.Lock();
            _bitmap.AddDirtyRect(new(0, 0, _bitmap.PixelWidth, _bitmap.PixelHeight));
            _bitmap.Unlock();
        }

        private void Display_MouseDown(object sender, MouseButtonEventArgs e)
        {
            _grab = e.RightButton == MouseButtonState.Pressed;

            if (_grab)
            {
                _base = e.GetPosition(sender as Image);
            }
        }
        private void Display_MouseUp(object sender, MouseButtonEventArgs e)
        {
            _grab = e.RightButton == MouseButtonState.Pressed;
        }

        private void Display_MouseMove(object sender, MouseEventArgs e)
        {
            if (_grab)
            {
                Vector delta = e.GetPosition(sender as Image) - _base;
            }
        }
        
        private void Display_MouseEnter(object sender, MouseEventArgs e)
        {
            _over = true;
        }
        
        private void Display_MouseLeave(object sender, MouseEventArgs e)
        {
            _over = false;
            _grab = false;
        }

        private void Display_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            if (_over)
            {
                if (e.Delta > 0 && _scale > 0)
                {
                    _scale -= _step;
                    _scale = _scale > 0 ? _scale : 0.01f;
                }

                if (e.Delta < 0)
                {
                    _scale += _step;
                }
            }
        }
    }
}
