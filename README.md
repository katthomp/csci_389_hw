# csci_389_hw
CSCI 389 HW collabs:
#Rhody Kaner and Kathy Thompson (mem_restart.cpp)

1. Jumps occur in our graph after 32KB, 256KB, so it appears that those are the sizes of the L1 and L2 caches, respectively.
There are then many small jumps between 1024 and 65536. The biggest of these jumps occur after 1024 and 2048, so our guess is that the size of L3 is one of those two values. 

2. Our numbers don't match up very well with these numbers, and we're not exactly sure why. The values in L1 seem too large, possible because of other processes running in the background when our code was run, but the L2 and L3 ones seem much too small, and we have no idea why that is.   

3. The caches in our test computer have sizes L1 = 32KB, L2 = 256KB, and L3 = 3072. These values match with our guesses for the sizes of L1 and L2, but the size of L3 turned out to be larger than we anticipated based on our data.



