///*
//���ھ����ģʽ����>=6�Ĺ��˳���
//*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//using namespace std;
///*
//����:my_split(const std::string& src, const char& delim,
//		 std::vector<std::string>& vec)
//����:�÷ָ�����Դ�ַ����ָ�Ϊ����Ӵ�������; n���ָ���, ��n+1���Ӵ�
//
//����:
//	 src-�������, Դ�ַ���;
//	 delim-�������, �ָ���;
//	 vec-��������, �Ӵ��ļ���;
//
//����ֵ:
//	0-�ɹ�;
//	����-ʧ��;
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
//		//1.�Ҳ����ָ���
//		if (-1 == find_cursor) {
//			if (read_cursor <= 0) return -1;
//
//			//���һ���Ӵ�, src��βû�зָ���
//			if (read_cursor < src_len) {
//				vec.push_back(src.substr(read_cursor, src_len - read_cursor));
//				return 0;
//			}
//		}
//		//2.�������ָ��������
//		else if (find_cursor == read_cursor) {
//			//�ַ�����ͷΪ�ָ���, Ҳ�����Ӵ�����, �粻��Ҫ�ɼ����ж�&&(read_cursor!=0)
//			vec.push_back(string(""));
//		}
//		//3.�ҵ��ָ���
//		else
//			vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));
//
//		read_cursor = ++find_cursor;
//		if (read_cursor == src_len) {
//			//�ַ����Էָ�����β, �粻��Ҫĩβ���Ӵ�, ֱ��return
//			vec.push_back(string(""));
//			return 0;
//		}
//	}//end while()
//	return 0;
//}
//
//int main()
//{
//	//ʱ�����+AOI
//	//Sequence8���Sequence7 Option�ϲ���
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
//	};//"Patstr_recording25new",���û���ھ�ģʽ
//	//mid-shu-01-output û��25
//	//mid-shu-03-output û��25
//	//mid-shu-04-output û��23
//	//hou-shu-04-output û��23 25
//	string in_path;
//	for (int k = 0; k < names.size(); k++) {
//		in_path = in_dir + names[k] + ".txt";
//		cout << "��" << k << "���ļ�·��Ϊ��" << in_path << endl;
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
//		fgets(original_data, sizeof(original_data), fp);//��ͷ
//		const char * split = "\t";
//		string last_eye_movement_type = "0";
//		int start_flag = 0;
//		vector <string> res;//���ڼ�¼����
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