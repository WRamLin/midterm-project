#include<iostream>
using namespace std;

int **transInfo = new int*[3];
for(int i = 0; i < 2; i++){
	transInfo[i] = new int[storeNum];
	for(int j = 0; j < 2; j++){
		if(i == 0 && j == 0)
		transInfo[i][j] = -1;
		transInfo[i][j] = 0;
	}//record the number of store & center
}
int deliver(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int **transInfo, int time);
int transAm(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int **transInfo){
	int transProfit = 0, time = 0;
	while(deliver(storeNum, centerNum, storeSet, centerSet, profitTable, storeInfo, centerInfo, transInfo, time) == true){
		transProfit += deliver(storeNum, centerNum, storeSet, centerSet, profitTable, storeInfo, centerInfo, transInfo, time);
		time++;
	}//if profit != 0, keep adding gross profit
	transInfo[time][0] = -1;//to know that before[i][0] == -1, there are the record of transmit
	return transProfit;
}

int deliver(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfo[2]){
	int transStore = -1, transCenter = -1, profit = 0, category = 0;
	for(int i = 0; i < storeNum; i++){
		for(int j = 0; j < centerNum; j++){
			int temPro = 0, type = 0;
			if(storeSet[i] && centerSet[j] && profitTable[i][j] && storeInfo[i][2] && centerInfo[j][2]){ //if the store & center are built and still have demand & capacity
				if(storeInfo[i][2] >= centerInfo[j][2]){
					temPro = profitTable[i][j] * centerInfo[j][2];
					type = 0;//if demand >= capacity, to know which amount is used
				}
				else{
					temPro = profitTable[i][j] * storeInfo[i][2];
					type = 1;
				}
				if(temPro > profit){
					profit = temPro;
					transStore = i;
					transCenter = j;
					category = type;
				}
			}
		}
	}
	
	if(profit > 0){
		transInfo[time][0] = category;
		transInfo[time][1] = transStore;
		transInfo[time][2] = transCenter;
	}
	return profit;
}
