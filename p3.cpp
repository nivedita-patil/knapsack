#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
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
	int w;
	vector<vector<int> > knapsackMatrix;
	knapsackMatrix.resize(n+1);
	for(int h=0; h<(n+1); h++)
	{
		knapsackMatrix[h].resize(maxWeight+1);
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
			}
			else
			{
				knapsackMatrix[k][w] = knapsackMatrix[k-1][w];
			}
		}
	}

	for(int i=0; i<=n; i++)
	{
		for (int j = 0; j <= maxWeight; j++)
		{
			printf("%d\t", knapsackMatrix[i][j]);
		}
		printf("\n");
	}
}
