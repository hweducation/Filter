///*
//把挖掘出的模式长度>=6的过滤出来
//*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
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
//int main()
//{
//	//时间起点+AOI
//	//Sequence8相比Sequence7 Option合并了
//	FILE *fp;
//	string questionid = "hou-shu-01-output\\";
//	const string in_dir = "E:\\read-all\\" + questionid;
//	const string out_dir = "E:\\out\\filter\\";
//	vector<string> names{
//		"Patstr_recording18","Patstr_recording24","Patstr_recording23","Patstr_recording25",
//		"Patstr_recording26","Patstr_recording28","Patstr_recording30",
//		"Patstr_recording31","Patstr_recording32","Patstr_recording46",
//		"Patstr_recording63","Patstr_recording70",
//		"Patstr_recording18new","Patstr_recording24new","Patstr_recording23new",
//		"Patstr_recording26new","Patstr_recording28new","Patstr_recording30new",
//		"Patstr_recording31new","Patstr_recording32new","Patstr_recording46new",
//		"Patstr_recording63new","Patstr_recording70new"
//	};//"Patstr_recording25new",这个没有挖掘到模式
//	//mid-shu-01-output 没有25
//	//mid-shu-03-output 没有25
//	//mid-shu-04-output 没有23
//	//hou-shu-04-output 没有23 25
//	string in_path;
//	for (int k = 0; k < names.size(); k++) {
//		in_path = in_dir + names[k] + ".txt";
//		cout << "第" << k << "个文件路径为：" << in_path << endl;
//		const string out_path = out_dir + questionid + names[k] + ".txt";//.tsv
//		ofstream out_file(out_path, ofstream::out);
//
//		fp = fopen(in_path.c_str(), "r");//string to const char*
//		if (!fp)
//		{
//			cout << "OPEN ERROR!" << endl;
//			return 0;
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
//			if (line[3] == "2" || line[3] == "3" || line[3] == "4" || line[3] == "5" || line[3] == "6") {
//				res.push_back(original_data);
//			}
//			if (feof(fp))
//				break;
//		}
//		stringstream ss;
//		string tab = "\t";
//		for (auto a : res) {
//			//ss << a.first << "," << a.second.first << "," << a.second.second << endl;
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