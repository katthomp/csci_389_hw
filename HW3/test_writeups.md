Part 1:
 |TEST|TEST NAME|DESCRIPTION|PASS?|
  |------|------|-----------|-----|
  |SET/GET|test_one|A single get returns correct value and size|PASS|
  |DEL|test_two|a single delete call removes the key|PASS|
  |DEL AND REPLACE|test_three|deleting and replacing the value of a key returns the correct value|PASS|
  |EVICTOR|test_four|if there is not enough space, the evictor is called and removes a key/value pair|PASS|
  |SPACE_USED| test_five|space_used method returns the correct value|PASS|
  |ADD A TOO-BIG VAL|test_six|a value that is too large for the cache is not added|FAIL|

Part 2:

1. Betsy Hoekstra and Robert McCaull.

  I had problems being able to compile this code, and the terminal gave this error:
  \\include graphics here
  They called an explicit operator and the compiler mistook it for a function. Additionally, there is no specified terminal command
  to run the files for evictors.cpp, which was confusing for me.
  
   | Test| PASS?|
  |------|------|
  |SET/GET| PASS|
  |DEL| PASS|
  |DEL AND REPLACE| PASS|
  |EVICTOR| PASS|
  |SPACE_USED| FAIL|
  |ADD A TOO-BIG VAL| PASS|

  
2. Jillian James and Marika Swanberg

I had no problems compiling and linking these files. 

  | Test| PASS?|
  |------|-------|
  |SET/GET| PASS|
  |DEL| PASS|
  |DEL AND REPLACE| PASS|
  |EVICTOR| PASS|
  |SPACE_USED| FAIL|
  |ADD A TOO-BIG VAL| FAIL|
  
3. Josh Reiss and Ezra Schwartz
Small problem with <cache.hh> instead of "cache.hh", but easily fixed.

  | Test| PASS?|
  |------|-------|
  |SET/GET| PASS|
  |DEL| PASS|
  |DEL AND REPLACE| PASS|
  |EVICTOR| PASS|
  |SPACE_USED| FAIL|
  |ADD A TOO-BIG VAL| PASS|
