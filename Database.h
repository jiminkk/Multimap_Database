//
//  Database.h
//  Project_4
//
//  Created by Jasmine on 3/12/14.
//  Copyright (c) 2014 Jasmine. All rights reserved.
//

#ifndef __Project_4__Database__
#define __Project_4__Database__

#include <iostream>
#include <vector>
#include "MultiMap.h"

class	Database
{
public:
    enum IndexType	{ it_none, it_indexed };
    enum OrderingType	{ ot_ascending,	ot_descending };
	
    struct FieldDescriptor
    {
        std::string	name;
        IndexType index;
    };
	
    struct SearchCriterion
    {
        std::string	fieldName;
        std::string	minValue;
        std::string	maxValue;
    };
	
    struct SortCriterion
    {
        std::string	fieldName;
        OrderingType ordering;
    };
    
    static const int ERROR_RESULT =	-1;
	
    Database();
    ~Database();
    bool specifySchema(const std::vector<FieldDescriptor>& schema);
    bool addRow(const std::vector<std::string>& rowOfData);
    bool loadFromURL(std::string url);
    bool loadFromFile(std::string filename);
    int	getNumRows() const;
    bool getRow(int rowNum, std::vector<std::string>& row) const;
    int	search(const std::vector<SearchCriterion>& searchCriteria, const std::vector<SortCriterion>&	sortCriteria, std::vector<int>&	results);
	
private:
    //	To	prevent	Databases	from	being	copied	or	assigned,	declare	these	members
    //	private	and	do	not	implement	them.
    Database(const	Database&	other);
    Database&	operator=(const	Database&	rhs);
    std::vector<std::vector<std::string>> m_rows;
    std::vector<MultiMap*> m_fieldIndex;
    std::vector<FieldDescriptor*> m_schema;
};



#endif /* defined(__Project_4__Database__) */
