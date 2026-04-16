import galois

def main():
    print("Генератор ЛРП с максимальным периодом над F_q (с использованием galois)")
    q = int(input("Введите простое число q: "))
    if not galois.is_prime(q):
        print("Ошибка: q должно быть простым.")
        return
    k = int(input("Введите порядок k (натуральное число): "))
    if k < 1:
        print("Ошибка: k должно быть >= 1")
        return

    # Находим примитивный многочлен степени k над GF(q)
    prim_poly = galois.primitive_poly(q, k)
    print(f"\nНайден примитивный многочлен: {prim_poly}")

    # Получаем коэффициенты a_{k-1} ... a_0 (без старшего 1) как элементы поля
    coeffs_field = prim_poly.coeffs[1:]
    # Преобразуем в обычные целые числа Python
    coeffs_int = [int(c) for c in coeffs_field]
    # Коэффициенты рекурренты: c_i = -a_i mod q
    rec_coeffs = [(-c) % q for c in coeffs_int]   # rec_coeffs[0] = -a_{k-1}, ..., rec_coeffs[-1] = -a_0

    # Вывод рекуррентного соотношения в читаемом виде
    terms = []
    for i, c in enumerate(rec_coeffs):
        if c == 0:
            continue
        power = k - 1 - i
        term = f"{c}·S_{{n+{power}}}" if c != 1 else f"S_{{n+{power}}}"
        terms.append(term)
    rec_str = " + ".join(terms) if terms else "0"
    print(f"Рекуррентное соотношение: S_{{n+{k}}} = {rec_str} (mod {q})")

    # Генерация последовательности с максимальным периодом
    period = q**k - 1
    # Начальные условия: S_0 = 1, S_1 = ... = S_{k-1} = 0
    seq = [0] * k
    seq[0] = 1

    # Количество выводимых членов: покажем не более 40, но если период мал, то весь период
    show_terms = min(40, max(period, 20)) if period < 100 else 40
    print(f"\nПервые {show_terms} членов последовательности (период = {period}):")
    for n in range(show_terms):
        if n < k:
            val = seq[n]
        else:
            next_val = 0
            for i in range(k):
                next_val = (next_val + rec_coeffs[i] * seq[n - k + i]) % q
            seq.append(next_val)
            val = next_val
        print(val, end=", " if n < show_terms - 1 else "\n")
    print(f"Последовательность имеет максимально возможный период {period}.")

if __name__ == "__main__":
    main()