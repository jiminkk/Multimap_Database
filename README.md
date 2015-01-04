Multimap_Database
=================

CS 32 Project
Used C++


MultiMap::findEqual()
This function looks for the key that is equal to the parameter key as an iterator moves next from m_root. Because the iterator starts from m_root and traverses to the right, the Big O would be O(log N) (assuming N is the number of nodes to be traversed) it finds the right key. If not, then the worst case would be O(N).

MultiMap::Iterator::next()
Iterates to the next node in a MultiMap. The Big O for this function is O(1) (N being the number of nodes) because the function has no loop that would increase the Big O significantly.

Database::search()
Searches for the matching row numbers and returns the number of matching rows, updating the results vector with the matching row numbers. My time complexity does not follow the requirements of the spec. I have also not been able to complete the sorting portion of the search function.
