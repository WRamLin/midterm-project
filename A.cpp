#include <iostream>
using namespace std;

int setTransAm(int cap, int dem);
void setTable(int **profitTable, int storeNum, int residualCap, int **storeInfo, bool *storeSet);
int findBestI( int **profit, int center, int storeNum );
int *findRelatStore(int *bestJ, int **profitTable, int storeNum);
int* findBestJ( int  **centerInfo, int **storeInfo, int **profitTable, int centerNum, int storeNum, bool *storeSet, bool *centerSet);


int* findBestJ( int  **centerInfo, int **storeInfo, int **profitTable, int centerNum, int storeNum, bool *storeSet, bool *centerSet)
{
	int relatStoreNum = 0;
	int maxProfit = 0;
	int bestCen = 0;
	
	for( int j = 0; j < centerNum; j++ )
	{
		if(centerSet[j] == false)
		{
			int profit = 0;
			int residualCap = centerInfo[j][2];
			
			
			setTable(profitTable, storeNum, centerNum, residualCap, storeInfo, storeSet);
			int bestI = findBestI( profitTable, j, storeNum );
			int a = 0;
			while( residualCap && bestI != -1) //center still have capacity
			{
				int transAm = setTransAm(residualCap, storeInfo[bestI][2]);
				residualCap -= transAm;
				profit += profitTable[bestI][j] * transAm;
				profit -= storeInfo[bestI][3];
			
				setTable(profitTable, storeNum, centerNum, residualCap, storeInfo, storeSet);
				bestI = findBestI( profitTable, j, storeNum );
				a++;	
			}
			profit -= centerInfo[j][3];
			if( profit > maxProfit )
			{
				maxProfit = profit;
				bestCen = j;
				relatStoreNum = a;
			}
		}	
	}
	int *bestJ = new int[relatStoreNum +2];
	//first for netProfit,second for bestJ's index,third for relatStoreNum,others for relative I's index
	bestJ[0] = maxProfit;
	bestJ[1] = bestCen;
	bestJ[2] = relatStoreNum;
	for( int a = 0; a < relatStoreNum; a++)
		bestJ[a+3] = 0;
	return bestJ;	
}

int *findRelatStore(int *bestJ, int **profitTable, int storeNum)
{
	for( int a = 0; a < bestJ[2]; a++ )
	{
		bestJ[a + 3] = findBestI( profitTable, bestJ[1], storeNum );
	}
	
	return bestJ;
}
	


int setTransAm(int cap, int dem)
{
	int transAm = (cap > dem? dem:cap);
	
	return transAm;
}

void setTable(int **profitTable, int storeNum, int centerNum, int residualCap, int **storeInfo, bool *storeSet)
{
	//consider transAm & fixed cost of store
	int *transAm = new int[storeNum];
	for( int i = 0; i < storeNum; i++ )
	{
		transAm[i] = setTransAm(residualCap, storeInfo[i][2]);
	}
	for( int j = 0; j < centerNum; j++)
		for( int i = 0; i < storeNum; i++)
		{
			profitTable[i][j] = profitTable[i][j] * transAm[i];
			if( storeSet[i] == false )
			{
				profitTable[i][j] -= storeInfo[i][3];
			}		
		}
}

int findBestI( int **profit, int center, int storeNum )
{
	int max = 0;
	for( int i = 0; i < storeNum; i++)
	{
		if( profit[i][center] > profit[max][center] )
		{
			max = i;
		}
	}
	if(profit[max][center] == 0)
		return -1;
		
	profit[max][center] = 0;
		return max;
}
