using System;
using Microsoft.Xna.Framework;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Подписчик (Обработчик) столкновений – выдаёт реакцию на столкновение
//столкнувшиеся объекты  могут «замереть», «пропасть», «улететь в другую строну», «разделиться на мелкие», «свой вариант”
//– главное чтобы эффект был визуально заметен.

namespace practice7
{
    internal class SubscriberHandler
    {
        private GameManager gameManager;

        public SubscriberHandler(GameManager manager)
        {
            gameManager = manager;

            // Подписываемся на событие столкновения
            gameManager.OnCollision += HandleCollision;
        }

        // Реакция на событие "Столкновение"
        private void HandleCollision(object sender, CollisionEventArgs e)
        {
            Console.WriteLine($"Объекты столкнулись: {e.ObjectA} и {e.ObjectB}");

            // Реализуем эффект "замирание"
            e.ObjectA.Speed = Vector2.Zero;
            e.ObjectB.Speed = Vector2.Zero;

        }
    }
}
