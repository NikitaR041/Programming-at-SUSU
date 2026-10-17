import re

# text = "Google, Gooogle, Goooooogle"
# match = re.findall(r"Go{,4}gle", text)
# text = "Картинка <img src='bg.jpg'> в тексте</p>"
# match = re.findall(r"<img\s+[^>]*src=[\"'](.+?)[\"']", text)
# match = re.findall(r"<img\s+[^>]*src=([\"'])(.+?)\1", text)
# match = re.findall(r"<img\s+[^>]*src=(?P<quote>[\"'])(.+?)(?P=quote)", text)
txt = "(еда), еда, победа"
g = re.findall(r".", txt)
h = re.findall(r"\w", txt)
print(g)
print(h)