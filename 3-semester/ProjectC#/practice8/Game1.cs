using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using SharpDX.Direct2D1;
using SharpDX.Direct3D9;
using System;

namespace practice8
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager _graphics;
        private Microsoft.Xna.Framework.Graphics.SpriteBatch _spriteBatch;

        private Texture2D backgroundTexture; // Объявляем текстуру фона
        private ManagerLight lightingManager; // Менеджер освещения

        public Game1()
        {
            _graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            IsMouseVisible = true;


            // Установить размер окна
            _graphics.PreferredBackBufferWidth = 1300;  // Ширина окна
            _graphics.PreferredBackBufferHeight = 900; // Высота окна
            _graphics.ApplyChanges(); // Применить изменения
        }

        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            // Создание менеджера освещения
            lightingManager = new ManagerLight();

            base.Initialize();
        }

        protected override void LoadContent()
        {
            _spriteBatch = new Microsoft.Xna.Framework.Graphics.SpriteBatch(GraphicsDevice);

            //_spriteBatch = new SpriteBatch(GraphicsDevice);

            // Загрузка текстур
            backgroundTexture = Content.Load<Texture2D>("light"); // Текстура фона
            Texture2D lightTexture = Content.Load<Texture2D>("light"); // Градиентная текстура

            // Создание источников света
            LightCircle light1 = new LightCircle(new Vector2(200, 200), 1.0f, 1.0f, lightTexture, Color.Red);
            LightCircle light2 = new LightCircle(new Vector2(700, 700), 1.0f, 1.2f, lightTexture, Color.Blue);
            LightCircle light3 = new LightCircle(new Vector2(500, 500), 1.0f, 0.8f, lightTexture, Color.Green);


            //Добавление экземпляров
            lightingManager.AddLightCircle(light1);
            lightingManager.AddLightCircle(light2);
            lightingManager.AddLightCircle(light3);
            // TODO: use this.Content to load your game content here
        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            // TODO: Add your update logic here
            int speed = 4;
            lightingManager.UpdateObject(GraphicsDevice, gameTime, speed);

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.Black);

            // Отрисовка фона сцены
            _spriteBatch.Begin();
            _spriteBatch.Draw(backgroundTexture, Vector2.Zero, Color.White); // Рисуем фон
            _spriteBatch.End();

            // Отрисовка источников света через менеджер освещения
            lightingManager.Draw(_spriteBatch);

            base.Draw(gameTime);
        }
    }
}
