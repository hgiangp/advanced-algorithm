import math 

c1 = input()
c2 = input()

c1x , c1y , c1r = map(int,c1.split(' '))
c2x , c2y , c2r = map(int,c2.split(' '))

d = math.sqrt((c1x - c2x)**2 + (c1y - c2y)**2)

if d > c1r + c2r:
    print(4)
elif d == c1r + c2r: 
    print(3)
elif d == abs(c1r - c2r): 
    print(1)
elif d < abs(c1r - c2r): 
    print(0)
else: 
    print(2)