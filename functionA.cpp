#include <iostream>
#include <algorithm>
using namespace std;

int *coffeeTeaOrMe(int storeNum, int centerNum, int cost, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo){
	int *decide = new int[5]; //maxNetProfit , center , store , build(1)/trans(0) , transAm
	//initialize
	for( int i = 0; i < 5; i++ ){
		decide[i] = 0;
	}
	
	for( int j = 0; j < centerNum; j++ ){
		if( centerSet[j] == false ){
			centerSet[j] = true;  //assume it is set
			
			int *ansB = newStore( j, storeNum, storeSet, centerSet, profitTable, storeInfo, centerInfo);  //call functionB
			int profitB = ansB[0];
			int transInfo[3] = {0};  //prepare for functionC
			int profitC = nowYouSeeMe(storeNum,j,storeSet,profitTable,storeInfo,centerInfo[j][2],transInfo);  //call functionC
			int profit = 0;
			if( profitB == profitC )
				profit = profitB;
			else
				profit = max( profitB, profitC );
			profit -= centerInfo[j][3];
			if( profit > decide[0] ){
				decide[0] = profit;  //maxNetProfit
				decide[1] = j;  //center
				if( profit == profitB ){
					//decided by functionB
					decide[2] = ansB[1];  //store
					decide[3] = 1;  //build
					decide[4] = ansB[2];  //transAm
				}
				else{
					//decided by functionC
					decide[2] = transInfo[1];  //store
					decide[3] = 0;  //trans
					decide[4] = transInfo[0];  //transAm
				}
			}
			delete [] transInfo;
			delete [] ansB;
			centerSet[j] = false;  //delete assumption
		}
	}

	return decide;
} 
