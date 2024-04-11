import re

rex = re.compile(r"[^\w\d’]+")

with open('./text_out.txt', 'w') as outFile:
    with open('./text.txt', 'r') as file:
        for textString in file:
            outString = rex.sub(' ', textString).replace("’", "'").replace(" ", "\n").lower().rstrip()
            outFile.write(outString)
