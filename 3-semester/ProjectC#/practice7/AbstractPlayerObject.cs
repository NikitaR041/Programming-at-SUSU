using Microsoft.Xna.Framework;
using SharpDX.Direct2D1;

using SharpDX.Direct3D11;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

//Абстрактный класс игрового (игрока) объекта

namespace practice7
{
    abstract class AbstractPlayerObject
    {
        protected Microsoft.Xna.Framework.Vector2 position; //Координаты
        protected Microsoft.Xna.Framework.Graphics.Texture2D texture; //Загрузка текстуры
        protected Microsoft.Xna.Framework.Vector2 speed; //Скорость изменения

        protected AbstractPlayerObject(Microsoft.Xna.Framework.Vector2 position, Microsoft.Xna.Framework.Graphics.Texture2D texture, Microsoft.Xna.Framework.Vector2 speed) { 
            Position = position;
            Texture = texture;
            Speed = speed;
        }


        //Метод отрисовки
        public abstract void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch);
        //Обновление передвижения
        public abstract void Update(GameTime gameTime);

        //Properties
        public Microsoft.Xna.Framework.Vector2 Position { get; set; }
        public Microsoft.Xna.Framework.Graphics.Texture2D Texture { get; set; }
        public Microsoft.Xna.Framework.Vector2 Speed { get; set; }

        public Rectangle CollisionRectangle => new Rectangle((int)position.X, (int)position.Y, texture.Width, texture.Height); // Границы объекта
    }
}
