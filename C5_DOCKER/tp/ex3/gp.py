import redis
import json

r = redis.Redis(host='localhost', port=6379, db=0)

with open("./gp.txt", "r") as f:
    data = f.read()


keys = r.hkeys("mots")

vals = []

for k in keys:
    v = r.hget("mots",k)
    vals.append([k.decode(), v.decode()])

vals.sort( key = lambda a : int(a[1]))

print(json.dumps(vals, indent=4))
