using System;
using System.Buffers;
using System.IO;
using System.Reflection.Metadata.Ecma335;
using System.Security.AccessControl;

namespace AIS 
{
    class Programm 
    {
        static void Main()
        {
            bool isworking = true;
            byte index = 0;
            FileStream fs = new FileStream("Example2.txt", FileMode.Open);
            StreamReader sr = new StreamReader(fs);

            List<AudioSpeaker> speakerList = new List<AudioSpeaker>(); //Создаем список объектов!
            ConsoleInterface process_console =  new ConsoleInterface(); // Создаем обработчик файла 
            //Сначала считываем файл и обработаем его
            process_console.ReadFile(sr, speakerList);

            //Затем изображаем интерфейс
            while (isworking)
            {
                index = ConsoleInterface.SelectMenuItem(50, 10, speakerList);
                ConsoleInterface.SearchValue(index, speakerList);
            }
            
            fs.Close();
            sr.Close();
            Console.ReadKey();
        }
    }
}