//
//  MultiMap.cpp
//  Project_4
//
//  Created by Jasmine on 3/8/14.
//  Copyright (c) 2014 Jasmine. All rights reserved.
//

#include "MultiMap.h"


MultiMap::MultiMap()
{
    m_root = nullptr;
}

MultiMap::~MultiMap()                       // correct implementation???
{
    clear();
}


void MultiMap::clear()                      // correct?
{
    delete m_root;
}

void MultiMap::insert(std::string key, unsigned int value)
{
    if (m_root == nullptr)
    {
        m_root = new node;
        m_root->m_key = key;
        m_root->m_left = nullptr;
        m_root->m_right = nullptr;
        m_root->m_parent = nullptr;
        
        m_root->m_head = new node::listNode;
        m_root->m_head->ln_value = value;
        m_root->m_head->next = nullptr;
        m_root->m_head->prev = nullptr;
        return;
    }
    node *current = new node;
    current = m_root;
    for (; ; )
    {
        node::listNode *curHead = new node::listNode;
        curHead = current->m_head;
        //node::listNode *latest = new node::listNode;
        
        if (key == current->m_key)
        {
            node::listNode *latest = new node::listNode;        // Insert at top
            latest->ln_value = value;
            latest->next = curHead;          // Next pointer becomes the current m_head
            if (curHead != nullptr)
            {
                while (curHead->prev != nullptr) {
                    curHead = curHead->prev;
                }
                curHead->prev = latest;     // fixed.
            }
            latest->prev = nullptr;         // There is nothing above the latest node
            curHead = latest;
            return;
        }
        else if (key < current->m_key)
        {
            if (current->m_left != nullptr)
            {
                current = current->m_left;
            }
            else
            {
                current->m_left = new node;
                current->m_left->m_key = key;
                current->m_left->m_head = new node::listNode;   //don't forget to actually create the node.
                
                current->m_left->m_head->ln_value = value;
                current->m_left->m_parent = current;                    // parent pointer
                return;
            }
        }
        else if (key > current->m_key)
        {
            if (current->m_right != nullptr)
                current = current->m_right;
            else
            {
                current->m_right = new node;
                current->m_right->m_key = key;
                current->m_right->m_head = new node::listNode;
                
                current->m_right->m_head->ln_value = value;
                current->m_right->m_parent = current;                    // parent pointer
                return;
            }
        }
    }
}

MultiMap::Iterator MultiMap::findEqual(std::string key) const
{
    MultiMap::Iterator it(m_root);
    
    while (it.next()) {
        if (it.getKey() == key)
            return it;
    }
    while (it.prev()) {
        if (it.getKey() == key)
            return it;
    }
    return MultiMap::Iterator();
}

MultiMap::Iterator MultiMap::findEqualOrSuccessor(std::string key) const
{
    MultiMap::Iterator it(m_root);
    while (it.next()) {
        if (it.getKey() >= key)
            return it;
    }
    while (it.prev()) {
        if (it.getKey() >= key)
            return it;
    }
    return MultiMap::Iterator();
}

MultiMap::Iterator MultiMap::findEqualOrPredecessor(std::string key) const
{
    MultiMap::Iterator it(m_root);
    while (it.next()) {
        if (it.getKey() <= key)
            return it;
    }
    while (it.prev()) {
        if (it.getKey() <= key)
            return it;
    }
    return MultiMap::Iterator();
}

MultiMap::Iterator::Iterator()
{
    m_isValid = false;
}

MultiMap::Iterator::Iterator(node* p_node)
{
    //m_node = new node;
    m_node = p_node;
    m_isValid = true;
}

MultiMap::Iterator::~Iterator()
{
}

bool MultiMap::Iterator::valid() const
{
    return m_isValid;
}

std::string	MultiMap::Iterator::getKey() const
{
    if (!valid())
        return "";
    else
    {
        return m_node->m_key;
    }
}

unsigned int MultiMap::Iterator::getValue()	const
{
    if (!valid())
        return -1;
    else{
        return m_node->m_head->ln_value;
    }
}

bool MultiMap::Iterator::next()
{
    if (!valid())
        return false;
    
    if (m_node->m_head->prev != nullptr)            //get the association
    {
        m_node->m_head = m_node->m_head->prev;
        return true;
    }
    
    if (m_node->m_right != nullptr)
    {
        m_node = m_node->m_right;
        while (m_node->m_left != nullptr) {
            m_node = m_node->m_left;
        }                                           //how do yo iterate through values.
        return true;
    }
    
    node *p = m_node->m_parent;
    while (p != nullptr && m_node == p->m_right)
    {
        m_node = p;
        p = p->m_parent;
    }
    if (p == nullptr) {
        m_isValid = false;
        return false;
    }
    else{
        m_node = p;
        return true;
    }
}

bool MultiMap::Iterator::prev()
{
    if (!valid())
        return false;
    
    if (m_node->m_head->next != nullptr)            //get the association
    {
        m_node->m_head = m_node->m_head->next;
        return true;
    }
    
    if (m_node->m_left != nullptr)          //if left node is available, set left node to m_node.
    {
        m_node = m_node->m_left;
        while (m_node->m_right != nullptr) {
            m_node = m_node->m_right;
        }
        return true;
    }
    
    node *p = m_node->m_parent;
    while (p != nullptr && m_node == p->m_left)
    {
        m_node = p;
        p = p->m_parent;
    }
    if (p == nullptr) {
        m_isValid = false;
        return false;
    }
    else{
        m_node = p;
        return true;
    }
}




































