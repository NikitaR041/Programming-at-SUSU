using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class MediumTank : TypeTank
    {
        //У средних танков можно дополнять прочности при помощи бронелистов
        private byte count_armor_plate;
        public MediumTank(string name, string weapon, string country, byte speed, int price, byte count_armor_plate) : base(name, weapon, country, speed, price){
            this.count_armor_plate = count_armor_plate;
        }

        public void AboutTank()
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Green;

            // Вывод по центру
            string[] lines = {
                $"Страна производства танка: {Country}",
                $"Название танка: {Name}",
                $"Тип орудия: {Weapon}",
                $"Средняя скорость: {Speed} км/ч",
                $"Количество бронелистов: {count_armor_plate} единиц",
                $"Стоимость танка: {Price} единиц"
            };

            int top = Console.WindowHeight / 2 - lines.Length / 2;

            for (int i = 0; i < lines.Length; i++)
            {
                int left = (Console.WindowWidth - lines[i].Length) / 2;
                Console.SetCursorPosition(left, top + i);
                Console.WriteLine(lines[i]);
            }
        }
    }
}
