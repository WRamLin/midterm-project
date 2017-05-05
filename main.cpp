#include <iostream>
#include <cmath>
using namespace std;

int posiProfit(int *storeInfo, int *centerInfo, int cost);//if profitPerGood(i,j) is positive
int distance(int *storePosit, int *centerPosit);
int numOfSet(int num, bool *setList);

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

    /*calculate function start
      functionA: check a most valuable netProfit center & an associated stores
      return netProftit & the indexOfCenter & the indexOfStores & type & transAm
      
      functionB: check a most valuable unset store set
      return netProfit & indexOfCenter & the indexOfStores & transAm

      functionC: check a most valuable transition
      return netProfit & indexOfCenter & the indexOfStores & transAm
    */

    //do functionA once
    //comparation between netProfit of functionA, functionB & functionC
    //satisfied the need, increase capacity or demand if satisfied, record the set of store or center if needed
    //do while the additProfit is minus

    //cout section
    int centerSetNum = numOfSet(centerNum,centerSet);
    int storeSetNum = numOfSet(storeNum,storeSet);
    cout << centerSetNum;
    for (int i = 0; i < centerSetNum; i++){
      if (centerSet[i])
	cout << " " << i+1;
    }
    cout << "\n";//new line
    cout << storeSetNum;
    for (int i = 0; i < storeSetNum; i++){
      if (storeSet[i])
	cout << " " << i+1;
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
