#include<iostream>

#define USED true
#define UNUSED false

//the power of the set
const int MAXN = 4;

//the set we are permuting
int given[MAXN] = { 3,11,23,7};

//buffer for generating the current permutation
int curPerm[MAXN];

//used in current permutation -> TRUE , else -> FALSE
bool used[MAXN] = { UNUSED, }; 


void print() {

	for (int i = 0; i < MAXN; i++)
		std::cout << curPerm[i] << " ";

	std::cout << std::endl;

}

// permuting the i-th element
void perm(int i) {

	//the bottom of the recursion
	if (i >= MAXN) {

		print();
		return;
	}


	for (int k = 0; k < MAXN; k++) {
		
		//trying to use the k-th element of the set
		if (used[k] == UNUSED) {

			used[k] = USED; //marking it as used 
			curPerm[i] = given[k];  //saving it's value
			perm(i + 1); //generating the next element
			used[k] = UNUSED; //unmarking after coming back form the recursion call

		}
	}

}




int main() {

	perm(0);

	return 0;
}