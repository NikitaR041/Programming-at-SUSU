using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace new_practice7
{
    internal class ActiveObjectCollision : BaseObjcet
    {
        public ActiveObjectCollision(Texture2D texture, Microsoft.Xna.Framework.Vector2 position, Microsoft.Xna.Framework.Rectangle bound) : base(texture, position, bound)
        {
        }

        //Для изменение направления  - нужно для ActiceObjectCollision и GameManager
        protected int directionX = 1; // 1 - вправо, -1 - влево
        protected int directionY = 1; //Аналогично


        //Простой метод по передвижению объектов

        public void MovementObj(GraphicsDevice graphicsDevice, int speed)
        {
            int screenWidth = graphicsDevice.Viewport.Width;
            int screenHeight = graphicsDevice.Viewport.Height;

            // Обновляем позицию объекта
            Position += new Vector2(directionX * speed, directionY * speed);

            // Если объект касается границы экрана по X
            if (Position.X + Texture.Width > screenWidth || Position.X < 0)
            {
                // Инвертируем направление движения
                directionX *= -1;

                // Корректируем позицию, чтобы не выходил за экран
                Position = new Vector2(
                    Math.Clamp(Position.X, 0, screenWidth - Texture.Width),
                    Position.Y
                );
            }

            if (Position.Y + Texture.Height > screenHeight || Position.Y < 0)
            {
                // Инвертируем направление движения по Y
                directionY *= -1;

                // Корректируем позицию по Y
                Position = new Vector2(
                    Position.X, // X остаётся неизменным
                    Math.Clamp(Position.Y, 0, screenHeight - Texture.Height)
                );
            }

            //Math.Clamp - проверяет не выходит ли объект за границы окна?
        }

        // Метод для изменения направления (при столкновении)
        public void ChangeDirection()
        {
            // Простейшая логика инвертирования направления (можно улучшить)
            Position = new Vector2(-Position.X, -Position.Y);
        }

        //Рисование объекта
        public override void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(Texture, Position, Color.White);
        }

        //Обновление объекта
        public override void UdpateObject(GraphicsDevice graphicsDevice, GameTime gameTime, short speed)
        {
            MovementObj(graphicsDevice, speed);
        }

    }
}
