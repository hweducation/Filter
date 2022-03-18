///*
//修改自main
//将mid02 mid03的optionCD互换
//输入
//E:\read-allquestion\themeout\hou-shu-01-output
//输出"E:\\out\\filter\\";
//E:\out\filter\hou-shu-01-output
//*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <algorithm>
//using namespace std;
///*
//名称:my_split(const std::string& src, const char& delim,
//		 std::vector<std::string>& vec)
//功能:用分隔符将源字符串分隔为多个子串并传出; n个分隔符, 分n+1个子串
//
//参数:
//	 src-传入参数, 源字符串;
//	 delim-传入参数, 分隔符;
//	 vec-传出参数, 子串的集合;
//
//返回值:
//	0-成功;
//	其它-失败;
// */
//
//int my_split(const string& src, const char& delim,
//	vector<string>& vec)
//{
//	int src_len = src.length();
//	int find_cursor = 0;
//	int read_cursor = 0;
//
//	if (src_len <= 0) return -1;
//
//	vec.clear();
//	while (read_cursor < src_len) {
//
//		find_cursor = src.find(delim, find_cursor);
//
//		//1.找不到分隔符
//		if (-1 == find_cursor) {
//			if (read_cursor <= 0) return -1;
//
//			//最后一个子串, src结尾没有分隔符
//			if (read_cursor < src_len) {
//				vec.push_back(src.substr(read_cursor, src_len - read_cursor));
//				return 0;
//			}
//		}
//		//2.有连续分隔符的情况
//		else if (find_cursor == read_cursor) {
//			//字符串开头为分隔符, 也按空子串处理, 如不需要可加上判断&&(read_cursor!=0)
//			vec.push_back(string(""));
//		}
//		//3.找到分隔符
//		else
//			vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));
//
//		read_cursor = ++find_cursor;
//		if (read_cursor == src_len) {
//			//字符串以分隔符结尾, 如不需要末尾空子串, 直接return
//			vec.push_back(string(""));
//			return 0;
//		}
//	}//end while()
//	return 0;
//}
//
//class TPattern {
//public:
//	int n;
//	int length;
//	string patstring;
//	TPattern(int nn, int ll, string ss) :n(nn), length(ll), patstring(ss) {
//
//	}
//};
//class CompGreater {
//public:
//	bool operator()(const TPattern& tpattern1, const TPattern& tpattern2) {
//		return tpattern1.n > tpattern2.n;
//	}
//};
//int main()
//{
//	//时间起点+AOI
//	//Sequence8相比Sequence7 Option合并了
//	FILE *fp;
//
//	vector<string> lengthVec;//长度是
//	lengthVec.push_back("2");
//	lengthVec.push_back("3");
//	lengthVec.push_back("4");
//	lengthVec.push_back("5");
//	lengthVec.push_back("6");
//
//
//	vector<string> questionVec;
//	questionVec.push_back("hou-shu-01-output");
//	questionVec.push_back("hou-shu-04-output");
//	questionVec.push_back("mid-shu-02-output");//2
//	questionVec.push_back("mid-shu-03-output");//3
//	questionVec.push_back("mid-shu-04-output");
//
//	string questionid = questionVec[3];//注意23需要多一段代码
//	 
//	const string in_dir = "E:\\read-allquestion\\themeout\\" + questionid + "\\";
//	//read-allquestion\themeout\hou - shu - 01 - output
//	const string out_dir = "E:\\out\\filter\\";
//	vector<string> names{
//		//"Patstr_recording18", "Patstr_recording23","Patstr_recording24","Patstr_recording25",
//		//"Patstr_recording26","Patstr_recording28","Patstr_recording30",
//		//"Patstr_recording31","Patstr_recording32","Patstr_recording46",
//		//"Patstr_recording63","Patstr_recording70",
//		"Patstr_recording18new","Patstr_recording23new","Patstr_recording24new","Patstr_recording25new",
//		"Patstr_recording26new","Patstr_recording28new","Patstr_recording30new",
//		"Patstr_recording31new","Patstr_recording32new","Patstr_recording46new",
//		"Patstr_recording63new","Patstr_recording70new",
//		//新加的10道
//		"Patstr_recording19new","Patstr_recording20new","Patstr_recording27new",
//		"Patstr_recording33new","Patstr_recording34new","Patstr_recording35new",
//		"Patstr_recording45new","Patstr_recording47new","Patstr_recording52new","Patstr_recording71new",
//
//	};//这个没有挖掘到模式
//	//mid-shu-01-output 没有25
//	//mid-shu-03-output 没有25
//	//mid-shu-04-output 没有23
//	//hou-shu-04-output 没有23 25
//	string in_path;
//	for (int k = 0; k < names.size(); k++) {
//		in_path = in_dir + names[k] + ".txt";
//		cout << "第" << k << "个文件路径为：" << in_path << endl;
//		const string out_path = out_dir + questionid + "\\" + names[k] + ".txt";//.tsv
//		ofstream out_file(out_path, ofstream::out);
//
//		fp = fopen(in_path.c_str(), "r");//string to const char*
//		if (!fp)
//		{
//			cout << in_path << "OPEN ERROR!" << endl;
//			continue;
//			//return 0;
//		}
//		int i = 0;
//		vector<string> sequence;
//
//		char original_data[20000], data2[1000];
//		fgets(original_data, sizeof(original_data), fp);//表头
//		const char * split = "\t";
//		string last_eye_movement_type = "0";
//		int start_flag = 0;
//		vector <string> res;//用于记录总数
//
//		string lastType = "-1";
//		while (fgets(original_data, sizeof(original_data), fp))
//		{
//			i++;//recode current line
//			vector<string> line;
//			//;get a line data in .tsv
//			my_split(original_data, '\t', line);
//			if (line.size() == 0) {
//				break;
//			}
//
//			if (line[3] == "2" || line[3] == "3" || line[3] == "4" || line[3] == "5" || line[3] == "6") {
//			//if (line[3] == "3") {
//				//if (line[3] == "3" || line[3] == "7" || line[3] == "8" || line[3] == "4" || line[3] == "5" || line[3] == "6") {
//
//				//line[7]进行字符串替换 只有mid02 mid03需要这么操作
//
//				vector<string> AOIarr;
//				my_split(line[7], ' ', AOIarr);
//				/*
//				//只有mid02 mid03需要这段cd转换的代码
//				for (int p = 0; p < AOIarr.size(); p++) {
//					if (AOIarr[p] == "optiond") {
//						AOIarr[p] = "optionc";
//					}
//					else if (AOIarr[p] == "optionc") {
//						AOIarr[p] = "optiond";
//					}
//				}*/
//				string newline7;
//				for (int p = 0; p < AOIarr.size()-1; p++) {
//					newline7 += AOIarr[p] + " ";
//				}
//				newline7 += AOIarr[AOIarr.size() - 1];
//				string new_data = line[0] + '\t' + line[1] + '\t' + line[2] + '\t' + line[3] + '\t' + line[4] + '\t' + line[5] + '\t' + line[6] + '\t' + newline7;
//				res.push_back(new_data);
//			}
//			if (feof(fp))
//				break;
//		}
//		stringstream ss;
//		string tab = "\t";
//		/* 对模式按照支持度排序
//		vector<TPattern> tPatternVec;
//		for (auto a	 : res) {
//			//ss << a.first << "," << a.second.first << "," << a.second.second << endl;
//			vector <string> temp;
//			my_split(a, '\t', temp);
//			TPattern tpttern(atoi(temp[2].c_str()), atoi(temp[3].c_str()), temp[7]);
//			tPatternVec.push_back(tpttern);
//			//ss << a;
//		}
//		//对vector<TPattern*> tPatternVec排序
//		sort(tPatternVec.begin(), tPatternVec.end(), CompGreater());//降序排序
//		for (auto a : tPatternVec) {
//			ss << a.n << '\t' << a.length << '\t' << a.patstring;
//		}
//		*/
//
//		for (auto a : res) {
//			ss << a;
//		}
//		//ss << "total sequence " << merge_res.size() << endl;
//		//cout << ss.str() << endl;
//		out_file << ss.str() << endl;
//		cout << ss.str() << endl;
//		fclose(fp);
//		out_file.close();
//	}
//	system("pause");
//}