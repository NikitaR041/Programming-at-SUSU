import math
from itertools import product
# import galois as gs
# import numpy as mp

def is_prime(n: int) -> bool:
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True

def poly_mul_mod(p, q, mod, field_char):
    """Умножение многочленов над полем F_field_char с приведением коэффициентов по модулю mod (не используется)"""
    # Здесь mod не нужен, но оставим для единообразия
    deg = len(p) + len(q) - 1
    res = [0] * deg
    for i, coef_p in enumerate(p):
        for j, coef_q in enumerate(q):
            res[i + j] = (res[i + j] + coef_p * coef_q) % field_char
    # обрезаем ведущие нули
    while len(res) > 0 and res[-1] == 0:
        res.pop()
    return res

def poly_mod(p, m, field_char):
    """Остаток от деления многочлена p на m над полем F_field_char (оба списки коэффициентов от старшей степени)"""
    # копируем, чтобы не портить исходный
    r = p[:]
    deg_m = len(m) - 1
    while len(r) >= len(m) and any(r):
        # ведущая степень r
        deg_r = len(r) - 1
        if deg_r < deg_m:
            break
        # коэффициент при старшей степени r делим на старший коэффициент m (он 1, т.к. m нормирован)
        coef = r[-1]  # старший коэффициент r
        # вычитаем coef * m * x^(deg_r - deg_m)
        shift = deg_r - deg_m
        for i in range(len(m)):
            r[shift + i] = (r[shift + i] - coef * m[i]) % field_char
        # удаляем ведущие нули
        while len(r) > 0 and r[-1] == 0:
            r.pop()
    if not r:
        return [0]
    return r

def poly_pow_mod(base, exponent, modulus, field_char):
    """Возведение многочлена base в степень exponent по модулю modulus над полем F_field_char"""
    result = [1]  # многочлен 1
    base_pow = base[:]
    while exponent > 0:
        if exponent & 1:
            result = poly_mul_mod(result, base_pow, None, field_char)
            result = poly_mod(result, modulus, field_char)
        base_pow = poly_mul_mod(base_pow, base_pow, None, field_char)
        base_pow = poly_mod(base_pow, modulus, field_char)
        exponent >>= 1
    return result

def is_irreducible(poly, field_char):
    """Проверка неприводимости нормированного многочлена poly над F_field_char"""
    # poly - список коэффициентов от старшей степени, старший коэффициент = 1
    deg = len(poly) - 1
    if deg <= 1:
        return True  # линейный многочлен неприводим
    # Проверяем делимость на все нормированные многочлены степени от 1 до deg//2
    # Для ускорения можно проверять только неприводимые, но для малых степеней перебор всех нормированных допустим
    from itertools import product
    for d in range(1, deg // 2 + 1):
        # все нормированные многочлены степени d (коэффициенты при x^d = 1)
        for coeffs in product(range(field_char), repeat=d):
            divisor = [1] + list(coeffs)  # старший коэффициент 1, затем коэффициенты от x^{d-1} до x^0
            # проверка, что степень divisor = d (т.е. не все коэффициенты нулевые, кроме первого)
            if len(divisor) > 1 and any(divisor[1:]):
                # делим poly на divisor
                remainder = poly_mod(poly, divisor, field_char)
                if len(remainder) == 1 and remainder[0] == 0:
                    return False
    return True

def get_prime_factors(n):
    """Возвращает список простых множителей числа n (без повторений)"""
    factors = set()
    while n % 2 == 0:
        factors.add(2)
        n //= 2
    p = 3
    while p * p <= n:
        while n % p == 0:
            factors.add(p)
            n //= p
        p += 2
    if n > 1:
        factors.add(n)
    return list(factors)

def is_primitive(poly, field_char):
    """Проверка, что полином poly степени k примитивен: его корни имеют порядок field_char^k - 1"""
    k = len(poly) - 1
    order = field_char ** k - 1
    # Проверяем, что x^order ≡ 1 mod poly
    x = [0, 1]  # многочлен x
    rem = poly_pow_mod(x, order, poly, field_char)
    if len(rem) != 1 or rem[0] != 1:
        return False
    # Проверяем для каждого простого делителя d порядка, что x^(order/d) ≠ 1 mod poly
    for factor in get_prime_factors(order):
        rem = poly_pow_mod(x, order // factor, poly, field_char)
        if len(rem) == 1 and rem[0] == 1:
            return False
    return True

def find_primitive_polynomial(q, k):
    """Поиск примитивного нормированного многочлена степени k над F_q"""
    # перебираем все нормированные многочлены степени k
    # коэффициенты при x^{k-1} ... x^0
    total = q ** k
    print(f"Поиск примитивного многочлена степени {k} над F_{q}... (всего {total} вариантов)")
    for coeffs in product(range(q), repeat=k):
        poly = [1] + list(coeffs)  # старший коэффициент 1, затем коэффициенты от x^{k-1} до x^0
        # сначала проверяем неприводимость
        if is_irreducible(poly, q):
            if is_primitive(poly, q):
                return poly
    raise ValueError(f"Не удалось найти примитивный многочлен степени {k} над F_{q}")

def generate_sequence(poly, q, num_terms=20):
    """Генерирует ЛРП с максимальным периодом, заданную характеристическим многочленом poly.
       poly: список коэффициентов [1, a_{k-1}, ..., a_0] (нормированный).
       Рекуррента: S_{n+k} = -a_{k-1} S_{n+k-1} - ... - a_0 S_n (mod q).
       Возвращает список первых num_terms членов последовательности."""
    k = len(poly) - 1
    # коэффициенты рекурренты (c_i = -a_i mod q)
    rec_coeffs = [(-coeff) % q for coeff in poly[1:]]  # в порядке от a_{k-1} до a_0
    # начальные условия: S_0=1, остальные 0 (ненулевые)
    seq = [0] * k
    seq[0] = 1
    # генерируем
    for n in range(num_terms):
        if n < k:
            yield seq[n]
        else:
            next_val = 0
            for i in range(k):
                next_val = (next_val + rec_coeffs[i] * seq[n - k + i]) % q
            seq.append(next_val)
            yield next_val

def main():
    print("Генератор ЛРП с максимальным периодом над F_q")
    q = int(input("Введите простое число q: "))
    if not is_prime(q):
        print("Ошибка: q должно быть простым.")
        return
    k = int(input("Введите порядок k (натуральное число): "))
    if k < 1:
        print("Ошибка: k должно быть >= 1")
        return

    try:
        prim_poly = find_primitive_polynomial(q, k)
        print(f"\nНайден примитивный многочлен: ", end="")
        # выводим в виде x^{k} + a_{k-1} x^{k-1} + ... + a_0
        poly_str = f"x^{k}"
        for i, coeff in enumerate(prim_poly[1:]):
            power = k - i - 1
            if coeff == 0:
                continue
            sign = "+" if coeff >= 0 else "-"
            coeff_abs = abs(coeff)
            if power == 0:
                term = f"{coeff_abs}"
            elif power == 1:
                term = f"{coeff_abs}x" if coeff_abs != 1 else "x"
            else:
                term = f"{coeff_abs}x^{power}" if coeff_abs != 1 else f"x^{power}"
            poly_str += f" {sign} {term}"
        print(poly_str)

        # рекуррентное соотношение
        rec_coeffs = [(-c) % q for c in prim_poly[1:]]
        rec_str = f"S_{{n+{k}}} = "
        terms = []
        for i, c in enumerate(rec_coeffs):
            if c == 0:
                continue
            term = f"{c}·S_{{n+{k-1-i}}}" if c != 1 else f"S_{{n+{k-1-i}}}"
            terms.append(term)
        rec_str += " + ".join(terms) + f" (mod {q})"
        print(f"Рекуррентное соотношение: {rec_str}")

        # генерируем последовательность
        print(f"\nПервые {max(20, q**k)} членов последовательности (период {q**k - 1}):")
        seq_gen = generate_sequence(prim_poly, q, num_terms=max(20, q**k))
        seq_list = list(seq_gen)
        print(", ".join(map(str, seq_list)))
        # проверка периода (для демонстрации)
        print(f"Период последовательности = {q**k - 1} (максимальный)")

    except ValueError as e:
        print(e)

if __name__ == "__main__":
    main()