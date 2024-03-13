# Lists
In here I tried to see how efficient is splitting up a list in C into smaller ordered lists.
Fun result with no proof:
For a list of size N taking elements in ascending order on average it can be split up into 
2*sqrt(N) lists of size sqrt(N)/2.
If I allow addition at both ends I get on average size_of_list * M = number_of_lists where 
1.85 <= M <= 2. But I do admit I haven't done any statistical analysis on this subject.
