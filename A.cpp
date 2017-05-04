#include <iostream>
using namespace std;

int findBestI( int **profit, int center, int storeNum, int **demand )
{
	int max = 0;
	for( int i = 0; i < storeNum; i++)
	{
		if( profit[i][center] > profit[max][center] && demand[i][2] > 0 )
		{
			max = i;
		}
	}
	if(profit[max][center] == 0)
		return -1;
		
	profit[max][center] = 0;
	return max;
}
void setTable2( int **profitTable ,int **profitTable2, int centerNum, int storeNum, int **transAm )
{
	//consider transAm
	for( int i = 0; i < storeNum; i++ )
	{
		for( int j = 0; j < centerNum; j++ )
		{
			profitTable2[i][j] = profitTable[i][j] * transAm[i][j]; 
		}
	}
}

int* findBestJ( int  **centerInfo, int **storeInfo, int **profitTable, int centerNum, int storeNum, bool *storeSet, bool *centerSet)
{
	int relatStoreNum = 0;
	int maxProfit = 0;
	int *bestJ = new int[relatStoreNum +2]; 
	//first for netProfit,second for bestJ's index,third for relatStoreNum,others for relative I's index 
	int** profitTable2 = new int*[storeNum];
	int **transAm = new int *[storeNum];
	
	//initialization
	for( int a = 0; a < relatStoreNum +2; a++)
	{
		bestJ[a] = 0;
	}
	for( int i = 0; i < storeNum; i++ )
	{
		transAm[i] = new int[centerNum];
		profitTable2[i] = new int[centerNum];
		for(int j = 0; j < centerNum; j++)
		{
			transAm[i][j] = centerInfo[j][2] < storeInfo[i][2]?centerInfo[j][2]:storeInfo[i][2];
		}
	}
	setTable2( profitTable, profitTable2, centerNum, storeNum, transAm);
	
	for( int j = 0; j < centerNum; j++ )
	{
		if(centerSet[j] == false)
		{
			int profit = 0;
			int residualCap = centerInfo[j][2];
		
			int a = 0;
			int bestI = findBestI( profitTable2, j, storeNum, storeInfo );
			while( residualCap && bestI != -1) //center still have capacity
			{
				residualCap -= transAm[bestI][j];
				profit += profitTable[bestI][j] * transAm[bestI][j];
			
				bestI = findBestI( profitTable2, j, storeNum, storeInfo );
				a++;	
			}

			if( profit > maxProfit )
			{
				maxProfit = profit;
				bestJ[1] = j;
				relatStoreNum = a;
			}
		}
		
	}
	bestJ[0] = maxProfit ;
	bestJ[2] = relatStoreNum;
	
	//reset setTale2
	setTable2( profitTable, profitTable2, centerNum, storeNum, transAm);
	
	for( int a = 0; a < relatStoreNum; a++ )
	{
		bestJ[a + 3] = findBestI( profitTable2, bestJ[1], storeNum, storeInfo );
	}

	return bestJ;
}


