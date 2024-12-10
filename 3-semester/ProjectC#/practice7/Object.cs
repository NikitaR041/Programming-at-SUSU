using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
//using SharpDX.Direct3D11;
using SharpDX.Direct3D9;
using System;
using System.Collections.Generic;
//using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

//Это обобщенный класс, от которого будут наследоваться подвижные и управляемые объекты

namespace new_practice7
{
    internal class Object
    {

        protected Texture2D texture; // Загрузка текстуры
        protected Microsoft.Xna.Framework.Vector2 position; // Местоположение
        protected Microsoft.Xna.Framework.Rectangle bound; //Размер прямоугольник - коллизия 
        public Object(Texture2D texture, Microsoft.Xna.Framework.Vector2 position, Microsoft.Xna.Framework.Rectangle bound)
        {
            Position = position;
            Texture = texture;
            //Задаем прямоугольник - спрайт коллизии
            Bound = new Microsoft.Xna.Framework.Rectangle((int)position.X, (int)position.Y, texture.Width, texture.Height);
        }
        //Property
        public Microsoft.Xna.Framework.Vector2 Position { get; set; }
        public Texture2D Texture { get; set; }

        public virtual void UdpateObject(GraphicsDevice graphicsDevice, GameTime gameTime, short speed) { }
        public Microsoft.Xna.Framework.Rectangle Bound { get { return new Microsoft.Xna.Framework.Rectangle((int)position.X, (int)position.Y, texture.Width, texture.Height); } set { } }
    }
}
