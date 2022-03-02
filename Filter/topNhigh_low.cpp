///*
//重新计算得到组别的总支持度后，输出在高分组中支持度高，低分组支持度低（通过支持度阈值设置）的模式 反之亦然
//由于低分组所有模式的支持度都比高分组模式支持度低，所以...(之前写错了，只是没有定义)
//解决方法
//1、重新定义支持度，还是改成rank的形式比较
//2、将低分组模式支持度乘以2（或者>1）试一试
//3、定义两个阈值
//
//
//输入 in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
//输出 out_dir = "E:\\out\\sum\\" + questionid + "\\";
//high中的支持度 low中的支持度 前两者相减 模式名称
//*/
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <unordered_map>
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
//	double supp;
//	string patstring;
//	TPattern(double support, string ss) :supp(support), patstring(ss) {
//
//	}
//};
//class CompGreater {
//public:
//	bool operator()(const TPattern& tpattern1, const TPattern& tpattern2) {
//		return tpattern1.supp > tpattern2.supp;
//	}
//};
//int main()
//{
//	//时间起点+AOI
//	//Sequence8相比Sequence7 Option合并了
//	FILE *fp;
//	string questionid = "mid-shu-02-output";
//	const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
//	const string out_dir = "E:\\out\\sum\\" + questionid + "\\";
//
//	unordered_map<string, double> umScsuppAll; //高分组或者低分组支持度map
//	unordered_map<string, string> umScsuppAll_everyone;//高分组或者低分组个人贡献的比率map
//	unordered_map<string, double> umHighScsuppAll;//高分组支持度map
//	unordered_map<string, string> umHighScsuppAll_everyone;//高分组个人贡献的比率map
//	unordered_map<string, double> umLowScsuppAll;//低分组支持度map
//	unordered_map<string, string> umLowScsuppAll_everyone;//低分组个人贡献的比率map
//	vector<string> categoryNames{ "low","high" };
//	for (int k = 0; k < categoryNames.size(); k++) {
//		string category = categoryNames[k];//low  high
//
//		vector<string> names;
//		//	//"Patstr_recording18","Patstr_recording23","Patstr_recording24","Patstr_recording25",
//		//	//"Patstr_recording26","Patstr_recording28","Patstr_recording30",
//		//	//"Patstr_recording31","Patstr_recording32","Patstr_recording46",
//		//	//"Patstr_recording63","Patstr_recording70",
//		//	"Patstr_recording18new","Patstr_recording23new","Patstr_recording24new","Patstr_recording28new",
//		//	"Patstr_recording46new","Patstr_recording70new"
//		//};//高分组
//		if (category == "high") {
//			names.push_back("Patstr_recording18new");
//			names.push_back("Patstr_recording46new");
//			names.push_back("Patstr_recording23new");
//			names.push_back("Patstr_recording24new");
//			names.push_back("Patstr_recording25new");//25变成high了
//			names.push_back("Patstr_recording28new");
//			names.push_back("Patstr_recording70new");
//			//后加的
//			names.push_back("Patstr_recording20new");
//			names.push_back("Patstr_recording47new");
//			names.push_back("Patstr_recording52new");
//			names.push_back("Patstr_recording71new");
//		}
//		else {
//			names.push_back("Patstr_recording26new");
//			names.push_back("Patstr_recording30new");
//			names.push_back("Patstr_recording31new");
//			names.push_back("Patstr_recording32new");
//			names.push_back("Patstr_recording63new");
//			//后加的
//			names.push_back("Patstr_recording19new");
//			names.push_back("Patstr_recording27new");
//			names.push_back("Patstr_recording33new");
//			names.push_back("Patstr_recording34new");
//			names.push_back("Patstr_recording35new");
//			names.push_back("Patstr_recording45new");
//		}
//		/*
//		低分组
//			"Patstr_recording25new", "Patstr_recording26new", "Patstr_recording30new",
//			"Patstr_recording31new", "Patstr_recording32new", "Patstr_recording63new",
//		*/
//		string tab = "\t";
//		string in_path;
//		int fileNum = 0;
//
//		//支持度计算开始
//		for (int k = 0; k < names.size(); k++) {
//			in_path = in_dir + names[k] + ".txt";
//			cout << "第" << k << "个文件路径为：" << in_path << endl;
//
//			long sum = 0;
//			fp = fopen(in_path.c_str(), "r");//string to const char*
//			if (!fp)
//			{
//				cout << "OPEN ERROR!" << endl;
//				continue;
//			}
//			fileNum++;
//			int i = 0;
//
//			char original_data[20000];
//			//fgets(original_data, sizeof(original_data), fp);//表头
//			const char * split = "\t";
//
//			//读第一遍，将出现频率相加，计算sum
//			while (fgets(original_data, sizeof(original_data), fp))
//			{
//				i++;//recode current line
//				vector<string> line;
//				//;get a line data in .tsv
//				my_split(original_data, '\t', line);
//				if (line.size() == 0) {
//					break;
//				}
//				sum += atoi(line[2].c_str());
//				if (feof(fp))
//					break;
//			}
//
//			fp = fopen(in_path.c_str(), "r");//string to const char*
//			if (!fp)
//			{
//				cout << "OPEN ERROR!" << endl;
//				continue;
//				//return 0;
//			}
//			//读第二遍，加入全局支持度哈希表中，估计会爆内存？
//			while (fgets(original_data, sizeof(original_data), fp))
//			{
//				vector<string> line;
//				//;get a line data in .tsv
//				my_split(original_data, '\t', line);
//				if (line.size() == 0) {
//					break;
//				}
//				double temp = (double)atoi(line[2].c_str()) / (double)sum;//如果对值做平均的话，改为(double)sum; 如果单纯相加，改为1.0
//
//				umScsuppAll[line[7]] += temp / names.size();//全局支持度修改成了平均值，即除以了总人数
//				umScsuppAll_everyone[line[7]] += names[k] + to_string(temp) + ";";
//				if (feof(fp))
//					break;
//			}
//			fclose(fp);
//		}
//		//支持度计算结束
//		if (category == "high") {
//			umHighScsuppAll = umScsuppAll;
//			umHighScsuppAll_everyone = umScsuppAll_everyone;
//		}
//		else {
//			umLowScsuppAll = umScsuppAll;
//			umLowScsuppAll_everyone = umScsuppAll_everyone;
//		}
//		umScsuppAll.clear();
//		umScsuppAll_everyone.clear();
//	}
//
//	////输出在high中支持度高在low中支持度低
//	//string outName = out_dir + "high_low.csv";
//	//ofstream out_file(outName, ofstream::out);//全局支持度路径
//	//double thereshold = 0.02;//支持度阈值
//	////unordered_map<string, double> 
//	//stringstream ss;
//	//for (auto aUmHighScsuppAll : umHighScsuppAll) {
//	//	//目前不设置阈值
//	//	if (aUmHighScsuppAll.second > 0 && umLowScsuppAll[aUmHighScsuppAll.first] < 100) {//thereshold
//	//		vector <string> name_suppHigh; //high中各用户的贡献 格式，例：Patstr_recording18new0.000595
//	//		my_split(umHighScsuppAll_everyone[aUmHighScsuppAll.first], ';', name_suppHigh);
//	//		int suppHighSize = name_suppHigh.size() == 0 ? 0 : name_suppHigh.size() - 1; //high中用户贡献的个数
//
//	//		vector <string> name_suppLow; //low中各用户的贡献 格式，例：Patstr_recording18new0.000595
//	//		my_split(umLowScsuppAll_everyone[aUmHighScsuppAll.first], ';', name_suppLow);
//	//		int suppLowSize = name_suppLow.size() == 0 ? 0 : name_suppLow.size() - 1;//low中用户贡献的个数
//	//		//支持度差要大于等于0，人数要>=2(一共六个人)，人数差要>=0
//	//		if (aUmHighScsuppAll.second - umLowScsuppAll[aUmHighScsuppAll.first] < 0 || suppHighSize < 2 || suppHighSize - suppLowSize < 0) {
//	//			continue;
//	//		}
//	//		//high中的支持度 low中的支持度 前两者相减 high中各用户的贡献 数量 low中各用户的贡献 数量 模式名称
//	//		ss << aUmHighScsuppAll.second << "," << umLowScsuppAll[aUmHighScsuppAll.first] << "," <<
//	//			aUmHighScsuppAll.second - umLowScsuppAll[aUmHighScsuppAll.first] << "," <<
//	//			umHighScsuppAll_everyone[aUmHighScsuppAll.first] << "," << to_string(suppHighSize) << "," <<
//	//			umLowScsuppAll_everyone[aUmHighScsuppAll.first] << "," << to_string(suppLowSize) << "," <<
//	//			to_string(suppHighSize - suppLowSize) << "," <<
//	//			aUmHighScsuppAll.first;
//	//	}
//	//}
//	//out_file << ss.str() << endl;
//	//cout << ss.str() << endl;
//	//out_file.close();
//
//
//	//输出在low中支持度高在high中支持度低
//	string outName = out_dir + "low_high.csv";
//	ofstream out_file(outName, ofstream::out);//全局支持度路径
//	double thereshold1 = 0;//支持度阈值
//	double thereshold2 = 100;//支持度阈值
//
//	//unordered_map<string, double> 
//	stringstream ss;
//	string tab = ",";
//	ss << "low中的支持度" << tab << "high中的支持度" << tab << "low支持度-high支持度" << tab << "low中各用户贡献" << tab <<
//		"low用户数量" << tab << "high中各用户贡献" << tab << "high用户数量" << tab <<
//		"low用户数量-high用户数量" << tab << "模式名称" << endl;
//	for (auto aUmLowScsuppAll : umLowScsuppAll) {
//		if (aUmLowScsuppAll.second > thereshold1 && umHighScsuppAll[aUmLowScsuppAll.first] < thereshold2) {
//			vector <string> name_suppHigh; //high中各用户的贡献 格式，例：Patstr_recording18new0.000595
//			my_split(umHighScsuppAll_everyone[aUmLowScsuppAll.first], ';', name_suppHigh);
//			int suppHighSize = name_suppHigh.size() == 0 ? 0 : name_suppHigh.size() - 1; //high中用户贡献的个数
//
//			vector <string> name_suppLow; //low中各用户的贡献 格式，例：Patstr_recording18new0.000595
//			my_split(umLowScsuppAll_everyone[aUmLowScsuppAll.first], ';', name_suppLow);
//			int suppLowSize = name_suppLow.size() == 0 ? 0 : name_suppLow.size() - 1;//low中用户贡献的个数
//			//支持度差要大于等于0，人数要>=2(一共六个人)，人数差要>=0
//			if (aUmLowScsuppAll.second - umHighScsuppAll[aUmLowScsuppAll.first] < 0 || suppLowSize < 2 || suppLowSize - suppHighSize < 0) {
//				continue;
//			}
//			//low中的支持度 high中的支持度 前两者相减 low中各用户的贡献 数量 high中各用户的贡献 数量 两者相减 模式名称
//			ss << aUmLowScsuppAll.second << "," << umHighScsuppAll[aUmLowScsuppAll.first] << "," <<
//				aUmLowScsuppAll.second - umHighScsuppAll[aUmLowScsuppAll.first] << "," <<
//				umLowScsuppAll_everyone[aUmLowScsuppAll.first] << "," << to_string(suppLowSize) << "," <<
//				umHighScsuppAll_everyone[aUmLowScsuppAll.first] << "," << to_string(suppHighSize) << "," <<
//				to_string(suppLowSize - suppHighSize) << "," <<
//				aUmLowScsuppAll.first;
//		}
//	}
//	out_file << ss.str() << endl;
//	cout << ss.str() << endl;
//	out_file.close();
//	
//	system("pause");
//}