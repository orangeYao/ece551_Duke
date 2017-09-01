from __future__ import print_function
import subprocess

frontName = ["./isPrime-correct ", "./isPrime-broken1 ", "./isPrime-broken2 ", "./isPrime-broken3 ", "./isPrime-broken4 "]
k = input('Choose a number: ')

name=frontName[k]
for i in range(1,1000):
    bashCommand = name + str(i)
    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    print(output, end="")
