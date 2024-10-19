using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    abstract class TypeTank
    {
        //Общие особенности у всех танков
        protected string name; //Название танка
        protected string weapon; //Название орудия
        protected string country; //Страна производства танка
        protected byte speed; //Скорость танка
        protected int price; //Стоимость танка

        protected TypeTank(string name, string weapon, string country, byte speed, int price)
        {
            this.name = name;
            this.weapon = weapon;
            this.country = country;
            this.speed = speed;
            this.price = price;
        }

        //Создаем аксессор для дочерних классов
        //Не можем задавать значение к полю 
        public string Name { get { return this.name; } }

        public string Weapon { get { return this.weapon; } }

        public string Country { get { return this.country; } }

        public int Speed { get { return this.speed; } }

        public int Price { get { return this.price; } }

    }   
}
