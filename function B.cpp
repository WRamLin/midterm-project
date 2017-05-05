#include <iostream>
#include <cmath>
using namespace std;

void newStore(int j, int storeNum, int cost, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo){

	bool* tempStoreSet= new bool[storeNum];
	for(int i=0; i<storeNum; i++){
		tempStoreSet[i]=storeSet[i];
	}

	int netProfitB=0;
	int maxProfitB=-1;
	int storeOfMaxB=-1;
	for(int i=0; i<storeNum; i++){
		if(tempStoreSet[i]==false){
			if(profitTable[i][j]!=0 && centerSet[j]==true){
				if(storeInfo[i][2]<=centerInfo[i][2]){
					netProfitB+=(storeInfo[i][4]-(cost*abs(storeInfo[i][0]-centerInfo[j][0])+abs(storeInfo[i][1]-centerInfo[j][1])));
					netProfitB-=storeInfo[i][3];
					if(netProfitB>maxProfitB){
						maxProfitB=netProfitB;
						storeOfMaxB=i;
					}		
				}
			}
		}
	}
}

int netProfitOfNewStore(int j, int storeNum, int cost, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo){
	newStore(storeNum, cost, *storeSet, *centerSet, **profitTable, **storeInfo, **centerInfo);
	return maxProfitB;
}

int numOfNewStore(int j, int storeNum, int cost, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo){
	newStore(storeNum, cost, *storeSet, *centerSet, **profitTable, **storeInfo, **centerInfo);
	return storeOfMaxB;
}
