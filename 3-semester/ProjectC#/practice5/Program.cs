using System;
using System.IO;
using System.Security.AccessControl;

namespace AIS 
{
    class Programm{
        static void Main()
        {
            string path = "Example.txt";  // путь к файлу
            string content = File.ReadAllText(path); // Считать всё содержимое в одну строку
            Console.WriteLine(content);

            // или считать построчно
            string[] lines = File.ReadAllLines(path);
            foreach (var line in lines)
            {
                Console.WriteLine(line);
            }
            //fsr.Close();    
            //fs.Close();
            Console.ReadKey();
        }
    }
}