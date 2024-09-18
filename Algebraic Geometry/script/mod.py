def is_prime(n):
    if n == 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(n**0.5)+1, 2):
        if n % i == 0:
            return False
    return True

def is_circular_prime(n):
    s = str(n)
    for i in range(len(s)):
        if not is_prime(int(s)):
            return False
        s = s[1:] + s[0]
    return True

def circular_primes(n):
    return [i for i in range(1, n) if is_circular_prime(i)]

def prime(n):
    return [i for i in range(1, n) if is_prime(i)]

n = 100000

circular = circular_primes(n)
prime = prime(n)

print(circular)
# [2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 197, 199, 311, 337, 373, 719, 733, 919, 971, 991, 1193, 1931, 3119, 3779, 7793, 7937, 9311, 9377, 11939, 19391, 19937, 37199, 39119, 71993, 91193, 93719, 93911, 99371]