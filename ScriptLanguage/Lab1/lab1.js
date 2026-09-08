const { performance } = require('perf_hooks');

const arr = Array.from({ length: 10000 }, () => Math.floor(Math.random() * 100000) + 1);

function myFunc(arr) {
    let count = 0;
    const len = arr.length;
    for (let i = 0; i < len; i++) {
        for (let j = i + 1; j < len; j++) {
            if (arr[i] === arr[j]) {
                count++;
            }
        }
    }
    return count;
}

const start = performance.now();
const c = myFunc(arr);
const finish = (performance.now() - start); 

console.log(`Количество дубликатов в массиве ${c}`);
console.log(`Время работы алгоритма на JS: ${finish.toFixed(2)} миллисекунд`);