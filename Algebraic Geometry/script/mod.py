# Cohomology
def Cohomology(n):
    return 2**(n-1)-((n**2-n+2)/(2))

for i in range(3,9):
    print(Cohomology(i))    
