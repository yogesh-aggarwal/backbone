import glob
import os

result = []

for x in os.walk("Source"):
    for y in glob.glob(os.path.join(x[0], '*')):
        result.append(y)

total = 0

for file in result:
    try:
        with open(file) as f:
            total += len(f.readlines())
    except Exception:
        pass

print(total)