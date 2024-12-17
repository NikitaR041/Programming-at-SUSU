<!DOCTYPE html>
<head>
    <title>Изменение элемента</title>
    <style>
        /* Исходный стиль квадрата */
        #square {
            width: 100px;
            height: 100px;
            background-color: lightblue;
            margin: 20px;
            transition: all 0.3s ease; /*Плавный переход* */
        }
        button {
            margin: 5px;
            padding: 8px 12px;
            font-size: 14px;
        }
    </style>
</head>
<body>
    <h2>Изменение параметров квадрата</h2>
    <div id="square"></div> <!-- Квадрат -->
    <button onclick="changeColor()">Изменить цвет</button>
    <button onclick="changeSizeRandom()">Изменить размер</button> <!-- Исправлено название функции -->
    <button onclick="reset()">Сбросить</button>

    <script>
        //Функция рандомного числа для цвета
        function getRandColor(){
            const letters = '0123456789ABCDEF';
            let color = '#';
            for (let i = 0; i < 6; i++) {
                color += letters[Math.floor(Math.random() * 16)];
            }
            return color;
        }

        //Функция рандомного числа для размера
        function getRandomSize(min, max) {
            return Math.floor(Math.random() * (max - min + 1)) + min;
        }

        // Функция для изменения цвета квадрата
        function changeColor() {
            const square = document.getElementById('square');
            square.style.backgroundColor = getRandColor(); // Новый цвет
        }

        // Функция для изменения размера квадрата
        function changeSizeRandom() {
            const square = document.getElementById('square');
            
            // Генерация случайных размеров для ширины и высоты
            const newWidth = getRandomSize(50, 300); // Размер от 50px до 300px
            const newHeight = getRandomSize(50, 300); // Размер от 50px до 300px

            // Применяем случайные размеры к квадрату
            square.style.width = String(newWidth) + "px";
            square.style.height = String(newHeight) + "px";
        }

        // Функция для сброса свойств квадрата
        function reset() {
            const square = document.getElementById('square');
            square.style.backgroundColor = 'lightblue'; // Исходный цвет
            square.style.width = '100px';  // Исходная ширина
            square.style.height = '100px'; // Исходная высота
        }
    </script>
</body>
</html>
