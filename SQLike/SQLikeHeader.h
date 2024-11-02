#pragma once
#include <iostream>
#include <cstring>  // for strcpy_s

//daca te prind ca te plangi ca nu avem sqllikeheader.cpp
//ma doare capu ca imi da compiler error C2011 type redefinition
//lasa asa sau fa tu dupa ce merge xd

enum class DataType
{
    INT,
    DOUBLE,
    NONVARCHAR,
    VARCHAR
};

union DataUnion {
    int intval;
    double dblval;
    const char* nonvarchar;
    char* varchar;

    DataUnion() : intval(0) {}  // Default constructor
    DataUnion(int val) : intval(val) {}
    DataUnion(double val) : dblval(val) {}
    DataUnion(const char* val) : nonvarchar(val) {}
};

class Data {
private:
    DataType type;
    DataUnion value;
public:
    DataType getDataType()
    {
        return type;
    }
    DataUnion getValue()
    {
        return value;
    }

    Data() : type(DataType::INT), value(0) {}
    Data(int val) : type(DataType::INT), value(val) {}
    Data(double val) : type(DataType::DOUBLE), value(val) {}
    Data(const char* val) : type(DataType::NONVARCHAR), value(val) {}
    Data(const char* val, unsigned int size) : type(DataType::VARCHAR) {
        value.varchar = new char[size + 1];
        strcpy_s(value.varchar, size + 1, val);
    }

    Data(const Data& other) {
        type = other.type;
        switch (type) {
        case DataType::INT:
            value.intval = other.value.intval;
            break;
        case DataType::DOUBLE:
            value.dblval = other.value.dblval;
            break;
        case DataType::NONVARCHAR:
            value.nonvarchar = other.value.nonvarchar;
            break;
        case DataType::VARCHAR:
            unsigned int len = strlen(other.value.varchar);
            value.varchar = new char[len + 1];
            strcpy_s(value.varchar, len + 1, other.value.varchar);
            break;
        }
    }

    ~Data() {
        if (type == DataType::VARCHAR && value.varchar != nullptr) {
            delete[] value.varchar;
            std::cout << "Deleted dynamic varchar\n";
        }
    }

    void print() const  // this will not alter member values
    {
        switch (type) {
        case DataType::INT:
            std::cout << "Int: " << value.intval << std::endl;
            break;
        case DataType::DOUBLE:
            std::cout << "Double: " << value.dblval << std::endl;
            break;
        case DataType::NONVARCHAR:
            std::cout << "Non-varchar string: " << value.nonvarchar << std::endl;
            break;
        case DataType::VARCHAR:
            std::cout << "Dynamic varchar: " << value.varchar << std::endl;
            break;
        }
    }
};

//incomplete below
class row
{
private:
	Data* records;
public:
    row()
    {
        records = new Data[1];
    }
};

class column
{
private:
	char* columnName;
	DataType columnType;
public:
	char* getColumnName();
	void setColumnName();
};

class table
{
private:
	char* table_name;
	column* columns;
	row* rows;
public:
};

class database
{
private:
	char* database_name;
	table* tables;

public:
    void createTable();
};