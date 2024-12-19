<script setup>
import { ref } from 'vue'

const color = ref('orange') // Цвет
const resize = ref(50) // Размер 
const figure = ref('circle') // Тип фигуры
</script>

<template>
  <div>
    <h1>Выбор фигуры</h1>
    <div class="figure-container">
      <!-- Фигура, которая меняет форму и цвет -->
      <div :class="figure":style="{'background-color': color,'width': (resize * 2) + 'px','height': (figure === 'rectangle' ? resize + 'px' : (resize * 2) + 'px')}"></div>
      <div>
        <div>
          <label for="resize">Размер фигуры</label>
          <select id="resize" v-model="resize">
            <option value="10">10px</option>
            <option value="50">50px</option>
            <option value="100">100px</option>
            <option value="150">150px</option>
            <option value="200">200px</option>
          </select>
        </div>
        <div>
          <label for="color">Цвет</label>
          <select id="color" v-model="color">
            <option value="blue">Синий</option>
            <option value="red">Красный</option>
            <option value="yellow">Жёлтый</option>
            <option value="magenta">Фиолетовый</option>
          </select>
        </div>
        <div>
          <label for="figure">Выбор фигуры</label>
          <select id="figure" v-model="figure">
            <option value="circle">Круг</option>
            <option value="square">Квадрат</option>
            <option value="rhomb">Ромб</option>
            <option value="triangle">Треугольник</option>
            <option value="rectangle">Прямоугольник</option>
            <option value="heart">Сердце 50px</option>
          </select>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.figure-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 20px;
  margin-top: 20px;
}

label {
  display: block;
  margin-bottom: 5px;
}

select {
  margin-bottom: 15px;
}

/* Стили фигур */
.circle {
  border-radius: 50%;
}

.square, .rectangle{
  border-radius: 0;
}

.rhomb {
  transform: rotate(45deg);
}

.triangle{
  clip-path: polygon(50% 0%, 0% 100%, 100% 100%);
}

.heart {
  width: 100px;
  height: 90px;
  position: relative;
  transform: rotate(-45deg);
  margin: 10px auto;
}
.heart:before, .heart:after {
  content: '';
  width: 100px;
  height: 100px;
  background: inherit;
  position: absolute;
  border-radius: 50%;
}

.heart:before {
  top: -50px;
  left: 0;
}

.heart:after {
  left: 50px;
}</style>
