class Vector2d:
    typecode = 'd'

    def __init__(self, x, y):
        self.__x = float(x)
        self._y = float(y)
    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self._y

    def __iter__(self):
        return (i for i in (self.x, self.y))

v = Vector2d(1,2)
print (v.x)
print (v.y)
print (v._y)
print (v._Vector2d__x)