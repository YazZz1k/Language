#include"tokenator.hpp"


token::token(string str, Type _type)
{
    assert(!str.empty());
    value = str;
    type  = _type;
}


token::~token()
{

}


token::token(const token& token)
{
    value = token.value;
    type  = token.type;
}


token token::operator= (const token& t)
{
    return token(t);
}


Tokenator::Tokenator(ifstream* _input)
{
    assert(_input);

    input = _input;
    error = false;
}


Tokenator::~Tokenator()
{

}


vector<string> Tokenator::get_tokens(string str)
{
    size_t len = str.length();
    vector<string> ret;

    string tmp_str;
    for(int j=0; j<len; j++)
    {
        if(str[j] != ' ')
        {
            tmp_str+=str[j];
        }
        else
        {
            ret.emplace_back(tmp_str);
            tmp_str.clear();
            while((j+1<len)&&(str[j+1] == ' '))
                j++;
        }
    }
    ret.emplace_back(tmp_str);

    return ret;
}


bool Tokenator::isdigit(const char symbol)
{
    return ((symbol>='0')&&(symbol<='9'));
}


bool Tokenator::Is_Int_Number(const string str)
{
    size_t len = str.length();
    int i=0;

    if(len)
    {
        if(str[0]=='-')
        {
            if((len!=1)&&(isdigit(str[1])))
            {
                i = 2;
            }
            else return false;
        }

        for(i; i<len; i++)
        {
            if(!isdigit(str[i]))
                return false;
        }
    }
    else return false;

    return true;
}

vector<token> Tokenator::convert_string_to_token(string input_str, size_t line = 0)
{
    vector<token> ret;
    vector<string> arr_string_token = get_tokens(input_str);

    size_t size = arr_string_token.size();
    bool get_operator = false;

    for(int i=0; i<size; i++)
    {
        if(arr_string_token[i][0] == ';')            //get_comment
        {
            i = size;
        }
        else if(arr_string_token[i][0] == ':')            //get label
        {
            arr_string_token[i].erase(0,1);
            token tok(arr_string_token[i], LAB);
            ret.emplace_back(tok);
        }
        else if(map_tokens.count(arr_string_token[i]))    //get token in map
        {
            token tok = token(arr_string_token[i],map_tokens[arr_string_token[i]]);

            if(tok.type == OP)
            {
                if(get_operator)
                {
                    //Error_More_Than_One_Operator(tmp_string, line);
                }
                get_operator = true;
            }
            ret.emplace_back(tok);
        }
        else if(Is_Int_Number(arr_string_token[i]))      //get number
        {
            token tok(arr_string_token[i], NUM);
            ret.emplace_back(tok);
        }
        else
        {
            //Error_Invalid_Token(tmp_string, line);
        }
    }

    //if(!get_operator)
    //    Error_There_isnt_Operator(tmp_string, line);

    return ret;
}


int main()
{
    ifstream file("tnput.txt");
    Tokenator t(&file);
    vector<token> tok = t.convert_string_to_token("-11 -122 1212 1.22 ;push pop ax");
    for(int i=0; i<tok.size(); i++)
        cout << tok[i].value << '\n';
}
