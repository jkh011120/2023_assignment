#include<iostream>
#include<fstream>

using namespace std;



typedef struct SC{
	long long Key = -1;
	int Next = -1;	
}SC;


void insert(SC data[], long long key);
int find_NULL(SC data[]);
bool check(SC data[],long long key);
void remove(SC data[], long long key);


void insert(SC data[], long long key){
	int hash_key = key % 16;
	int index = hash_key;
	
	//insert first_key 
	if(data[hash_key].Key ==  -1) {
		data[hash_key].Key = key;
		return;
	}
	
	// find index or can't
	int push = find_NULL(data); 
	if(push == -1) return;
	//isnert key
	data[push].Key = key;
	
	//insert next index
	while(1){
		if(data[index].Next == -1){
			data[index].Next = push;
			break;
		}
		else{
			index = data[index].Next;
		}
	}	
	
}

//return index
int find_NULL(SC data[]){
	for(int i = 16; i < 32; i++){
		if(data[i].Key == -1) return i;
	}
	return -1;
}


// have key  => return true
bool check(SC data[], long long key){
	for(int i = 0; i < 32; i++){
		if(data[i].Key == key) return true;
	}
	return false;
}


void remove(SC data[], long long key){
	int hash_key = key % 16;
	int index = hash_key;
		
	while(1){
		
		if(data[index].Key == key){
			
			int next = data[index].Next;
			
			data[index].Key = data[data[index].Next].Key;
			data[index].Next = data[data[index].Next].Next;
		
			data[next].Key = -1;
			data[next].Next = -1;
			return;
		}
		
		index = data[index].Next;
		
	}	
	
}




void print_result(SC data[]){
	
	ofstream fout;
	fout.open("result.txt");
	
	
	for(int i = 0; i < 16; i++){
		fout << i << ":";
		int index = i;
		while(1){
			if(index == -1) break;
			fout << data[index].Key << ",";
			index = data[index].Next;
		}
		if(index == i) fout << "-1,";
		fout << "\n";	
	}
	
	fout.close();
}




int main(){
	
	// main : 0 ~ 15    overflow : 16 ~ 31
	SC hash[32] = {};
	//cmd start. 
	ifstream fin;
	fin.open("hash_cmd.txt");
	
	while(1){
		char cmd = 0;
		long long num = 0;
		if(fin.eof())break;
		fin >> cmd >> num;
//		cout << cmd << " " << num << " \n";
		
		if(cmd == 'i'){
			if(check(hash,num)) continue;
			else insert(hash,num);
		}
		if(cmd == 'r'){
			if(!check(hash,num)) continue;
			else remove(hash, num);
		}

//		cout << "     ";
//		for(int i = 0; i < 32; i++){
//			cout << hash[i].Key << " ";
//		}
//		cout << "\n";
	
	}
	//end 
	fin.close();
	
	print_result(hash);
	
	
//	ofstream fout;
//	fout.open("test.txt");
//	
//	fout.close();
	
	return 0;
}
