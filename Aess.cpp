#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <unordered_map>

using namespace std;

#if defined(_WIN32)
#define PAUSE "pause"
#define CLR "cls"
#elif defined(unix) || defined(__unix__) || defined(__unix)
#define PAUSE "read -p 'Press Enter to continue...' var"
    #define CLR "clear"
#endif

class SAES
{
    const string RC1 = "10000000"; 
    const string RC2 = "00110000"; 
    string SBox[4][4] = { {"1001","0100","1010","1011"},
                          {"1101","0001","1000","0101"},
                          {"0110","0010","0000","0011"},
                          {"1100","1110","1111","0111"} };
    string invSBox[4][4] = { {"1010","0101","1001","1011"},
                             {"0001","0111","1000","1111"},
                             {"0110","0000","0010","0011"},
                             {"1100","0100","1101","1110"}};

    unordered_map<string,int> stringToInt;
    unordered_map<int,string> intToString;

    const int TextLength = 16;
    const int KeyLength = 16;

    string key0;
    string key1;
    string key2;

    string XOR_OP(const string &, const string &);
    string key_function_g(const string &, const string&);
    string Encryption_Rounds(const string &, const string&, int);
    string Decryption_Rounds(const string &, const string&, int);

public:
    

    SAES()
    {
         key0.resize(KeyLength,'x');
         key1.resize(KeyLength,'x');
         key2.resize(KeyLength,'x');
         stringToInt["00"]=0;
         stringToInt["01"]=1;
         stringToInt["10"]=2;
         stringToInt["11"]=3;
         intToString[0]="00";
         intToString[1]="01";
         intToString[2]="10";
         intToString[3]="11";
    }

    void SAES_KEY_GENERATION(const string&);
    string SAES_Encryption(const string&);
    string SAES_Decryption(const string&);

    string getKey0(){
        return key0;
    }

    string getKey1(){
        return key1;
    }

    string getKey2(){
        return key2;
    }

    char xor_char(char a, char b, char c='0') {
        if (b == c) 
            return a;
        else if(a == '0')
            return '1';
        else
            return '0';
    };

};

string SAES::SAES_Encryption(const string& ip)
{
    
    string cipherOp = XOR_OP(ip, key0);
    cipherOp = Encryption_Rounds(cipherOp, key1, 1);
    cipherOp = Encryption_Rounds(cipherOp, key2, 2);

    return cipherOp;
}

string SAES::SAES_Decryption(const string& ip)
{
    string plainText = XOR_OP(ip, key2);
    plainText = Decryption_Rounds(plainText, key1, 1);
    plainText = Decryption_Rounds(plainText, key0, 2);

    return plainText;
}

string SAES::Encryption_Rounds(const string &text, const string& key, int round)
{
    int dim = 2; 
    string StateM [dim][dim]; 

    StateM[0][0] = text.substr(0,4); 
    StateM[0][1] = text.substr(8,4);
    StateM[1][0] = text.substr(4,4); 
    StateM[1][1] = text.substr(12,4); 

    int sub_row, sub_col;

    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
        {
            sub_row = stringToInt[StateM[i][j].substr(0,2)]; 
            sub_col = stringToInt[StateM[i][j].substr(2,2)]; 
            StateM[i][j] = SBox[sub_row][sub_col];
        }
    }
    
    StateM[1][0].swap(StateM[1][1]);


  string outputM[dim][dim]={{StateM[0][0], StateM[0][1]}, 
                            {StateM[1][0], StateM[1][1]}};

   if(round != 2)
   {
       for(int i=0; i<dim; i++)
        {
             outputM[0][i][0] =  xor_char(StateM[0][i][0], StateM[1][i][2]);
             outputM[0][i][1] =  xor_char(StateM[0][i][1], StateM[1][i][0], StateM[1][i][3]); 
             outputM[0][i][2] =  xor_char(StateM[0][i][2], StateM[1][i][0], StateM[1][i][1]); 
             outputM[0][i][3] =  xor_char(StateM[0][i][3], StateM[1][i][1]); 

             outputM[1][i][0] =  xor_char(StateM[0][i][2], StateM[1][i][0]); 
             outputM[1][i][1] =  xor_char(StateM[0][i][0], StateM[0][i][3], StateM[1][i][1]); 
             outputM[1][i][2] =  xor_char(StateM[0][i][0], StateM[0][i][1], StateM[1][i][2]); 
             outputM[1][i][3] =  xor_char(StateM[0][i][1], StateM[1][i][3]); 
        }
    }

    string op =  outputM[0][0] + outputM[1][0] +  outputM[0][1] +  outputM[1][1];
    op = XOR_OP(op, key);

    return op;
}

string SAES::Decryption_Rounds(const string &text, const string& key, int round)
{
    int dim = 2; 
    string StateM [dim][dim]; 

    StateM[0][0] = text.substr(0,4); 
    StateM[0][1] = text.substr(8,4); 
    StateM[1][0] = text.substr(4,4);
    StateM[1][1] = text.substr(12,4); 

    StateM[1][0].swap(StateM[1][1]);

    int sub_row, sub_col;

    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
        {
            sub_row = stringToInt[StateM[i][j].substr(0,2)]; 
            sub_col = stringToInt[StateM[i][j].substr(2,2)]; 
            StateM[i][j] = invSBox[sub_row][sub_col];
        }
    }

    string op =  StateM[0][0] + StateM[1][0] +  StateM[0][1] +  StateM[1][1];
    op = XOR_OP(op, key);
    
   if(round != 2)
   { 
     string temp = op;
       for(int i=0; i<TextLength; i=i+8)
        {
             temp[i+0] =  xor_char(op[i+3], op[i+5]);
             temp[i+1] =  xor_char(op[i+0], op[i+6]); 
             temp[i+2] =  xor_char(op[i+1], op[i+4], op[i+7]);
             temp[i+3] =  xor_char(op[i+2], op[i+3], op[i+4]);
             temp[i+4] =  xor_char(op[i+1], op[i+7]);
             temp[i+5] =  xor_char(op[i+2], op[i+4]); 
             temp[i+6] =  xor_char(op[i+0], op[i+3], op[i+5]); 
             temp[i+7] =  xor_char(op[i+0], op[i+6], op[i+7]); 
        }
        op = temp;
    }

    return op;
}

void SAES::SAES_KEY_GENERATION(const string& key)
{
    string w0 = key.substr(0,8); 
    string w1 = key.substr(8,8); 
    key0 = w0+w1;

    string w1g = key_function_g(w1, RC1);

    string w2 = XOR_OP(w0, w1g);
    string w3 = XOR_OP(w2, w1);

    key1 = w2+w3;

    string w3g = key_function_g(w3, RC2);

    string w4 = XOR_OP(w2, w3g);
    string w5 = XOR_OP(w4, w3);

    key2 = w4+w5;

}

string SAES::key_function_g(const string &w, const string& RC)
{
    string N0 = w.substr(0,4);
    string N1 = w.substr(4,4);

    int sub_row, sub_col;
    sub_row = stringToInt[N1.substr(0,2)]; 
    sub_col = stringToInt[N1.substr(2,2)]; 


    string N1_ = SBox[sub_row][sub_col];

    sub_row = stringToInt[N0.substr(0,2)]; 
    sub_col = stringToInt[N0.substr(2,2)]; 

    string N0_ = SBox[sub_row][sub_col];

    string w_ = N1_+N0_; 

    string output = XOR_OP(w_, RC);
    return output;
}

string SAES::XOR_OP(const string &t1, const string &t2){
    string result_xor;
    for(int i=0; i<t1.length(); i++){
        if(t1[i] == t2[i])
            result_xor.push_back('0');
        else
            result_xor.push_back('1');
    }
    return result_xor;
}

int main()
{
    char choice;
    string ip_plain_txt, op_plain_txt; 
    string op_cipher_txt, ip_cipher_txt;
    string key;

    SAES *obj = new SAES();
    do{
        char ch;

        cout<<endl<<endl<<endl;
        system(PAUSE);
        system(CLR);

        cout<<"\n ---------------- SAES Encryption and Decryption MENU ----------------";

        cout<<"\n e. SAES Encryption";
        cout<<"\n d. SAES Decryption";

        cout<<"\n\n n. Exit - Bye \n\n --Choice : ";
            cin>>ch;
        cout<<"\n <-------->";

        switch(ch){
            case 'e':
                cout<<"\n Enter Plain Text String (16-bits) : ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,ip_plain_txt);

                cout<<"\n Enter Key String (16-bits) : ";
                getline(cin,key);

               // ip_plain_txt="0110111101101011";  //--> op_cipher_txt="0000011100111000";
               // key="1010011100111011";

                obj->SAES_KEY_GENERATION(key);
                op_cipher_txt = obj->SAES_Encryption(ip_plain_txt);

                cout<<"\n SAES ENCRYPTION DONE :"
                    << "\n :::::=> Plain Text (input) : "<<ip_plain_txt
                    << "\n :::::=> Key0 (input) : " <<obj->getKey0()
                    << "\t:::=> Key1 : "<<obj->getKey1()
                    << "\t:::=> Key2  : " <<obj->getKey2()
                    << "\n :::::=> Cipher Text (output) : " <<op_cipher_txt;

                break;
            case 'd':
                cout<<"\n Enter Cipher Text String : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, ip_cipher_txt);

                cout<<"\n Enter Key String (16-bits) : ";
                    cin>>key;
                // ip_cipher_txt="0000011100111000";
                //  key="1010011100111011";

                obj->SAES_KEY_GENERATION(key);
                op_plain_txt = obj->SAES_Decryption(ip_cipher_txt);

                cout<<"\n SAES DECRYPTION DONE :"
                    << "\n :::::=> Cipher Text (input) : " <<ip_cipher_txt
                    << "\n :::::=> Key0 (input) : " <<obj->getKey0()
                    << "\t:::=> Key1 : "<<obj->getKey1()
                    << "\t:::=> Key2  : " <<obj->getKey2()
                    << "\n :::::=> Plain Text (output) : "<<op_plain_txt;

                break;

            case 'n': cout<<"\n Bye \n"; break;
            default: cout<< "\n--Invalid Choice. Enter Again \n";
        }

        choice=ch;
    }while(choice != 'n');

    delete obj;
    cout<<"\n Press Enter To Exit. ";
    cin.get();
    cin.get();
    return 0;
}