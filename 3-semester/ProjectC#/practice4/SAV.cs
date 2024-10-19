using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class SAV : TypeTank
    {
        //SAV - это танки типа САУ, отличные от ПТ-САУ
        private byte angle_vision; // Угол обзора и дальность обзора 
        private byte add_speed_chassis; //Буст к повороту корпуса танка
        public SAV(string name, string weapon, string country, byte speed, int price, byte angle_vision, byte add_speed_chassis) : base(name, country, country, speed, price)
        {
            this.angle_vision = angle_vision;
            this.add_speed_chassis = add_speed_chassis;
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
                $"Угол и дальность обзора: {angle_vision} единиц",
                $"Дополнительная скорость поворота корпуса: {add_speed_chassis} км/ч",
                $"Стоимость танка: {Price}"
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
