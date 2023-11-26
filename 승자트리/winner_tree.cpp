#include<iostream>
#include<fstream>
using namespace::std;


typedef struct Data{
	int size=0; // ũ�� 
	long long arr[100]={0}; // ������ 
	int p=0; // ������ 
} Data;


//����Ȯ��  
long long winner(long long left, long long right){
	if(left <= right) return left;
	else return right;
}

//ù��° ���� Ʈ�� ����� 
void first_data(long long Data[]){
	for(int i = 13; i > 0; i -= 2){
		Data[i/2] = winner(Data[i], Data[i+1]);
	} 
}

//txt���� ������ �ޱ�. 
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

//��Ʈ Ȯ�� 
void print_route(int route[]){
	for(int i = 0; i < 4; i++){
		cout << route[i] << " ";
	}
	cout << "\n";
}

//���� Ʈ�� ���   
void print_tree(long long Data[]){
	for(int i = 0; i < 15; i++) cout << Data[i] << "\n";
} 

//��Ʈ Ȯ�� :: ��ȯ�� = ����. 
long long find_route(long long Data[], int route[]){
	long long winner = Data[0];
	int p = 0;
	int l = p*2 + 1;
	int r = p*2 + 2;
	route[3] = 0;
	for(int i = 0; i < 3; i++){
		if(winner == Data[l]){ // ����
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

//�ٽ� ������ ����. :: ��ȯ�� ���� ��ġ. 
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


//���� Ʈ�� ��ġ��. 
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
	
	//���� �ޱ�.  
	Data file[8]; // 0 ~ 7
	char file_name[] = "input_*.txt";
	for(int i = 0; i < 8; i++){
		file_name[6] = '0' + i;
		get_data(file_name, file[i]);
	}
	
	//ó�� ���� ��� ����. 
	long long Data[15] = {}; 
	for(int i = 0; i < 8; i++){
		Data[7+i] = file[i].arr[file[i].p];
	}
	
	
	ofstream fout;
	fout.open("merged_out.txt");
	
	//ó�� ����Ʈ���� �����, ó�� ��Ʈ ã��. 
	first_data(Data); 
	int route[4] = {0};
	long long winner = find_route(Data, route);
	fout << winner << "\n";
	//print_route(route); 
	for(int i = 0; i < 4; i++){
		fout << route[i] << " ";
	}
	fout << "\n";
	
	//���� ���� ����Ʈ�� 
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
