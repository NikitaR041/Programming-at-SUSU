using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class HeavyTank : TypeTank
    {
        //У тяжелых танков можно применить буст к скорости, чтобы передвигаться быстрее
        private byte add_speed;

        public HeavyTank(string name, string weapon, string country, byte speed, int price, byte add_speed) : base(name, weapon, country, speed, price) {
            this.add_speed = add_speed;
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
                $"Дополнительная скорость: {add_speed} км/ч",
                $"Стоимость танка: {Price}  единиц"
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
