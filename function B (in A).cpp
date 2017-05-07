#include <iostream>
using namespace std;

int transInfoB[2] = {0};
int newStore(int j, int storeNum, bool* storeSet, int** profitTable, int** storeInfo, int** centerInfo, int transInfoB[2]){	
	int netProfitB=0;
	int maxProfitB=-2147483648;
	int storeOfMaxB=-1;
	int category = -1;
	for(int i=0; i<storeNum; i++){
		if(storeSet[i]==false){
			int tempCate = 0;
			if(profitTable[i][j]!=0){
				if(storeInfo[i][2]<=centerInfo[j][2]){
					netProfitB+=(profitTable[i][j]*storeInfo[i][2]);
					netProfitB-=storeInfo[i][3];	
				}
				else{
					netProfitB+=(profitTable[i][j]*centerInfo[j][2]);
					netProfitB-=storeInfo[i][3];
					tempCate = 1;
				}
				if(netProfitB>maxProfitB){
					maxProfitB=netProfitB;
					storeOfMaxB=i;
					category = tempCate;
				}
			}
		}
	}
	ansB[0]=storeOfMaxB;
	if(category)
		ansB[1] = centerInfo[j][2];
	else
		ansB[1]=storeInfo[storeOfMaxB][2];
	return maxProfitB;
}



