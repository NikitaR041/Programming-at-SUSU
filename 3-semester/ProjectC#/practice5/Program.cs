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

            List<string> th_mass = new List<string>();
            List<string> td_mass = new List<string>();

            string stroka = sr.ReadLine();
            string title_stroka = string.Empty;
            string h1_title = string.Empty;
            //Console.WriteLine(stroka);
            //byte index = 0;
            //Console.WriteLine(stroka);
            //Считываем информацию из файла, пока не дошли доконца
            //while (!sr.EndOfStream)
            //{
            //    //Пробный вариант
            //    if (stroka.IndexOf("<tr>") != -1 || stroka.IndexOf("</tr>") != -1)
            //    {
            //        stroka = sr.ReadLine();
            //        continue;
            //    }
            //    else if (stroka.IndexOf("<td>") != -1)
            //    {
            //        stroka = stroka.Substring(stroka.IndexOf("<td>") + 4, stroka.LastIndexOf("</td>") - stroka.IndexOf("<td>")-4).Trim();
            //        //mass = mass.Insert(index, stroka);
            //        stroka = stroka.Trim();
            //        mass.Add(stroka);
            //        stroka = sr.ReadLine();
            //        index++;
            //    }
            //    else {
            //        continue;
            //    }
            //}

            //Пробуем обработать полностью текст
            //while(!sr.EndOfStream){
            //    if (stroka.IndexOf("<h1>") == -1 || stroka.IndexOf("<title>") == -1 || stroka.IndexOf("<th>") == -1 || stroka.IndexOf("<td>") == -1) {
            //        stroka = sr.ReadLine();
            //        continue;
            //    }
            //    //|| stroka.IndexOf("<title>") != -1 || stroka.IndexOf("<th>") != -1 || stroka.IndexOf("<td>") != -1
            //    else if (stroka.IndexOf("<title>") != -1)
            //    {
            //        title_stroka = stroka.Substring(stroka.IndexOf("<title>") + 7, stroka.LastIndexOf("/<title>") - stroka.IndexOf("<title>") - 7).Trim();
            //        stroka = sr.ReadLine();

            //    }else if (stroka.IndexOf("<h1>") != -1)
            //    {
            //        h1_title = stroka.Substring(stroka.IndexOf("<h1>") + 4, stroka.LastIndexOf("/<h1>") - stroka.IndexOf("<h1>") - 4).Trim();
            //        stroka = sr.ReadLine();

            //    }
            //    else if (stroka.IndexOf("<th>") != -1)
            //    {
            //        stroka = stroka.Substring(stroka.IndexOf("<th>") + 4, stroka.LastIndexOf("</th>") - stroka.IndexOf("<th>") - 4).Trim();
            //        //mass = mass.Insert(index, stroka);
            //        stroka = stroka.Trim();
            //        th_mass.Add(stroka);
            //        stroka = sr.ReadLine();

            //    }
            //    else if (stroka.IndexOf("<td>") != -1)
            //    {
            //        stroka = stroka.Substring(stroka.IndexOf("<td>") + 4, stroka.LastIndexOf("</td>") - stroka.IndexOf("<td>") - 4).Trim();
            //        //mass = mass.Insert(index, stroka);
            //        stroka = stroka.Trim();
            //        td_mass.Add(stroka);
            //        stroka = sr.ReadLine();
            //    }
            //}
            while (!sr.EndOfStream)
            {
                stroka = sr.ReadLine();  // Важно считать строку перед проверкой условий!

                // Проверяем наличие хотя бы одного из тегов
                if (stroka.IndexOf("<h1>") != -1 || stroka.IndexOf("<title>") != -1 || stroka.IndexOf("<th>") != -1 || stroka.IndexOf("<td>") != -1)
                {
                    // Делаем проверки для разных тегов
                    if (stroka.IndexOf("<title>") != -1)
                    {
                        title_stroka = stroka.Substring(stroka.IndexOf("<title>") + 7, stroka.LastIndexOf("</title>") - stroka.IndexOf("<title>") - 7).Trim();
                    }
                    else if (stroka.IndexOf("<h1>") != -1)
                    {
                        h1_title = stroka.Substring(stroka.IndexOf("<h1>") + 4, stroka.LastIndexOf("</h1>") - stroka.IndexOf("<h1>") - 4).Trim();
                    }
                    else if (stroka.IndexOf("<th>") != -1)
                    {
                        stroka = stroka.Substring(stroka.IndexOf("<th>") + 4, stroka.LastIndexOf("</th>") - stroka.IndexOf("<th>") - 4).Trim();
                        th_mass.Add(stroka);
                    }
                    else if (stroka.IndexOf("<td>") != -1)
                    {
                        stroka = stroka.Substring(stroka.IndexOf("<td>") + 4, stroka.LastIndexOf("</td>") - stroka.IndexOf("<td>") - 4).Trim();
                        td_mass.Add(stroka);
                    }
                }
            }


            //int h = stroka.IndexOf("<tr>");
            //Console.WriteLine(h);

            //Console.WriteLine(stroka);
            Console.WriteLine(title_stroka);
            Console.WriteLine(h1_title);

            foreach (var elem1 in th_mass)
            {
                Console.WriteLine(elem1);
            }

            foreach (var elem2 in td_mass)
            {
                Console.WriteLine(elem2);
            }

            fs.Close();
            sr.Close();
            Console.ReadKey();
        }
    }
}