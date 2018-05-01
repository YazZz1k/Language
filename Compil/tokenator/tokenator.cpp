#include"tokenator.hpp"


Tokenator::Tokenator(ifstream* _input)
{
    assert(_input);

    input = _input;
    error = false;
}


Tokenator::~Tokenator()
{

}

void Run_Tokenizator(Tokenator& tokenator)
{
    string get_str;
    vector<token> tmp_arr;
    size_t line = 1;
    token start("start_token//line_0", PUN, 0);
    token finish("finish_token//line100000", PUN, 100000);
    tokenator.arr_token.push_back(start);
    while(getline(*tokenator.input, get_str))
    {
        tmp_arr = tokenator.convert_string_to_token(get_str, line);

        tokenator.arr_token.insert(tokenator.arr_token.end(), tmp_arr.begin(), tmp_arr.end());
        line++;
    }

    tokenator.arr_token.push_back(finish);
    if(tokenator.error)
         tokenator.print_Errors();
}

vector<string> Tokenator::cut_string(string str)
{
    size_t len = str.length();
    vector<string> ret;

    string tmp_str;

    for(int j=0; j<len; j++)
    {
        if(str[j] != ' ')
        {
            if((str[j] == '+')||(str[j] == '-')||(str[j] == '*')||(str[j] == '/')||(str[j] == '=')||(str[j] == '$')||(str[j] == '(')||(str[j] == ')'))
            {
                if(!tmp_str.empty())
                {
                    ret.push_back(tmp_str);
                }

                tmp_str.clear();

                tmp_str+=str[j];
                ret.push_back(tmp_str);

                tmp_str.clear();
            }
            else
                tmp_str+=str[j];
        }
        else
        {
            if(!tmp_str.empty())
                ret.push_back(tmp_str);

            tmp_str.clear();
            while((j+1<len)&&(str[j+1] == ' '))
                j++;
        }
    }

    if(!tmp_str.empty())
        ret.push_back(tmp_str);

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
    vector<string> arr_string_token = cut_string(input_str);

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
            get_operator = true;
            arr_string_token[i].erase(0,1);
            token tok(arr_string_token[i], LAB, line);
            ret.push_back(tok);
        }
        else if((arr_string_token[i] == "-")&&(i+1<size)&&(Is_Int_Number(arr_string_token[i+1]))&&((i-1)!=0)&&(!Is_Int_Number(arr_string_token[i-1]))) //унарный минус
        {
            token tok = token(arr_string_token[i]+arr_string_token[i+1], NUM, line);
            i++;
            ret.push_back(tok);
        }
        else if(map_tokens.count(arr_string_token[i]))    //get token in map
        {
            token tok = token(arr_string_token[i],map_tokens[arr_string_token[i]], line);

            if((tok.type == OP)||(tok.type == LAB))
            {
                if(get_operator)
                    Error_More_Than_One_Operator_at_Line(tok.value, line);

                get_operator = true;
            }
            ret.push_back(tok);
        }
        else if(Is_Int_Number(arr_string_token[i]))      //get number
        {
            token tok(arr_string_token[i], NUM, line);
            ret.push_back(tok);
        }
        else
            Error_Invalid_Token(arr_string_token[i], line);
    }

    if(!get_operator)
        Error_There_arent_any_Operator_at_Line(input_str, line);

    return ret;
}


void Tokenator::Error_More_Than_One_Operator_at_Line(const string err_token, size_t line)
{
    error = true;
    char error_str[256];

    sprintf(error_str, "В строке %d встречено больше одного оператора. Последний встреченный оператор: %s\n", line, err_token.c_str());

    arr_Errors.push_back(error_str);
}


void Tokenator::Error_Invalid_Token(const string err_token, size_t line)
{
    error = true;
    char error_str[256];
    char tmp_str[128];


    strncpy(tmp_str, err_token.c_str(), 128);
    sprintf(error_str, "в строке %d встречен неизвестный токен: %s\n", line, tmp_str);

    arr_Errors.push_back(error_str);
}


void Tokenator::Error_There_arent_any_Operator_at_Line(const string err_line,  size_t line)
{
    error = true;
    char error_str[512];
    char tmp_str[256];


    strncpy(tmp_str, err_line.c_str(), 256);
    sprintf(error_str, "в строке %d не встречен ни один оператор\n %s\n", line, tmp_str);

    arr_Errors.push_back(error_str);

}


void Tokenator::print_Errors()
{
    if(error)
    {
        size_t size = arr_Errors.size();
        for(int i=0; i<size; i++)
            cout<<arr_Errors[i]<<"\n";
    }
    else
        cout<<"В процессе токенизации не встречено ошибок.\n";
}

/*int main()
{
    ifstream file("input.txt");
    string str;
    if(!file)
        cout<<"HUI\n";
    Tokenator t(&file);
    Run_Tokenizator(t);
}*/
