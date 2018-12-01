1. Our general goal is to evaluate performance of our cache over the network. The system boundaries for the cache include 
maxmem, requirement of unique keys, and the other basic defining characteristics of hash tables. However, since we are 
accessing our cache over the network, we also have to take into account the system boundaries of the server and client, and 
ensure that we are never overloading the server with too many closely-spaced requests (as this would result in testing 
the server rather than the cache).

2. Our relevant services include set and get requests that assign and access key-value pairs, respectively. The cache provides 
additional services (such as space_used, del, etc.) but these are less relevant to our current benchmarking goals. The network 
also provides the service of sending packets of data, and in this case providing us access to our cache over the server. It is 
possible for any of these services to fail, but the cache ones appear to be relatively reliable, and provided that we do not
overload our server with requests, we can hopefully assume a reasonably high level of reliability there as well.

3. Our metrics will include sustained throughput (which in this case means the maximum load of requests for which the mean 
response time remains under 1 millisecond), as well as mean response time and accuracy??? (checking if the sets/gets match up and stuff?) 

4. Parameters: number of gets/second, number of sets/second, value size in key-value pairs, attributes of the network possible?

5. Factors: number of gets/second, number of sets/second, size of values.

6. We intended to use the technique of measuring a real system as indicated in the project assignment. However, we never managed to get our networking code working in the last assignment and have have also had issues with either compiling/running the networking code from both of the other groups whose code we tried to adopt for this assignment. After much frustration and many failed attempts to get a server up and running, we have decided to switch our evaluation technique to analytical modeling in the interest of completing this assignment and preserving our sanity. We recognize that this choice significantly decreases the accuracy and relevance of our benchmarking as we will have to make many assumptions in our analytical models, but it also seems to be the only choice left available to us given our current predicament.    

7. After reading the papers on workload analysis of a large-scale key-value store and many-core key-value store, we decided that it would be reasonable to use a distribution made up of 3/4 get requests and 1/4 deletes, as write requests seem to be a lot faster and have little impact on the timing. We chose to make the majority of our distrubtion read requests and a smaller proportion deletes to mimic a potentially likely distribution in actual usage of a cache. Obviously we've made a lot of assumptions and simplifications in choosing to use this fixed distribution partly because this cache isn't actually intended to be used for any purpose, so it is difficult to ascertain any particular sense of 'normal' usage and partly to make our lives easier while trying to complete this assignment.

8. Hypothetical experimental design (what we would do if we had a working networked cache): We would first fill the cache to saturation with values of varying sizes, mimicing the choices made in the memcache workload analysis paper, such that the values fit the following distribution: 20% in the size range 1 to 10 bytes, 20% in range 10-100, 20% in range 100-1000 bytes, 20% 1000-10,000, 20% in range 10,000 to 100,000 bytes. We would then vary the total sum of read + delete requests (keeping the breakdown to 3/4 read, 1/4 delete) per second, starting at 100 and increasing up to 10,000 (increasing by a power of 10 each time, and provided that the larger values do not overload the server). In each trial, we would space the requests out equally over a second, and then measure the time each individual request takes (keeping track of read and delete requests separately, in case there are noticeable differences in the timing of each of these request types). 

9.  

