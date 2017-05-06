#include <iostream>
#include <algorithm>
using namespace std;

functionA(int storeNum, int centerNum, int cost, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo){
	int *decide = new int[5]; //maxNetProfit , center , store , build(1)/trans(0) , transAm
	//initialize
	for( int i = 0; i < 5; i++ ){
		decide[i] = 0;
	}
	
	for( int j = 0; j < centerNum; j++ ){
		if( centerSet[j] == false ){
			centerSet[j] = true;  //assume it is set
			
			newStore( j, storeNum, storeSet, centerSet, profitTable, storeInfo, centerInfo);  //call functionB
			int profitB = netProfitOfNewStore(j, storeNum, centerSet, profitTable, storeInfo, centerInfo );
			int *transInfo = new int[2];  //prepare for functionC
			for( int i = 0; i < 2; i++ ){
				transInfo[i] = 0;
			}
			int profitC = functionC();  //call functionC
			if( profitB == profitC )
			{
				int profit = profitB;
			}
			else
				int profit = max( profitB, profitC );
			
			if( profit > decide[0] ){
				decide[0] = max(profitB,profitC) - centerInfo[j][3];  //maxNetProfit
				decide[1] = j;  //center
				if( profit == profitB ){
					//decided by functionB
					decide[2] = numOfNewStore(j, storeNum, centerSet, profitTable, storeInfo, centerInfo );  //store
					decide[3] = 1;  //build
					decide[4] = transOfNewStore;  //transAm
				}
				else{
					//decided by functionC
					decide[2] = transInfo[1];  //store
					decide[3] = 0;  //trans
					decide[4] = transInfo[0];  //transAm
				}
			}
			
			centerSet[j] = false;  //delete assumption
		}
	}
	return decide;
} 
