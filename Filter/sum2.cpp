///*
//��sum�Ļ����ϸĵ�
//ģʽ����>=6�Ĺ��˳����󣬼���ÿ��ģʽ��֧�ֶȣ����мӺ�
//�޸ĳ����ڵõ�������Ŀ�����ӷ��������ļ�
//���� "E:\\read-all\\filter\\" + questionid + "\\";
//��� "E:\\out\\sum\\";
////����Ŀ���ģʽ����
//
////������Ŀͳһ���ģʽ����
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
//	names.push_back("Patstr_recording25new");//25���high��
//	names.push_back("Patstr_recording28new");
//	names.push_back("Patstr_recording70new");
//	//��ӵ�
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
//	//��ӵ�
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
//	unordered_map<string, vector<pair<double, int> > > umAlpha_suppVec;//ģʽ����֧�ֶȣ�֧�ֶȣ�֧�ֶȣ�֧�ֶȣ�֧�ֶ�...
//	//mid-shu-01-output û��25
//	//mid-shu-03-output û��25
//	//mid-shu-04-output û��23
//	//hou-shu-04-output û��23 25
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
//			cout << "��" << k << "���ļ�·��Ϊ��" << in_path << endl;
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
//			//fgets(original_data, sizeof(original_data), fp);//��ͷ
//			const char * split = "\t";
//
//			//����һ�飬����sum
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
//			//���ڶ��飬�����ϣ���У����ƻᱬ�ڴ棿
//			while (fgets(original_data, sizeof(original_data), fp))
//			{
//				vector<string> line;
//				//;get a line data in .tsv
//				my_split(original_data, '\t', line);
//				if (line.size() == 0) {
//					break;
//				}
//				double tempSupp = (double)atoi(line[2].c_str()) / (double)sum;//�����ֵ��ƽ���Ļ�����Ϊsum,���������ӣ���Ϊ1.0
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
//		//suppVec 0.002,0  0.03,5   0.23 6   ��˵��1234֧�ֶ�ȫΪ0
//		vector<double> suppVecZero;//suppVec��0
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