/*
���¼���õ�������֧�ֶȺ�����ڸ߷�����֧�ֶȸߣ��ͷ���֧�ֶȵͣ�ͨ��֧�ֶ���ֵ���ã���ģʽ ��֮��Ȼ

���� in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
��� out_dir = "E:\\out\\sum\\" + questionid + "\\";
high�е�֧�ֶ� low�е�֧�ֶ� ǰ������� ģʽ����
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
����:my_split(const std::string& src, const char& delim,
		 std::vector<std::string>& vec)
����:�÷ָ�����Դ�ַ����ָ�Ϊ����Ӵ�������; n���ָ���, ��n+1���Ӵ�

����:
	 src-�������, Դ�ַ���;
	 delim-�������, �ָ���;
	 vec-��������, �Ӵ��ļ���;

����ֵ:
	0-�ɹ�;
	����-ʧ��;
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

		//1.�Ҳ����ָ���
		if (-1 == find_cursor) {
			if (read_cursor <= 0) return -1;

			//���һ���Ӵ�, src��βû�зָ���
			if (read_cursor < src_len) {
				vec.push_back(src.substr(read_cursor, src_len - read_cursor));
				return 0;
			}
		}
		//2.�������ָ��������
		else if (find_cursor == read_cursor) {
			//�ַ�����ͷΪ�ָ���, Ҳ�����Ӵ�����, �粻��Ҫ�ɼ����ж�&&(read_cursor!=0)
			vec.push_back(string(""));
		}
		//3.�ҵ��ָ���
		else
			vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));

		read_cursor = ++find_cursor;
		if (read_cursor == src_len) {
			//�ַ����Էָ�����β, �粻��Ҫĩβ���Ӵ�, ֱ��return
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
	//ʱ�����+AOI
	//Sequence8���Sequence7 Option�ϲ���
	FILE *fp;
	string questionid = "hou-shu-04-output";
	const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
	const string out_dir = "E:\\out\\sum\\" + questionid + "\\";

	unordered_map<string, double> umScsuppAll;
	unordered_map<string, double> umHighScsuppAll;
	unordered_map<string, double> umLowScsuppAll;
	vector<string> categoryNames{ "low","high" };
	for (int k = 0; k < categoryNames.size(); k++) {
		string category = categoryNames[k];//low  high

		vector<string> names;
		//	//"Patstr_recording18","Patstr_recording23","Patstr_recording24","Patstr_recording25",
		//	//"Patstr_recording26","Patstr_recording28","Patstr_recording30",
		//	//"Patstr_recording31","Patstr_recording32","Patstr_recording46",
		//	//"Patstr_recording63","Patstr_recording70",
		//	"Patstr_recording18new","Patstr_recording23new","Patstr_recording24new","Patstr_recording28new",
		//	"Patstr_recording46new","Patstr_recording70new"
		//};//�߷���
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
		�ͷ���
			"Patstr_recording25new", "Patstr_recording26new", "Patstr_recording30new",
			"Patstr_recording31new", "Patstr_recording32new", "Patstr_recording63new",
		*/

		string tab = "\t";
		string in_path;
		int fileNum = 0;

		//֧�ֶȼ��㿪ʼ
		for (int k = 0; k < names.size(); k++) {
			in_path = in_dir + names[k] + ".txt";
			cout << "��" << k << "���ļ�·��Ϊ��" << in_path << endl;

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
			//fgets(original_data, sizeof(original_data), fp);//��ͷ
			const char * split = "\t";

			//����һ�飬������Ƶ����ӣ�����sum
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
			//���ڶ��飬����ȫ��֧�ֶȹ�ϣ���У����ƻᱬ�ڴ棿
			while (fgets(original_data, sizeof(original_data), fp))
			{
				vector<string> line;
				//;get a line data in .tsv
				my_split(original_data, '\t', line);
				if (line.size() == 0) {
					break;
				}
				double temp = (double)atoi(line[2].c_str()) / (double)sum;//�����ֵ��ƽ���Ļ�����Ϊsum,���������ӣ���Ϊ1.0

				umScsuppAll[line[7]] += temp;

				if (feof(fp))
					break;
			}
			fclose(fp);
		}
		//֧�ֶȼ������
		if (category == "high") {
			umHighScsuppAll = umScsuppAll;
		}
		else {
			umLowScsuppAll = umScsuppAll;

		}
	}
	////�����high��֧�ֶȸ���low��֧�ֶȵ�
	//string outName = out_dir + "high_low.csv";
	//ofstream out_file(outName, ofstream::out);//ȫ��֧�ֶ�·��
	//double thereshold = 0.02;//֧�ֶ���ֵ
	////unordered_map<string, double> 
	//stringstream ss;
	//for (auto aUmHighScsuppAll : umHighScsuppAll) {
	//	if (aUmHighScsuppAll.second > thereshold && umLowScsuppAll[aUmHighScsuppAll.first] < thereshold) {
	//		//high�е�֧�ֶ� low�е�֧�ֶ� ǰ������� ģʽ����
	//		ss << aUmHighScsuppAll.second << "," << umLowScsuppAll[aUmHighScsuppAll.first] << "," <<
	//			aUmHighScsuppAll.second - umLowScsuppAll[aUmHighScsuppAll.first] << "," << aUmHighScsuppAll.first;
	//	}
	//}
	//out_file << ss.str() << endl;
	//cout << ss.str() << endl;
	//out_file.close();

	//�����low��֧�ֶȸ���high��֧�ֶȵ�
	string outName = out_dir + "low_high.csv";
	ofstream out_file(outName, ofstream::out);//ȫ��֧�ֶ�·��
	double thereshold = 0.1;//֧�ֶ���ֵ
	//unordered_map<string, double> 
	stringstream ss;
	for (auto aUmLowScsuppAll : umLowScsuppAll) {
		if (aUmLowScsuppAll.second > thereshold && umHighScsuppAll[aUmLowScsuppAll.first] < thereshold) {
			//high�е�֧�ֶ� low�е�֧�ֶ� ǰ������� ģʽ����
			ss << aUmLowScsuppAll.second << "," << umHighScsuppAll[aUmLowScsuppAll.first] << "," <<
				aUmLowScsuppAll.second - umHighScsuppAll[aUmLowScsuppAll.first] << "," << aUmLowScsuppAll.first;
		}
	}
	out_file << ss.str() << endl;
	cout << ss.str() << endl;
	out_file.close();
	
	system("pause");
}