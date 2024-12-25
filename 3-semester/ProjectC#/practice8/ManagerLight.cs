using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics.Metrics;
using System.Xml.Linq;
using Microsoft.Xna.Framework.Graphics;

namespace practice8
{
    class ManagerLight
    {
        private List<LightCircle> lightCircles; //Список таких экземпляров

        public ManagerLight() {
           lightCircles = new List<LightCircle>();
        }

        //Добавление экземпляра в список
        public void AddLightCircle(LightCircle lightCircle) => lightCircles.Add(lightCircle);

        //Удаление экземпляра из списка
        public void RemoveLightCircle(LightCircle lightCircle) => lightCircles.Remove(lightCircle);

        //Обновление передвижения
        public void UpdateObject(GraphicsDevice graphicsDevice, GameTime gameTime, int speed)
        {
            foreach (var obj in lightCircles)
            {
                obj.UpdateObject(graphicsDevice, gameTime, speed);
            }
        }

        //Отображение светового пятна на дисплее
        public void Draw(Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch)
        {
            spriteBatch.Begin(SpriteSortMode.Deferred, BlendState.Additive);

            foreach (var light in lightCircles)
            {
                light.Draw(spriteBatch);
            }

            spriteBatch.End();
        }

    }
}
