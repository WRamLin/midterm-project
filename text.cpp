#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int posiProfit(int *storeInfo, int *centerInfo, int cost);//if profitPerGood(i,j) is positive
int distance(int *storePosit, int *centerPosit);
int numOfSet(int num, bool *setList);
int catchMeIfYouCan(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfo[]);//return profit
int *coffeeTeaOrMe(int storeNum, int centerNum, int cost, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo);//return decide
int *newStoreOutside(int storeNum, int centerNum, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo);
int nowYouSeeMe(int storeNum, int bestJ, bool *storeSet, int **profitTable, int **storeInfo, int centerCapa, int transInfo[2]);
int *newStore(int j, int storeNum, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo);

const int storeCol = 5; //first two for x, y, third for demand, forth for fixed cost, fifth for price
const int centerCol = 4; //first two for x, y, third for capacity, forth for fixed cost
int main(){
    //initialization part
    int centerNum = 0;
    int storeNum = 0;
    int cost = 0;
    cin >> centerNum >> storeNum >> cost;
    int **storeInfo = new int*[storeNum];
    int **centerInfo = new int*[centerNum];
    for (int i = 0; i < storeNum; i++){
        storeInfo[i] = new int[storeCol];
        for (int j = 0; j < storeCol; j++)
            storeInfo[i][j] = 0;
    }
    for (int i = 0; i < centerNum; i++){
        centerInfo[i] = new int[centerCol];
        for (int j = 0; j < centerCol; j++)
            centerInfo[i][j] = 0;
    }
    
    //cin part
    for (int i = 0; i < storeNum; i++){
        for (int j = 0; j < 2; j++)
            cin >> storeInfo[i][j];
    }//store positioin
    for (int i = 0; i < centerNum; i++){
        for (int j = 0; j < 2; j++)
            cin >> centerInfo[i][j];
    }//center position
    for (int i = 0; i < storeNum; i++)
        cin >> storeInfo[i][2];//demand
    for (int i = 0; i < storeNum; i++)
        cin >> storeInfo[i][3];//fixed cost
    for (int i = 0; i < storeNum; i++)
        cin >> storeInfo[i][4];//price
    for (int i = 0; i < centerNum; i++)
        cin >> centerInfo[i][3];//fixed cost
    for (int i = 0; i < centerNum; i++)
        cin >> centerInfo[i][2];//capacity
    
    //match store & center if profitPerGood is positive
    int **profitTable = new int*[storeNum];
    for (int i = 0; i < storeNum; i++){
        profitTable[i] = new int[centerNum];
    }
    
    for (int i = 0; i < storeNum; i++){
        for (int j = 0; j < centerNum; j++){
            int value = posiProfit(storeInfo[i],centerInfo[j],cost);
            if (value)
                profitTable[i][j] = value;
            else
                profitTable[i][j] = 0;
        }
    }
    
    //for cout record
    bool *storeSet = new bool[storeNum];
    bool *centerSet = new bool[centerNum];
    int **setTable = new int*[storeNum];
    for (int i = 0; i < storeNum; i++)
        storeSet[i] = 0;
    for (int i = 0; i < centerNum; i++)
        centerSet[i] = 0;
    for (int i = 0; i < storeNum; i++){
        setTable[i] = new int[centerNum];
        for (int j = 0; j < centerNum; j++)
            setTable[i][j] = 0;
    }

    //main algorithim
    //functionA
    int *decide = coffeeTeaOrMe(storeNum,centerNum,cost,storeSet,centerSet,profitTable,storeInfo,centerInfo);
    int profitA = decide[0];
    centerSet[decide[1]] = 1;
    storeSet[decide[2]] = 1;
    setTable[decide[2]][decide[1]] += decide[4];
    storeInfo[decide[2]][2] -= decide[4];
    centerInfo[decide[1]][2] -= decide[4];
    
    //functionB
    int *ansB =  newStoreOutside(storeNum,centerNum,storeSet,centerSet,profitTable,storeInfo,centerInfo);
    int profitB = ansB[0];
    if (profitB > 0){
      storeSet[ansB[1]] = 1;
      setTable[ansB[1]][ansB[3]] += ansB[2];
      storeInfo[ansB[1]][2] -= ansB[2];
      centerInfo[ansB[3]][2] -= ansB[2];
    }

    while (true){
      //functionC
      int transInfo[3] = {0};
      int profitC = catchMeIfYouCan(storeNum,centerNum,storeSet,centerSet,profitTable,storeInfo,centerInfo,transInfo);
      if (profitC > 0){
	setTable[transInfo[1]][transInfo[2]] += transInfo[0];
	storeInfo[transInfo[1]][2] -= transInfo[0];
	centerInfo[transInfo[2]][2] -= transInfo[0];
      }
      else
	break;
    }
    
    //cout section
    int centerSetNum = numOfSet(centerNum,centerSet);
    int storeSetNum = numOfSet(storeNum,storeSet);
    cout << centerSetNum;
    for (int i = 0; i < centerNum; i++){
        if (centerSet[i])
            cout << " " << i+1;
    }
    cout << "\n";//new line
    cout << storeSetNum;
    for (int i = 0; i < storeNum; i++){
        if (storeSet[i]){
            cout << " " << i+1;
        }
    }
    cout << "\n";//new line
    for (int i = 0; i < storeNum; i++){
        for (int j = 0; j < centerNum; j++){
            if (j != 0)
                cout << " ";
            cout << setTable[i][j];
        }
        cout << "\n";
    }
    
    //delete section
    for (int i = 0; i < storeNum; i++)
        delete[] storeInfo[i];
    delete[] storeInfo;
    for (int i = 0; i < centerNum; i++)
        delete[] centerInfo[i];
    delete[] centerInfo;
    for (int i = 0; i < storeNum; i++){
        delete[] profitTable[i];
    }
    delete[] profitTable;
    delete[] centerSet;
    delete[] storeSet;
    for (int i = 0; i < storeNum; i++)
        delete[] setTable[i];
    delete[] setTable;
    
    return 0;
}

int posiProfit(int *storeInfo, int *centerInfo, int cost){
    int dist = distance(storeInfo,centerInfo);
    int profit = storeInfo[4] - dist*cost;
    if (profit > 0)
        return profit;
    else
        return 0;
}

int distance(int *storePosit, int *centerPosit){
    int deltaX = abs(storePosit[0] - centerPosit[0]);
    int deltaY = abs(storePosit[1] - centerPosit[1]);
    return deltaX + deltaY;
}

int numOfSet(int num, bool *setList){
    int setNum = 0;
    for (int i = 0; i < num; i++){
        if (setList[i])
            setNum++;
    }
    return setNum;
}

int catchMeIfYouCan(int storeNum, int centerNum, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo, int transInfo[3]){
    int *storeDem = new int[storeNum];
    for(int i = 0; i < storeNum; i++){
        storeDem[i] = storeInfo[i][2];
    }
    
    int *centerCapa = new int[centerNum];
    for(int i = 0; i < centerNum; i++){
        centerCapa[i] = centerInfo[i][2];
    }
    int transStore = -1, transCenter = -1, transAm = 0, profit = 0, category = 0;
    for(int i = 0; i < storeNum; i++){
        if(storeSet[i]){
            for(int j = 0; j < centerNum; j++){
                int temPro = 0, type = 0;
                if(centerSet[j] && profitTable[i][j] && storeDem[i] && centerCapa[j]){ //if the store & center are built and still have demand & capacity
                    if(storeDem[i] >= centerCapa[j]){
                        temPro = profitTable[i][j] * centerCapa[j];
                        type = 0;//if demand >= capacity, to know which amount is used
                    }
                    else{
                        temPro = profitTable[i][j] * storeDem[i];
                        type = 1;
                    }
                    if(temPro > profit){
                        profit = temPro;
                        transStore = i;
                        transCenter = j;
                        category = type;
                        if(category){
                            transAm = storeDem[transStore];
                        }
                        else{
                            transAm = centerCapa[transCenter];
                        }
                    }
                }
            }
        }
        
    }
    
    if(profit > 0){
        transInfo[0] = transAm;
        transInfo[1] = transStore;
        transInfo[2] = transCenter;
    }
    
    delete[]storeDem;
    delete[]centerCapa;
    return profit;
}

int *coffeeTeaOrMe(int storeNum, int centerNum, int cost, bool *storeSet, bool *centerSet, int **profitTable, int **storeInfo, int **centerInfo){
	int *decide = new int[5]; //maxNetProfit , center , store , build(1)/trans(0) , transAm
	//initialize
	for( int i = 0; i < 5; i++ ){
		decide[i] = 0;
	}
	
	for( int j = 0; j < centerNum; j++ ){
		if( centerSet[j] == false ){
			centerSet[j] = true;  //assume it is set
			
			int *ansB = new int[3];  //prepare for functionB
			ansB = newStore( j, storeNum, storeSet, centerSet, profitTable, storeInfo, centerInfo);  //call functionB
			int profitB = ansB[0]- centerInfo[j][3];
			int *transInfo = new int[2];  //prepare for functionC
			for( int i = 0; i < 2; i++ ){
				transInfo[i] = 0;
			}
			int profitC = nowYouSeeMe(storeNum,j,storeSet,profitTable,storeInfo,centerInfo[j][2],transInfo);  //call functionC
			profitC -= centerInfo[j][3];
			int profit = 0;
			if( profitB == profitC )
			{
				profit = profitB;
			}
			else
				profit = max( profitB, profitC );
			
			if( profit > decide[0] && profit > 0){
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

int* newStore(int j, int storeNum, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo){
    
    int *ansB = new int[3];
    for( int i = 0; i < 3; i++ ){
        ansB[i] = 0;
    }
    
    int netProfitB=0;
    int maxProfitB=-1;
    int storeOfMaxB=-1;
    int category = -1;
    for(int i=0; i<storeNum; i++){
        if(storeSet[i]==false){
            int tempCate = 0;
            if(profitTable[i][j]!=0 && centerSet[j]==true){
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
    ansB[0]=maxProfitB;
    ansB[1]=storeOfMaxB;
    if(category)
        ansB[2] = centerInfo[j][2];
    else
        ansB[2]=storeInfo[storeOfMaxB][2];
    
    return ansB;
}

int nowYouSeeMe(int storeNum, int bestJ, bool *storeSet, int **profitTable, int **storeInfo, int centerCapa, int transInfo[3]){
    int *storeDem = new int[storeNum];
    for(int i = 0; i < storeNum; i++){
        storeDem[i] = storeInfo[i][2];
    }
    
    int transStore = -1, transAm = 0, profit = 0, category = 0;
    for(int i = 0; i < storeNum; i++){
        int temPro = 0, type = 0;
        if(storeSet[i] && profitTable[i][bestJ] && storeDem[i] && centerCapa){
	  //if the store & center are built and still have demand & capacity
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
        transInfo[0] = transAm;
        transInfo[1] = transStore;
    }
    
    delete[]storeDem;
    return profit;
}

int* newStoreOutside(int storeNum, int centerNum, bool* storeSet, bool* centerSet, int** profitTable, int** storeInfo, int** centerInfo){
    
    int *ansB = new int[4];
    for( int i = 0; i < 4; i++ ){
        ansB[i] = 0;
    }
    
    int netProfitB=0;
    int maxProfitB=-1;
    int storeOfMaxB=-1;
    int category = -1;
    int centerOfB=-1;
    for(int i=0; i<storeNum; i++){
        for(int j=0; j<centerNum; j++){
            if(storeSet[i]==false){
                int tempCate = 0;
                if(profitTable[i][j]!=0 && centerSet[j]==true){
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
                        centerOfB=j;
                        category = tempCate;
                    }
                }
            }
        }	
    }
    ansB[0]=maxProfitB;
    ansB[1]=storeOfMaxB;
    if(category)
        ansB[2] = centerInfo[centerOfB][2];
    else
        ansB[2]=storeInfo[storeOfMaxB][2];
    ansB[3]=centerOfB;
    
    return ansB;
}
