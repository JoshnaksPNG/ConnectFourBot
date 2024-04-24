using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ConnectFourBot.BotInnards
{
    internal class Board
    {
        public enum PieceType
        {
            Empty,
            Red,
            Yellow,
        }

        PieceType[,] boardPieces;

        IntPtr dllBoard;

        public Board() 
        {
            boardPieces = new PieceType[7, 6];
            dllBoard = NewBoard();
        }

        public bool DropPiece(int stack, PieceType piece)
        {
            if (piece == PieceType.Empty)
            { return false; }

            if (stack < 0 || stack > 6)
            {
                return false;
            }

            int topOfStack = 5;

            if (boardPieces[stack, topOfStack] != PieceType.Empty)
            { return false; }

            while ( topOfStack != -1 && boardPieces[stack, topOfStack] == PieceType.Empty)
            {
                --topOfStack;
            }

            boardPieces[stack, topOfStack + 1] = piece;

            BoardSetPiece(dllBoard, stack, topOfStack + 1, (int)piece);

            return true;
        }

        public override string ToString()
        {
            string str = string.Empty;

            for (int i = 5; i >= 0; --i)
            {
                for (int j = 0; j < 7; ++j)
                {
                    char piece;

                    switch (boardPieces[j, i]) 
                    {
                        case PieceType.Red:
                            piece = 'R';
                            break;

                        case PieceType.Yellow:
                            piece = 'Y';
                            break;

                        case PieceType.Empty:
                        default:
                            piece = 'O';
                            break;
                    }

                    str += piece;
                    str += "  ";
                }

                str += '\n';
            }

            return str;
        }

        public string getDllPlacement()
        {
            byte[] bytes = BoardGetPlacement(dllBoard);
            string s = "";

            foreach (byte b in bytes)
            {
                s += (char)b;
            }

            return s;
        }


        // DLL Imports
        [DllImport("botDLL.dll")]
        public static extern IntPtr NewBoard();

        [DllImport("botDLL.dll")]
        public static extern void BoardSetPiece(IntPtr b, int r, int f, int p);

        [DllImport("botDLL.dll")]
        public static extern byte[] BoardGetPlacement(IntPtr b);
    }
}
