import os
import re
import sys

table = {}
variables = {}
mixins = {}


def find_var(name):
    return variables.get(name, f"${name}")


def substitute_vars(text):
    if not text:
        return text 

    def replacer(match):
        var_name = match.group(1)
        return find_var(var_name)

    result = re.sub(r'(?<!\$)\$([a-zA-Z0-9_]+)', replacer, text)
    result = result.replace("$$", "$")
    return result


def load(path):
    section = ""
    skip_stack = []

    try:
        with open(path, encoding="utf-8") as f:
            lines = f.readlines()
    except OSError:
        raise OSError(f"не удалось открыть файл '{path}'")

    i = 0
    while i < len(lines):
        raw_line = lines[i]
        number = i + 1
        where = f"{os.path.basename(path)}:{number}"

        line = raw_line.rstrip()

        if not line.strip():
            i += 1
            continue

        indent = len(line) - len(line.lstrip())
        stripped = line.strip()

        if stripped.startswith("@mixin"):
            mixin_name = stripped.split()[1]
            mixins[mixin_name] = []
            i += 1
            while i < len(lines):
                m_raw = lines[i].split('//')[0].rstrip()
                if not m_raw.strip():
                    i += 1
                    continue
                m_indent = len(m_raw) - len(m_raw.lstrip())
                if m_indent > indent:
                    if ":" in m_raw:
                        k, v = m_raw.strip().split(":", 1)
                        mixins[mixin_name].append((k.strip(), v.strip()))
                    i += 1
                else:
                    break
            continue

        if stripped.startswith("$"):
            if ":" not in stripped:
                raise ValueError(f"{where}: некорректное объявление переменной '{stripped}'")
            var_name, var_val = stripped.split(":", 1)
            var_name = var_name.strip().lstrip("$")
            variables[var_name] = substitute_vars(var_val.strip())
            i += 1
            continue

        if indent == 0 and not stripped.startswith("@") and ":" not in stripped:
            section = stripped
            i += 1
            continue

        if stripped.startswith("@if"):
            var_name = stripped.split()[1].lstrip("$")
            val = variables.get(var_name, "").strip().lower()
            is_true = val not in ("", "false", "0", "off", "none")
            skip_stack.append(not is_true)
            i += 1
            continue

        if stripped.startswith("@else"):
            if not skip_stack:
                raise ValueError(f"{where}: @else без @if")
            prev_status = skip_stack.pop()
            skip_stack.append(not prev_status)
            i += 1
            continue

        if any(skip_stack) and indent > 0:
            i += 1
            continue

        if indent == 0 and skip_stack:
            skip_stack.clear()

        if stripped.startswith("@include"):
            mixin_name = stripped.split()[1]
            if mixin_name not in mixins:
                raise ValueError(f"{where}: миксин '{mixin_name}' не найден")
            for k, v in mixins[mixin_name]:
                val = substitute_vars(v)
                table[(section, k)] = val
            i += 1
            continue

        if ":" in stripped:
            name, value = stripped.split(":", 1)
            name = name.strip()
            value = substitute_vars(value.strip())
            table[(section, name)] = value
            i += 1
            continue

        raise ValueError(f"{where}: непонятная строка '{stripped}'")

if len(sys.argv) > 1:
    path = sys.argv[1]
else:
    path = input("Имя файла конфигурации: ").strip()

try:
    load(path)
except ValueError as error:
    print("ошибка:", error)
    sys.exit(1)
except OSError as error:
    print(f"ошибка: {error}")
    sys.exit(1)

print(f"{'РАЗДЕЛ':<12} {'ИМЯ':<16} ЗНАЧЕНИЕ")
print("-" * 45)
for (section, name), value in table.items():
    print(f"{section or '-':<12} {name:<16} {value}")