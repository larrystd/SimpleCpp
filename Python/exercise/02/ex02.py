# -*- coding:utf-8 -*-

"""
    binary search method, that is, take the intermediate value every time to guess, 
    so that the number of steps is the least.

    If the iteration cannot be found, then the user is cheating

    The guess interval is [1,100] by default, and the interval can be customized by changing the incoming parameters
"""

def detect_lie():
    """detect_lie and exit(-1)
    """
    print ("Hey friend, what a big heartbreak that you lie me!!!")
    exit(-1)

def play_chess(left = 1, right = 100):
    """ play_chess program
        the interval is left closed and right closed, [left, right]
    Args:
        left (int): Defaults to 0.
        right (int): Defaults to 100.
    """
    if left <= right:
        print ("The interval's left border should less than right, stop!!!")
    print ("Think of a number between {0} and {1}!".format(left, right))

    start = left
    end = right
    num_step = 0
    while start <= end:
        num_step+=1
        mid = (start + end)>>1    # means (start+right)/2
        print ("Is your number greater (>), equal (=), or less (<) than {}?".format(mid))
        symbol = input("Please answer <,=, or >! > ")
        if symbol == "=":
            print ("I have guessed it!")
            print ("I needed {} steps!".format(num_step))
            exit(0)
        elif symbol == ">":
            start = mid+1
        else:
            end = mid-1

    detect_lie()  # detect lie

if __name__ == "__main__":
    play_chess(1, 100)

    # play_chess(-10,10)  # you can set interval Manually