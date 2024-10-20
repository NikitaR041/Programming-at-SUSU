using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class LightTank : TypeTank
    {
        private string camouflage; //У легких танков может быть цвет камуфляжа

        public LightTank(string name, string weapon, string country, byte speed, int price, string camouflage) : base(name, weapon, country, speed, price)
        {
            this.camouflage = camouflage;
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
                $"Цвет камуфляжа: {camouflage}",
                $"Стоимость танка: {Price} единиц"
            };

            int top = Console.WindowHeight / 2 - lines.Length / 2;

            for (byte i = 0; i < lines.Length; i++)
            {
                int left = (Console.WindowWidth - lines[i].Length) / 2;
                Console.SetCursorPosition(left, top + i);
                Console.WriteLine(lines[i]);
            }
        }
    }
}
