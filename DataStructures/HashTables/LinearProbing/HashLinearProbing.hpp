#pragma once

#include<iostream> //std::cin, std::cout

#include<vector> //std::vector
#include<string> //std::string
#include<list>	//std::list

#include <functional> //std::hash

typedef int data_type;
typedef std::string key_type;

class HashTable {

	typedef struct {

		key_type key;
		data_type data;

	} table_elem;

	using hash_table = std::vector<table_elem>;

private:

	hash_table table;

	size_t logicFill;

	static const size_t STEP;

public:

	HashTable(size_t size) : table(size * 2), logicFill(0) {


	}

	//big 4 / 7 ?!
	//the ones generated by the compiler himself
	//will do the trick

public:


	//the hash function will be one for all hash tables
	static size_t hashFunction(const key_type&, size_t);

	//basic interface
	void put(const key_type&, const data_type&);

	data_type get(const key_type& key);

	void erase(const key_type& key);

private:

	//helper for re-sizing the hash table
	void rehash();

};

const size_t HashTable::STEP = 1; //gcd(STEP,size) == 1 !!!

size_t HashTable::hashFunction(const key_type& key, const size_t size) {

	//C++ 11 way : 
	
	//making an temporary instance of hash<string> -> object which is a function,
	//then call it with the key
	return std::hash<std::string>{}(key) % size;

}

void HashTable::put(const key_type& key, const data_type& data) {

	size_t index = hashFunction(key, table.size());

	if (logicFill * 2 >= table.size()) {

		rehash();
		index = hashFunction(key, table.size());
	}

	//searching for the first free position
	unsigned int trys = table.size();

	while (table[index].key != "" && --trys)
		index = (index + STEP) % table.size();

	if (table[index].key == "") { //successfully found a free position

		table[index].key = key;
		table[index].data = data;

		logicFill++;
	}

	std::cout << "stored at hash " << index << std::endl;

}

data_type HashTable::get(const key_type& key) {

	size_t index = hashFunction(key, table.size());

	//searching for the first free position
	size_t trys = table.size();

	while (table[index].key != key && table[index].key != "" && --trys)
		index = (index + STEP) % table.size();

	if (table[index].key == key) {

		return table[index].data;
	}

	throw std::logic_error("there isn't element with such key\n");

}



void HashTable::erase(const key_type& key) {

	size_t index = hashFunction(key, table.size());

	//searching for the first free position
	size_t trys = table.size();

	while (table[index].key != key && table[index].key != "" && --trys)
		index = (index + STEP) % table.size();

	if (table[index].key != key)
		throw std::logic_error("there isn't element with such key\n");

	//at index there is the wanted element

	
	size_t indexNext = (index + STEP) % table.size();

	//moving it down the cluster
	while (table[indexNext].key == table[index].key) {

		std::swap(table[indexNext], table[index]);

		indexNext = (indexNext + STEP) % table.size();
		index = (index + STEP) % table.size();
	}

	//now the wanted element is a the bottom of the cluster
	//we can remove it

	table[index].key = "";
	table[index].data = -1; //clear for more complex data
	--logicFill;

	
}

void HashTable::rehash() {

	//debug reasons
	std::cout << "\n...rehashing ...\n";


	//taking all old elements
	hash_table oldTable = std::move(table);

	//in this line our table is empty object
	table.resize(oldTable.size() * 2);

	//for each element form the old table ...
	for (auto el : oldTable) { 		
		put(el.key, el.data); //put it in the now table
		//which will lead to re-calculating the hash values
		
		--logicFill; //because put will increase the logic size
	} 

	std::cout << ".............\n";

}
