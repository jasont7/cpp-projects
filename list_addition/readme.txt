Suppose we represent an integer in base 10 with a list object, using one element per digit. For example, the number 610 would be correspond to the list {6, 1, 0}. This exercise uses such a representation to perform positional arithmetic.

Your task is to implement a function add_lists which takes two list objects in the representation described above and returns a new list in the same format (with one element per digit) containing the sum of the numbers represented by each input list.

For example, if list 1 contains {1, 1, 6} and list 2 contains {1, 1, 1}, the returned list would be {2, 2, 7}. If list 1 contains {9, 1, 2} and list 2 contains {2, 1, 0}, the returned list would be {1, 1, 2, 2}.
