Write a program which receives two integer data sets from standard input, then removes all complete sequences of data set 1 from data set 2, and finally prints the filtered data set. The number -1 will be used to separate the two data sets in the input stream.

If a text file named data_sets.txt contains the following:

	1 1
	-1
	1 1 1 2 6 5 1 1 6

An example run of a successful solution on data_sets.txt appears below:

	./filter_data < data_sets.txt
	Data Set 1: 1 1
	Data Set 2: 1 1 1 2 6 5 1 1 6 
	Filtered: 1 2 6 5 6