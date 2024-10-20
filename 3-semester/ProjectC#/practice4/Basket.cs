using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class Basket
    {
        //Динамическая память, в котором хранятся объекты танков - корзина
        private List<TypeTank> elem = new List<TypeTank>();
        private bool IsEmpty = false; //Проверка, что д.п. пуста

        //Дальше реализация управления с паматью

        //Добавление в танка в корзину
        public void AddInBasket(TypeTank tank) {
            elem.Add(tank);
            IsEmpty = true;
            Console.WriteLine($"Ваш танк {tank.Name} добавлен в корзину!");
        }

        //Удаление танка из корзины
        public void DeleteInBasket(TypeTank tank) {
            if (IsEmpty == true) 
            {
                elem.Remove(tank);
                Console.WriteLine($"Ваш танк {tank.Name} удален из корзины!");
            }
            else {
                Console.WriteLine($"Нет такого танка {tank.Name} из корзины!");
            }
        }

        //Просмотр выбранного танка 
        public void ShowElemInBasket() {
            if (IsEmpty == false)
            {
                Console.WriteLine("Ваша корзина пуста!");
            }
            else {
                Console.WriteLine("Ваша корзина:");
                foreach (TypeTank tank in elem)
                {
                    Console.WriteLine($"Танк {tank.Name} - его цена {tank.Price} единиц");
                }
            }
        }

        //Получение цены от танка
        public void GetElemPrice() {
            int total = 0;
            foreach (var item in elem)
            {
                total += item.Price;
            }
            Console.WriteLine($"Ваша конечная цена: {total}");
        }
    }
}
