using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


class Fertilization
{
    
    static void PrintAtPosition(int x, int y, string symbol, ConsoleColor color)
    {
        Console.SetCursorPosition(x, y);
        Console.ForegroundColor = color;
        Console.Write(symbol);
    }

    static void PrintStringAtPosition(int x, int y, string text, ConsoleColor color)
    {
        Console.SetCursorPosition(x, y);
        Console.ForegroundColor = color;
        Console.WriteLine(text);
    }

    struct Elements
    {
        public int x;
        public int y;
        public ConsoleColor color;
        public string symbol;
        public Elements(int x, int y, ConsoleColor color, string symbol)
        {
            this.x = x;
            this.y = y;
            this.color = color;
            this.symbol = symbol;
        }
    }

    static void Main()
    {
        Console.BufferHeight = Console.WindowHeight = 40;
        Console.BufferWidth = Console.WindowWidth = 80;

        List<Elements> Contraceptions = new List<Elements>();
        Random randomGenerator = new Random();
        int effectiveness = 100;
        int speed = 0;
        int score = 0;

        // defining spermatozoid
        Elements spermatozoid = new Elements();
        spermatozoid.x = (Console.WindowWidth / 2) - 1;
        spermatozoid.y = Console.WindowHeight - 2;
        spermatozoid.color = ConsoleColor.White;
        spermatozoid.symbol = "?";

        // defining the walls
        Elements[] firstWall = new Elements[Console.WindowHeight - 6];
        for (int i = 0; i < Console.WindowHeight - 6; i++)
        {
            firstWall[i] = new Elements(i + 6, Console.WindowWidth / 2 - 10, ConsoleColor.Red, "*");
        }
        //foreach (Elements element in firstWall)
        //{
        //    Console.SetCursorPosition(element.y, element.x);
        //    Console.ForegroundColor = element.color;
        //    Console.Write(element.symbol);
        //}

        Elements[] secondWall = new Elements[Console.WindowHeight - 6];
        for (int i = 0; i < Console.WindowHeight - 6; i++)
        {
            secondWall[i] = new Elements(i + 6, Console.WindowWidth / 2 + 10, ConsoleColor.Red, "*");
        }
        //foreach (Elements element in secondWall)
        //{
        //    Console.SetCursorPosition(element.y, element.x);
        //    Console.ForegroundColor = element.color;
        //    Console.Write(element.symbol);
        //}

        while (true)
        {
            bool hitTheWall = false;

            // defining the obstacles/contraceptions
            Elements contraception = new Elements();
            contraception.x = randomGenerator.Next(Console.WindowWidth / 2 - 10, Console.WindowWidth / 2 + 10);
            contraception.y = 6;
            contraception.color = ConsoleColor.Yellow;
            contraception.symbol = "X";

            Contraceptions.Add(contraception);

            int plus = randomGenerator.Next(-1, 2);

            // moving the first wall
            for (int i = firstWall.Length - 1; i > 0; i--)
            {
                firstWall[i].y = firstWall[i - 1].y;
            }
            do
            {
                firstWall[0].y = firstWall[1].y + plus;
            }
            while (firstWall[0].y < 0);

            // moving the second wall
            for (int i = secondWall.Length - 1 ; i > 0; i--)
            {
                secondWall[i].y = secondWall[i - 1].y;
            }
            do
            {
                secondWall[0].y = secondWall[1].y + plus;
            }
            while (secondWall[0].y > Console.WindowWidth);

            // drawing the walls
            foreach (Elements element in firstWall)
            {
                Console.SetCursorPosition(element.y, element.x);
                Console.ForegroundColor = element.color;
                Console.Write(element.symbol);
            }

            foreach (Elements element in secondWall)
            {
                Console.SetCursorPosition(element.y, element.x);
                Console.ForegroundColor = element.color;
                Console.Write(element.symbol);
            }

            PrintAtPosition(spermatozoid.x, spermatozoid.y, spermatozoid.symbol, spermatozoid.color);
            // moving the spermatozoid
            if (Console.KeyAvailable)
            {
                ConsoleKeyInfo keyPressed = Console.ReadKey(true);
                while (Console.KeyAvailable)
                {
                    Console.ReadKey(true);
                }
                if (keyPressed.Key == ConsoleKey.LeftArrow)
                {
                    if (spermatozoid.x > firstWall[firstWall.Length - 1].x)
                    {
                        spermatozoid.x--;
                    }
                    else
                    {
                        Console.Clear();
                        PrintStringAtPosition(Console.WindowWidth / 2, Console.WindowHeight / 2 - 5, "GAME OVER", ConsoleColor.Red);
                        PrintStringAtPosition(Console.WindowWidth / 2 - 1, Console.WindowHeight / 2 - 5, "Press [enter] to continue", ConsoleColor.Red);
                        Console.ReadLine();
                        break;
                    }
                }
                if (keyPressed.Key == ConsoleKey.RightArrow)
                {
                    if (spermatozoid.x < secondWall[secondWall.Length - 1].x)
                    {
                        spermatozoid.x++;
                    }
                    else
                    {
                        Console.Clear();
                        PrintStringAtPosition(Console.WindowWidth / 2, Console.WindowHeight / 2 - 5, "GAME OVER", ConsoleColor.Red);
                        PrintStringAtPosition(Console.WindowWidth / 2 - 1, Console.WindowHeight / 2 - 5, "Press [enter] to continue", ConsoleColor.Red);
                        Console.ReadLine();
                        break;
                    }
                }
            }

            //Console.Clear();
            //Thread.Sleep(500);

            // drawing effectiveness, speed and score
            for (int i = 0; i < Console.WindowWidth; i++) 
            {
                PrintAtPosition(i, 5, "_", ConsoleColor.Gray);
            }
            PrintStringAtPosition(10, 2, "Effectiveness: " + effectiveness, ConsoleColor.Green);
            PrintStringAtPosition(20, 2, "Speed: " + speed, ConsoleColor.Green);
            PrintStringAtPosition(20, 3, "Score: " + score, ConsoleColor.Magenta);



        }
    }
}
