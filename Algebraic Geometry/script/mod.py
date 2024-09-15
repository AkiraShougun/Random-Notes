# Cohomology
def Cohomology(n):
    return 2**(n-1)-((n**2-n+2)/(2))

for i in range(3,12):
    print(Cohomology(i))    

#Write a print statement to print a hatsune miku ascii art in the console

text = """
            .--.
            |o_o |
            |:_/ |
             //   \ \\
            (|     | )
             /'\_   _/`\\
                \___)=(___/
    """ 

print(text)
