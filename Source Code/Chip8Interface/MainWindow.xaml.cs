using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using Chip8Bridge;
using Microsoft.Win32;
using System.IO;

namespace Chip8Interface
{
    public partial class MainWindow : Window
    {
        public IntPtr myPanelHandle;
        public Thread myThread;
        public CBridge myBridge;

        public MainWindow()
        {
            InitializeComponent();
            myPanelHandle = myEngineRenderPanel.Handle;
            myThread = new Thread(new ThreadStart(Init));
            myThread.Start();
        }

        public void Init()
        {
            myBridge = new CBridge();
            myBridge.Init(myPanelHandle);
        }

        private void WindowsFormsHost_ChildChanged(object sender, System.Windows.Forms.Integration.ChildChangedEventArgs e)
        {

        }

        private void KeyboardPressed(object sender, System.Windows.Input.KeyEventArgs e)
        {
            
            switch(e.Key)
            {
                case System.Windows.Input.Key.D1:
                    myBridge.GetInput((sbyte)'1', true );
                    break;
                case System.Windows.Input.Key.D2:
                    myBridge.GetInput((sbyte)'2', true);
                    break;
                case System.Windows.Input.Key.D3:
                    myBridge.GetInput((sbyte)'3', true);
                    break;
                case System.Windows.Input.Key.D4:
                    myBridge.GetInput((sbyte)'4', true);
                    break;
                case System.Windows.Input.Key.Q:
                    myBridge.GetInput((sbyte)'Q', true);
                    break;
                case System.Windows.Input.Key.W:
                    myBridge.GetInput((sbyte)'W', true);
                    break;
                case System.Windows.Input.Key.E:
                    myBridge.GetInput((sbyte)'E', true);
                    break;
                case System.Windows.Input.Key.R:
                    myBridge.GetInput((sbyte)'R', true);
                    break;
                case System.Windows.Input.Key.A:
                    myBridge.GetInput((sbyte)'A', true);
                    break;
                case System.Windows.Input.Key.S:
                    myBridge.GetInput((sbyte)'S', true);
                    break;
                case System.Windows.Input.Key.D:
                    myBridge.GetInput((sbyte)'D', true);
                    break;
                case System.Windows.Input.Key.F:
                    myBridge.GetInput((sbyte)'F', true);
                    break;
                case System.Windows.Input.Key.Z:
                    myBridge.GetInput((sbyte)'Z', true);
                    break;
                case System.Windows.Input.Key.X:
                    myBridge.GetInput((sbyte)'X', true);
                    break;
                case System.Windows.Input.Key.C:
                    myBridge.GetInput((sbyte)'C', true);
                    break;
                case System.Windows.Input.Key.V:
                    myBridge.GetInput((sbyte)'V', true);
                    break;
                default:
                    break;
            }
        }

        private void KeyboardReleased(object sender, System.Windows.Input.KeyEventArgs e)
        {
            switch (e.Key)
            {
                case System.Windows.Input.Key.D1:
                    myBridge.GetInput((sbyte)'1', false);
                    break;
                case System.Windows.Input.Key.D2:
                    myBridge.GetInput((sbyte)'2', false);
                    break;
                case System.Windows.Input.Key.D3:
                    myBridge.GetInput((sbyte)'3', false);
                    break;
                case System.Windows.Input.Key.D4:
                    myBridge.GetInput((sbyte)'4', false);
                    break;
                case System.Windows.Input.Key.Q:
                    myBridge.GetInput((sbyte)'Q', false);
                    break;
                case System.Windows.Input.Key.W:
                    myBridge.GetInput((sbyte)'W', false);
                    break;
                case System.Windows.Input.Key.E:
                    myBridge.GetInput((sbyte)'E', false);
                    break;
                case System.Windows.Input.Key.R:
                    myBridge.GetInput((sbyte)'R', false);
                    break;
                case System.Windows.Input.Key.A:
                    myBridge.GetInput((sbyte)'A', false);
                    break;
                case System.Windows.Input.Key.S:
                    myBridge.GetInput((sbyte)'S', false);
                    break;
                case System.Windows.Input.Key.D:
                    myBridge.GetInput((sbyte)'D', false);
                    break;
                case System.Windows.Input.Key.F:
                    myBridge.GetInput((sbyte)'F', false);
                    break;
                case System.Windows.Input.Key.Z:
                    myBridge.GetInput((sbyte)'Z', false);
                    break;
                case System.Windows.Input.Key.X:
                    myBridge.GetInput((sbyte)'X', false);
                    break;
                case System.Windows.Input.Key.C:
                    myBridge.GetInput((sbyte)'C', false);
                    break;
                case System.Windows.Input.Key.V:
                    myBridge.GetInput((sbyte)'V', false);
                    break;
                default:
                    break;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog saveFileDialog = new OpenFileDialog();
            if (saveFileDialog.ShowDialog() == true)
            {
                myBridge.LoadRom(saveFileDialog.FileName);
            }
        }

        private void WindowClosed(object sender, EventArgs e)
        {
            myBridge.Shutdown();
        }
    }
}
