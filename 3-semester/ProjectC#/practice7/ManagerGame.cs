using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

//Менеджер игры - Менеджер, который хранит в себе все игровые объекты, отрисовывает и обрабатывает столкновения если нужно.
//Обработка информации - это столкновение двух объектов, т.е. передаем информацию о двух объектах 

namespace practice7
{
    class GameManager
    {
        private List<AbstractPlayerObject> objects = new();

        //CollisionEventHandler "Издатель"
        public delegate void CollisionEventHandler(object sender, CollisionEventArgs e);       
        public event CollisionEventHandler OnCollision;

        public void AddObject(AbstractPlayerObject obj)
        {
            objects.Add(obj);
        }

        public void Update(GameTime gameTime)
        {
            foreach (var obj in objects)
                obj.Update(gameTime);

            CheckCollisions();
        }

        public void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch)
        {
            foreach (var obj in objects)
                obj.Draw(spriteBatch);
        }

        private void CheckCollisions()
        {
            for (int i = 0; i < objects.Count; i++)
            {
                for (int j = i + 1; j < objects.Count; j++)
                {
                    if (objects[i].CollisionRectangle.Intersects(objects[j].CollisionRectangle))
                    {
                        OnCollision?.Invoke(this, new CollisionEventArgs(objects[i], objects[j]));
                    }
                }
            }
        }
    }

    //Класс, который обрабатывает события о двух экземлпяров
    class CollisionEventArgs : EventArgs
    {
        public AbstractPlayerObject ObjectA { get; }
        public AbstractPlayerObject ObjectB { get; }

        public CollisionEventArgs(AbstractPlayerObject objectA, AbstractPlayerObject objectB)
        {
            ObjectA = objectA;
            ObjectB = objectB;
        }
    }
}
