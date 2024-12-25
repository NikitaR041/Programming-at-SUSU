using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using SharpDX.Direct2D1;
using SharpDX.Direct2D1.Effects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace practice8
{
    class LightCircle
    {
        //Поля - координаты, яркость, цвет, длину отдачи и фокукс
        private Vector2 coords; // Координаты света
        private float brightness; //Яркость пятна
        private float focus; //Ширина фокуса | угол распространения
        private Texture2D texture; //Тексутра пятна
        private Color color; // Цвет пятна

        private int directionX = 1; // 1 - вправо, -1 - влево
        private int directionY = 1; //Аналогично

        public LightCircle(Vector2 coords, float brightness, float focus, Texture2D texture, Color color) 
        {
            this.coords = coords;
            this.brightness = brightness;
            this.focus = focus;
            this.texture = texture;
            this.color = color;
        }

        //Отображение на текстуры/спрайта на экране
        public void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch _spriteBatch) {
            //Перегрузка метода Draw
            _spriteBatch.Draw(
                Texture,
                Coords,
                null,
                Ccolor * Brightness,
                0f,
                new Vector2(texture.Width / 2, texture.Height / 2),
                new Vector2(focus, focus),
                SpriteEffects.None,
                0f
             );
        }

        //Метод передвижения объектов
        public void MovementObj(GraphicsDevice graphicsDevice, int speed)
        {
            int screenWidth = graphicsDevice.Viewport.Width;
            int screenHeight = graphicsDevice.Viewport.Height;

            // Проверка, чтобы размер текстуры не превышал размеры экрана
            int maxX = Math.Max(0, screenWidth - Texture.Width);
            int maxY = Math.Max(0, screenHeight - Texture.Height);

            // Обновляем позицию объекта
            Coords += new Vector2(directionX * speed, directionY * speed);

            // Если объект касается границы экрана по X
            if (Coords.X + Texture.Width > screenWidth || Coords.X < 0)
            {
                // Инвертируем направление движения
                directionX *= -1;

                // Корректируем позицию
                Coords = new Vector2(
                    Math.Clamp(Coords.X, 0, maxX),
                    Coords.Y
                );
            }

            if (Coords.Y + Texture.Height > screenHeight || Coords.Y < 0)
            {
                // Инвертируем направление движения
                directionY *= -1;

                // Корректируем позицию
                Coords = new Vector2(
                    Coords.X,
                    Math.Clamp(Coords.Y, 0, maxY)
                );
            }

            //Math.Clamp - проверяет не выходит ли объект за границы окна
        }

        //Обновление объекта
        public void UpdateObject(GraphicsDevice graphicsDevice, GameTime gameTime, int speed)
        {
            MovementObj(graphicsDevice, speed);
        }


        //Аксессоры
        public Vector2 Coords { get => coords; set => coords = value; }
        public float Brightness { get => brightness; set => brightness = value; }
        public float Focus { get => focus; set => focus = value; }
        public Texture2D Texture { get => texture; }
        public Color Ccolor { get => color; set => color = value; }
    }
}
