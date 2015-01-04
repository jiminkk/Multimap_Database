//
//  MultiMap.h
//  Project_4
//
//  Created by Jasmine on 3/8/14.
//  Copyright (c) 2014 Jasmine. All rights reserved.
//

#ifndef __Project_4__MultiMap__
#define __Project_4__MultiMap__

#include <iostream>

class	MultiMap
{
private:
    //	To	prevent	Multimaps	from	being	copied	or	assigned,	declare	these	members
    //	private	and	do	not	implement	them.
    MultiMap(const	MultiMap&	other);
    MultiMap&	operator=(const	MultiMap&	rhs);
    
    struct node
    {
        std::string m_key;
        node *m_left;
        node *m_right;
        node *m_parent;
        
        struct listNode
        {
            listNode *next;
            listNode *prev;
            unsigned int ln_value;
        };
        listNode *m_head;
    };
    node *m_root;
    
public:
    //	You	must	implement	this public	nested	MultiMap::Iterator	class
    class	Iterator
    {
    public:
        Iterator();		//	You	must	have	a	default	constructor
        Iterator(node* p_node);
        ~Iterator();
        bool	valid()	const;
        std::string	getKey()	const;
        unsigned	int	getValue()	const;
        bool	next();
        bool	prev();
    private:
        bool m_isValid;
        node* m_node;
    };
	
    MultiMap();
    ~MultiMap();
    void	clear();
    void	insert(std::string	key,	unsigned	int	value);
    Iterator	findEqual(std::string	key)	const;
    Iterator	findEqualOrSuccessor(std::string	key)	const;
    Iterator	findEqualOrPredecessor(std::string	key)	const;
};

/*
 
 #ifndef MULTIMAP_INCLUDED
 #define MULTIMAP_INCLUDED
 
 // Implementation of MultiMap using std::multimap
 
 // This is provided solely so that you can test Database even if you
 // are not confident that your implementation of MultiMap is correct.
 // Of course, since it uses std::multimap, the spec forbids you from using
 // this as the MultiMap implementation you turn in.
 
 // All the implementation is in this file, so to use it, you do not need
 // a MultiMap.cpp file with it, or if you had one, it can be an empty file.
 
 #include <map>
 #include <string>
 #include <utility> // for make_pair
 #include <cassert>
 
 class MultiMap
 {
 private:
 typedef std::multimap<std::string, unsigned int> MMap;
 typedef MMap::const_iterator MMapIterator;
 public:
 class Iterator
 {
 public:
 Iterator() : m_mmap(nullptr) {}
 Iterator(const MMap& mm, MMapIterator iter)
 : m_mmap(iter != mm.end() ? &mm : nullptr), m_iter(iter) {}
 bool valid() const { return m_mmap != nullptr; }
 std::string getKey() const { assert(valid()); return m_iter->first; }
 unsigned int getValue() const { assert(valid()); return m_iter->second; }
 bool next()
 {
 if (!valid())
 return false;
 if (++m_iter != m_mmap->end())
 return true;
 m_mmap = nullptr;
 return false;
 }
 bool prev()
 {
 if (!valid())
 return false;
 if (m_iter != m_mmap->begin())
 {
 m_iter--;
 return true;
 }
 m_mmap = nullptr;
 return false;
 }
 private:
 // Class invariant:  m_mmap == nullptr || m_iter != m_mmap->end()
 const MMap* m_mmap;
 MMapIterator m_iter;
 };
 
 MultiMap() {}
 ~MultiMap() {}
 void clear() { m_mmap.clear(); }
 void insert(std::string key, unsigned int value)
 { m_mmap.insert(make_pair(key, value)); }
 Iterator findEqual(std::string key) const
 {
 MMapIterator p = m_mmap.lower_bound(key);
 if (p == m_mmap.end()  ||  p->first != key)
 return Iterator();
 return Iterator(m_mmap, p);
 }
 Iterator findEqualOrSuccessor(std::string key) const
 {
 MMapIterator p = m_mmap.lower_bound(key);
 if (p == m_mmap.end())
 return Iterator();
 return Iterator(m_mmap, p);
 }
 Iterator findEqualOrPredecessor(std::string key) const
 {
 MMapIterator p = m_mmap.upper_bound(key);
 if (p == m_mmap.begin())
 return Iterator();
 return Iterator(m_mmap, --p);
 }
 
 private:
 MMap m_mmap;
 
 // To prevent MultiMaps from being copied or assigned, declare these members
 // private and do not implement them.
 MultiMap(const MultiMap& other);
 MultiMap& operator=(const MultiMap& rhs);
 };
 
 #endif // MULTIMAP_INCLUDED
*/
#endif // defined(__Project_4__MultiMap__) //

 
