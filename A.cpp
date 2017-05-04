#include <iostream>
using namespace std;

int findBestI( int **profit, int center, int storeNum, bool *storeSet )
{
	int max = 0;
	for( int i = 0; i < storeNum; i++)
	{
		if( profit[i][center] > profit[max][center] && storeSet[i] == false)
		{
			max = i;
		}
	}
	if(profit[max][center] == 0)
		return -1;
		
	profit[max][center] = 0;
	return max;
}
void setTable2( int **profitTable ,int **profitTable2, int centerNum, int storeNum, int **capacity, int **demand )
{
	for( int i = 0; i < storeNum; i++ )
	{
		for( int j = 0; j < centerNum; j++ )
		{
			profitTable2[i][j] = profitTable[i][j] * ( capacity[j][2] < demand[i][2]?capacity[j][2]:demand[i][2]); 
		}
	}
}

int* findBestJ( int  **centerInfo, int **storeInfo, int **profitTable, int centerNum, int storeNum, bool *storeSet, bool *centerSet)
{
	int relatStoreNum = 0;
	int maxProfit = 0;
	int *bestJ = new int[relatStoreNum +2]; //first for bestJ's index,second for maxNetProfit,others for relative I's index 
	int** profitTable2 = new int*[storeNum];
	
	//initialization
	for( int a = 0; a < relatStoreNum +2; a++)
	{
		bestJ[a] = 0;
	}
	for( int i = 0; i < storeNum; i++ )
	{
		profitTable2[i] = new int[centerNum];
	}
	setTable2( profitTable, profitTable2, centerNum, storeNum, centerInfo, storeInfo);
	
	for( int j = 0; j < centerNum; j++ )
	{
		if(centerSet[j] == false)
		{
			int profit = 0;
			int residualCap = centerInfo[j][2];
		
			int a = 0;
			int bestI = findBestI( profitTable2, j, storeNum, storeSet );
			while( residualCap && bestI != -1) //center still have capacity
			{
				if( storeInfo[bestI][2] <= residualCap )
				{
					residualCap -= storeInfo[bestI][2];
					profit += profitTable[bestI][j] * storeInfo[bestI][2];
				}			
				else
				{
				residualCap = 0;
				profit += profitTable[bestI][j] * residualCap;
				}
				a++;
				bestI = findBestI( profitTable2, j, storeNum, storeSet );	
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
	
	//reset
	setTable2( profitTable, profitTable2, centerNum, storeNum, centerInfo, storeInfo);
	
	for( int a = 0; a < relatStoreNum; a++ )
	{
		bestJ[a + 3] = findBestI( profitTable2, bestJ[1], storeNum, storeSet );
	}

	return bestJ;
}


