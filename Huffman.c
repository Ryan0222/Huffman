typedef struct {
    char data;
    int weight ;
    int flag;
    int parent ;
    int leftChild ;
    int rightChild ;
}HaffNode ;

typedef struct {
    char bit[MaxNode];
    int start ;
    int weight ;
    char data ;
}Code ;

void Haffman(int weight[],char str[],int n,HaffNode haffTree[])
{
    int i,j,m1,m2,x1,x2 ;
    for(i=0;i<2*n-1;i++){
        if(i<n) {
            haffTree[i].weight=weight[i];
            haffTree[i].data=str[i];
        }else {
            haffTree[i].weight=0;
            haffTree[i].data='0';
        }
        haffTree[i].parent=-1;
        haffTree[i].flag=0;
        haffTree[i].leftChild=-1;
        haffTree[i].rightChild=-1;
    }
    for(i=0;i<n-1;i++){
        m1=m2=MaxValue ;
        x1=x2=0;
        for(j=0;j<n+i;j++){
            if(haffTree[j].weight<m1&&haffTree[j].flag==0){
                m2=m1;
                x2=x1;
                m1=haffTree[j].weight;
                x1=j;
            }else if(haffTree[j].weight<m2&&haffTree[j].flag==0)
            {
                m2=haffTree[j].weight;
                x2=j ;
            }
        }
        haffTree[x1].parent=n+i;
        haffTree[x2].parent=n+i;
        haffTree[x1].flag=haffTree[x2].flag=1;
        haffTree[n+i].weight=haffTree[x1].weight+haffTree[x2].weight;
        haffTree[n+i].leftChild=x1;
        haffTree[n+i].rightChild=x2;
    }
}

void HaffmanCode(HaffNode haffTree[],int n,Code haffCode[])
{
    Code *cd=(Code *)malloc(sizeof(Code));
    int i,j,child,parent ;
    for(i=0;i<n;i++){
        cd->start=n-1;
        cd->weight=haffTree[i].weight;
        cd->data=haffTree[i].data ;
        child=i;
        parent=haffTree[child].parent ;
        while(parent!=-1){
            if(haffTree[parent].leftChild==child)
                cd->bit[cd->start]='0';
            else 
                cd->bit[cd->start]='1';

            cd->start--;
            child=parent ;
            parent=haffTree[child].parent;
        }
        for(j=cd->start+1;j<n;j++)
            haffCode[i].bit[j]=cd->bit[j];
        haffCode[i].bit[j]='\0';
        haffCode[i].start=cd->start+1;
        haffCode[i].weight=cd->weight;
        haffCode[i].data=cd->data;
    }
}



#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<fstream>
#define MaxValue 32767
#define MaxNode 10000
#include"Haffman.h"
using namespace std ;

ifstream input_file ;
ofstream output_file ;
int n,m=0;
HaffNode *myHaffTree=(HaffNode *)malloc(sizeof(HaffNode)*(2*MaxNode-1));
Code *myHaffCode=(Code *)malloc(sizeof(Code)*MaxNode);

void Initialization(){
    char str[MaxNode];
    int weight[MaxNode];
    cout<<"请输入字符个数："<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"请输入第"<<i+1<<"个字符以及相应的权值"<<endl;
        cin>>str[i]>>weight[i];
    }

    Haffman(weight,str,n,myHaffTree);
    HaffmanCode(myHaffTree,n,myHaffCode);

    for(int i=0;i<n;i++){
        cout<<myHaffCode[i].data<<": ";
        for(int j=myHaffCode[i].start;j<n;j++){
            cout<<myHaffCode[i].bit[j];
        }
        cout<<endl;
    }

    output_file.open("hfmTree.txt");
    if(!output_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    for(int i=0;i<n;i++){
        output_file<<"("<<myHaffTree[i].data<<myHaffTree[i].weight<<")"<<endl;
    }
    output_file.close();
    cout<<"哈夫曼树已创建完成，并且已放入hfmTree.txt中."<<endl;
    cout<<endl<<endl;
}

void Coding(){
    cout<<"请输入字符或字符串："<<endl;
    string str ;
    string code ;
    cin>>str;
    output_file.open("tobetran.txt");
    if(!output_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    output_file<<str;
    output_file.close();
    output_file.open("codefile.txt");
    if(!output_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    for(int i=0;i<str.size();i++){
        for(int j=0;j<n;j++){
        if(myHaffTree[j].data==str[i]){
            for(int k=myHaffCode[j].start;k<n;k++){
                output_file<<myHaffCode[j].bit[k];
            }
            break;
            }
        }
    }
    output_file.close();
    cout<<"编码完毕，并且已经存入codefile.txt中！"<<endl;
    input_file.open("codefile.txt");
    if(!input_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    input_file>>code;
    cout<<"编码码值为："<<endl;
    cout<<code<<endl;
    input_file.close();
    cout<<endl<<endl;
}


void Decoding(){
    char s[MaxNode],s1[MaxNode];
    int i,j,k,l,p;
    input_file.open("codefile.txt");
    if(!input_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    input_file>>s;
    input_file.close();
    output_file.open("textfile.txt");
    if(!output_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    k=0;
    while(s[k]!='\0'){
        for( i=0;i<n;i++){
            l=k;
            for( j=0;j<strlen(myHaffCode[i].bit)-myHaffCode[i].start;j++,l++){
                s1[j]=s[l];
            }
            s1[j]='\0';
            for(p=myHaffCode[i].start,j=0;p<n;p++,j++)
                if(myHaffCode[i].bit[p]!=s1[j]) break;
            if(p==n){
                output_file<<myHaffTree[i].data;
                k+=strlen(myHaffCode[i].bit)-myHaffCode[i].start;
                break;
            }
        }
    }
    output_file.close();
    input_file.open("textfile.txt");
    if(!input_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    input_file>>s;
    cout<<s<<endl;
    input_file.close();
    cout<<"译码结束，字符已经存入textfile.txt文件中!"<<endl;
    cout<<endl<<endl;
}

void Print(){
    char s[MaxNode],s1[MaxNode];
    int i,j,k,l,p;
    input_file.open("codefile.txt");
    if(!input_file){
        cout<<"can't open file !"<<endl;
        return ;
    }
    input_file>>s;
    int icount=0;
    for(int i=1;i<strlen(s)+1;i++){
        cout<<s[i-1];
        if(i%50==0) cout<<endl;
    }
    cout<<endl;
    input_file.close();
    output_file.open("codeprint.txt");
    k=0;
    while(s[k]!='\0'){
        for( i=0;i<n;i++){
            l=k;
            for( j=0;j<strlen(myHaffCode[i].bit)-myHaffCode[i].start;j++,l++){
                s1[j]=s[l];
            }
            s1[j]='\0';
            for(p=myHaffCode[i].start,j=0;p<n;p++,j++)
                if(myHaffCode[i].bit[p]!=s1[j]) break;
            if(p==n){
                output_file<<myHaffTree[i].data;
                k+=strlen(myHaffCode[i].bit)-myHaffCode[i].start;
                break;
            }
        }
    }
    output_file.close();
    cout<<"字符形式的编码文件写入文件codeprint中！"<<endl;
    cout<<endl<<endl;
}

void TreePrinting(HaffNode *myHaffTree1,HaffNode *myHaffTree2,int m){
    if(myHaffTree1!=myHaffTree2-1)
    {
        if(m)output_file.close();
        output_file.open("treeprint.txt");
        if(!output_file){
            cout<<"can't  open file !"<<endl;
            return ;
        }
        TreePrinting(myHaffTree2+myHaffTree1->rightChild,myHaffTree2,m+1);
        cout<<setw(4*m)<<myHaffTree1->weight<<endl;
        output_file<<myHaffTree1->weight<<endl;
        TreePrinting(myHaffTree2+myHaffTree1->leftChild,myHaffTree2,m+1);
        output_file.close();
    }
}


int main(){
    char ch ;
    while(1){
        cout<<"          *******************哈夫曼编/译码器****************"<<endl;
        cout<<"              I---Initialization"<<"         C---Coding"<<endl;
        cout<<"              D---Decoding"<<"               P---Print"<<endl;
        cout<<"          T---Tree  printing"<<"         E---Exit"<<endl;
        cout<<"              ------------------------------------------"<<endl;
        cout<<"please select a function key:"<<endl;
        cin>>ch;
        if(ch=='I')
            Initialization();
        else if(ch=='C')
            Coding();
        else if(ch=='D')
            Decoding();
        else if(ch=='P')
            Print();
        else if(ch=='T'){
            TreePrinting(myHaffTree+2*n-2,myHaffTree,0);
            cout<<"此字符形式的哈夫曼树已写入文件treeprint中"<<endl;
            cout<<endl<<endl;
        }
        else if(ch=='E')
            break;
        else 
            cout<<"The key is not exsit, please select again !"<<endl;
    }
    return 0;
}







