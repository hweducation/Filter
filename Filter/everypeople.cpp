/*
��sum��
ģʽ����>=6�Ĺ��˳����󣬼���ÿ��ģʽ��֧�ֶȣ����мӺ�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
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

int main()
{
	//ʱ�����+AOI
	//Sequence8���Sequence7 Option�ϲ���
	FILE *fp;
	string questionid = "hou-shu-04-output";
	const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
	const string out_dir = "E:\\out\\sum\\";
	vector<string> names{
		"Patstr_recording18","Patstr_recording24","Patstr_recording23","Patstr_recording25",
		"Patstr_recording26","Patstr_recording28","Patstr_recording30",
		"Patstr_recording31","Patstr_recording32","Patstr_recording46",
		"Patstr_recording63","Patstr_recording70"
	};
	unordered_map<string, double> um;
	//mid-shu-01-output û��25
	//mid-shu-03-output û��25
	//mid-shu-04-output û��23
	//hou-shu-04-output û��23 25
	string tab = "\t";
	string in_path;
	const string out_path = out_dir + questionid + ".txt";//.tsv
	cout << out_path << endl;
	ofstream out_file(out_path, ofstream::out);
	int fileNum = 0;

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

		//����һ�飬����sum
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
			return 0;
		}
		//���ڶ��飬�����ϣ���У����ƻᱬ�ڴ棿
		while (fgets(original_data, sizeof(original_data), fp))
		{
			vector<string> line;
			//;get a line data in .tsv
			my_split(original_data, '\t', line);
			if (line.size() == 0) {
				break;
			}
			double temp = (double)atoi(line[2].c_str()) / (double)sum;//�����ֵ��ƽ���Ļ�����Ϊsum,���������ӣ���Ϊ1.0

			um[line[7]] += temp;

			if (feof(fp))
				break;
		}
		fclose(fp);
	}


	stringstream ss;
	for (auto a : um) {
		ss << a.second / (double)fileNum << tab << a.first;
	}

	out_file << ss.str() << endl;
	cout << ss.str() << endl;

	out_file.close();
	system("pause");
}