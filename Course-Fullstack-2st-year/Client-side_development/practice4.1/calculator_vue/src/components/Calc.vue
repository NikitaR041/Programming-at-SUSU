<script setup>
import { ref } from 'vue'

const operand1 = ref('') // Левый операнд
const operand2 = ref('') // Правый операнд
const operator = ref('') // Оператор (+, -, *, /)
const result = ref('') // Результат

// Функция для вычисления результата
const calculate = () => {
  if (operator.value && operand1.value !== '' && operand2.value !== '') {
    const num1 = parseFloat(operand1.value)
    const num2 = parseFloat(operand2.value)

    switch (operator.value) {
      case '+':
        result.value = num1 + num2
        break
      case '-':
        result.value = num1 - num2
        break
      case '*':
        result.value = num1 * num2
        break
      case '/':
        result.value = num2 !== 0 ? num1 / num2 : 'Ошибка: деление на 0'
        break
      default:
        result.value = 'Некорректная операция'
    }
  } else {
    result.value = 'Пожалуйста, введите корректные данные'
  }
}

// Функция для сброса всех значений
const clearAll = () => {
  operand1.value = ''
  operand2.value = ''
  operator.value = ''
  result.value = ''
}
</script>

<template>
  <div class="calculator">
    <h1>Калькулятор</h1>
    <div class="input-section">
      <!-- Поля для ввода чисел -->
      <input type="number" placeholder="Число 1" v-model="operand1"/>
      <select v-model="operator">
        <option disabled value="">Выберите операцию</option>
        <option value="+">+</option>
        <option value="-">-</option>
        <option value="*">*</option>
        <option value="/">/</option>
      </select>
      <input type="number" placeholder="Число 2" v-model="operand2"/>
      <button @click="calculate">=</button>
    </div>
    <!-- Вывод результата -->
    <div class="result">
      <h2>Результат: {{ result }}</h2>
    </div>
    <!-- Кнопка сброса -->
    <button @click="clearAll">СЕ</button>
  </div>
</template>

<style scoped>
.calculator {
  max-width: 400px;
  margin: center;
}

.input-section {
  display: flex;
  gap: 10px;
  margin-bottom: 20px;
}

input, select, button {
  padding: 10px;
  font-size: 16px;
}

.result {
  margin: 20px 0;
  font-size: 18px;
  color: #21eb13;
}
</style>
