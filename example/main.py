from pyextensions import mymath, lilterminal
from pyextensions.lilterminal import system

lilterminal.xablau() # Print xablau
result = mymath.add(2,2) # Add 2 and 2
print(result) 

system("echo Return of 5+5 = " + str(mymath.add(5,5))) # Echo result of 5 and 5
system("echo '\nHere are your files:\n'") 
system("ls") # Print files in directory
