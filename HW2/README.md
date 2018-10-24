Part 1: We used an unordered map to implement our cache, which included both built in methods such as .erase and .count as well as 
much of the necessary optimizations for later parts of the assignment

Part 2: We wrote several simple tests to ensure that set, get, del, and the evictor policy all work as expected.

Part 3: the unordered_map structure already allows any hash function to be passed in and used for hashing.

Part 4: Unordered_map uses bucket hashing to avoid collisions.

Part 5: dynamic resizing is also built in for unordered_maps, so we simply set the max_load_factor to 0.5 to implement this.

Part 6: We implemented a FIFO eviction policy by creating an additional list structure (called actual_cache_struct) that keeps 
track of the order in which keys were added to the cache in order to remove the least recently added when the sum of the 
sizes of the values in the cache gets too close to maxmem to add the next value.


