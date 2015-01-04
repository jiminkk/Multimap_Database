//
//  Database.cpp
//  Project_4
//
//  Created by Jasmine on 3/12/14.
//  Copyright (c) 2014 Jasmine. All rights reserved.
//

#include "Database.h"
#include "Tokenizer.h"
#include "http.h"
#include <iostream>
#include <fstream>
using namespace std;

Database::Database()
{
    
}

Database::~Database()
{
    std::vector<MultiMap*>::iterator it;
    std::vector<FieldDescriptor*>::iterator it2;
    
    for (it = m_fieldIndex.begin(); it != m_fieldIndex.end(); ++it)
        delete *it;
    for (it2 = m_schema.begin(); it2 != m_schema.end(); ++it2)
        delete *it2;
}

bool Database::specifySchema(const std::vector<FieldDescriptor> &schema)
{
    //traverse through vector of FieldDescriptors
    //then insert each FD into MultiMap
    
    std::vector<FieldDescriptor>::const_iterator it;
    int countIndexed = 0;
    
    for (it = schema.begin(); it != schema.end(); ++it)
    {
        if (it->index == Database::it_indexed) {
            m_fieldIndex.push_back(new MultiMap);             // initialized MultiMaps?
            countIndexed++;
        }
        m_schema.push_back(new FieldDescriptor);
    }
    for (int i = 0; i < m_schema.size(); i++) {
        m_schema[i]->index = schema[i].index;
        m_schema[i]->name = schema[i].name;
    }
    
    if (countIndexed < 1)
        return false;
    return true;
}

bool Database::addRow(const std::vector<std::string>& rowOfData)
{
    if (rowOfData.size() != m_schema.size())
        return false;
    
    m_rows.push_back(rowOfData);
    unsigned int sizeOfm_rows = m_rows.size();
    
    for (int i = 0; i < rowOfData.size(); i++)
    {
        m_fieldIndex.push_back(new MultiMap);
        //std::cerr << rowOfData[i] << std::endl;
        //std::cerr << rowOfData.size() << std::endl;
        //std::cerr << m_rows.size();
        
        if (m_schema[i]->index == it_indexed)
            m_fieldIndex[i]->insert(rowOfData[i], sizeOfm_rows-1);
    }
    return true;
}

bool Database::loadFromURL(std::string url)
{
    std::string data;
    if (!HTTP().get(url, data))
        return false;
    Tokenizer t(data, "\n");
    std::string w;
    
    if (t.getNextToken(w))                  // Get first line.
    {
        Tokenizer t2(w, ",");
        std::string w2;
        while (t2.getNextToken(w2)) {                   // w2 = first line with "*"
            Tokenizer t3(w2, "*");
            std::string w3;
            if (t3.getNextToken(w3)) {
                FieldDescriptor* fd = new FieldDescriptor;
                fd->name = w3;
                if (w3 != w2){
                    fd->index = it_indexed;
                    //std::cerr << w3 << std::endl;
                }
                else{
                    fd->index = it_none;
                    //std::cerr << "nonindexed: " << w3 << std::endl;
                }
                m_schema.push_back(fd);                                         // Load schema.
                //std::cerr << w3 << std::endl;
            }
            else
                return false;
        }
    }
    else
        return false;
    //for (int i = 0; i < m_schema.size(); i++)             // test.
    //    std::cerr << m_schema[i]->name << std::endl;
    
    while (t.getNextToken(w))                           //Import all rows.
    {
        //std::cerr << w << std::endl;
        std::vector<std::string> stringInEachRow;
        Tokenizer row(w, ",");
        std::string rowString;
        int count = 0;
        while (row.getNextToken(rowString))
        {
            count++;
            if (count > m_schema.size())
                break;
            stringInEachRow.push_back(rowString);
            //std::cerr << rowString << std::endl;
        }
        //std::cerr << rowString << std::endl;
        addRow(stringInEachRow);
    }
    //for (int i = 0; i < m_rows.size(); i++)             // test.
    //    std::cerr << m_rows[i][3] << std::endl;
    //std::cerr << m_rows.size() << std::endl;
    //std::cerr << m_fieldIndex.size() << std::endl;
    return true;
}

bool Database::loadFromFile(std::string filename)
{
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Failure" << endl;
        return false;
    }
    std::string s;
	getline(infile, s);
    //cerr << s << endl;
	if ( ! infile)
    {
	    cerr << "End of file when trying to read a string" << endl;
        return false;
    }
    
    Tokenizer t2(s, ",");
    std::string w2;
    while (t2.getNextToken(w2)) {                   // w2 = first line with "*"
        Tokenizer t3(w2, "*");
        std::string w3;
        if (t3.getNextToken(w3)) {
            FieldDescriptor* fd = new FieldDescriptor;
            fd->name = w3;
            if (w3 != w2){
                fd->index = it_indexed;
                //std::cerr << w3 << std::endl;
            }
            else{
                fd->index = it_none;
                //std::cerr << "nonindexed: " << w3 << std::endl;
            }
            m_schema.push_back(fd);                                         // Load schema.
            //std::cerr << w3 << std::endl;
        }
    }
    string s2;
    int lineCount = 0;
    while (getline(infile, s2))
    {
        lineCount++;
        if (lineCount == 0) {
            continue;
        }
        //std::cerr << w << std::endl;
        std::vector<std::string> stringInEachRow;
        Tokenizer row(s2, ",");
        std::string rowString;
        int count = 0;
        while (row.getNextToken(rowString))
        {
            count++;
            if (count > m_schema.size())
                break;
            stringInEachRow.push_back(rowString);
            //std::cerr << rowString << std::endl;
        }
        //std::cerr << rowString << std::endl;
        addRow(stringInEachRow);
    }
    //for (int i = 0; i < m_rows.size(); i++)             // test.
    //    std::cerr << m_rows[i][5] << std::endl;
    //std::cerr << m_rows.size() << std::endl;
    //std::cerr << m_fieldIndex.size() << std::endl;
    
    return true;
}

int Database::getNumRows() const
{
    return m_rows.size();
}

bool Database::getRow(int rowNum, std::vector<std::string> &row) const
{
    if (rowNum < 0)
        return false;
    
    for (size_t i = 0; i < m_rows[rowNum].size(); i++)
        row.push_back(m_rows[rowNum][i]);
    return true;
}

int Database::search(const std::vector<SearchCriterion> &searchCriteria, const std::vector<SortCriterion> &sortCriteria, std::vector<int> &results)
{
    vector<int> rowNums;
    int value = 0;
    
    for (int i = 0; i < searchCriteria.size(); i++)
    {
        for (int j = 0; j < m_schema.size(); j++)
        {
            if (searchCriteria[i].fieldName == m_schema[j]->name)
            {
                if (m_schema[j]->index == it_none) {            // check for errors.
                    results.clear();
                    return ERROR_RESULT;
                }
            }                                                   // check for errors.
            if (searchCriteria[i].maxValue == "" && searchCriteria[i].minValue == "") {
                results.clear();
                return ERROR_RESULT;
            }
            for (int t = 0; t < m_rows.size(); t++)
            {
                if (m_rows[t][i] >= searchCriteria[i].minValue || m_rows[t][i] <= searchCriteria[i].maxValue)
                {
                    if (m_fieldIndex[i]->findEqual(m_rows[t][i]).getKey() == m_rows[t][i])
                        value = m_fieldIndex[i]->findEqual(m_rows[t][i]).getValue();
                    rowNums.push_back(value);
                }
            }
        }
    }
    vector<int> matchingRows;
    int numMatchingRows = 0;
    for (int i = 0; i < rowNums.size(); i++)
    {
        int increment = 0;
        for (int j = 0; j < rowNums.size(); j++)
        {
            if (rowNums[i] == rowNums[j])
                increment++;
        }
        if (increment == searchCriteria.size())
        {
            numMatchingRows += increment;               //number of matching rows among all search criteria.
            results.push_back(rowNums[i]);
        }
    }
    
    vector<int> temp;
    if (sortCriteria[0].ordering == Database::ot_descending) {      // sort first criteria.
        for (size_t i = results.size()-1; i >= 0 ; i--)
        {
            temp.push_back(results[i]);
        }
        results.clear();
        for (int j = 0; j < temp.size(); j++) {
            results.push_back(results[j]);
        }
    }
    
    return numMatchingRows;
}



































