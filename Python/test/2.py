def deco(func):
    print('running register(%s)' % func)
    print('abc')
    def inner():
        print ('running inner()')
    return inner

@deco
def target():
    print ('running target()')

# target()

#target