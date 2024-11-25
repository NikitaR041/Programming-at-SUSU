using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace practice6
{
    public class ActiveGameObject : GameObject
    {
        protected Vector2 speed; //Скорость
        public ActiveGameObject(Vector2 position, Texture2D texture, Vector2 speed) : base(position, texture)
        {
            Speed = speed;
        }

        //Переопределяем из базового класса метод Update
        public override void Update(GameTime gameTime)
        {
            // Проверяем границы экрана
            int screenWidth = 1580; 
            int screenHeight = 960; 

            Position += Speed*5;

            if (Position.X < 0 || Position.X + Texture.Width > screenWidth)
            {
                Speed = new Vector2(-Speed.X, Speed.Y); // Меняем направление по X
            }

            if (Position.Y < 0 || Position.Y + Texture.Height > screenHeight)
            {
                Speed = new Vector2(Speed.X, -Speed.Y); // Меняем направление по Y
            }

        }

        //Property
        public Vector2 Speed { get; set; }
    }
}
