using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System;


namespace new_practice7
{
    internal class ActiveObject : BaseObjcet
    {
        public ActiveObject(Texture2D texture, Microsoft.Xna.Framework.Vector2 position, Microsoft.Xna.Framework.Rectangle bound) : base(texture, position, bound) {}

        //Частный метод - метод для передвижения фона
        public void MovementBack(GraphicsDevice graphicsDevice, GameTime gameTime, short speed) {
            int screenWidth = graphicsDevice.Viewport.Width;
            Position += new Vector2(position.X - speed, position.Y);

            if (Position.X + Bound.Width <= 0)
            {
                Position = new Vector2(Position.X + Texture.Width, Position.Y);
            }
        }

        //Рисование объекта
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch) {
            spriteBatch.Draw(Texture, Position, Color.White);
            spriteBatch.Draw(Texture, new Vector2(Position.X + Texture.Width, Position.Y), Color.White); //Вторая повторная картинка
        }
    }
}
