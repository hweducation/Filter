///*
//����everyPeopleQuestion�ĵļ���߷ֵͷ�����Ͷ�
//
//���� in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
//��� out_dir = "E:\\out\\sum\\" + questionid + "\\";
//high�е�֧�ֶ� low�е�֧�ֶ� ǰ������� ģʽ����
//*/
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <unordered_map>
//#include <algorithm>
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
//const double hss = 0.04;//PWF�ֶκ����еĲ�����ȫ��֧�ֶ���ֵ�������ǣ���ȫ��֧�ֶ��д������֧�ֶ���ֵ��ģʽ��Ҫ��
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
//class TPattern {
//public:
//	double supp;
//	string patstring;
//	TPattern(double support, string ss) :supp(support), patstring(ss) {
//
//	}
//};
//class CompGreaterTPattern {
//public:
//	bool operator()(const TPattern& tpattern1, const TPattern& tpattern2) {
//		return tpattern1.supp > tpattern2.supp;
//	}
//};
//class UpsPattern {
//public:
//	double ar;
//	double rr;
//	double typical;
//	string patstring;
//	string personName;
//	string questionName;
//	UpsPattern(double myAR, double myRR, double myTypical, string patname, string person, string question)
//		:ar(myAR), rr(myRR), typical(myTypical), patstring(patname), personName(person), questionName(question) {
//
//	}
//};
//class CompGreaterUpsPattern {
//public:
//	bool operator()(const UpsPattern& upsPattern1, const UpsPattern& upsPattern2) {
//		return upsPattern1.typical > upsPattern2.typical;
//	}
//};
//int main()
//{
//	//ʱ�����+AOI
//	//Sequence8���Sequence7 Option�ϲ���
//
//	vector<string> questionVec;
//	questionVec.push_back("hou-shu-01-output");
//	questionVec.push_back("hou-shu-04-output");
//	questionVec.push_back("mid-shu-02-output");
//	questionVec.push_back("mid-shu-03-output");
//	questionVec.push_back("mid-shu-04-output");
//
//	//�����˵ĵ��Ͷȵ�TopN����vec���淽��Ա�
//	vector<UpsPattern> allTopNVec;
//	int topNumber = 20;
//	vector<string> categoryNames{ "low","high" };
//	unordered_map<string, double> umScsuppAll;
//	unordered_map<string, double> umScsuppAllHigh;//�߷���֧�ֶ�
//	unordered_map<string, double> umScsuppAllLow;//�ͷ���֧�ֶ�
//	const string out_dir = "E:\\out\\sum\\";
//	string tab = ",";
//	string questionid = questionVec[2];
//
//	for (int k = 0; k < categoryNames.size(); k++) {
//		string category = categoryNames[k];//low  high categoryNames[k]
//
//		//for (int m = 0; m < questionVec.size(); m++) {
//		FILE *fp;
//		const string in_dir = "E:\\read-all\\filter\\" + questionid + "\\";
//
//		vector<string> names;
//		//	//"Patstr_recording18","Patstr_recording23","Patstr_recording24","Patstr_recording25",
//		//	//"Patstr_recording26","Patstr_recording28","Patstr_recording30",
//		//	//"Patstr_recording31","Patstr_recording32","Patstr_recording46",
//		//	//"Patstr_recording63","Patstr_recording70",
//		//	"Patstr_recording18new","Patstr_recording23new","Patstr_recording24new","Patstr_recording28new",
//		//	"Patstr_recording46new","Patstr_recording70new"
//		//};//�߷���
//		if (category == "high") {
//			names.push_back("Patstr_recording18new");
//			names.push_back("Patstr_recording46new");
//			names.push_back("Patstr_recording23new");
//			names.push_back("Patstr_recording24new");
//			names.push_back("Patstr_recording25new");//25���high��
//			names.push_back("Patstr_recording28new");
//			names.push_back("Patstr_recording70new");
//			//��ӵ�
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
//			//��ӵ�
//			names.push_back("Patstr_recording19new");
//			names.push_back("Patstr_recording27new");
//			names.push_back("Patstr_recording33new");
//			names.push_back("Patstr_recording34new");
//			names.push_back("Patstr_recording35new");
//			names.push_back("Patstr_recording45new");
//		}
//		/*
//		�ͷ���
//			"Patstr_recording25new", "Patstr_recording26new", "Patstr_recording30new",
//			"Patstr_recording31new", "Patstr_recording32new", "Patstr_recording63new",
//		*/
//		//mid-shu-01-output û��25
//		//mid-shu-03-output û��25
//		//mid-shu-04-output û��23
//		//hou-shu-04-output û��23 25
//		string in_path;
//		int fileNum = 0;
//
//		//֧�ֶȼ��㿪ʼ
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
//			//����һ�飬������Ƶ����ӣ�����sum
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
//			//���ڶ��飬����ȫ��֧�ֶȹ�ϣ���У����ƻᱬ�ڴ棿
//			while (fgets(original_data, sizeof(original_data), fp))
//			{
//				vector<string> line;
//				//;get a line data in .tsv
//				my_split(original_data, '\t', line);
//				if (line.size() == 0) {
//					break;
//				}
//				double temp = (double)atoi(line[2].c_str()) / (double)sum;//�����ֵ��ƽ���Ļ�����Ϊsum,���������ӣ���Ϊ1.0
//
//				umScsuppAll[line[7]] += temp / names.size();//ȫ��֧�ֶ��޸ĳ���ƽ��ֵ����������������
//
//				if (feof(fp))
//					break;
//			}
//
//			fclose(fp);
//		}
//		//֧�ֶȼ������
//
//		/*
//		//����������֧�ֶȿ�ʼ
//		vector<TPattern> tPatternVec;
//		string suppallName = "E:\\out\\sum\\all\\" + questionid + "\\" + category + "_suppall.csv";
//		ofstream out_file(suppallName, ofstream::out);//ȫ��֧�ֶ�·��
//		stringstream ss;
//		for (auto aUmScsuppAll :umScsuppAll) {
//			TPattern tpttern(aUmScsuppAll.second, aUmScsuppAll.first);
//			tPatternVec.push_back(tpttern);
//		}
//		sort(tPatternVec.begin(), tPatternVec.end(), CompGreaterTPattern());//��������
//
//		for (auto aTPatternVec : tPatternVec) {
//			ss << aTPatternVec.supp << "," << aTPatternVec.patstring;
//		}
//
//		out_file << ss.str() << endl;
//		cout << ss.str() << endl;
//
//		out_file.close();
//		//����������֧�ֶȽ���
//		*/
//
//		if (category == "low") {
//			umScsuppAllLow = umScsuppAll;
//		}
//		else {
//			umScsuppAllHigh = umScsuppAll;
//		}
//		umScsuppAll.clear();
//	}
//
//	//���ϡ���Լ��㿪ʼ
//	unordered_map<string, double> umAR;
//	unordered_map<string, double> umRR;
//	unordered_map<string, double> umTypical;//���Ͷ�
//
//	vector<UpsPattern> upsPatternVec;
//
//	double ARsum = 0;
//	int alphasum = 0;//ģʽ����
//
//	////����߷�����Ͷ�
//	//for (auto aumScsuppAllHigh : umScsuppAllHigh) {
//	//	double AR = aumScsuppAllHigh.second - umScsuppAllLow[aumScsuppAllHigh.first];
//	//	umAR[aumScsuppAllHigh.first] = AR;
//	//	ARsum += AR;
//	//	alphasum++;
//	//}
//	//for (auto aUmAR : umAR) {
//	//	double RR = aUmAR.second - ARsum / (double)alphasum;
//	//	umRR[aUmAR.first] = RR;
//	//	//��ʽ3.7�ķֶκ���
//	//	if (umScsuppAllLow[aUmAR.first] >= hss) {
//	//		umTypical[aUmAR.first] = 0;
//	//	}
//	//	else {
//	//		umTypical[aUmAR.first] = (hss - umScsuppAllLow[aUmAR.first])* umRR[aUmAR.first];
//	//	}
//	//}
//	////��ϡ���Լ������
//	//stringstream ss;
//	//ss <<  "AR" << tab << "RR" << tab << "Typical" << tab << "�߷���֧�ֶ�" << tab << "�ͷ���֧�ֶ�" << tab << "alpha" << endl;
//	//for (auto aUmScsuppAllHigh : umScsuppAllHigh) {
//	//	ss << umAR[aUmScsuppAllHigh.first] << tab << umRR[aUmScsuppAllHigh.first] << tab << umTypical[aUmScsuppAllHigh.first] << tab <<
//	//		umScsuppAllHigh[aUmScsuppAllHigh.first] << tab << umScsuppAllLow[aUmScsuppAllHigh.first] << tab <<
//	//		aUmScsuppAllHigh.first;
//	//}
//	//cout << out_dir + questionid + "\\highLowTypical.csv" << endl;
//	//ofstream out_file(out_dir + questionid + "\\highLowTypical.csv", ofstream::out);
//	//out_file << ss.str() << endl;
//
//	//cout << ss.str() << endl;
//	//out_file.close();
//
//
//
//
//
//	//����ͷ�����Ͷ�
//	for (auto aumScsuppAllLow : umScsuppAllLow) {
//		double AR = aumScsuppAllLow.second - umScsuppAllHigh[aumScsuppAllLow.first];
//		umAR[aumScsuppAllLow.first] = AR;
//		ARsum += AR;
//		alphasum++;
//	}
//	for (auto aUmAR : umAR) {
//		double RR = aUmAR.second - ARsum / (double)alphasum;
//		umRR[aUmAR.first] = RR;
//		//��ʽ3.7�ķֶκ���
//		if (umScsuppAllHigh[aUmAR.first] >= hss) {
//			umTypical[aUmAR.first] = 0;
//		}
//		else {
//			umTypical[aUmAR.first] = (hss - umScsuppAllHigh[aUmAR.first])* umRR[aUmAR.first];
//		}
//	}
//
//	//��ϡ���Լ������
//	stringstream ss;
//	ss << "AR" << tab << "RR" << tab << "Typical" << tab << "�߷���֧�ֶ�" << tab << "�ͷ���֧�ֶ�" << tab << "alpha" << endl;
//	for (auto aUmScsuppAllLow : umScsuppAllLow) {
//		ss << umAR[aUmScsuppAllLow.first] << tab << umRR[aUmScsuppAllLow.first] << tab << umTypical[aUmScsuppAllLow.first] << tab <<
//			umScsuppAllLow[aUmScsuppAllLow.first] << tab << umScsuppAllHigh[aUmScsuppAllLow.first] << tab <<
//			aUmScsuppAllLow.first;
//	}
//	ofstream out_file(out_dir + questionid + "\\lowHighTypical.csv", ofstream::out);
//	out_file << ss.str() << endl;
//
//	cout << ss.str() << endl;
//	out_file.close();
//
//
//	system("pause");
//}