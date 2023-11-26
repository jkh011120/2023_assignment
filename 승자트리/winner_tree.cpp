#include<iostream>
#include<fstream>
using namespace::std;


typedef struct Data{
	int size=0; // 크기 
	long long arr[100]={0}; // 데이터 
	int p=0; // 포인터 
} Data;


//승자확인  
long long winner(long long left, long long right){
	if(left <= right) return left;
	else return right;
}

//첫번째 승자 트리 만들기 
void first_data(long long Data[]){
	for(int i = 13; i > 0; i -= 2){
		Data[i/2] = winner(Data[i], Data[i+1]);
	} 
}

//txt파일 데이터 받기. 
void get_data(char file_name[], Data& data){

	ifstream fin;
	fin.open(file_name);
	data.size = 0;
	while(1){
		int num = 0;
		if(fin.eof())break;
		fin >> data.arr[data.size];
		//cout << data.arr[data.size] << "\n";
		data.size++;
	}
	//cout << "\n";
	fin.close();
}

//루트 확인 
void print_route(int route[]){
	for(int i = 0; i < 4; i++){
		cout << route[i] << " ";
	}
	cout << "\n";
}

//승자 트리 출력   
void print_tree(long long Data[]){
	for(int i = 0; i < 15; i++) cout << Data[i] << "\n";
} 

//루트 확인 :: 반환값 = 승자. 
long long find_route(long long Data[], int route[]){
	long long winner = Data[0];
	int p = 0;
	int l = p*2 + 1;
	int r = p*2 + 2;
	route[3] = 0;
	for(int i = 0; i < 3; i++){
		if(winner == Data[l]){ // 왼쪽
			Data[l] = -1;
			route[2-i] = l;
			p = l;
			l = p*2 + 1;
			r = p*2 + 2;
		}
		else{
			Data[r] = -1;
			route[2-i] = r;
			p = r;
			l = p*2 + 1;
			r = p*2 + 2;
		}
		
	}
	return winner;
}

//다시 데이터 삽입. :: 반환값 삽입 위치. 
long long input_data(long long arr[], Data file[]){
	long long number = 0;
	for(int i = 7; i < 15; i++){
		if(i == 14){
			arr[i] = file[7].arr[++file[7].p];
			number = i;
			break;
		}
		if(arr[i] == -1) {
			arr[i] = file[i%7].arr[++file[i%7].p];
			number = i;
			break;
		}
	}
	return number;
}


//승자 트리 고치기. 
void winner_tree(long long new_input, long long Data[]) {
	 if(new_input%2 == 0){
		new_input--;
	}
	for(int i = 0; i < 3; i++){
		Data[new_input/2] = winner(Data[new_input],Data[new_input+1]);
		new_input /= 2;
		if(new_input%2 == 0){
			new_input--;
		}
	}
}

int main(){
	
	//파일 받기.  
	Data file[8]; // 0 ~ 7
	char file_name[] = "input_*.txt";
	for(int i = 0; i < 8; i++){
		file_name[6] = '0' + i;
		get_data(file_name, file[i]);
	}
	
	//처음 리프 노드 삽입. 
	long long Data[15] = {}; 
	for(int i = 0; i < 8; i++){
		Data[7+i] = file[i].arr[file[i].p];
	}
	
	
	ofstream fout;
	fout.open("merged_out.txt");
	
	//처음 승자트리로 만들기, 처음 루트 찾기. 
	first_data(Data); 
	int route[4] = {0};
	long long winner = find_route(Data, route);
	fout << winner << "\n";
	//print_route(route); 
	for(int i = 0; i < 4; i++){
		fout << route[i] << " ";
	}
	fout << "\n";
	
	//이후 수선 승자트리 
	for(int i = 0; i < 9; i++){
		long long pointer = input_data(Data,file);
		winner_tree(pointer,Data);
		winner = find_route(Data, route);
		fout << winner << "\n";
		for(int i = 0; i < 4; i++){
			fout << route[i] << " ";
		}
		fout << "\n";
	}
	
	fout.close();
	
	
	return 0;
}
