from nprime.pyprime import miller_rabin
from math import gcd as bltin_gcd
from secrets import randbits, randbelow
from sympy import mod_inverse

cryptos = {
    "RSA" : (RSA_enc(), RSA_dec())
}


class RSA_enc:
    
    def __init__(self):
        self.__len
    

class RSA_dec:
        

class cryptosystem:
    
    def __init__(self, system_type, bits=512):
        self.enc, self.dec = cryptos[system_type]
        
    


def generate_prime_candidate(len):
    p_can = randbits(len)
    
    p_can |= (1 << len - 1) | 1
    return p_can

def gen_prime_number(len=1024):
    p = 4
    while not miller_rabin(p, t=128):
        p = generate_prime_candidate(len)
    return p

def str_to_int(in_string):
    int_list = [None] * len(in_string)
    for index, c in enumerate(in_string.upper()):
        int_list[index] = ord(c)
    l_to_i = [str(num) for num in int_list]
    l_to_i = int("".join(l_to_i))
    return l_to_i

def int_to_str(in_int):
    i_str = str(in_int)
    new_str = ""
    for x in range(len(i_str) // 2):
        new_str += (chr(int(i_str[x*2:x*2 + 2])))
    return new_str.lower()

# Coprime generation functions
def coprime2(a, b):
    return bltin_gcd(a, b) == 1

def gen_coprime(n):
    m = randbelow(n - 1) + 2
    while not coprime2(m, n):
        m = randbelow(n - 1) + 2
    return m