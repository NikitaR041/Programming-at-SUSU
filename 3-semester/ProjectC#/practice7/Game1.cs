using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
//using Microsoft.Xna.Framework;
using SharpDX.Direct2D1;
using System;
//using System.Drawing;

namespace new_practice7
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager _graphics;
        private Microsoft.Xna.Framework.Graphics.SpriteBatch _spriteBatch;

        private GameManager _gameManager;
        private Texture2D _backgroundTexture;
        private Texture2D _shipTexture;
        private Texture2D _evilTexture;

        private ActiveObject obj1; //Отдельно создаем объект заднего фона

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
            _gameManager = new GameManager();

            //Подписка события 
            _gameManager.CollisionDetected += GameManager_CollisionDetected;

            base.Initialize();
        }

        //Метод, который будет вызываться при столкновении объектов
        private void GameManager_CollisionDetected(BaseObjcet obj1, BaseObjcet obj2) {
            Console.WriteLine($"Столкновение между объектами: {obj1.GetType().Name} и {obj2.GetType().Name}");
        }

        protected override void LoadContent()
        {
            _spriteBatch = new Microsoft.Xna.Framework.Graphics.SpriteBatch(GraphicsDevice);

            _backgroundTexture = Content.Load<Texture2D>("MilkiWay");
            _shipTexture = Content.Load<Texture2D>("Ship");
            _evilTexture = Content.Load<Texture2D>("planet3");


            obj1 = new ActiveObject(_backgroundTexture, new Vector2(0, 0), new Microsoft.Xna.Framework.Rectangle(0, 0, _backgroundTexture.Width, _backgroundTexture.Height)); //Зданий фон
            ManageObject obj2 = new ManageObject(_shipTexture, new Vector2(50, 50), new Microsoft.Xna.Framework.Rectangle(50, 50, _shipTexture.Width, _shipTexture.Height)); //Движущийся корабль
            ActiveObjectCollision obj3 = new ActiveObjectCollision(_evilTexture, new Vector2(800, 600), new Microsoft.Xna.Framework.Rectangle(800, 600, _evilTexture.Width, _evilTexture.Height)); //Движущися противник-колиззия

            //_gameManager.AddObject(obj1);
            _gameManager.AddObject(obj2);
            _gameManager.AddObject(obj3);

            // TODO: use this.Content to load your game content here
        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            // TODO: Add your update logic here

            short speed = 4; // Пример скорости движения
            _gameManager.UpdateObject(GraphicsDevice, gameTime, speed);
            obj1.MovementBack(GraphicsDevice,  gameTime, speed);
            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Microsoft.Xna.Framework.Color.CornflowerBlue);

            _spriteBatch.Begin();

            obj1.Draw(_spriteBatch);

            //TODO: Add your drawing code here
            //Рисуем все объекты через менеджер
            foreach (var obj in _gameManager.GetObjects())
            {
                obj.Draw(_spriteBatch);
            }


            _spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
