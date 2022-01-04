#include <cstdio>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

void read_vector() {
    FILE* fp = fopen("input.txt", "r");
    char ch[80];
    //fscanf(fp,"%s",ch);     // 按行读入
    //cout<< ch << endl;
    while (!feof(fp)) {
        fgets(ch,80,fp);
        printf("%d\n", strlen(ch));
        printf("%s", ch);
    }

}

void read_vector_std() {
    char ch[80];
    fgets(ch,80,stdin);
    printf("%d\n", strlen(ch));
    fputs(ch, stdout);

    char* s = ch;
    int b = atoi(s);
    //fputs(b, stdout);
    fprintf(stdout, "%d", b);

}

void read_vector_str() {
    int n;
    char ch[80];
    fscanf(stdin, "%d", &n);
    fgetc(stdin);
    vector<string> strs;
    for (int i = 0; i < n; i++){

        fgets(ch,80,stdin);
        //gets(ch);
        cout << strlen(ch) <<endl;
        ///cout << ch;
        strs.push_back(string(ch, strlen(ch)-1));
    }
    fputs("next\n", stdout);
    for (int i = 0; i < n; i++) {
        fputs(strs[i].c_str(), stdout);
        fprintf(stdout, "\n%s\n", strs[i].c_str());
    }
}

void test_str() {
    char str[30];
    char ch;
    printf("请输入字符串：");
    scanf("%s", str);
    printf("%s", str);
    fscanf(stdin, "%c", &ch);
    printf("ch = %c", ch);
    fscanf(stdin, "%c", &ch);
    printf("ch = %c", ch);
}

void readStrCpp() {
    int n;
    char ch[80];
    string buffer;
    cin >> n;
    getc(stdin);
    vector<string> buffers;

    for (int i = 0; i < n; i++) {
        cout <<n<<" : "<<i <<":\n";
        getline(cin, buffer);
        buffers.push_back(buffer);
    }
    for (auto& str : buffers) {
        cout << str <<"\n";
    }
}

int main() {
    //ifstream fs("input.txt");
    ifstream infile; 
    string data;
    infile.open("input.txt"); 
    
    //infile >> data; 

    getline(infile, data);
    getline(infile, data);        
            // 在屏幕上写入数据
    cout << data << endl;
    while (!infile.eof()) {
        getline(infile, data);
            
            // 在屏幕上写入数据
        cout << data << endl;
    }

    
    read_vector();

    char a[5] = {'a', 'b', '\n'};
    char* b = a;
    cout << b<<endl;
    cout << strlen(b) <<endl;
    cout << sizeof(b) <<endl;
    cout << sizeof(a) <<endl;

    char * c = "abc";
    cout << strlen(c) <<endl;
    cout << sizeof(c) <<endl;
    cout << sizeof("abc")<<endl;

    readStrCpp();

    return 0;
}