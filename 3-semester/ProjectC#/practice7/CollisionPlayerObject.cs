using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//Дочерний класс абстрактного-родительского класса AbstractPlayerObject

namespace practice7
{
    internal class CollisionPlayerObject : AbstractPlayerObject
    {
        public CollisionPlayerObject(Vector2 position, Texture2D texture, Vector2 speed) : base(position, texture, speed) {}

        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(Texture, Position, Color.White);
        }

        public override void Update(GameTime gameTime)
        {
            // Проверяем границы экрана
            int screenWidth = 1580;
            int screenHeight = 960;

            // Используем время для плавного движения
            //Position += Speed * (float)gameTime.ElapsedGameTime.TotalSeconds;

            Position += Speed * 5;

            if (Position.X < 0 || Position.X + Texture.Width > screenWidth)
            {
                Speed = new Vector2(-Speed.X, Speed.Y); // Меняем направление по X
            }

            if (Position.Y < 0 || Position.Y + Texture.Height > screenHeight)
            {
                Speed = new Vector2(Speed.X, -Speed.Y); // Меняем направление по Y
            }
        }
    }
}
