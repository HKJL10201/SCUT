import math
class Vector2D(object):
    def __init__(self, a, b):
        self.x=a
        self.y=b
        pass

    def __add__(self, Vector2D):
        self.x+=Vector2D.x
        self.y+=Vector2D.y
        pass

    def __sub__(self, Vector2D):
        self.x-=Vector2D.x
        self.y-=Vector2D.y
        pass

    def __mul__(self, num):
        self.x*=num
        self.y*=num
        pass
    
    def __abs__(self):
        return (self.x*self.x+self.y*self.y)**0.5

    def __str__(self):
        return "({},{})".format(self.x,self.y)
    
    def angle(self,Vector2D):
        cos=abs((self.x*Vector2D.x+self.y*Vector2D.y)/(self.__abs__()*Vector2D.__abs__()))
        return math.acos(cos)

a=Vector2D(4,3)
b=Vector2D(-3,4)
print(a.__str__())  #print a
print(a.__abs__())  #print length of a
print(b.__abs__())  #print length of b

a.__add__(b)
print(a.__str__())  #print a+b
a.__sub__(b)
print(a.__str__())  #print a-b
a.__mul__(2)
print(a.__str__())  #print a*2
a.__mul__(0.5)
print(a.__str__())  #print a/2

print(a.angle(b))   #print angle of a&b
print(math.degrees(a.angle(b))) #print angle of a&b by degrees
