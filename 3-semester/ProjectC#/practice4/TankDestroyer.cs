using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class TankDestroyer : TypeTank
    {
        //TankDestroyer - ПТ-САУ, которые не имеют башни и поворачиваются только корпусом
        private byte add_speed_chassis; //Буст к повороту корпуса танка
        private byte angle_weapon; //Угол поднятия/опускания орудия

        public TankDestroyer(string name, string weapon, string country, byte speed, int price, byte add_speed_chassis, byte angle_weapon) : base(name, weapon, country, speed, price) {
            this.add_speed_chassis = add_speed_chassis;
            this.angle_weapon = angle_weapon;
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
                $"Дополнительная скорость поворота корпуса: {add_speed_chassis} км/ч",
                $"Дополнительный угол поднятия/опуская орудия: {angle_weapon} единиц",
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
