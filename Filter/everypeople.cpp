///*
//��sum��
//ģʽ����>=6�Ĺ��˳�����
//1���������ϡ���ԣ����ϡ���ԣ����Ͷȵ�
//���� "E:\\read-all\\filter\\" + questionid + "\\";
//��� "E:\\out\\sum\\" + questionid + "\\";
//
//2������ÿ��ģʽ��֧�ֶȣ����мӺͣ������������֧�ֶ�
//���� "E:\\read-all\\filter\\" + questionid + "\\";
//��� "E:\\out\\sum\\all\\" + questionid + "\\" + category + "_suppall.csv";
//
//3�����ÿ����ÿ����TopN��ģʽ��һ���ļ���
//���� "E:\\read-all\\filter\\" + questionid + "\\";
//��� "E:\\out\\sum\\" + questionid + "\\highallSparse.csv";
//
//
//3�����ÿ����TopN��ģʽ��һ���ļ��У����ǽ���Ŀ�ϲ�������ļ�����һ����Ŀ��
//���� "E:\\read-all\\filter\\" + questionid + "\\";
//��� "E:\\out\\sum\\highallSparse.csv";
//
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
//	int topNumber = 5;	
//
//	string category = "high";//low  high
//	const string out_dir = "E:\\out\\sum\\";
//	string tab = ",";
//	for (int m = 0; m < questionVec.size(); m++) {
//
//		FILE *fp;
//		string questionid = questionVec[m];
//
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
//			names.push_back("Patstr_recording23new");
//			names.push_back("Patstr_recording24new");
//			names.push_back("Patstr_recording28new");
//			names.push_back("Patstr_recording46new");
//			names.push_back("Patstr_recording70new");
//		}
//		else {
//			names.push_back("Patstr_recording25new");
//			names.push_back("Patstr_recording26new");
//			names.push_back("Patstr_recording32new");
//			names.push_back("Patstr_recording30new");
//			names.push_back("Patstr_recording31new");
//			names.push_back("Patstr_recording63new");
//		}
//		/*
//		�ͷ���
//			"Patstr_recording25new", "Patstr_recording26new", "Patstr_recording30new",
//			"Patstr_recording31new", "Patstr_recording32new", "Patstr_recording63new",
//		*/
//		unordered_map<string, double> umScsuppAll;
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
//				umScsuppAll[line[7]] += temp;
//
//				if (feof(fp))
//					break;
//			}
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
//		//ϡ���Լ��㿪ʼ
//		for (int k = 0; k < names.size(); k++) {
//			in_path = in_dir + names[k] + ".txt";
//			cout << "��" << k << "���ļ�·��Ϊ��" << in_path << endl;
//
//			const string out_path = out_dir + questionid + "\\" + names[k] + ".csv";//.txt  .tsv
//			cout << out_path << endl;
//			ofstream out_file(out_path, ofstream::out);
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
//			char original_data[20000];
//			//fgets(original_data, sizeof(original_data), fp);//��ͷ
//			const char * split = "\t";
//
//			unordered_map<string, double> umScsuppUesr;
//			unordered_map<string, double> umAR;
//			unordered_map<string, double> umRR;
//			unordered_map<string, double> umTypical;//���Ͷ�
//
//			vector<UpsPattern> upsPatternVec;
//
//			//fgets(original_data, sizeof(original_data), fp);//��ͷ
//			//����3�飬������Ƶ����ӣ�����sum
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
//			}
//			fileNum++;
//			//����4�飬����˽��֧�ֶȺ�ȫ��֧�ֶȹ�ϣ���У����ƻᱬ�ڴ棿
//			while (fgets(original_data, sizeof(original_data), fp))
//			{
//				vector<string> line;
//				//;get a line data in .tsv
//				my_split(original_data, '\t', line);
//				if (line.size() == 0) {
//					break;
//				}
//				double temp = (double)atoi(line[2].c_str()) / (double)sum;//�����ֵ��ƽ���Ļ�����Ϊsum,���������ӣ���Ϊ1.0
//				umScsuppUesr[line[7]] = temp;//ע��line[7]���л��е�
//
//				if (feof(fp))
//					break;
//			}
//			fclose(fp);
//			double ARsum = 0;
//			int alphasum = 0;//ģʽ����
//			for (auto aScsuppUser : umScsuppUesr) {
//				double AR = aScsuppUser.second - umScsuppAll[aScsuppUser.first];
//				umAR[aScsuppUser.first] = AR;
//				ARsum += AR;
//				alphasum++;
//			}
//			for (auto aUmAR : umAR) {
//				double RR = aUmAR.second - ARsum / (double)alphasum;
//				umRR[aUmAR.first] = RR;
//				umTypical[aUmAR.first] = umScsuppAll[aUmAR.first] * umRR[aUmAR.first];
//			}
//			stringstream ss;
//			ss << "AR" << tab << "RR" << tab << "Typical" << tab << "alpha" << endl;
//			for (auto aUmTypical : umTypical) {
//				//Ŀǰû���κ�ɸѡ
//				string alpha = aUmTypical.first;
//				// ss << umAR[alpha] << tab << umRR[alpha] << tab << umTypical[alpha] << tab << alpha;
//				UpsPattern temp(umAR[alpha], umRR[alpha], umTypical[alpha], alpha, names[k], questionid);
//				upsPatternVec.push_back(temp);
//			}
//			sort(upsPatternVec.begin(), upsPatternVec.end(), CompGreaterUpsPattern());
//			//��ÿ���˵�TopNģʽ���뵽������
//			if (upsPatternVec.size() > topNumber) {
//				for (int j = 0; j < topNumber; j++) {
//					allTopNVec.push_back(upsPatternVec[j]);
//				}
//			}
//			else {
//				for (int j = 0; j < upsPatternVec.size(); j++) {
//					allTopNVec.push_back(upsPatternVec[j]);
//				}
//			}
//
//			for (auto aUpsPatternVec : upsPatternVec) {
//				ss << aUpsPatternVec.ar << tab << aUpsPatternVec.rr << tab << aUpsPatternVec.typical << tab << aUpsPatternVec.patstring;
//			}
//			out_file << ss.str() << endl;
//			cout << ss.str() << endl;
//			out_file.close();
//		}
//		//ϡ���Լ������
//
//	}
//	//���ÿ����TopN��ģʽ��һ���ļ���
//	stringstream ss;
//	ss << "personName" << tab << "AR" << tab << "RR" << tab << "Typical" << tab << "questionid" << tab << "alpha" << endl;
//	for (auto aAllTopNVec : allTopNVec) {
//		ss << aAllTopNVec.personName << tab << aAllTopNVec.ar << tab << aAllTopNVec.rr << tab << aAllTopNVec.typical << tab << aAllTopNVec.questionName << tab << aAllTopNVec.patstring;
//	}
//	ofstream out_file(out_dir + category + "allSparse.csv", ofstream::out);
//	out_file << ss.str() << endl;
//	cout << ss.str() << endl;
//	out_file.close();
//
//	system("pause");
//}