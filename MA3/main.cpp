#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = {{"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}};
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }


    //
    // Your code goes here
    //

	map<string, TwitterData> map1;
	map<string, TwitterData> map2;
	for (int i = 0; i < 5; ++i) {
		map1.insert({twitter_data[i].getUserName(), twitter_data[i]});
		map2.insert({twitter_data[i].getEmail(), twitter_data[i]});
	}

	cout << "Printing the first map\n";
	for (map<string, TwitterData>::iterator it = map1.begin(); it != map1.end(); it++) {
		cout << "Key: " << it->first << ", Value: " << it->second.print() << "\n";
	} 
	
	cout << "Search for key: " << map1.find("savage1")->first << " Value: " << map1.find("savage1")->second.print() << "\n";
	map1.erase(map1.find("savage1"));

	cout << "Printing the second map\n";
	for (map<string, TwitterData>::iterator it = map2.begin(); it != map2.end(); it++)
	{
		cout << "Key: " << it->first << ", Value: " << it->second.print() << "\n";
	}

	cout << "Search for key: " << map2.find("kat@gmail.com")->first << " Value: " << map2.find("kat@gmail.com")->second.print() << "\n";
	map2.erase(map2.find("kat@gmail.com"));

	return 0;
}