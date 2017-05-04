
for(int i=0; i<storeNum; i++){
	if(storeSet[i]==false){
		if(profitTable[i][j]!=0 && centerSet[j]==true){
			if(storeInfo[i][2]<=centerInfo[i][2]){
					netProfit+=(storeInfo[i][4]-(cost*abs(storeInfo[i][0]-centerInfo[j][0])+abs(storeInfo[i][1]-centerInfo[j][1])));
					netProfit-=storeInfo[i][3];
					numOfStores++;
					storeSet[i]=true;		
			}
		}
	}
}

