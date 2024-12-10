using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics.Metrics;
using System.Xml.Linq;
using Microsoft.Xna.Framework.Graphics;


//GameManager - Менеджер, который хранит в себе все игровые объекты, отрисовывает и обрабатывает столкновения если нужно.

namespace new_practice7
{
    internal class GameManager
    {
        private List<BaseObjcet> activeObjects;

        //Создаем делегат и событие
        public delegate void CollisionEventHandler(BaseObjcet obj1, BaseObjcet obj2);
        public event CollisionEventHandler CollisionDetected;

        //Для изменение направления  - нужно для ActiceObjectCollision и GameManager
        private int directionX = 1; // 1 - вправо, -1 - влево
        private int directionY = 1; //Аналогично

        public GameManager() { 
            activeObjects = new List<BaseObjcet>();
        }

        public void UpdateObject(GraphicsDevice graphicsDevice, GameTime gameTime, short speed)
        {
            foreach (var obj in activeObjects)
            {
                if (obj is ActiveObjectCollision activeCollisObject)
                {
                    activeCollisObject.UdpateObject(graphicsDevice, gameTime, speed);
                }
                else if (obj is ManageObject manageObject)
                {
                    manageObject.UdpateObject(graphicsDevice, gameTime, speed);
                }
                else if (obj is ActiveObject activeBackObj) {
                    activeBackObj.UdpateObject(graphicsDevice, gameTime, speed);
                }
            }

            CheckCollision();
        }

        public void CheckCollision()
        {
            if (activeObjects.Count < 2)
                return; // Не хватает объектов для проверки столкновений.

            // Первый объект в списке — управляемый.
            var obj1 = activeObjects[0];

            // Остальные объекты — подвижные.
            for (int i = 1; i < activeObjects.Count; i++)
            {
                var obj2 = activeObjects[i];

                // Проверка на пересечение границ объектов.
                bool isColliding =
                    obj1.Position.X < obj2.Position.X + obj2.Texture.Width &&
                    obj1.Position.X + obj1.Texture.Width > obj2.Position.X &&
                    obj1.Position.Y < obj2.Position.Y + obj2.Texture.Height &&
                    obj1.Position.Y + obj1.Texture.Height > obj2.Position.Y;

                if (isColliding)
                {
                    //При столкновении вызываем событие
                    CollisionDetected?.Invoke(obj1, obj2);

                    obj2.Position = new Vector2(
                        obj2.Position.X + (obj2.Position.X - obj1.Position.X),
                        obj2.Position.Y + (obj2.Position.Y - obj1.Position.Y) 
                    );
                }
            }
        }

        public void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch _spriteObj) {
            foreach (var obj in activeObjects)
                obj.Draw(_spriteObj);
        }

        //Добавление объекта
        public void AddObject(BaseObjcet obj) => activeObjects.Add(obj);
        //Получение списка объектов
        public List<BaseObjcet> GetObjects() => activeObjects;
    }
}
