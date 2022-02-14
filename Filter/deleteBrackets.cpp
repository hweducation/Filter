//删除模式名中的括号
//输入"E:\\read-all\\filter\\" + questionid + "\\";
//输出 "E:\\out\\deleteBrackets\\";
//结束后把输出复制到输入重新跑另外3个代码
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int my_split(const string& src, const char& delim,
	vector<string>& vec)
{
	int src_len = src.length();
	int find_cursor = 0;
	int read_cursor = 0;

	if (src_len <= 0) return -1;

	vec.clear();
	while (read_cursor < src_len) {

		find_cursor = src.find(delim, find_cursor);

		//1.找不到分隔符
		if (-1 == find_cursor) {
			if (read_cursor <= 0) return -1;

			//最后一个子串, src结尾没有分隔符
			if (read_cursor < src_len) {
				vec.push_back(src.substr(read_cursor, src_len - read_cursor));
				return 0;
			}
		}
		//2.有连续分隔符的情况
		else if (find_cursor == read_cursor) {
			//字符串开头为分隔符, 也按空子串处理, 如不需要可加上判断&&(read_cursor!=0)
			vec.push_back(string(""));
		}
		//3.找到分隔符
		else
			vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));

		read_cursor = ++find_cursor;
		if (read_cursor == src_len) {
			//字符串以分隔符结尾, 如不需要末尾空子串, 直接return
			vec.push_back(string(""));
			return 0;
		}
	}//end while()
	return 0;
}

class TPattern {
public:
	int n;
	int length;
	string patstring;
	TPattern(int nn, int ll, string ss) :n(nn), length(ll), patstring(ss) {

	}
};
class CompGreater {
public:
	bool operator()(const TPattern& tpattern1, const TPattern& tpattern2) {
		return tpattern1.n > tpattern2.n;
	}
};
int main()
{
	//时间起点+AOI
	//Sequence8相比Sequence7 Option合并了
	FILE *fp;
	string questionid = "mid-shu-04-output\\";
	const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
	const string out_dir = "E:\\out\\deleteBrackets\\";
	vector<string> names{
		"Patstr_recording18", "Patstr_recording23","Patstr_recording24","Patstr_recording25",
		"Patstr_recording26","Patstr_recording28","Patstr_recording30",
		"Patstr_recording31","Patstr_recording32","Patstr_recording46",
		"Patstr_recording63","Patstr_recording70",
		"Patstr_recording18new","Patstr_recording23new","Patstr_recording24new","Patstr_recording25new",
		"Patstr_recording26new","Patstr_recording28new","Patstr_recording30new",
		"Patstr_recording31new","Patstr_recording32new","Patstr_recording46new",
		"Patstr_recording63new","Patstr_recording70new"
	};//这个没有挖掘到模式
	//mid-shu-01-output 没有25
	//mid-shu-03-output 没有25
	//mid-shu-04-output 没有23
	//hou-shu-04-output 没有23 25
	string in_path;
	for (int k = 0; k < names.size(); k++) {
		in_path = in_dir + names[k] + ".txt";
		cout << "第" << k << "个文件路径为：" << in_path << endl;
		const string out_path = out_dir + questionid + names[k] + ".txt";//.tsv
		ofstream out_file(out_path, ofstream::out);

		fp = fopen(in_path.c_str(), "r");//string to const char*
		if (!fp)
		{
			cout << in_path << "OPEN ERROR!" << endl;
			continue;
			//return 0;
		}
		int i = 0;
		vector<string> sequence;

		char original_data[20000], data2[1000];
		fgets(original_data, sizeof(original_data), fp);//表头
		const char * split = "\t";
		string last_eye_movement_type = "0";
		int start_flag = 0;
		vector <string> res;//用于记录总数

		string lastType = "-1";
		while (fgets(original_data, sizeof(original_data), fp))
		{
			i++;//recode current line
			vector<string> line;
			//;get a line data in .tsv
			my_split(original_data, '\t', line);
			if (line.size() == 0) {
				break;
			}
			//if (line[3] == "2" || line[3] == "3" || line[3] == "4" || line[3] == "5" || line[3] == "6") {
			//	res.push_back(original_data);
			//}
			string newOriginal_data = "";
			for (int i = 0; i < 6; i++) {
				newOriginal_data += line[i] + '\t';
			}
			string patStringDeleteBracket = "";
			//删除括号
			for (auto a : line[7]) {
				if (a != '(' && a != ')') {
					patStringDeleteBracket += a;
				}
			}
			newOriginal_data += patStringDeleteBracket;
			//line[6]
			res.push_back(newOriginal_data);
			if (feof(fp))
				break;
		}
		//把出现次数合并


		stringstream ss;
		for (auto a : res) {
			ss << a;
		}
		out_file << ss.str() << endl;
		cout << ss.str() << endl;
		fclose(fp);
		out_file.close();
	}
	system("pause");
}