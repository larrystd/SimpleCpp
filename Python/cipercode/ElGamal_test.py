import random
from math import pow

a = random.randint(2, 10) #产生小于p的随机常数a


def gcd(a, b):
    if a < b:
        return gcd(b, a)
    elif a % b == 0:
        return b
    else:
        return gcd(b, a % b)

    # Generating large random numbers


def gen_key(q):
    key = random.randint(pow(10, 20), q)
    while gcd(q, key) != 1:
        key = random.randint(pow(10, 20), q)

    return key


# Modular exponentiation
def power(a, b, c):
    x = 1
    y = a

    while b > 0:
        if b % 2 == 0:
            x = (x * y) % c
        y = (y * y) % c
        b = int(b / 2)

    return x % c


# Asymmetric encryption
def encrypt(msg, p, h, r):

    # h 公钥
    # r素根
    b = 30
    #K = power(h, b, p)#K=(Sa)^b mod p
    K = h**b % p
    #C1 = power(r, b, p) #C1=Sb=r^b mod p
    C1 = r**b % p

    print("C1 : ", C1)

    c2 = K%p * msg % p
    # print("(Sa)^b mod p used : ", K)
    print("C2 : ", c2)
    return c2, C1


def decrypt(C2, C1, x, p):
    #h = power(C1, x, p)
    h = C1**x %p
    return C2 / h

# Driver code
def main():
    msg = 123456               # 共125位数字，1000bit
    print("明文 :", msg)

    p = 73 # 获得大素数q
    r = 5 #得r

    x = 60  # Private key for receiver
    h = power(r, x, p)  # 公钥

    C2, C1 = encrypt(msg, p, h, r)
    dr_msg = decrypt(13, 24, x, p)
    print("解密后文 :", dr_msg)


if __name__ == '__main__':
    main()