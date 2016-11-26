#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<ctime>
#include"p3.h"

using namespace std;

int main()
{
	vector<int> weight;
	vector<int> profit;
	int n = 0;
	int maxWeight = 0;
	ifstream infile("input.txt");
	string fileInput;
	if(infile.is_open())
	{
		while(true)
		{
			infile>>fileInput;
			if(infile.eof()) break;
			n = atoi(fileInput.c_str());
			if(n == 0) break;
			infile>>fileInput;
			maxWeight = atoi(fileInput.c_str());
			weight.resize(n);
			profit.resize(n);

			for(int i=0; i<n; i++)
			{
				infile>>fileInput;
				weight[i] = atoi(fileInput.c_str());
				infile>>fileInput;
				profit[i] = atoi(fileInput.c_str());
			}
			calculateKnapsack(maxWeight, n, weight, profit);
		}
		infile.close();
	}

	return 0;
}

void calculateKnapsack(int maxWeight, int n, vector<int>weight, vector<int>profit)
{
	const clock_t begin = clock();
	int w;
	int p=0;
	int maxProfit=0;
	vector<vector<int> > knapsackMatrix;
	vector<vector<int> > itemsList;
	knapsackMatrix.resize(n+1);
	itemsList.resize(n+1);
	for(int h=0; h<(n+1); h++)
	{
		knapsackMatrix[h].resize(maxWeight+1);
		itemsList[h].resize(maxWeight+1);
	}
	for(w=0; w<=maxWeight; w++)
	{
		knapsackMatrix[0][w] = 0;
	}
	for (int k = 1; k <= n; k++)
	{
		knapsackMatrix[k][0] = 0;
		for (w = 1; w <= maxWeight; w++)
		{
			if((weight[k-1] <= w) && ((knapsackMatrix[k-1][w-weight[k-1]] + profit[k-1]) > knapsackMatrix[k-1][w]))
			{
				knapsackMatrix[k][w] = knapsackMatrix[k-1][w-weight[k-1]] + profit[k-1];
				itemsList[k][w] = 1;
				p++;
				if(knapsackMatrix[k][w]>maxProfit)
				{
					maxProfit = knapsackMatrix[k][w];
				}
			}
			else
			{
				knapsackMatrix[k][w] = knapsackMatrix[k-1][w];
				itemsList[k][w] = 0;
			}
		}
	}
	float total_time = float(clock() - begin)/CLOCKS_PER_SEC;

	int toPrint = maxWeight;

	cout<<n<<" "<<maxProfit<<" "<<total_time<<endl;

	for(int v=n; 1<=v; v--)
	{
		if(itemsList[v][toPrint]==1)
		{
			cout<<weight[v-1]<<" "<<profit[v-1]<<endl;
			toPrint = toPrint - weight[v-1];
		}
	}

}
