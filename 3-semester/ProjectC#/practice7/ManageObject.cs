using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System;


namespace new_practice7
{
    internal class ManageObject : BaseObjcet
    {
        public ManageObject(Texture2D texture, Microsoft.Xna.Framework.Vector2 position, Microsoft.Xna.Framework.Rectangle bound) : base(texture, position, bound) {}

        //Метод по передвижению объекта с клавиатуры
        public void KeyManage(GameTime gameTime, short speed)
        {
            // Получаем текущее состояние клавиатуры
            KeyboardState ks = Keyboard.GetState();

            // Проверяем, какие клавиши нажаты, и изменяем координаты
            if (ks.IsKeyDown(Keys.Left))
                Position = new Microsoft.Xna.Framework.Vector2(Position.X - speed, Position.Y);
            if (ks.IsKeyDown(Keys.Right))
                Position = new Microsoft.Xna.Framework.Vector2(Position.X + speed, Position.Y);
            if (ks.IsKeyDown(Keys.Up))
                Position = new Microsoft.Xna.Framework.Vector2(Position.X, Position.Y - speed);
            if (ks.IsKeyDown(Keys.Down))
                Position = new Microsoft.Xna.Framework.Vector2(Position.X, Position.Y + speed);
        }

        // Метод для получения направления движения
        public Microsoft.Xna.Framework.Vector2 GetVelocity()
        {
            return new Microsoft.Xna.Framework.Vector2(Position.X * 2, Position.Y * 2); // Пример направления
        }

        //Рисование оюъекта
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(Texture, Position, Color.White);
        }

        //Обновление объекта
        public override void UdpateObject(GraphicsDevice graphicsDevice, GameTime gameTime, short speed)
        {
            KeyManage(gameTime, speed);
        }
    }
}
