﻿using System;
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
        private static extern IntPtr NewBot();

        [DllImport("botDLL.dll")]
        private static extern int SuggestColumn(IntPtr bot);


        IntPtr internalBot;

        public Bot()
        {
            internalBot = NewBot();
        }

        public int suggestColumn()
        {
            return SuggestColumn(internalBot);
        }

        
    }
}
