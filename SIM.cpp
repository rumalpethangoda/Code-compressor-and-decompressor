/* On my honor, I have neither given nor received unauthorized aid on this assignment */
///180472V///
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
#include <vector>

string check_for_mismatch(string &line , vector <string> &dict){
    for (int j = 0; j < dict.size(); j++) {
        string dict_entry = dict[j];
        int mismatch_counter = 0;
        int consecutive_mismatch_counter = 1;
        bool cond_1 = false;
        bool cond_2 = false;
        bool cond_3 = false;
        bool cond_4 = false;
        bool cond_2Redun = false;
        
        for (int i = 0; i < 32; i++) {
            if (dict_entry[i] != line[i]){
                mismatch_counter +=1;
                if (dict_entry[i-1] != line[i-1]){
                    consecutive_mismatch_counter += 1;    
                }
            }
            if(i < 29){  // upto 28 devide the string into subportions // i i+1 i+2 i+3
                if ((dict_entry[i] != line[i]) && (dict_entry[i+1] == line[i+1]) && (dict_entry[i+2] == line[i+2]) && (dict_entry[i+3] != line[i+3])) 
                    cond_1 = true;
                else if ((dict_entry[i] != line[i]) && (dict_entry[i+1] == line[i+1]) && (dict_entry[i+2] != line[i+2]) && (dict_entry[i+3] == line[i+3])) 
                    cond_2 = true;
                else if ((dict_entry[i] == line[i]) && (dict_entry[i+1] != line[i+1]) && (dict_entry[i+2] == line[i+2]) && (dict_entry[i+3] != line[i+3])) 
                    cond_2Redun  = true;
                else if ((dict_entry[i] != line[i]) && (dict_entry[i+1] != line[i+1]) && (dict_entry[i+2] == line[i+2]) && (dict_entry[i+3] != line[i+3])) 
                    cond_3 = true;
                else if ((dict_entry[i] != line[i]) && (dict_entry[i+1] == line[i+1]) && (dict_entry[i+2] != line[i+2]) && (dict_entry[i+3] != line[i+3])) 
                    cond_4 = true;
            }
            if (cond_2 && cond_2Redun ){
                cond_2Redun = false;
            }
            if (cond_2 && cond_3 ){
                cond_2 = false;
            }
        }
        
        if (mismatch_counter == 1){
            return "1 bit mismatch found";
        }
        else if (consecutive_mismatch_counter == 2 && mismatch_counter == 2){
            return "2 bit consecutive mismatch found";

        }
        else if ((consecutive_mismatch_counter == 3 && mismatch_counter == 3)  || (consecutive_mismatch_counter == 4 && mismatch_counter == 4) || (mismatch_counter == 2 && cond_1) || (mismatch_counter == 2 && (cond_2 || cond_2Redun) ) ){
            return "4 bit consecutive mismatch found";
        }
        

        else if ( (consecutive_mismatch_counter == 2 && mismatch_counter == 3 && cond_3)  || (consecutive_mismatch_counter == 2 && mismatch_counter == 3 && cond_4) ){
            return "4 bit consecutive mismatch found";
        }

        else if (mismatch_counter == 2){
            return "2 bit mismatch found";
        }
    }
    return "no  mismatches";
}

vector<int>  find_1_bit_mismatch_position(string &line , vector <string> &dict) {
    int mis_pos;
    vector <int> ret;
    for (int i = 0; i < dict.size(); i++) {
        string dict_entry1 = dict[i];
        int mismatch_counter1 = 0;
        for (int j = 0; j < 32; j++) {
            if (dict_entry1[j] != line[j]){
                mismatch_counter1 +=1;
                mis_pos = j;
            }
        }
        if (mismatch_counter1 == 1){
            ret.push_back(mis_pos); // position first
            ret.push_back(i); // dict entry second
            return ret;
        }
    }
    return {};
}

vector<int> find_2_bit_mismatch_position(string &line , vector <string> &dict) {
    int mis_pos_bit2;
    vector <int> ret;
    for (int i = 0; i < dict.size(); i++) {
        string dict_entry2 = dict[i];
        int mismatch_counter2 = 0;
        int cons_bit2_counter = 1;
        for (int j = 0; j < 32; j++) {
            if (dict_entry2[j] != line[j]){
                mismatch_counter2 +=1;
                if (dict_entry2[j-1] != line[j-1]){
                    cons_bit2_counter +=1;
                    mis_pos_bit2 = j-1 ;
                }

            }
        }
        if (mismatch_counter2  == 2 && cons_bit2_counter == 2){
            ret.push_back(mis_pos_bit2); // position first
            ret.push_back(i); // dict entry second
            return ret;
        }
    }
    return {};
}

vector <int>  find_2_bit_mismatch_anywhere(string &line , vector <string> &dict) {
    vector <int> ret;
    for (int i = 0; i < dict.size(); i++) {
        string dict_entry = dict[i];
        int mismatch_counter2 = 0;
        for (int j = 0; j < 32; j++) {
            if (dict_entry[j] != line[j]){
                mismatch_counter2 +=1;
            }
        }
        if (mismatch_counter2 == 2){
            for (int k=0; k<32;k++){
                if (line[k] != dict_entry[k]){
                    ret.push_back(k);
                }
            }
        ret.push_back(i);
        return ret;
        }
    }

    return {};
}



string xor_op(string &a, string &b){
string ans = "";
    for (int i = 0; i < 4; i++)
    {
        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}


vector<string> find_bitmask4bit_position_mask (string &line , vector <string> &dict){
    int mis_pos_bit4;
    int dic_index;
    vector <string> ret;
    int bit_pos = 0;
    for (int i = 0; i < dict.size(); i++) {
        string dict_entry3 = dict[i];
        int mismatch_counter4 = 0;
        int cons_bit4_counter = 1;
        bool cond_1 = false;
        bool cond_2 = false;
        bool cond_3 = false;
        bool cond_4 = false;
        bool cond_2_redun = false;
        for (int j = 0; j < 32; j++) {
            if (dict_entry3[j] != line[j]){
                mismatch_counter4 +=1;
                if (dict_entry3[j-1] != line[j-1]){
                    cons_bit4_counter +=1;
                    mis_pos_bit4 = j;
                }
            }
            if(j < 29){  // upto 28 devide the string into subportions // i i+1 i+2 i+3
                if ((dict_entry3[j] != line[j]) && (dict_entry3[j+1] == line[j+1]) && (dict_entry3[j+2] == line[j+2]) && (dict_entry3[j+3] != line[j+3])){
                    cond_1 = true;
                    bit_pos = j;
                    
                }
                else if ((dict_entry3[j] != line[j]) && (dict_entry3[j+1] == line[j+1]) && (dict_entry3[j+2] != line[j+2]) && (dict_entry3[j+3] == line[j+3])){
                    cond_2 = true;
                    bit_pos = j;
                    
                }
                else if ((dict_entry3[j] == line[j]) && (dict_entry3[j+1] != line[j+1]) && (dict_entry3[j+2] == line[j+2]) && (dict_entry3[j+3] != line[j+3])){ 
                    cond_2_redun = true;
                    bit_pos = j;
                }
                else if ((dict_entry3[j] != line[j]) && (dict_entry3[j+1] != line[j+1]) && (dict_entry3[j+2] == line[j+2]) && (dict_entry3[j+3] != line[j+3])){
                    cond_3 = true;
                    bit_pos = j;
        
                }
                else if ((dict_entry3[j] != line[j]) && (dict_entry3[j+1] == line[j+1]) && (dict_entry3[j+2] != line[j+2]) && (dict_entry3[j+3] != line[j+3])){
                    cond_4 = true;
                    bit_pos = j;
                
                }
            }
            if (cond_2 && cond_2_redun){
                cond_2_redun = false;
                ///bit_pos = j-1;
            }
            if (cond_2 && cond_3 ){
                cond_2 = false;
                bit_pos = j-1;
            }

        }

        if (cons_bit4_counter == 4 && mismatch_counter4 == 4){
            dic_index = i;
            int start_pos = mis_pos_bit4 - 3;
            string dic_part = dict_entry3.substr(start_pos,4);
            string line_part = line.substr(start_pos,4);
            string bitmask = xor_op(dic_part,line_part);
            ret.push_back(to_string(start_pos));  //position
            ret.push_back(bitmask);  // bitmask
            ret.push_back(to_string(dic_index));  //dic index 
            return ret;
        }
        else if (cons_bit4_counter == 3 && mismatch_counter4 == 3){
            dic_index = i;
            int start_pos = mis_pos_bit4 - 2;
            if (start_pos== 29)
                start_pos = 28;
            string dic_part = dict_entry3.substr(start_pos,4);
            string line_part = line.substr(start_pos,4);
            string bitmask = xor_op(dic_part,line_part);
            ret.push_back(to_string(start_pos));  //position
            ret.push_back(bitmask);  // bitmask
            ret.push_back(to_string(dic_index));  //dic index 
            return ret;
        }
        else if((mismatch_counter4 == 2 && cond_1) || (mismatch_counter4 == 2 && (cond_2 || cond_2_redun)) ||  (cons_bit4_counter == 2 && mismatch_counter4 == 3 && cond_3) || (cons_bit4_counter == 2 && mismatch_counter4 == 3 && cond_4)){
            dic_index = i;
            int start_pos = bit_pos;
            string dic_part = dict_entry3.substr(start_pos, 4);
            string line_part = line.substr(start_pos,4);
            string bitmask = xor_op(dic_part,line_part);
            ret.push_back(to_string(start_pos));  //position
            ret.push_back(bitmask);  // bitmask
            ret.push_back(to_string(dic_index));  //dic index 
            return ret;
        }
        
        
    }
    
    return {};
    
}
bool sortfn(const pair<string,vector<int>> &a,  const pair<string,vector<int>> &b){
       if (a.second[1] == b.second[1]){
         return a.second[0]<b.second[0]; 
       }
       return a.second[1]>b.second[1];
}

string dToBinary(int &number, int &Nbits){
    string str1;
    while(number){
        if(number & 1) 
            str1+='1';
        else 
            str1+='0';
        number>>=1; 
    }
    if (str1.length() < Nbits){
        int len = Nbits - str1.length();
        for (int i = 0; i < len; i++){
            str1 += '0';
        }
    }
    reverse(str1.begin(), str1.end());
    return str1;  

}

int find_enc_length(string &str){
    if (str == "000")
        return 5;
    else if (str == "001")
        return 15;
    else if (str == "010")
        return 11;
    else if (str == "011")
        return 11;
    else if (str == "100")
        return 16;
    else if (str == "101")
        return 6;
    else if (str == "110")
        return 35;
    
    return 0;
}
int binaryToDecimal(string &num)
{
    int dec = 0;
    int base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec += base;
        base = base * 2;
    }
 
    return dec;
}
string bit_1_decompress(string &line, int &loc){
    
    char ch = line[loc];
    if (ch == '0')
        ch = '1';
    else
        ch = '0';
    line[loc] = ch;
    return line;
    
}

string bit_2_cons_decompress(string &line, int &loc){
    
    string ch = line.substr(loc,2);
    if (ch == "00")
        ch = "11";
    else if (ch == "01")
        ch = "10";
    else if (ch == "10")
        ch = "01";
    else if (ch == "11")
        ch = "00";
    line.replace(loc,2,ch);
    return line;
    
}

string bit_2_anywhere_decompress(string &line, int &loc1, int &loc2){
    for (int i = 0; i < line.length(); i++){
        if (i == loc1 || i == loc2){
            char ch = line[i];
            if (ch == '0')
                ch = '1';
            else
                ch = '0';
            line[i] = ch;
        }
    }
    return line;
    
}

string bit4_mask_decompress(string &line, string &bitmask, int &loc){
    string mask1 = line.substr(loc,4);
    string mask = xor_op(bitmask,mask1);
    line.replace(loc,4,mask);
    return line;

}


string decompress_fn(vector <string> &dict , string &cmpStr, string &encPor ){
    int dic_index;
    string dic = "";
    
        
    if (encPor == "001"){
       dic = cmpStr.substr(12,3); 
       dic_index = binaryToDecimal(dic);
       string dic_line = dict[dic_index];
       string start_loc = cmpStr.substr(3,5);
       int startLoc = binaryToDecimal(start_loc);
       string bitmask = cmpStr.substr(8,4);
       string ret = bit4_mask_decompress(dic_line,bitmask,startLoc);
       return ret; 

    }
    else if (encPor == "010"){
       dic = cmpStr.substr(8,3); 
       dic_index = binaryToDecimal(dic);
       string dic_line = dict[dic_index];
       string start_loc = cmpStr.substr(3,5);
       int startLoc = binaryToDecimal(start_loc);
       string ret = bit_1_decompress(dic_line,startLoc);
       return ret;
    }
    else if (encPor == "011"){
       dic = cmpStr.substr(8,3); 
       dic_index = binaryToDecimal(dic);
       string dic_line = dict[dic_index];
       string start_loc = cmpStr.substr(3,5);
       int startLoc = binaryToDecimal(start_loc);
       string ret = bit_2_cons_decompress(dic_line,startLoc);
       return ret;

    }
    else if (encPor == "100"){
       dic = cmpStr.substr(13,3); 
       dic_index = binaryToDecimal(dic);
       string dic_line = dict[dic_index];
       string start_loc_1 = cmpStr.substr(3,5);
       int startLoc_1 = binaryToDecimal(start_loc_1);
       string start_loc_2 = cmpStr.substr(8,5);
       int startLoc_2 = binaryToDecimal(start_loc_2);
       string ret = bit_2_anywhere_decompress(dic_line,startLoc_1,startLoc_2);
       return ret;


    }
    else if (encPor == "101"){
        dic = cmpStr.substr(3,3);
        dic_index = binaryToDecimal(dic);
        return dict[dic_index];
    }
    else if (encPor == "110"){
        return cmpStr.substr(3,32);

    }
    return "";
}

void file_write(string &fname , vector <string> &arr){
    string l_line = arr.back();
    arr.pop_back();
    fstream wFile;
    wFile.open(fname , ios::out);
    if (wFile.is_open()){
        for (int i = 0 ; i <arr.size(); i++){
            string entry = arr[i];
            wFile << entry << endl;
        }
        wFile << l_line;
        wFile.close();
    }

}

int main(int argc,char* argv[]){
    /////////////////////compressor/////////////////////////////////////
    if (atoi(argv[1]) == 1){
        fstream inFile;
        vector <string> entries ; 
        vector <string> original_code ;
        vector< pair <string,int> > new_entries;
        vector <string> dictionary_entries;
        vector <string> compressed_code;
        std::vector<string>::iterator it;
        std::unordered_map<string, int> map2;
        inFile.open("original.txt",ios::in);
        if (inFile.is_open()){
            string line;
            while (getline(inFile,line)){
                ++map2[line];
                original_code.push_back(line);
                it = std::find (entries.begin(), entries.end(), line);
                if (it == entries.end()){
                    entries.push_back(line);
                }
            }
            inFile.close();
        }

        

    
        for (int i = 0 ; i <entries.size(); i++){
            string entry = entries[i];
            new_entries.push_back( make_pair(entries[i],map2[entry]) );
        }
        vector <pair<string,vector<int>>> sortV;
        vector<int> y ={};


        int i = 0;
        for (pair <string,int> p: new_entries){
            vector<int> y ={i,p.second};
            sortV.push_back(make_pair(p.first,y));
            i++;
            
        }

        std::sort(sortV.begin(),sortV.end(),sortfn);

        for (int i = 0;  i<8 ; i++){
            dictionary_entries.push_back(sortV[i].first);
        }
        ////////////////Main algorithm///////////////////////////

        int line_count = 0;
        string prev_line = "";
        string compressed_entry;
        int Nbits;
        vector <int> ret_arr;
        string mismatch_loc;
        string dic_entryNum;

        int number = original_code.size() - 1;


        for (int i = 0 ; i <= number; i++){
            string code_line = original_code[i];
        
            if (prev_line == code_line){
                Nbits = 2;
                line_count += 1;
                if (i == number || (line_count == 4)){
                    line_count -= 1;
                    Nbits = 2;
                    compressed_entry = "000" + dToBinary(line_count , Nbits);
                    compressed_code.push_back(compressed_entry);
                    line_count = 0;
                    code_line = "";    
                }
            }

            else{

                if (line_count > 0){
                    line_count -= 1;
                    Nbits = 2;
                    compressed_entry = "000" + dToBinary(line_count , Nbits);
                    compressed_code.push_back(compressed_entry);
                    line_count = 0;
                }

                std::vector<string>::iterator it1 = std::find(dictionary_entries.begin(), dictionary_entries.end(), code_line);
                if (it1 != dictionary_entries.end()){   // checking the element is present in dictionary
            
                    int index = std::distance(dictionary_entries.begin(), it1); // obtaining the index
                    Nbits = 3;
                    compressed_entry = "101" + dToBinary(index , Nbits);
                    compressed_code.push_back(compressed_entry);
                } 

                else{

                    string check = check_for_mismatch(code_line, dictionary_entries);
                    if (check == "1 bit mismatch found" ){
                        ret_arr = find_1_bit_mismatch_position(code_line, dictionary_entries);
                        Nbits = 5;
                        mismatch_loc = dToBinary(ret_arr[0] , Nbits);
                        Nbits = 3;
                        dic_entryNum = dToBinary(ret_arr[1] , Nbits);
                        compressed_entry = "010" + mismatch_loc + dic_entryNum;
                        compressed_code.push_back(compressed_entry);
                        
                    }

                    else if (check == "2 bit consecutive mismatch found"){
                        ret_arr = find_2_bit_mismatch_position(code_line, dictionary_entries);
                        Nbits = 5;
                        mismatch_loc = dToBinary(ret_arr[0] , Nbits);
                        Nbits = 3;
                        dic_entryNum = dToBinary(ret_arr[1] , Nbits);
                        compressed_entry = "011" + mismatch_loc + dic_entryNum;
                        compressed_code.push_back(compressed_entry);
                    
                    }

                    else if (check == "4 bit consecutive mismatch found"){
                        vector <string> ret_arr1 = find_bitmask4bit_position_mask(code_line, dictionary_entries);

                        int pos2;
                        int dEnt;
                        stringstream op1(ret_arr1[0]);
                        op1 >> pos2;
                        stringstream op2(ret_arr1[2]);
                        op2 >> dEnt;
                        Nbits = 5;
                        mismatch_loc = dToBinary(pos2 , Nbits);
                        Nbits = 3;
                        dic_entryNum = dToBinary(dEnt , Nbits);
                        compressed_entry = "001" + mismatch_loc + ret_arr1[1] + dic_entryNum;
                        compressed_code.push_back(compressed_entry);
                    

                    }

                    else if (check == "2 bit mismatch found"){
                        vector <int> vec1 = find_2_bit_mismatch_anywhere(code_line, dictionary_entries);
                        int entry1 = vec1[0];
                        int entry2 = vec1[1];
                        int
                        Nbits = 5;
                        string pos_1 = dToBinary(entry1 , Nbits);
                        string pos_2 = dToBinary(entry2 , Nbits);
                        Nbits = 3;
                        dic_entryNum = dToBinary( vec1[2], Nbits);
                        compressed_entry = "100" + pos_1 + pos_2 + dic_entryNum;
                        compressed_code.push_back(compressed_entry);

                    }

                    else if (check == "no  mismatches"){
                        compressed_entry = "110" + code_line;
                        compressed_code.push_back(compressed_entry);

                    }

                }
            }  
            prev_line = code_line;     
            
        }

        string input = "";

        vector <string> ent;
        
        for (int i = 0 ; i < compressed_code.size(); i++){
            string entry = compressed_code[i];
            input += entry;
            if (input.size() > 32){
            
                string input_entering = input.substr(0,32);
                string input_excess = input.substr(32,input.size());
                input = input_excess;
                ent.push_back(input_entering);
            }
            if ((i == (compressed_code.size()-1)) && (input.size()<33)){
                string str(32-input.size(),'1');
                ent.push_back (input + str);
            }
            

        }
       

        string comp_out = "cout.txt";
        ent.push_back("xxxx");
        vector <string> wVec(ent.size() + dictionary_entries.size());
        ent.insert(ent.end() , dictionary_entries.begin() , dictionary_entries.end());
        for (int i = 0 ; i <ent.size(); i++){
            string entry = ent[i];
        }
        file_write(comp_out, ent);
    }

    else if (atoi(argv[1]) == 2){

        /////////////////////////////decompressor////////////////////////////////
        vector <string> compressed_entries;
        vector <string> compressed_dict;
        fstream inFile;
        inFile.open("compressed.txt",ios::in);
        if (inFile.is_open()){
            string line;
            while (getline(inFile,line)){
                compressed_entries.push_back(line);
            }
            inFile.close();
        }

        std::vector<string>::iterator it_d = std::find(compressed_entries.begin(), compressed_entries.end(),"xxxx");
        int gar_ind = std::distance(compressed_entries.begin(), it_d);

        for (int i = gar_ind + 1 ; i <compressed_entries.size(); i++){
            string entry = compressed_entries[i];
            compressed_dict.push_back(entry);
        }
        string compressed_str = "";
        vector <string> compressed_arr;
        for (int i = 0 ; i < compressed_entries.size(); i++){
            string entry = compressed_entries[i];
            if (entry == "xxxx")
                break; 
            else{
                compressed_str += entry;
            }
            
        }

        int str_len = 0;
        string enc_por = "";
        int enc_len;
        string cmp_str = "";
        string prev_decom = "";

    
        while (str_len != compressed_str.length()){
            enc_por= compressed_str.substr(str_len,3);
            enc_len = find_enc_length(enc_por);
            if (enc_len == 0){
                break;
            }
            else{
                cmp_str= compressed_str.substr(str_len,enc_len);
                str_len += enc_len;
                if (enc_por == "000"){
                    string rle_s = cmp_str.substr(3,2);
                    int rle = binaryToDecimal(rle_s) + 1;
                    for (int i = 0; i < rle ; i++){
                        compressed_arr.push_back(prev_decom);
                    }
                }
                else{
                    string decomp_str = decompress_fn(compressed_dict,cmp_str,enc_por);
                    prev_decom = decomp_str;
                    compressed_arr.push_back(decomp_str);
                }
            }
            
        }
        string decomp_out = "dout.txt";
        file_write(decomp_out, compressed_arr);
    }
    return 0;
}   
