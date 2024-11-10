using System;
using System.IO;
using System.Reflection.Metadata.Ecma335;
using System.Security.AccessControl;

namespace AIS 
{
    class Programm{
        static void Main()
        {
            FileStream fs = new FileStream("Example.txt", FileMode.Open);
            StreamReader sr = new StreamReader(fs);

            List<string> mass = new List<string>();
            string stroka = sr.ReadLine();

            //Console.WriteLine(stroka);
            byte index = 0;
            //Console.WriteLine(stroka);
            //Считываем информацию из файла, пока не дошли доконца
            while (!sr.EndOfStream)
            {
                //Пробный вариант
                if (stroka.IndexOf("<tr>") != -1 || stroka.IndexOf("</tr>") != -1)
                {
                    stroka = sr.ReadLine();
                    continue;
                }
                else if (stroka.IndexOf("<td>") != -1)
                {
                    stroka = stroka.Substring(stroka.IndexOf("<td>") + 4, stroka.LastIndexOf("</td>") - stroka.IndexOf("<td>")-4).Trim();
                    //mass = mass.Insert(index, stroka);
                    stroka = stroka.Trim();
                    mass.Add(stroka);
                    stroka = sr.ReadLine();
                    index++;
                }
                else {
                    continue;
                }
            }

            //int h = stroka.IndexOf("<tr>");
            //Console.WriteLine(h);

            //Console.WriteLine(stroka);
            foreach (var elem in mass) {
                Console.WriteLine(elem);
            }

            fs.Close();
            sr.Close();
            Console.ReadKey();
        }
    }
}