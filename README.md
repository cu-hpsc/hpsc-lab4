# HPSC Lab 4
2019-09-20

Click to [accept this assignment](LINK ME).

The goals for this lab are:
* Add thread parallelism to a quicksort implementation.
* Discuss differences in strategies and challenges between `omp for` and `omp task` approaches.


WEEKLY WORDS OF WISDOM:
Start simple.  A good foundation is not only more stable to build from, but also helps you better appreciate the significance of each addition.

-----

The repository contains an implementation of [quicksort](https://en.wikipedia.org/wiki/Quicksort#Algorithm).  This sorting algorithm actually has poor worse-case performance (although not to the *bogosort* degree); its name derives from having good *expected* performance on randomly permuted arrays.  Another nice property is that the sorting can be done "in place" (without having to allocate a new buffer that has a size that scales with the original array size) in a fairly straightforward manner.

The algorithm uses a top-down recursion, where at each step it chooses a "pivot" value from the array and then rearranges array elements according to whether they should be placed before or after that pivot.  Each of the two sets (*before* and *after*) can then be viewed as a new unordered arrays, and are ready for the next recursion.  An example of one recursion with images:

<<<add images>>>

With randomly permuted arrays, any index chosen randomly from the current focus of subarray works as well (on expectation) as any other.  There are also techniques for estimating good pivots by examining multiple indexes, but we should regard such techniques as a distraction for this lab.

-----

Once you've followed the algorithm in the code, think abstractly about how you might leverage multiple threads.  It could help to draw a DAG (directed acyclic graph) of the recursions and convince yourself of which work can be parallelized while maintaining correct output!

In class we've now discussed a few models for structuring multiple thread work: primarily `omp for`, and `omp task`.  The way you first thought of leveraging multiple threads above likely fits into one of these models better.  Can you tell which?  And can you think abstractly about how the other model could be used?

There are many "correct" possibilities.  Choose one to implement.  I suggest starting with the simplest you can, even if you can think of some reasons that it might be adding inefficiencies.

-----

Hopefully there will be a mix of `for` and `task` implementations in the class.  This is an opportunity to learn from each other what ideas came to others' minds, and what inefficiencies might have been initially encountered or other ideas for improvement.  Try improving your implementation by perhaps adding more intensive code revisions or more complicated structuring.  Or if something someone else said inspired you in a new direction, run with that.  Hopefully there will be time for a second round of sharing.

-----

Looking for more challenges?  Pick another efficient sorting algorithm such as mergesort or heapsort.  The most obvious implementations of mergesort is out-of-place in memory, but because mergesort is at least top-down recursive it should otherwise be no more complicated to parallelize than quicksort.  Heapsort you may find to be quite a bit harder!