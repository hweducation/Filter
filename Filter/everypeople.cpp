/*
在sum的
模式长度>=6的过滤出来后，计算每个模式的支持度，进行加和
输出绝对稀疏性，相对稀疏性，典型度等
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
名称:my_split(const std::string& src, const char& delim,
		 std::vector<std::string>& vec)
功能:用分隔符将源字符串分隔为多个子串并传出; n个分隔符, 分n+1个子串

参数:
	 src-传入参数, 源字符串;
	 delim-传入参数, 分隔符;
	 vec-传出参数, 子串的集合;

返回值:
	0-成功;
	其它-失败;
 */

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
	double supp;
	string patstring;
	TPattern(double support, string ss) :supp(support), patstring(ss) {

	}
};
class CompGreater {
public:
	bool operator()(const TPattern& tpattern1, const TPattern& tpattern2) {
		return tpattern1.supp > tpattern2.supp;
	}
};
int main()
{
	//时间起点+AOI
	//Sequence8相比Sequence7 Option合并了
	FILE *fp;
	string questionid = "mid-shu-04-output";
	const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
	const string out_dir = "E:\\out\\sum\\" + questionid + "\\";
	string category = "low";//low  high
	vector<string> names;
	//	//"Patstr_recording18","Patstr_recording23","Patstr_recording24","Patstr_recording25",
	//	//"Patstr_recording26","Patstr_recording28","Patstr_recording30",
	//	//"Patstr_recording31","Patstr_recording32","Patstr_recording46",
	//	//"Patstr_recording63","Patstr_recording70",
	//	"Patstr_recording18new","Patstr_recording23new","Patstr_recording24new","Patstr_recording28new",
	//	"Patstr_recording46new","Patstr_recording70new"
	//};//高分组
	if (category == "high") {
		names.push_back("Patstr_recording18new");
		names.push_back("Patstr_recording23new");
		names.push_back("Patstr_recording24new");
		names.push_back("Patstr_recording28new");
		names.push_back("Patstr_recording46new");
		names.push_back("Patstr_recording70new");
	}
	else {
		names.push_back("Patstr_recording25new");
		names.push_back("Patstr_recording26new");
		names.push_back("Patstr_recording30new");
		names.push_back("Patstr_recording31new");
		names.push_back("Patstr_recording32new");
		names.push_back("Patstr_recording63new");
	}
	/*
	低分组
		"Patstr_recording25new", "Patstr_recording26new", "Patstr_recording30new",
		"Patstr_recording31new", "Patstr_recording32new", "Patstr_recording63new",
	*/

	unordered_map<string, double> umScsuppAll;
	//mid-shu-01-output 没有25
	//mid-shu-03-output 没有25
	//mid-shu-04-output 没有23
	//hou-shu-04-output 没有23 25
	string tab = "\t";
	string in_path;
	int fileNum = 0;

	//支持度计算开始
	for (int k = 0; k < names.size(); k++) {
		in_path = in_dir + names[k] + ".txt";
		cout << "第" << k << "个文件路径为：" << in_path << endl;

		long sum = 0;
		fp = fopen(in_path.c_str(), "r");//string to const char*
		if (!fp)
		{
			cout << "OPEN ERROR!" << endl;
			continue;
		}
		fileNum++;
		int i = 0;

		char original_data[20000];
		//fgets(original_data, sizeof(original_data), fp);//表头
		const char * split = "\t";

		//读第一遍，将出现频率相加，计算sum
		while (fgets(original_data, sizeof(original_data), fp))
		{
			i++;//recode current line
			vector<string> line;
			//;get a line data in .tsv
			my_split(original_data, '\t', line);
			if (line.size() == 0) {
				break;
			}
			sum += atoi(line[2].c_str());
			if (feof(fp))
				break;
		}

		fp = fopen(in_path.c_str(), "r");//string to const char*
		if (!fp)
		{
			cout << "OPEN ERROR!" << endl;
			continue;
			//return 0;
		}
		//读第二遍，加入全局支持度哈希表中，估计会爆内存？
		while (fgets(original_data, sizeof(original_data), fp))
		{
			vector<string> line;
			//;get a line data in .tsv
			my_split(original_data, '\t', line);
			if (line.size() == 0) {
				break;
			}
			double temp = (double)atoi(line[2].c_str()) / (double)sum;//如果对值做平均的话，改为sum,如果单纯相加，改为1.0
	
			umScsuppAll[line[7]] += temp;

			if (feof(fp))
				break;
		}
		fclose(fp);
	}
	//支持度计算结束

	//输出支持度
	vector<TPattern> tPatternVec;
	string suppallName = "E:\\out\\sum\\all\\" + questionid + "\\" + category + "_suppall.csv";
	ofstream out_file(suppallName, ofstream::out);//全局支持度路径
	stringstream ss;
	for (auto aUmScsuppAll :umScsuppAll) {
		TPattern tpttern(aUmScsuppAll.second, aUmScsuppAll.first);
		tPatternVec.push_back(tpttern);
	}

	sort(tPatternVec.begin(), tPatternVec.end(), CompGreater());//降序排序
	//unordered_map<string, double> umScsuppAll;

	for (auto aTPatternVec : tPatternVec) {
		ss << aTPatternVec.supp << "," << aTPatternVec.patstring;
	}

	out_file << ss.str() << endl;
	cout << ss.str() << endl;

	out_file.close();

	//输出支持度结束

	////稀疏性计算开始
	//for (int k = 0; k < names.size(); k++) {
	//	in_path = in_dir + names[k] + ".txt";
	//	cout << "第" << k << "个文件路径为：" << in_path << endl;

	//	const string out_path = out_dir + names[k] + ".txt";//.tsv
	//	cout << out_path << endl;
	//	ofstream out_file(out_path, ofstream::out);

	//	long sum = 0;
	//	fp = fopen(in_path.c_str(), "r");//string to const char*
	//	if (!fp)
	//	{
	//		cout << "OPEN ERROR!" << endl;
	//		continue;
	//	}
	//	fileNum++;
	//	int i = 0;
	//	char original_data[20000];
	//	//fgets(original_data, sizeof(original_data), fp);//表头
	//	const char * split = "\t";

	//	unordered_map<string, double> umScsuppUesr;
	//	unordered_map<string, double> umAR;
	//	unordered_map<string, double> umRR;
	//	unordered_map<string, double> umTypical;//典型度

	//	//fgets(original_data, sizeof(original_data), fp);//表头
	//	//读第3遍，将出现频率相加，计算sum
	//	while (fgets(original_data, sizeof(original_data), fp))
	//	{
	//		i++;//recode current line
	//		vector<string> line;
	//		//;get a line data in .tsv
	//		my_split(original_data, '\t', line);
	//		if (line.size() == 0) {
	//			break;
	//		}
	//		sum += atoi(line[2].c_str());
	//		if (feof(fp))
	//			break;
	//	}

	//	fp = fopen(in_path.c_str(), "r");//string to const char*
	//	if (!fp)
	//	{
	//		cout << "OPEN ERROR!" << endl;
	//		continue;
	//	}
	//	fileNum++;
	//	//读第4遍，加入私有支持度和全局支持度哈希表中，估计会爆内存？
	//	while (fgets(original_data, sizeof(original_data), fp))
	//	{
	//		vector<string> line;
	//		//;get a line data in .tsv
	//		my_split(original_data, '\t', line);
	//		if (line.size() == 0) {
	//			break;
	//		}
	//		double temp = (double)atoi(line[2].c_str()) / (double)sum;//如果对值做平均的话，改为sum,如果单纯相加，改为1.0
	//		umScsuppUesr[line[7]] = temp;//注意line[7]是有换行的

	//		if (feof(fp))
	//			break;
	//	}
	//	fclose(fp);
	//	double ARsum = 0;
	//	int alphasum = 0;//模式总数
	//	for (auto aScsuppUser : umScsuppUesr) {
	//		double AR = aScsuppUser.second - umScsuppAll[aScsuppUser.first];
	//		umAR[aScsuppUser.first] = AR;
	//		ARsum += AR;
	//		alphasum++;
	//	}
	//	for (auto aUmAR : umAR) {
	//		double RR = aUmAR.second - ARsum / (double)alphasum;
	//		umRR[aUmAR.first] = RR;
	//		umTypical[aUmAR.first] = umScsuppAll[aUmAR.first] * umRR[aUmAR.first];
	//	}
	//	stringstream ss;
	//	ss << "AR" << tab << "RR" << tab << "Typical" << tab << "alpha" << endl;
	//	for (auto aUmTypical : umTypical) {
	//		//目前没做任何筛选
	//		string alpha = aUmTypical.first;
	//		ss << umAR[alpha] << tab << umRR[alpha] << tab << umTypical[alpha] << tab << alpha;
	//	}

	//	out_file << ss.str() << endl;
	//	cout << ss.str() << endl;

	//	out_file.close();
	//}
	////稀疏性计算结束

	system("pause");
}