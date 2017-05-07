#include<iostream>
using namespace std;

int transInfoC[2] = {0};
//bestJ = bestJ[1] = bestCen,centerCapa = centerInfo[bestCen][2];
int nowYouSeeMe(int storeNum, int bestJ, bool *storeSet, int **profitTable, int **storeInfo, int centerCapa, int transInfoC[2]){
	int *storeDem = new int[storeNum];
	for(int i = 0; i < storeNum; i++){
		storeDem[i] = storeInfo[i][2];
	}

	int transStore = -1, transAm = 0, profit = 0, category = 0;
	for(int i = 0; i < storeNum; i++){
		int temPro = 0, type = 0;
		if(storeSet[i] && profitTable[i][bestJ] && storeDem[i] && centerCapa){ //if the store & center are built and still have demand & capacity
			if(storeDem[i] >= centerCapa){
				temPro = profitTable[i][bestJ] * centerCapa;
				type = 0;//if demand >= capacity, to know which amount is used
			}
			else{
				temPro = profitTable[i][bestJ] * storeDem[i];
				type = 1;
			}
			if(temPro > profit){
				profit = temPro;
				transStore = i;
				category = type;
				if(category){
					transAm = storeDem[transStore];
				}
				else{
					transAm = centerCapa;
				}
			}
		}
	}
	
	if(profit > 0){
		transInfoC[0] = transAm;
		transInfoC[1] = transStore;
	}
	
	delete[]storeDem;
	return profit;
}
