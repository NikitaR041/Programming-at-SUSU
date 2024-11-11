using System;
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
            FileStream fs = new FileStream("Example.txt", FileMode.Open);
            StreamReader sr = new StreamReader(fs);

            List<AudioSpeaker> speakerList = new List<AudioSpeaker>(); //Создаем список объектов!
            ConsoleInterface process_console =  new ConsoleInterface(); // Создаем обработчик файла 
            //Сначала считываем файл и обработаем его
            process_console.read_files(sr, speakerList);

            while (isworking) { 
                
            }
            
            

            fs.Close();
            sr.Close();
            Console.ReadKey();
        }
    }
}