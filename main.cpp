#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <iomanip>
#include <cctype>

using namespace std;

vector<int> UniqueEntityPerDomain(vector<vector<string>>);
vector<int> SumOfRepeatCount(vector<vector<string>>);
vector<double> MeanOfEntity(vector<vector<string>>);
vector<double> MeanOfRepeatCont(vector<vector<string>>);
void PrintInfo(vector<string>, vector<int>, vector<int>, vector<double>, vector<double>);
vector<string> Domain(vector<vector<string>>);

int main()
{

	vector<vector<string>> content;
	vector<string> row;
	vector<int> lUniqueEntity;
	vector<int> lSum;
	string line, word;
	vector<string> lDomain;
	vector<double> lMean;
	vector<double> lMeanRep;
	int count = 0;
	int check = 0;
	bool exit = true;


	
	


		string fname = " ";
		cout << "Enter the CSV file's full Path here: ";
		getline(cin, fname);
		cout << endl;



		bool lError = false;

		fstream file;


		file.open(fname);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				row.clear();

				stringstream str(line);

				while (getline(str, word, ',')) {

					count++;
					check = isdigit(word[1]);

					if (count == 3 && check > 0)
						lError = true;

					if (word.size() > 21 && word.substr(21) == "000+00:00\"") {

						lError = true;
					}
					row.push_back(word);
				}
				if (lError == !true) {

					content.push_back(row);

				}

				count = 0;
				lError = false;

			}

		}
		else
			cout << "Could not open the file\n";
		file.close();
		file.clear();

		for (int i = 0; i < content.size(); i++)
		{
			for (int j = 0; j < content[i].size(); j++)
			{
				content[i][j].erase(0, 1);
				content[i][j].pop_back();

			}
		}

		lDomain = Domain(content);
		lUniqueEntity = UniqueEntityPerDomain(content);
		lSum = SumOfRepeatCount(content);
		lMean = MeanOfEntity(content);
		lMeanRep = MeanOfRepeatCont(content);
		PrintInfo(lDomain, lUniqueEntity, lSum, lMeanRep, lMean);


		//cout << "Exit enter 0" << endl;
		//cin >> exit;
		//if (exit == 0)
		//	exit = false;
		//else exit = true; cin.clear(); cin.ignore(10000, '\n');

	

		system("pause");
	return 0;
}

vector<string> Domain(vector<vector<string>> aContent) {

	vector<string> domain;
	string flag;

	for (int i = 1; i != aContent.size(); ++i)
	{

		if (i == 1) {
			flag = aContent[i][1];
		}
		else if (flag != aContent[i][1]) {

			domain.push_back(flag);
			flag = aContent[i][1];
			
		}

	}

	return domain;

}
vector<int> UniqueEntityPerDomain(vector<vector<string>> aContent){

	int lSum = 0;
	set<string> lMySet;
	string flag;
	vector<int> lMyVal;

	for (int i = 1; i < aContent.size(); i++)
	{
		lMySet.insert(aContent[i][2]);
		


		if (i == 1) {
			flag = aContent[i][1];
		}
		if (flag != aContent[i][1]) {

			lMyVal.push_back(lMySet.size());
		
			lMySet.clear();

			flag = aContent[i][1];

		}


	}

	lMyVal.push_back( lMySet.size() +1);
	
	lMySet.clear();

	return lMyVal;
}
vector<int> SumOfRepeatCount(vector<vector<string>> aContent) {

	vector<int> lMyVec;
	int lSumR = 0;
	string flag;

	for (int i = 1; i != aContent.size(); ++i)
	{
		

		if (i == 1) {
			flag = aContent[i][1];
		}

		if (flag == aContent[i][1]) {

			lSumR += stoi(aContent[i][5]);


		}
		else if(flag != aContent[i][1]) {

			lMyVec.push_back(lSumR);
			
			flag = aContent[i][1];
			lSumR = 0;

		}

	}

	lMyVec.push_back(lSumR);
	
	
	return lMyVec;


}
vector<double> MeanOfRepeatCont(vector<vector<string>> aContent) {

	double lSum = 0;
	string flag;
	double count = 0;
	double mean = 0.0;
	vector<double> lMyVec;

	for (int i = 1; i != aContent.size(); ++i)
	{


		if (i == 1) {
			flag = aContent[i][1];
		}

		if (flag == aContent[i][1]) {

			lSum += stod(aContent[i][5]);
			count++;

		}
		else if (flag != aContent[i][1]) {

			mean = lSum / count;
			lMyVec.push_back(mean);


			flag = aContent[i][1];
			lSum = 0;

		}

	}

	lMyVec.push_back(mean);

	return lMyVec;

}

vector<double> MeanOfEntity(vector<vector<string>> aContent) {

	double lSum = 0.0;
	string flag;
	double count = 0.0;
	double mean = 0.0;
	vector<double>lMyVec;

	for (int i = 1; i != aContent.size(); ++i)
	{


		if (i == 1) {
			flag = aContent[i][1];
		}

		if (flag == aContent[i][1]) {

			lSum += 1;
		}
		else if (flag != aContent[i][1]) {
			count++;
			flag = aContent[i][1];
		}

	}

	mean = lSum / count;
	lMyVec.push_back(mean);

	return lMyVec; 
	
}
void PrintInfo(vector<string>adomain, vector<int> aUniqueEntity, vector<int> alSum, vector<double> alMeanRep, vector<double> alMean) {

	
	for (int i = 0; i < adomain.size(); i++) {
		
		cout << adomain[i] << endl;
		cout << "Unique Entity: " << aUniqueEntity[i] << "\t" << "Sum of Repeat: " << alSum[i] << "\t " << "Mean of Repeat : " << alMeanRep[i] << endl;
		cout << endl;
		cout << "**********************************************************************************************" << endl;

	}

	cout << endl;
	cout << endl;
	cout << "Mean of all Entity: " << alMean[0] << endl;
}




