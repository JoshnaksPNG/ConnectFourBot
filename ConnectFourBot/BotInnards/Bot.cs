using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.ComponentModel;

namespace ConnectFourBot.BotInnards
{
    internal class Bot
    {
        [DllImport("botDLL.dll")]
        public static extern IntPtr Create(int x);


        IntPtr internalBot;

        public Bot(int x)
        {
            internalBot = Create(x);
        }

    }
}
