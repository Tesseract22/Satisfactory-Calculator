import re

text = "(120m³ / min)12m³ Alumina Solution"
name = "aa bb"
pat_n = re.compile("([a-z]|\s)*")
pat = re.compile("\(.*\)(\d*.\d*)(x|m³)\s(([a-z]|\s)*)", re.I)

r = re.match(pat, text)

print(r.group(3))

# with open("Recipe Spyder/local/item_html.txt") as f:
#     print(type(56))