#include <iostream>
using namespace std;

int* newStore(int j, int storeNum, int cost, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo){

	int ansB[3]={0};
	int netProfitB=0;
	int maxProfitB=-1;
	int storeOfMaxB=-1;
	for(int i=0; i<storeNum; i++){
		if(storeSet[i]==false){
			if(profitTable[i][j]!=0 && centerSet[j]==true){
				if(storeInfo[i][2]<=centerInfo[i][2]){
					netProfitB+=(profitTable[i][j]*storeInfo[i][2]);
					netProfitB-=storeInfo[i][3];
					if(netProfitB>maxProfitB){
						maxProfitB=netProfitB;
						storeOfMaxB=i;
					}		
				}
			}
		}
	}
	ansB[0]=maxProfitB;
	ansB[1]=storeOfMaxB;
	ansB[2]=storeInfo[storeOfMaxB][2];
	
	return *ansB;
}



