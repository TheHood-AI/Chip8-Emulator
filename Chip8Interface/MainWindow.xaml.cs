using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using Chip8Bridge;

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
    }
}
