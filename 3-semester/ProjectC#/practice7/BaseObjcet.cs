using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace new_practice7
{
    internal class BaseObjcet
    {

        protected Texture2D texture; // Загрузка текстуры
        protected Microsoft.Xna.Framework.Vector2 position; // Местоположение
        protected Microsoft.Xna.Framework.Rectangle bound; //Размер прямоугольник - коллизия 
        public BaseObjcet(Texture2D texture, Microsoft.Xna.Framework.Vector2 position, Microsoft.Xna.Framework.Rectangle bound)
        {
            Position = position;
            Texture = texture;
            //Задаем прямоугольник - спрайт коллизии
            Bound = new Microsoft.Xna.Framework.Rectangle((int)position.X, (int)position.Y, Texture.Width, Texture.Height);
        }
        //Property
        public Microsoft.Xna.Framework.Vector2 Position { get; set; }
        public Texture2D Texture { get; set; }
        public Microsoft.Xna.Framework.Rectangle Bound { get { return new Microsoft.Xna.Framework.Rectangle((int)position.X, (int)position.Y, Texture.Width, Texture.Height); } set { } }


        // Направление движения объекта
        public float DirectionX { get; set; } = 1; // По оси X (1 — вправо, -1 — влево)
        public float DirectionY { get; set; } = 1; // По оси Y (1 — вниз, -1 — вверх)

        public virtual void UdpateObject(GraphicsDevice graphicsDevice, GameTime gameTime, short speed) { }

        public virtual void Draw(SpriteBatch spriteBatch) {
            spriteBatch.Draw(Texture, Position, Color.White);
        }

    }
}
