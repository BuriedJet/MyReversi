//#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize ("O3")

#include <iostream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include "jsoncpp/json.h"
//#include "jsoncpp.cpp"

#include "reversi.h" //++
//#include "reversi.cc" //++
 
using namespace std;
 
int main(){
	int x,y;
	bool mycolor;

	board brd;
	brd.assign(0x0000000810000000,0x0000001008000000);
 
 	// input JSON
 	string str;
 	getline(cin, str);
 	Json::Reader reader;
 	Json::Value input,result;
	Json::FastWriter writer;
 	reader.parse(str, input);

 	// �����Լ��յ���������Լ���������������ָ�״̬
 	int turns = input["responses"].size();
 	mycolor = (input["requests"][(Json::Value::UInt) 0]["x"].asInt() < 0);

 	for (int i = 0; i < turns; i++)
 	{
 		// ������Щ��������𽥻ָ�״̬����ǰ�غ�
 		x = input["requests"][i]["x"].asInt();
 		y = input["requests"][i]["y"].asInt();
 		if (x >= 0)
 			brd.flip(!mycolor,x,y); // ģ��Է�����

 		x = input["responses"][i]["x"].asInt();
 		y = input["responses"][i]["y"].asInt();
 		if (x >= 0)
 		 	brd.flip(mycolor,x,y); // ģ�⼺������
 	}

 	// �����Լ����غ�����
 	x = input["requests"][turns]["x"].asInt();
 	y = input["requests"][turns]["y"].asInt();

 	if (x >= 0)
 		brd.flip(!mycolor,x,y); // ģ��Է�����

 	auto temp = brd.play(mycolor);
	x = std::get<0>(temp);
	y = std::get<1>(temp);

	// ���߽���������������ֻ���޸����ϲ��֣�

	result["response"]["x"] = x;
	result["response"]["y"] = y;
	cout << writer.write(result) << endl;

	return 0;
}
