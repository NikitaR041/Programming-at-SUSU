using System;
using System.IO;
using System.Security.AccessControl;

class Program {
    //Пробуем метод, который считывает важную информацию из <td> и <\td> в двумерный список
    static void SearchText(List<List<string>> obj1, StreamReader obj2)
    {
        //Пробуем построчно считать
        string line;
        int index = 0;
        while (true) {
            line = obj2.ReadLine();
            if (!string.IsNullOrEmpty(line) && line[0] == '<' && line[line.Length - 1] == '>')
            {
                continue;
            }
            else {
                obj1[index].Add(line);
                index++;
            }
        }

    }
    static void Main() {
        FileStream fs = new FileStream("Example.txt", FileMode.Open);
        StreamReader fsr = new StreamReader(fs);

        List<List<string>> importantElements = new List<List<string>>();

        SearchText(importantElements, fsr);

        foreach (var elem in importantElements) { 
        
            }
        
        
        fsr.Close();
        fs.Close();
        Console.ReadKey();
    }
}