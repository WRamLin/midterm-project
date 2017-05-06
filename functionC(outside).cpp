#include<iostream>
using namespace std;

int transInfo[3] = {0};

int catchMeIfYouCan(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfo[3]){
	int *storeDem = new int[storeNum];
	for(int i = 0; i < storeNum; i++){
		storeDem[i] = storeInfo[i][2];
	}

	int *centerCapa = new int[centerNum];
	for(int i = 0; i < centerNum; i++){
		centerCapa[i] = centerInfo[i][2];
	}
	int transStore = -1, transCenter = -1, transAm = 0, profit = 0, category = 0;
	for(int i = 0; i < storeNum; i++){
		if(storeSet[i]){
			for(int j = 0; j < centerNum; j++){
				int temPro = 0, type = 0;
				if(centerSet[j] && profitTable[i][j] && storeDem[i] && centerCapa[j]){ //if the store & center are built and still have demand & capacity
					if(storeDem[i] >= centerCapa[j]){
						temPro = profitTable[i][j] * centerCapa[j];
						type = 0;//if demand >= capacity, to know which amount is used
					}
					else{
						temPro = profitTable[i][j] * storeDem[i];
						type = 1;
					}
					if(temPro > profit){
						profit = temPro;
						transStore = i;
						transCenter = j;
						category = type;
						if(category){
							transAm = storeDem[transStore];
						}
						else{
							transAm = centerCapa[transCenter];
						}
					}
				}
			}
		}
		
	}
	
	if(profit > 0){
		transInfo[0] = transAm;
		transInfo[1] = transStore;
		transInfo[2] = transCenter;
	}
	
	delete[]storeDem;
	delete[]centerCapa;
	return profit;
}
