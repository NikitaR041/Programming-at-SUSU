using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using SharpDX.Direct2D1;
using System.Collections.Generic;
using System.Drawing;

namespace practice6
{
    public class Game1 : Game
    {
        private GraphicsDeviceManager graphics;
        private Microsoft.Xna.Framework.Graphics.SpriteBatch spriteBatch;

        private List<GameObject> gameObjects;

        public Game1()
        {
            this.graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";

            this.graphics.PreferredBackBufferWidth = 1580;  // Ширина окна
            this.graphics.PreferredBackBufferHeight = 960; // Высота окна
            gameObjects = new List<GameObject>();

            IsMouseVisible = true;
        }

        protected override void Initialize()
        {
            // TODO: Add your initialization logic here

            base.Initialize();
        }

        protected override void LoadContent()
        {
            this.spriteBatch = new Microsoft.Xna.Framework.Graphics.SpriteBatch(GraphicsDevice);

            Texture2D stationaryTexture = Content.Load<Texture2D>("ant");
            Texture2D movingTexture = Content.Load<Texture2D>("airplane");
            Texture2D playerTexture = Content.Load<Texture2D>("Ship");

            // Создаём объекты
            GameObject stationary = new GameObject(new Vector2(100, 100), stationaryTexture);
            ActiveGameObject moving = new ActiveGameObject(new Vector2(200, 200), movingTexture, new Vector2(1, 0));
            ControlObject player = new ControlObject(new Vector2(300, 300), playerTexture, new Vector2(2, 2));

            // Добавляем их в список
            gameObjects.Add(stationary);
            gameObjects.Add(moving);
            gameObjects.Add(player);
        }

        protected override void Update(GameTime gameTime)
        {

            foreach (var obj in gameObjects)
            {
                obj.Update(gameTime);
            }


            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Microsoft.Xna.Framework.Color.CornflowerBlue);

            // TODO: Add your drawing code here
            this.spriteBatch.Begin();
            foreach (var obj in gameObjects)
            {
                obj.Draw(this.spriteBatch);
            }
            this.spriteBatch.End();


            base.Draw(gameTime);
        }
    }
}
