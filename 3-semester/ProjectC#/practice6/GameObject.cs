using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using SharpDX.Direct3D9;

namespace practice6
{
    public class GameObject {
        //Приватные поля 
        protected Vector2 position; //Координаты
        protected Texture2D texture; //Текстура

        //Конструктор
        public GameObject(Vector2 position, Texture2D texture) {
            Position = position;
            Texture = texture;
        }
        public virtual void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(Texture, Position, Color.White);
        }
        public virtual void Update(GameTime gameTime) {

        }

        //Property
        public Vector2 Position { get; set; }
        public Texture2D Texture { get; set; }
    }
}
