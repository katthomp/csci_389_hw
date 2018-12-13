I created a new function to be called in place of atoi, called fast_atoi. 
Because of the nature of the data I was parsing, I could assume things that made this function marginally faster than the original atoi.

When I ran this function within the loop, I had a best time of .03 seconds, which is a little bit faster than the original atoi with .04 sec.
