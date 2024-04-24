// See https://aka.ms/new-console-template for more information
using ConnectFourBot.BotInnards;

Console.WriteLine("Hello, World!");

Board board = new Board();

board.DropPiece(0, Board.PieceType.Red);
board.DropPiece(0, Board.PieceType.Red);
board.DropPiece(0, Board.PieceType.Red);

board.DropPiece(1, Board.PieceType.Red);
board.DropPiece(1, Board.PieceType.Yellow);
board.DropPiece(1, Board.PieceType.Red);
board.DropPiece(1, Board.PieceType.Yellow);

board.DropPiece(2, Board.PieceType.Yellow);
board.DropPiece(2, Board.PieceType.Red);
board.DropPiece(2, Board.PieceType.Yellow);
board.DropPiece(2, Board.PieceType.Red);

board.DropPiece(3, Board.PieceType.Yellow);
board.DropPiece(3, Board.PieceType.Yellow);
board.DropPiece(3, Board.PieceType.Yellow);

Console.WriteLine(board.ToString());

Bot bot = new Bot(10);

Console.WriteLine(bot.add(9));

//string dllshit = board.getDllPlacement();

//Console.WriteLine(dllshit);

//string shitter = board.getDllPlacement();