#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const bool DEBUG = false;

int main(int argc, char* argv[]) {
    string file;
    ifstream fin;
    if (argc <= 1) {
        cout << "�������ļ����ƣ�";
        cin >> file;
    } else {
        file = argv[1];
    }
    fin.open(file);
    if (!fin.is_open()) {
        cout << "�޷����ļ�" << endl;
        system("pause");
        return 1;
    }
    // �����ļ�
    string code((std::istreambuf_iterator<char>(fin)),
                std::istreambuf_iterator<char>());
    fin.close();
    if (DEBUG) {
        cout << code << endl;
        cout << "-----------------" << endl;
    }
    // ������ѧ��ʽ�Ŀ�ͷ�ͽ�β
    vector<pair<int, int>> maths;
    cout << "��ʼѰ��������ѧ��ʽ" << endl;
    for (int i = 0; i < code.length(); i++) {
        if (code[i] == '$') {
            i++;
            bool is_double = false;
            int start = i;
            if (code[i] == '$') {
                is_double = true;
                i++;
                start = i;
            }
            while (i < code.length() && code[i] != '$') {
                i++;
            }
            if (is_double) {
                i++;
            }
            if (i >= code.length() || code[i] != '$') {
                cout << "����ȱ�ٽ�����" << endl;
                system("pause");
                return 1;
            }
            int end = i;
            maths.push_back(pair<int, int>(start, end));
            cout << start << " " << end << endl;
            if (DEBUG) {
                string math = code.substr(start, end - start);
                cout << math << endl;
            }
        }
    }
    cout << "Ѱ����ɣ���ʼ����" << endl;
    int count = 0;
    for (int i = 0; i < maths.size(); i++) {
        for (int j = maths[i].first + count; j < maths[i].second + count; j++) {
            if (code[j] == '_') {
                code.insert(j, "\\");
                count++;
                j++;
            } else if (code[j] == '\\') {
                j++;
                if (code[j] == '\\') {
                    code.insert(j, "\\\\");
                    count += 2;
                    j += 2;
                } else if (code[j] == '{' || code[j] == '}') {
                    code.insert(j, "\\");
                    count++;
                    j++;
                }
            }
        }
    }
    if (DEBUG) {
        cout << code << endl;
    }
    cout << "������ɣ���ʼд���ļ�" << endl;
    ofstream fout;
    string location = file.substr(0, file.find_last_of('\\') + 1);
    fout.open(location + "index.md");
    if (!fout.is_open()) {
        cout << "�޷����ļ�" << endl;
        system("pause");
        return 1;
    }
    fout << code;
    return 0;
}

