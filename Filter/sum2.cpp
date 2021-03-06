///*
//在sum的基础上改的
//模式长度>=6的过滤出来后，计算每个模式的支持度，进行加和
//修改成用于得到所有题目的因子分析输入文件
//输入 "E:\\read-all\\filter\\" + questionid + "\\";
//输出 "E:\\out\\sum\\";
////按题目输出模式表格
//
////所有题目统一输出模式表格
//
//*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <unordered_map>
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
//	vector<string> questionVec;
//	questionVec.push_back("hou-shu-01-output");
//	questionVec.push_back("hou-shu-04-output");
//	questionVec.push_back("mid-shu-02-output");
//	questionVec.push_back("mid-shu-03-output");
//	questionVec.push_back("mid-shu-04-output");		
//	vector<string> names;
//
//	names.push_back("Patstr_recording18new");
//	names.push_back("Patstr_recording46new");
//	names.push_back("Patstr_recording23new");
//	names.push_back("Patstr_recording24new");
//	names.push_back("Patstr_recording25new");//25变成high了
//	names.push_back("Patstr_recording28new");
//	names.push_back("Patstr_recording70new");
//	//后加的
//	names.push_back("Patstr_recording20new");
//	//names.push_back("Patstr_recording47new");
//	names.push_back("Patstr_recording52new");
//	names.push_back("Patstr_recording71new");
//	names.push_back("Patstr_recording34new");
//	names.push_back("Patstr_recording26new");
//	names.push_back("Patstr_recording30new");
//	//names.push_back("Patstr_recording31new");
//	names.push_back("Patstr_recording32new");
//	names.push_back("Patstr_recording63new");
//	//后加的
//	names.push_back("Patstr_recording19new");
//	names.push_back("Patstr_recording27new");
//	names.push_back("Patstr_recording33new");
//	//names.push_back("Patstr_recording34new");
//	names.push_back("Patstr_recording35new");
//	names.push_back("Patstr_recording45new");
//	names.push_back("Patstr_recording31new");
//	names.push_back("Patstr_recording47new");
//
//	unordered_map<string, double> umScsuppAll;
//	unordered_map<string, vector<pair<double, int> > > umAlpha_suppVec;//模式名，支持度，支持度，支持度，支持度，支持度...
//	//mid-shu-01-output 没有25
//	//mid-shu-03-output 没有25
//	//mid-shu-04-output 没有23
//	//hou-shu-04-output 没有23 25
//	string tab = ",";
//	string in_path;
//	int fileNum = 0;
//
//	const string out_dir = "E:\\out\\sum\\";
//	const string out_path = out_dir + "forFactorAnalysis.csv";//.tsv
//
//	for (int m = 0; m < questionVec.size(); m++) {
//		const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
//
//		string questionid = questionVec[m];
//
//		ofstream out_file(out_path, ofstream::out);
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
//			//读第一遍，计算sum
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
//			fp = fopen(in_path.c_str(), "r");//string to const char*
//			if (!fp)
//			{
//				cout << "OPEN ERROR!" << endl;
//				return 0;
//			}
//			//读第二遍，加入哈希表中，估计会爆内存？
//			while (fgets(original_data, sizeof(original_data), fp))
//			{
//				vector<string> line;
//				//;get a line data in .tsv
//				my_split(original_data, '\t', line);
//				if (line.size() == 0) {
//					break;
//				}
//				double tempSupp = (double)atoi(line[2].c_str()) / (double)sum;//如果对值做平均的话，改为sum,如果单纯相加，改为1.0
//
//				umScsuppAll[line[7]] += tempSupp;
//				pair<double, int> supp_index(tempSupp, k);
//				umAlpha_suppVec[line[7]].push_back(supp_index);
//
//				if (feof(fp))
//					break;
//			}
//			fclose(fp);
//
//		}
//	}
//
//	stringstream ss;
//
//	for (int i = 0; i < names.size(); i++) {
//		ss << names[i] << tab;
//	}
//	ss << endl;
//	for (auto aAlpha_suppVec : umAlpha_suppVec) {
//		vector<pair<double, int> > suppVec = aAlpha_suppVec.second;
//		//suppVec 0.002,0  0.03,5   0.23 6   就说明1234支持度全为0
//		vector<double> suppVecZero;//suppVec补0
//		int index = 0;
//		for (int i = 0; i < suppVec.size(); ) {
//			if (suppVec[i].second == index) {
//				suppVecZero.push_back(suppVec[i].first);
//				i++;
//			}
//			else {
//				suppVecZero.push_back(0);
//			}
//			index++;
//		}
//		for (int i = index; i < names.size(); i++) {
//
//			suppVecZero.push_back(0);
//		}
//
//		for (int i = 0; i < names.size(); i++) {
//			ss << suppVecZero[i] << tab;
//		}
//		ss << aAlpha_suppVec.first;//alpha
//	}
//
//	out_file << ss.str() << endl;
//	//cout << ss.str() << endl;
//	out_file.close();
//
//
//	system("pause");
//}