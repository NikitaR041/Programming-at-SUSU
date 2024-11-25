using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace practice6
{
    public class ControlObject : ActiveGameObject
    {
        public ControlObject(Vector2 position, Texture2D texture, Vector2 speed) : base(position, texture, speed){}

        //Переопределили Udpate для передвижения объектов класса ActiveGameObject
        public override void Update(GameTime gameTime)
        {
            // Получаем текущее состояние клавиатуры
            KeyboardState ks = Keyboard.GetState();

            // Проверяем, какие клавиши нажаты, и изменяем координаты
            if (ks.IsKeyDown(Keys.Left))
                Position = new Vector2(Position.X - Speed.X, Position.Y);
            if (ks.IsKeyDown(Keys.Right))
                Position = new Vector2(Position.X + Speed.X, Position.Y);
            if (ks.IsKeyDown(Keys.Up))
                Position = new Vector2(Position.X, Position.Y - Speed.Y);
            if (ks.IsKeyDown(Keys.Down))
                Position = new Vector2(Position.X, Position.Y + Speed.Y);
        }
    }
}
