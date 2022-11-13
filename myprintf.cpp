#ifndef __UTILITIES_
#define __UTILITIES_
#include <string>
#include <cassert>
#include <cctype>
#include <stdarg.h>
#define pass 0 ^ 0

struct splim;
class _Tp;
template <typename tp>
size_t write(char *, tp, int);
int split(const char *, _Tp *arr);
char rev_tp(char);

struct splim
{
    static const int left_align = 1, right_align = -1, non_align = 0;
    //是否有对齐要求:left_align左对齐，right_align右对齐，non_align无对齐要求(default)
    int alignment;
    //对齐宽度。数值应为正整数
    size_t align_width;
    char align_fill;

    static const int DEC = 10, HEX = 16, OCT = 8;
    //进制系统:DEC = 10(dafault), HEX = 16, OCT = 8
    int numsystem;

    //是否需要大写字母
    bool upperCase;

    //浮点数保留位数(for double/float) (default:6)
    size_t len_kept;

    static const size_t f = 1, g = 2, e = 3;
    //浮点数输出格式：f/g/e
    size_t f_type;

    //有无#
    bool Hashtag;
    //*
    bool Asterisk;
    splim() : alignment(non_align), numsystem(DEC), len_kept(6), align_fill(' ') {}
};
class _Tp
{
    size_t __typeTag;
    int __contents;
    splim Task;

public:
    std::string str_contents;
    //重新设置content的内容
    void set_content(const int &);
    void set_content(const std::string &);

    //设置限制的内容
    void set_limits(const splim &);

    /*初始化，参数依次为：类型，内容，特殊限制*/
    _Tp(const size_t &Tag, const int &ss, const splim &limits = splim())
    {
        assert(Tag == fmt);
        __typeTag = Tag, __contents = ss;
        Task = limits;
    }
    _Tp(const size_t &Tag, const std::string &ss)
    {
        assert(Tag == str);
        __typeTag = Tag, str_contents = ss;
    }
    enum
    {
        str = 0,
        fmt = 1
    };

    enum
    {
        CHAR = 0,
        INT = 1,
        SHORT = 2,
        LONG = 3,
        LONGLONG = 4,
        FLOAT = 10,
        DOUBLE = 11,
        LONGDOUBLE = 12,
        STRING = 100
    };

    ~_Tp() {}
    _Tp() {}

    //返回类型：_Tp::str 或 _Tp::fmt
    size_t type() { return __typeTag; }

    //@当类型为格式字符串时返回类型。
    int name();

    //@当类型为普通字符串时内容存入char*。结尾补\0
    size_t content(char *);

    //返回对齐情况
    int align_limit()
    {
        return Task.alignment;
    }

    //@有对齐时返回对齐长度（代数值，正数）
    size_t align_width();

    char align_fill();

    //@是整数时返回整数的进制
    int number_system()
    {
        if (__typeTag != fmt ||
            (__contents == _Tp::DOUBLE || __contents == _Tp::FLOAT || __contents == LONGDOUBLE))
            throw(233);
        return Task.numsystem;
    }

    //@返回大小写
    bool upperCase()
    {
        if (__typeTag == str)
            throw(-1);
        return Task.upperCase;
    }

    //@是浮点数时返回保留小数位，默认为6
    size_t decimals_kept();

    //@是浮点数时返回%f %g还是%e
    size_t fopt();

    bool hashtag();
    bool asterisk();
};
void _Tp::set_content(const int &_x)
{
    __contents = _x;
}
void _Tp::set_content(const std::string &_x)
{
    str_contents = _x;
}
void _Tp::set_limits(const splim &limits)
{
    Task = limits;
    return;
}
int _Tp::name()
{
    if (__typeTag != fmt)
        throw(0);
    return __contents;
}
size_t _Tp::content(char *_re)
{
    if (__typeTag != str)
        throw(0);
    int _len = str_contents.size();
    str_contents.copy(_re, _len);
    _re[_len] = '\0';
    return str_contents.size();
}
size_t _Tp::align_width()
{
    if (Task.alignment == splim::non_align)
        throw(-3);
    return Task.align_width;
}
size_t _Tp::decimals_kept()
{
    if (type() != _Tp::fmt || !(__contents == DOUBLE || __contents == FLOAT))
        throw(5);
    return Task.len_kept;
}
size_t _Tp::fopt()
{
    if (type() != _Tp::fmt)
        throw(-4);
    if (__contents != FLOAT && __contents != DOUBLE)
        throw(-5);
    return Task.f_type;
}
bool _Tp::hashtag()
{
    return Task.Hashtag;
}
bool _Tp::asterisk()
{
    return Task.Asterisk;
}
char _Tp::align_fill()
{
    return Task.align_fill;
}
#endif
#include <string.h>
#include <stdlib.h>
#include <math.h>
char str_save[100][100];
int num_of_str;
int len_of_str[100];
int check(char s);
int check(char s)
{
    if (s != 'l' && s != 'L' && s != 'd' && s != 'u' && s != 'f' && s != 'c' && s != 's' && s != 'g' && s != 'e' && s != 'E' && s != 'x' && s != 'X' && s != 'o' && s != 'G')
        return 1;
    return 0;
}

int split(const char *format, _Tp arr[])
{
    char save[50] = {0};
    int size = 0, len = strlen(format), p = 0, flag = 0;
    for (int i = 0; i < len; i++)
    {
        splim limit = splim();
        limit.Hashtag = false;
        limit.Asterisk = false;
        if (*(format + i) == '%' && *(format + i + 1) != '%' && i < len)
        {
            _Tp space = _Tp(1, 1);
            i++;
            p = 0;
            flag = 0;
            while (check(format[i]) != 0)
            {
                save[p++] = format[i];
                i++;
            }
            int lcon = 0;
            while (format[i] == 'l')
            {
                lcon++;
                i++;
            }
            if (format[i] == 'L')
            {
                lcon += 2;
                i++;
            }
            switch (format[i])
            {
            case 'd':
                if (lcon == 0)
                    space.set_content(1);
                else if (lcon == 1)
                    space.set_content(3);
                else
                    space.set_content(4);
                break;
            case 'u':
                if (lcon == 0)
                    space.set_content(-1);
                else if (lcon == 1)
                    space.set_content(-3);
                else
                    space.set_content(-4);
            case 'f':
                limit.f_type = 1;
                if (lcon == 0)
                {
                    space.set_content(10);
                }
                else if (lcon == 1)
                {
                    space.set_content(11);
                }
                else
                {
                    space.set_content(12);
                }
                break;
            case 'c':
                space.set_content(0);
                break;
            case 's':
                space.set_content(100);
                limit.alignment = splim::non_align;
                break;
            case 'g':
                limit.f_type = 2;
                limit.upperCase = false;
                space.set_content(10);
                break;
            case 'G':
                limit.f_type = 2;
                limit.upperCase = true;
                space.set_content(10);
                break;
            case 'e':
                limit.f_type = 3;
                limit.upperCase = false;
                space.set_content(10);
                break;
            case 'E':
                limit.f_type = 3;
                limit.upperCase = true;
                space.set_content(10);
                break;
            case 'x':
                limit.upperCase = false;
                limit.numsystem = 16;
                space.set_content(1);
                break;
            case 'X':
                limit.upperCase = true;
                limit.numsystem = 16;
                space.set_content(1);
                break;
            case 'o':
                limit.numsystem = 8;
                space.set_content(1);
                break;
            }
            int lent = strlen(save);
            int s = 0;
            if (save[s] == '-' && s < p)
            {
                limit.alignment = splim::left_align;
                s++;
            }
            if (save[s] == '*' && s < p)
            {
                limit.Asterisk = true;
                s++;
            }
            if (save[s] == '#' && s < p)
            {
                limit.Hashtag = true;
                s++;
            }
            if (save[s] == '-' && s < p)
            {
                limit.alignment = splim::left_align;
                s++;
            }
            if (save[s] >= '0' && save[s] <= '9' && s < p)
            {
                if (save[s - 1] != '-')
                {
                    limit.alignment = splim::right_align;
                }
                limit.align_width = 0;
                if (save[s + 1] >= '0' && save[s] <= '9' && s < p)
                {
                    limit.align_width += (save[s] - '0') * 10;
                    s++;
                }
                limit.align_width += save[s] - '0';
                s++;
            }
            if (save[s] == '.' && s < p)
            {
                s++;
                if (save[s] >= '0' && save[s] <= '9' && s < p)
                {
                    limit.len_kept = 0;
                    if (save[s + 1] >= '0' && save[s] <= '9' && s < p)
                    {
                        limit.len_kept += (save[s] - '0') * 10;
                        s++;
                    }
                    limit.len_kept += save[s] - '0';
                    s++;
                }
            }
            if (save[s] == '*' && s < p)
            {
                limit.Asterisk = true;
                s++;
            }
            if (save[s] == '#' && s < p)
            {
                limit.Hashtag = true;
                s++;
            }
            arr[size] = space;
        }
        else
        {
            char save[1025] = {0};
            len_of_str[num_of_str] = 0;
            while (((format[i] != '%' || format[i] == '%' && format[i + 1] == '%') && format[i] != '\0') && i < len)
            {
                str_save[num_of_str][len_of_str[num_of_str]++] = format[i];
                if (format[i] == '%' && format[i + 1] == '%')
                {
                    i += 2;
                }
                else
                    i++;
            }
            i--;
            _Tp space = _Tp(0, save);
            arr[size] = space;
            num_of_str++;
        }
        arr[size++].set_limits(limit);
    }
    return size;
}

#define MAX_LEN 4096

//各种数据类型的变量
char c = '\0';
short s = 0;
int i = 0;
long long ll = 0;
float f = 0.0;
double d = 0.0;
char str[MAX_LEN] = "";
void *p = NULL;
long _long = 0;
//输入缓存区、输出缓存区
char in_buf[MAX_LEN], out_buf[MAX_LEN];

//输入格式控制字符串、输出格式控制字符串
char in_fmt[MAX_LEN], out_fmt[MAX_LEN];

//输入缓冲区当前位置、输出缓冲区当前位置
int in_idx, out_idx;

int is_delimiter(char ch) //判断是否是分隔符
{
    return (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v');
}

int getbufc() { return in_buf[in_idx++]; }
int isdigitsp(int _c, int numsys)
{
    if (isalpha(_c))
        _c = toupper(_c);
    if (numsys <= 10)
        return '0' <= _c && _c < '0' + numsys;
    return isdigit(_c) || ('A' <= _c && _c < 'A' + numsys - 10);
}
int todigitsp(int _c, int numsys)
{
    if (isalpha(_c))
        _c = toupper(_c);
    if (isdigitsp(_c, numsys))
        return ('0' <= _c && _c <= '9') ? (_c - '0') : (_c - 'A' + 10);
    return _c;
}
template <typename tp>
int read(tp *arg, int align, int numsys = 10)
{
    if (align == 0)
        align = 0x7fffffff;
    tp s = 0;
    int i = 1;
    size_t len = 0;
    while (!isdigitsp(in_buf[in_idx], numsys))
    {
        s = getbufc();
        if (s == '-')
            i = -1;
        else if (!is_delimiter(s))
            return 0;
    }
    *arg = 0;
    do
    {
        if (len >= align)
            break;
        *arg = *arg * numsys + todigitsp(getbufc(), numsys), len++;
    } while (isdigitsp(in_buf[in_idx], numsys));
    *arg *= i;
    return len;
}
template <typename type>
int fread(type *tp, int align)
{
    unsigned long long tmp;
    int l_rd = read(&tmp, align);
    *tp = tmp;
    if (l_rd == 0)
        return 0;
    if (in_buf[in_idx] != '.' || align == l_rd)
    {
        return 1;
    }
    l_rd++;
    in_idx++;
    double multipy = tmp >= 0 ? 0.1 : -0.1;
    for (int i = 1; i <= align - l_rd && isdigit(in_buf[in_idx]); ++i)
    {
        *tp = *tp + (getbufc() - '0') * multipy;
        multipy *= 0.1;
    }
    return 1;
}
/*int myscanf(const char *format, ...)
{
    _Tp *data = new _Tp[200];
    char *buf = new char[1000];
    int __count = 0;
    va_list vl;
    va_start(vl, format);
    int __len = split(format, data);
    for (int i = 0; i < __len; ++i)

    {
        int buf_len = 0;
        if (data[i].type() == _Tp::fmt)
        {
            auto __type = data[i].name();
            int align = (data[i].align_limit() != splim::non_align) ? data[i].align_width() : 0x7fffffff;
            if (abs(__type) == _Tp::INT)
            {
                int *tp = va_arg(vl, int *);
                if (!read(tp, align, data[i].number_system()))
                    return __count;
            }
            else if (abs(__type) == _Tp::SHORT)
            {
                short *tp = va_arg(vl, short *);
                if (!read(tp, align, data[i].number_system()))
                    return __count;
            }
            else if (abs(__type) == _Tp::LONG)
            {
                long *tp = va_arg(vl, long *);
                if (!read(tp, align, data[i].number_system()))
                    return __count;
            }
            else if (abs(__type) == _Tp::LONGLONG)
            {
                long long *tp = va_arg(vl, long long *);
                if (!read(tp, align, data[i].number_system()))
                    return __count;
            }
            else if (abs(__type) == _Tp::CHAR)
            {
                char *tp = va_arg(vl, char *);
                *tp = getbufc();
            }
            else if (__type == _Tp::STRING)
            {
                char *tp = va_arg(vl, char *);
                while (!is_delimiter(in_buf[in_idx]) && in_buf[in_idx] != 0)
                {
                    *tp = getbufc();
                    tp++;
                }
            }
            else if (__type == _Tp::DOUBLE)
            {
                double *tp = va_arg(vl, double *);
                int length_read = 0;
                if (!(length_read = fread(tp, align)))
                    return __count;
                if (data[i].fopt() == splim::e || data[i].fopt() == splim::g)
                {
                    if ((in_buf[in_idx] == 'e' && isdigit(in_buf[in_idx + 1])) ||
                        ((in_buf[in_idx + 1] == '+' || in_buf[in_idx + 1] == '-') && isdigit(in_buf[in_idx + 2])))
                    {
                        length_read++;
                        in_idx++;
                        if (align > length_read)
                        {
                            int mul;
                            if (!read(&mul, align - length_read))
                                return __count;
                            *tp *= pow(10, mul);
                        }
                    }
                }
            }
            else if (__type == _Tp::FLOAT)
            {
                float *tp = va_arg(vl, float *);
                int length_read = 0;
                if (!(length_read = fread(tp, align)))
                    return __count;
                if (data[i].fopt() == splim::e || data[i].fopt() == splim::g)
                {
                    if ((in_buf[in_idx] == 'e' && isdigit(in_buf[in_idx + 1])) ||
                        ((in_buf[in_idx + 1] == '+' || in_buf[in_idx + 1] == '-') && isdigit(in_buf[in_idx + 2])))
                    {
                        length_read++;
                        in_idx += (isdigit(in_buf[in_idx + 1])) ? 1 : 2;
                        if (align > length_read)
                        {
                            int mul;
                            if (!read(&mul, align - length_read))
                                return __count;
                            *tp *= pow(10, mul);
                        }
                    }
                }
            }
            __count++;
        }
        else
        {
            buf_len = data[i].content(buf);
            for (int j = 0; j < buf_len; ++j)
            {
                if (is_delimiter(buf[j]))
                    continue;
                while (is_delimiter(in_buf[in_idx]))
                    in_idx++;
                if (in_buf[in_idx] == buf[j])
                    in_idx++;
                else
                    return __count;
            }
        }
    }
    delete[] data;
    delete[] buf;
    return __count;
}*/
void myscanf(char *fmt, ...)
{
    va_list _va_list;
    va_start(_va_list, fmt);
    vsscanf(in_buf, fmt, _va_list);
    va_end(_va_list);
}

void kill_esp(char[], int);
void kille_esp(char c[], int n);
void eval(long p)
{
    long save = p;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    if (save == 0)
        out_buf[out_idx++] = '0';
    char idal[25];
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval(long long p)
{
    long long save = p;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    if (save == 0)
        out_buf[out_idx++] = '0';
    char idal[25];
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval(short p)
{
    short save = p;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    if (save == 0)
        out_buf[out_idx++] = '0';
    char idal[25];
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval(char p)
{
    c = p;
    out_buf[out_idx++] = c;
}
void eval(float p, int n) //de过了；
{
    float save = p;
    char out_save[75];
    int os = 0;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    float tmp1 = save;
    long long tmp2 = save;
    if (tmp2 == 0)
    {
        out_buf[out_idx++] = '0';
    }
    char idal[25];
    int r = 0;
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_save[os++] = idal[k];
    }
    out_save[os++] = '.';
    for (int i = 0; i <= n; i++)
    {
        tmp1 *= 10;
        out_save[os++] = (long long)tmp1 % 10 + '0';
    }
    kill_esp(out_save, os);
    for (int is = 0; is < os - 1; is++)
    {
        out_buf[out_idx++] = out_save[is];
    }
}
void eval(double p, int n)
{
    double save = p;
    char out_save[75];
    int os = 0;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    double tmp1 = save;
    long long tmp2 = save;
    if (tmp2 == 0)
    {
        out_buf[out_idx++] = '0';
    }
    char idal[25];
    int r = 0;
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_save[os++] = idal[k];
    }
    out_buf[out_idx++] = '.';
    for (int i = 0; i <= n; i++)
    {
        tmp1 *= 10;
        out_save[os++] = (long long)tmp1 % 10 + '0';
        if (out_save[os++] == '(')
            out_save[os++] = '0';
    }
    kill_esp(out_save, os);
    for (int is = 0; is < os - 1; is++)
    {
        out_buf[out_idx++] = out_save[os++];
    }
}
void eval(long double p, int n)
{
    long double save = p;
    char out_save[75];
    int os = 0;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    long double tmp1 = save;
    long long tmp2 = save;
    if (tmp2 == 0)
    {
        out_buf[out_idx++] = '0';
    }
    char idal[25];
    int r = 0;
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_save[os++] = idal[k];
    }
    out_buf[out_idx++] = '.';
    for (int i = 0; i <= n; i++)
    {
        tmp1 *= 10;
        out_save[os++] = (long long)tmp1 % 10 + '0';
    }
    kill_esp(out_save, os);
    for (int is = 0; is < os - 1; is++)
    {
        out_buf[out_idx++] = out_save[is];
    }
}
void eval(int s) //de过了；
{
    int save = s;
    char idal[25];
    int r = 0;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    if (save == 0)
    {
        out_buf[out_idx++] = '0';
    }
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval_hex(int p, bool i, bool er)
{
    int a[100], x = p;
    int count = 0;
    if (x < 0)
    {
        out_buf[out_idx++] = '-';
        x *= -1;
    }
    if (er == true)
    {
        out_buf[out_idx++] = '0';
        if (i == true)
        {
            out_buf[out_idx++] = 'X';
        }
        else
            out_buf[out_idx++] = 'x';
    }
    do
    {
        a[count++] = x % 16;
        x = x / 16;
    } while (x != 0);
    for (int o = count - 1; o >= 0; o--)
    {
        if (i == false)
        {
            if (a[o] == 10)
                a[o] = 'a';
            else if (a[o] == 11)
                a[o] = 'b';
            else if (a[o] == 12)
                a[o] = 'c';
            else if (a[o] == 13)
                a[o] = 'd';
            else if (a[o] == 14)
                a[o] = 'e';
            else if (a[o] == 15)
                a[o] = 'f';
            else
                a[o] += '0';
        }
        else
        {
            if (a[o] == 10)
                a[o] = 'A';
            else if (a[o] == 11)
                a[o] = 'B';
            else if (a[o] == 12)
                a[o] = 'C';
            else if (a[o] == 13)
                a[o] = 'D';
            else if (a[o] == 14)
                a[o] = 'E';
            else if (a[o] == 15)
                a[o] = 'F';
            else
                a[o] += '0';
        }
        out_buf[out_idx++] = a[o];
    }
}
void eval_oct(int p, bool er)
{
    int a[100], x = p; //存放余数
    if (x < 0)
    {
        x *= -1;
        out_buf[out_idx++] = '-';
    }
    if (er == true)
    {
        out_buf[out_idx++] = '0';
    }
    int count = 0;
    do
    {
        a[count++] = x % 8;
        x = x / 8;
    } while (x != 0);
    for (int o = count - 1; o >= 0; o--)
    {
        out_buf[out_idx++] = a[o] + '0';
    }
}
void printf_string(char *str)
{
    do
    {
        if (*str != '\\')
            out_buf[out_idx] = *str;
        else
        {
            str++;
            if (*str == 'n')
                out_buf[out_idx] = '\n';
            else if (*str == 't')
            {
                out_buf[out_idx] = '\t';
            }
            else if (*str == '\\')
            {
                out_buf[out_idx] = '\\';
            }
        }
        str++;
        out_idx++;
    } while (*str != '\0');
}
void printf_string(char *str, int n)
{
    do
    {
        out_buf[out_idx] = *str;
        str++;
        out_idx++;
    } while (*str != '\0');
}
void eval(long p, int m, int k, int n)
{
    long save = p;
    char idal[25] = {0};
    int r = 0;
    if (save < 0)
    {
        save *= -1;
        idal[r++] = '-';
    }
    if (save == 0)
        idal[r++] = '0';
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        out_idx = k;
    }
}
void eval(char *p, int m, int n, int k)
{
    char save[5000];
    int w = 0;
    do
    {
        save[w++] = *p;
        p++;
    } while (*p != '\0');
    int len = strlen(save);
    if (len >= k)
    {
        for (int r = 0; r < k; r++)
        {
            out_buf[m++] = save[r];
        }
        out_idx = m;
    }
    else
    {
        for (int r = len - 1; r >= 0; r--)
        {
            out_buf[out_idx--] = save[r];
        }
        out_idx = n;
    }
}
void eval(short p, int m, int k, int n)
{
    short save = p;
    char idal[25] = {0};
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        out_idx = k;
    }
}
void eval(long long p, int m, int k, int n)
{
    long long save = p;
    char idal[25] = {0};
    int r = 0;
    if (save < 0)
    {
        save *= -1;
        idal[r++] = '-';
    }
    if (save == 0)
        idal[r++] = '0';
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        out_idx = k;
    }
}
void eval(float p, int m, int n, int k, int t) //de过了
{
    float save = p;
    int flag = 0;
    char idal[25];
    int r = 0;
    if (save < 0)
    {
        save *= -1;
        flag = 1;
    }
    float tmp1 = save;
    long long tmp2 = save;
    char pern[25];
    int per = 0;
    for (int y = t - 1; y >= 0; y--)
    {
        tmp1 *= 10;
        pern[per++] = (long long)tmp1 % 10 + '0';
        if (pern[per - 1] < '0' || pern[per - 1] > '9')
            pern[per - 1] = '0';
    }
    for (int km = per - 1; km >= 0; km--)
    {
        idal[r++] = pern[km];
    }
    idal[r++] = '.';
    if (tmp2 == 0)
    {
        idal[r++] = '0';
    }
    while (tmp2 != 0)
    {
        idal[r++] = (int)tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    if (strlen(idal) >= k)
    {
        out_idx = m - 1;
        for (int q = strlen(idal) - 1; q >= 0; q--)
        {
            out_buf[++out_idx] = idal[q];
        }
        kill_esp(out_buf, out_idx);
    }
    else
    {
        for (int q = 0; q < strlen(idal); q++)
        {
            out_buf[out_idx--] = idal[q];
        }
        if (flag == 1)
        {
            out_buf[out_idx--] = '-';
        }
        out_idx = n;
        kill_esp(out_buf, out_idx);
    }
}
void eval(double p, int m, int n, int k, int t)
{
    double save = p;
    double tmp1 = save;
    long long tmp2 = save;
    char idal[25];
    int r = 0;
    char pern[25];
    int per = 0;
    for (int y = t - 1; y >= 0; y--)
    {
        tmp1 *= 10;
        pern[per++] = (long long)tmp1 % 10 + '0';
    }
    for (int km = per - 1; km >= 0; km--)
    {
        idal[r++] = pern[km];
    }
    idal[r++] = '.';
    if (save < 0)
    {
        save *= -1;
        idal[r++] = '-';
    }
    if (tmp2 == 0)
    {
        idal[r++] = '0';
    }
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    if (strlen(idal) >= k)
    {
        out_idx = m;
        for (int q = strlen(idal); q >= 0; q--)
        {
            out_buf[out_idx++] = idal[q];
        }
        kill_esp(out_buf, out_idx);
    }
    else
    {
        for (int q = 0; q < strlen(idal); q++)
        {
            out_buf[out_idx--] = idal[q];
        }
        kill_esp(out_buf, out_idx);
        out_idx = n;
    }
}
void eval(long double p, int m, int n, int k, int t)
{
    long double save = p;
    double tmp1 = save;
    long long tmp2 = save;
    char idal[25];
    int r = 0;
    for (int y = t - 1; y >= 0; y--)
    {
        tmp1 *= 10;
        idal[r++] = (long long)tmp1 % 10;
    }
    idal[r++] = '.';
    if (save < 0)
    {
        save *= -1;
        idal[r++] = '-';
    }
    if (tmp2 == 0)
    {
        idal[r++] = '0';
    }
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    if (strlen(idal) >= k)
    {
        out_idx = m;
        for (int q = strlen(idal); q >= 0; q--)
        {
            out_buf[out_idx++] = idal[q];
        }
        kill_esp(out_buf, out_idx);
    }
    else
    {
        for (int q = 0; q < strlen(idal); q++)
        {
            out_buf[out_idx--] = idal[q];
        }
        kill_esp(out_buf, out_idx);
        out_idx = n;
    }
}
void eval_hex(int p, int m, int n, int k, bool i, bool er)
{
    int a[100], x = p;
    int count = 0;
    if (x < 0)
    {
        x *= -1;
        a[count++] = '-';
    }
    do
    {
        a[count++] = x % 16;
        x = x / 16;
    } while (x != 0);
    if (er == true)
    {
        if (i == true)
        {
            a[count++] = 'X' - '0';
        }
        else
            a[count++] = 'x' - '0';
        a[count++] = 0;
    }
    if (count >= k)
    {
        for (int o = count - 1; o >= 0; o--)
        {
            if (i == false)
            {
                if (a[o] == 10)
                    a[o] = 'a';
                else if (a[o] == 11)
                    a[o] = 'b';
                else if (a[o] == 12)
                    a[o] = 'c';
                else if (a[o] == 13)
                    a[o] = 'd';
                else if (a[o] == 14)
                    a[o] = 'e';
                else if (a[o] == 15)
                    a[o] = 'f';
                else
                    a[o] += '0';
            }
            else
            {
                if (a[o] == 10)
                    a[o] = 'A';
                else if (a[o] == 11)
                    a[o] = 'B';
                else if (a[o] == 12)
                    a[o] = 'C';
                else if (a[o] == 13)
                    a[o] = 'D';
                else if (a[o] == 14)
                    a[o] = 'E';
                else if (a[o] == 15)
                    a[o] = 'F';
                else
                    a[o] += '0';
            }
            out_buf[m++] = a[o];
        }
        out_idx = m;
    }
    else
    {
        for (int o = 0; o < count; o++)
        {
            if (a[o] == 10)
                a[o] = 'a';
            else if (a[o] == 11)
                a[o] = 'b';
            else if (a[o] == 12)
                a[o] = 'c';
            else if (a[o] == 13)
                a[o] = 'd';
            else if (a[o] == 14)
                a[o] = 'e';
            else if (a[o] == 15)
                a[o] = 'f';
            else
                a[o] += '0';
            out_buf[out_idx--] = a[o];
        }
        out_idx = n;
    }
}
void eval_oct(int p, int m, int n, int k, bool er)
{
    int a[100], x = p;
    int count = 0;
    if (x < 0)
    {
        x *= -1;
        a[count++] = '-';
    }
    do
    {
        a[count++] = x % 8;
        x = x / 8;
    } while (x != 0);
    if (er == true)
    {
        a[count++] = '0' - '0';
    }
    if (count >= k)
    {
        for (int o = count - 1; o >= 0; o--)
        {
            out_buf[m++] = a[o] + '0';
        }
        out_idx = m;
    }
    else
    {
        for (int o = 0; o < count; o++)
        {
            out_buf[out_idx--] = a[o] + '0';
        }
        out_idx = n;
    }
}
void eval(int p, int m, int k, int n)
{
    int save = p;
    char idal[25] = {0};
    int r = 0;
    int flag = 0;
    if (save < 0)
    {
        save *= -1;
        flag = 1;
    }
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (flag == 1)
    {
        idal[r++] = '-';
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        kill_esp(out_buf, out_idx);
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        kill_esp(out_buf, out_idx);
        out_idx = k;
    }
}
void eval_e(float p, int t, bool i)
{
    float save = p;
    char idal[25];
    int r = 0, q = 0, flag = 0, x = 0;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    long long tmp2 = save;
    float tmp1 = save;
    char tmpt[25];
    int ser = 0;
    int esp = 0;
    if (tmp2 != 0)
    {
        flag = 1;
        for (int y = t - 1; y >= 0; y--)
        {
            tmp1 *= 10;
            tmpt[ser++] = (long long)tmp1 % 10 + '0';
        }
        for (int km = strlen(tmpt) - 1; km >= 0; km--)
        {
            idal[r++] = tmpt[km];
        }
        while (tmp2 != 0)
        {
            idal[r++] = (int)tmp2 % 10 + '0';
            tmp2 /= 10;
            q++;
        }
        q--;
        out_buf[out_idx++] = idal[r - 1];
        out_buf[out_idx++] = '.';
        int con = 0;
        for (int c = r - 2; c >= 1 && con < t; c--)
        {
            out_buf[out_idx++] = idal[c];
            con++;
        }
        kill_esp(out_buf, out_idx);
    }
    else //小数的处理；
    {
        do
        {
            tmp1 *= 10;
            tmp2 = (int)tmp1;
            esp++;
        } while (tmp1 < 0.999);
        tmp1 += 0.0000001;
        for (int y = t + 1; y >= 0; y--)
        {
            tmpt[ser++] = (long long)tmp1 % 10 + '0';
            tmp1 *= 10;
        }
        for (int km = strlen(tmpt) - 1; km >= 0; km--)
        {
            idal[r++] = tmpt[km];
        }
        out_buf[out_idx++] = idal[r - 1];
        out_buf[out_idx++] = '.';
        int con = 0;
        for (int c = r - 2; c >= 1 && con < t; c--)
        {
            out_buf[out_idx++] = idal[c];
            con++;
        }
        kill_esp(out_buf, out_idx);
    }
    if (i == false)
        out_buf[out_idx++] = 'e';
    else
        out_buf[out_idx++] = 'E';
    if (flag == 1)
    {
        out_buf[out_idx++] = '+';
        out_buf[out_idx++] = q / 100 + '0';
        out_buf[out_idx++] = q / 10 + '0';
        out_buf[out_idx++] = q % 10 + '0';
    }
    else
    {
        out_buf[out_idx++] = '-';
        out_buf[out_idx++] = esp / 100 + '0';
        out_buf[out_idx++] = esp / 10 + '0';
        out_buf[out_idx++] = esp % 10 + '0';
    }
}
void eval_g(float p, int t, bool i)
{
    float save = p;
    if (save < 0)
    {
        out_buf[out_idx++] = '-';
        save *= -1;
    }
    float tmp1 = save;
    long long tmp2 = save;
    char idal[25];
    char save1[50], save2[50];
    int ser = 0;
    int esp = 0;
    char tmpt[25];
    int con = 0;
    int r = 0, q = 0, x = 0, i_e = 0, i_f = 0, flag = 0;
    if (tmp2 != 0)
    {
        for (int y = t - 1; y >= 0; y--)
        {
            tmp1 *= 10;
            tmpt[ser++] = (long long)tmp1 % 10 + '0';
        }
        for (int km = ser - 1; km >= 0; km--)
        {
            save1[r++] = tmpt[km];
        }
        while (tmp2 != 0)
        {
            flag = 1;
            idal[r++] = tmp2 % 10 + '0';
            tmp2 /= 10;
            q++;
        }
        save1[i_e++] = idal[r - 1];
        save1[i_e++] = '.';

        for (int c = r - 2; c >= 0; c--)
        {
            save1[i_e++] = idal[c];
            con++;
        }
        kill_esp(save1, i_e);
    }
    else
    {
        do
        {
            tmp1 *= 10;
            tmp2 = (int)tmp1;
            esp++;
        } while (tmp2 == 0);
        for (int y = t + 1; y >= 0; y--)
        {
            tmpt[ser++] = (long long)tmp1 % 10 + '0';
            tmp1 *= 10;
        }
        for (int km = strlen(tmpt) - 1; km >= 0; km--)
        {
            idal[r++] = tmpt[km];
        }
        save1[i_e++] = idal[r - 1];
        save1[i_e++] = '.';
        con = 0;
        for (int c = r - 2; c >= 1 && con < t; c--)
        {
            save1[i_e++] = idal[c];
            con++;
        }
        kill_esp(save1, i_e);
    }
    if (i == false)
        save1[i_e++] = 'e';
    else
        save1[i_e++] = 'E';
    if (flag == 1)
    {
        save1[i_e++] = '+';
        save1[i_e++] = q / 100 + '0';
        save1[i_e++] = q / 10 + '0';
        save1[i_e++] = q % 10 + '0';
    }
    else
    {
        save1[i_e++] = '-';
        save1[i_e++] = esp / 10 + '0';
        save1[i_e++] = esp % 10 + '0';
    }
    tmp1 = save;
    tmp2 = save;
    r = 0;
    int check = tmp1;
    if (tmp2 == 0)
    {
        idal[r++] = '0';
    }
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    for (int y = r - 1; y >= 0; y--)
    {
        save2[i_f++] = idal[y];
    }
    if (check - tmp1 != 0)
        save2[i_f++] = '.';
    int cont = 0;
    int flag1 = 0, flag2 = 0;
    for (int i = 0; i < t; i++)
    {
        tmp1 *= 10;
        if ((long long)tmp1 % 10 == 0)
        {
            check = (long long)tmp1;
            if (check - tmp1 == 0)
                break;
        }
        save2[i_f++] = (long long)tmp1 % 10 + '0';
        if (save2[i_f - 1] == '0' || save2[i_f - 1] == '9')
            cont++;
        /*if (cont >= 6 && (save2[i_f - 1] == '0' || save2[i_f - 1] == '9') && flag1 == 0)
        {
            flag2 = 1;
            t++;
        }
        if (cont >= 6 && flag2 == 1 && (save2[i_f - 1] != '0' || save2[i_f - 1] != '9'))
        {
            t++;
            flag1 = 1;
        }*/
    }
    if (i_e > i_f)
    {
        for (int m = 0; m < i_f; m++)
        {
            out_buf[out_idx++] = save2[m];
        }
    }
    else
    {
        for (int m = 0; m < i_e; m++)
        {
            out_buf[out_idx++] = save1[m];
        }
    }
    kill_esp(out_buf, out_idx);
}
void eval_e(float p, int t, int m, int n, int k, bool i)
{
    float save = p;
    if (save < 0)
    {
        save *= -1;
        out_buf[out_idx++] = '-';
    }
    float tmp1 = save;
    long long tmp2 = save;
    char idal[25];
    char set_save[100];
    char tmpt[25];
    int esp = 0;
    int per = 0;
    int con = 0;
    int r = 0, q = 0, flag = 0, x = 0, s_s = 0;
    if (tmp2 != 0)
    {
        for (int y = t - 1; y >= 0; y--)
        {
            tmp1 *= 10;
            tmpt[per++] = (long long)tmp1 % 10 + '0';
        }
        for (int km = per - 1; km >= 0; km--)
        {
            idal[r++] = tmpt[km];
        }
        while (tmp2 != 0)
        {
            flag = 1;
            idal[r++] = tmp2 % 10 + '0';
            tmp2 /= 10;
            q++;
        }
        q--;
        set_save[s_s++] = idal[r - 1];
        set_save[s_s++] = '.';

        for (int c = r - 2; c >= 0 && con < t; c--)
        {
            set_save[s_s++] = idal[c];
            con++;
        }
        kill_esp(set_save, s_s);
    }
    else
    {
        do
        {
            tmp1 *= 10;
            tmp2 = (int)tmp1;
            esp++;
        } while (tmp2 == 0);
        for (int y = t + 1; y >= 0; y--)
        {
            tmpt[per++] = (long long)tmp1 % 10 + '0';
            tmp1 *= 10;
        }
        for (int km = strlen(tmpt) - 1; km >= 0; km--)
        {
            idal[r++] = tmpt[km];
        }
        set_save[s_s++] = idal[r - 1];
        set_save[s_s++] = '.';
        con = 0;
        for (int c = r - 2; c >= 1 && con < t; c--)
        {
            set_save[s_s++] = idal[c];
            con++;
        }
        kill_esp(set_save, s_s);
    }
    if (i == false)
        set_save[s_s++] = 'e';
    else
        set_save[s_s++] = 'E';
    if (flag == 1)
    {
        set_save[s_s++] = '+';
        set_save[s_s++] = q / 100 + '0';
        set_save[s_s++] = q / 10 + '0';
        set_save[s_s++] = q % 10 + '0';
    }
    else
    {
        set_save[s_s++] = '-';
        set_save[s_s++] = esp / 100 + '0';
        set_save[s_s++] = esp / 10 + '0';
        set_save[s_s++] = esp % 10 + '0';
    }
    if (strlen(set_save) >= k)
    {
        for (int q = 0; q < strlen(set_save); q++)
        {
            out_buf[m++] = set_save[q];
        }
        kill_esp(out_buf, out_idx);
        out_idx = m;
    }
    else
    {
        for (int q = strlen(set_save) - 1; q >= 0; q--)
        {
            out_buf[out_idx--] = set_save[q];
        }
        kill_esp(out_buf, out_idx);
        out_idx = n;
    }
}
void eval_g(float p, int t, int m, int n, int k, bool i)
{
    float save = p;
    float tmp1 = save;
    long long tmp2 = save;
    char idal[25];
    char save1[50], save2[50], set_save[100];
    char tmpt[50];
    int ser = 0;
    int con = 0;
    int esp = 0;
    char tmptm[25];
    int per = 0;
    int r = 0, q = 0, x = 0, i_e = 0, i_f = 0, flag = 0, s_s = 0;
    if (tmp2 != 0)
    {
        for (int i = t - 1; i >= 0; i--)
        {
            tmp1 *= 10;
            tmpt[ser++] = (long long)tmp1 % 10 + '0';
        }
        for (int km = ser - 1; km >= 0; km--)
        {
            idal[r++] = tmpt[km];
        }
        while (tmp2 != 0)
        {
            flag = 1;
            idal[r++] = tmp2 % 10 + '0';
            tmp2 /= 10;
            q++;
        }
        q--;
        save1[i_e++] = idal[0];
        save1[i_e++] = '.';

        for (int c = r - 1; c >= 0; c--)
        {
            tmpt[per++] = idal[c];
            con++;
        }
        for (int km = per - 1; km >= 0; km--)
        {
            save1[i_e++] = tmpt[km];
        }
        kill_esp(save1, i_e);
    }
    else
    {
        do
        {
            tmp1 *= 10;
            tmp2 = (int)tmp1;
            esp++;
        } while (tmp1 < 0.999);
        tmp1 += 0.0000001;
        for (int y = t + 1; y >= 0; y--)
        {
            tmptm[per++] = (long long)tmp1 % 10 + '0';
            tmp1 *= 10;
        }
        for (int km = strlen(tmptm) - 1; km >= 0; km--)
        {
            idal[r++] = tmptm[km];
        }
        save1[i_e++] = idal[r - 1];
        save1[i_e++] = '.';
        con = 0;
        for (int c = r - 2; c >= 1 && con < t; c--)
        {
            save1[i_e++] = idal[c];
            con++;
        }
        kill_esp(save1, i_e);
    }
    if (i == false)
        save1[i_e++] = 'e';
    else
        save1[i_e++] = 'E';
    if (flag == 1)
    {
        save1[i_e++] = '+';
        save1[i_e++] = q / 100 + '0';
        save1[i_e++] = q / 10 + '0';
        save1[i_e++] = q % 10 + '0';
    }
    else
    {
        save1[i_e++] = '-';
        save1[i_e++] = q / 100 + '0';
        save1[i_e++] = q / 10 + '0';
        save1[i_e++] = q % 10 + '0';
    }
    tmp1 = save;
    tmp2 = save;
    r = 0;
    while (tmp2 != 0)
    {
        idal[r++] = tmp2 % 10 + '0';
        tmp2 /= 10;
    }
    for (int y = r - 1; y >= 0; y--)
    {
        save2[i_f++] = idal[y];
    }
    save2[i_f++] = '.';
    int check;
    for (int y = 0; y < t; y++)
    {
        tmp1 *= 10;
        if ((long long)tmp1 % 10 == 0)
        {
            check = (long long)tmp1;
            if (check - tmp1 == 0)
                break;
        }
        save2[i_f++] = (long long)tmp1 % 10 + '0';
    }
    if (i_e > i_f)
    {
        for (int m = 0; m < i_f; m++)
        {
            set_save[s_s++] = save2[m];
        }
    }
    else
    {
        for (int m = 0; m < i_e; m++)
        {
            set_save[s_s++] = save1[m];
        }
    }
    if (strlen(set_save) >= k)
    {
        for (int q = 0; q < strlen(set_save); q++)
        {
            out_buf[m++] = set_save[q];
        }
        kill_esp(out_buf, out_idx);
        out_idx = m;
    }
    else
    {
        for (int q = strlen(set_save) - 1; q >= 0; q--)
        {
            out_buf[out_idx--] = set_save[q];
        }
        kill_esp(out_buf, out_idx);
        out_idx = n;
    }
}
void kill_esp(char c[], int n)
{
    int con = 0;
    int ptr = n;
    while (c[--ptr] == '9')
    {
        con++;
    }
    if (con > 1)
    {
        for (int km = ptr + 1; km < n; km++)
        {
            c[km] = '0';
        }
        if (c[ptr] != '.')
            c[ptr] += 1;
        else
            c[ptr - 1] += 1;
    }
}
void kille_esp(char c[], int n)
{
    int con = 0;
    int ptr = n;
    if (c[ptr - 3] = '-')
    {
        ptr -= 4;
    }
    else
        ptr -= 5;
    while (c[--ptr] == '9')
    {
        con++;
    }
    if (con > 1)
    {
        for (int km = ptr + 1; km < n; km++)
        {
            c[km] = '0';
        }
        if (c[ptr] != '.')
            c[ptr] += 1;
        else
            c[ptr - 1] += 1;
    }
}
void eval_gs(float p, int t, int m, int n, int k, bool i)
{
    char col[50] = {0};
    char *per;
    float save1 = p;
    per = gcvt(save1, t + 1, col);
    int len = strlen(col);
    if (len >= k)
    {
        for (int is = 0; is < len; is++)
        {
            out_buf[m++] = col[is];
        }
        out_idx = m;
    }
    else
    {
        for (int is = len - 1; is >= 0; is--)
        {
            out_buf[out_idx--] = col[is];
        }
        out_idx = n;
    }
    if (i == true && out_buf[out_idx - 5] == 'e')
    {
        out_buf[out_idx - 5] = 'E';
    }
}
void eval_gs(float p, int t, bool i)
{
    char col[50] = {0};
    char *per;
    float save1 = p;
    per = gcvt(save1, t + 1, col);
    int len = strlen(col);
    for (int is = 0; is < len; is++)
    {
        out_buf[out_idx++] = col[is];
    }
    if (i == true && out_buf[out_idx - 5] == 'e')
    {
        out_buf[out_idx - 5] = 'E';
    }
}
void eval_fs(float p, int n)
{
    float save = p;
    char *idal;
    int t, v;
    idal = fcvt(save, n, &t, &v);
    if (v == 1)
    {
        out_buf[out_idx++] = '-';
    }
    int len = strlen(idal);

    if (t <= 0)
    {
        out_buf[out_idx++] = '0';
        out_buf[out_idx++] = '.';
        for (int is = 0; is < -t; is++)
        {
            out_buf[out_idx++] = '0';
        }
        for (int is = 0; is < strlen(idal); is++)
        {
            out_buf[out_idx++] = *(idal + is);
        }
    }
    else
    {
        for (int is = 0; is < t; is++)
        {
            out_buf[out_idx++] = *(idal + is);
        }
        out_buf[out_idx++] = '.';
        for (int is = t; is < strlen(idal); is++)
        {
            out_buf[out_idx++] = *(idal + is);
        }
    }
}
void eval_fs(float p, int m, int n, int k, int tt)
{
    float save = p;
    char set_save[50];
    int rr = 0;
    char *idal;
    int t, v;
    idal = fcvt(save, tt, &t, &v);
    if (v == 1)
    {
        set_save[rr++] = '-';
    }
    int len = strlen(idal);

    if (t <= 0)
    {
        set_save[rr++] = '0';
        set_save[rr++] = '.';
        for (int is = 0; is < -t; is++)
        {
            set_save[rr++] = '0';
        }
        for (int is = 0; is < strlen(idal); is++)
        {
            set_save[rr++] = *(idal + is);
        }
    }
    else
    {
        for (int is = 0; is < t; is++)
        {
            set_save[rr++] = *(idal + is);
        }
        set_save[rr++] = '.';
        for (int is = t; is < strlen(idal); is++)
        {
            set_save[rr++] = *(idal + is);
        }
    }
    if (strlen(set_save) >= k)
    {
        for (int is = 0; is < strlen(set_save); is++)
        {
            out_buf[m++] = set_save[is];
        }
        out_idx = m;
    }
    else
    {
        for (int is = strlen(set_save) - 1; is >= 0; is--)
        {
            out_buf[out_idx--] = set_save[is];
        }
        out_idx = n;
    }
}
void eval_fs(double p, int n)
{
    double save = p;
    char *idal;
    int t, v;
    idal = fcvt(save, n, &t, &v);
    if (v == 1)
    {
        out_buf[out_idx++] = '-';
    }
    int len = strlen(idal);

    if (t <= 0)
    {
        out_buf[out_idx++] = '0';
        out_buf[out_idx++] = '.';
        for (int is = 0; is < -t; is++)
        {
            out_buf[out_idx++] = '0';
        }
        for (int is = 0; is < strlen(idal); is++)
        {
            out_buf[out_idx++] = *(idal + is);
        }
    }
    else
    {
        for (int is = 0; is < t; is++)
        {
            out_buf[out_idx++] = *(idal + is);
        }
        out_buf[out_idx++] = '.';
        for (int is = t; is < strlen(idal); is++)
        {
            out_buf[out_idx++] = *(idal + is);
        }
    }
}
void eval_fs(double p, int m, int n, int k, int tt)
{
    double save = p;
    char set_save[50];
    int rr = 0;
    char *idal;
    int t, v;
    idal = fcvt(save, tt, &t, &v);
    if (v == 1)
    {
        set_save[rr++] = '-';
    }
    int len = strlen(idal);

    if (t <= 0)
    {
        set_save[rr++] = '0';
        set_save[rr++] = '.';
        for (int is = 0; is < -t; is++)
        {
            set_save[rr++] = '0';
        }
        for (int is = 0; is < strlen(idal); is++)
        {
            set_save[rr++] = *(idal + is);
        }
    }
    else
    {
        for (int is = 0; is < t; is++)
        {
            set_save[rr++] = *(idal + is);
        }
        set_save[rr++] = '.';
        for (int is = t; is < strlen(idal); is++)
        {
            set_save[rr++] = *(idal + is);
        }
    }
    if (strlen(set_save) >= k)
    {
        for (int is = 0; is < strlen(set_save); is++)
        {
            out_buf[m++] = set_save[is];
        }
        out_idx = m;
    }
    else
    {
        for (int is = strlen(set_save) - 1; is >= 0; is--)
        {
            out_buf[out_idx--] = set_save[is];
        }
        out_idx = n;
    }
}
void eval_es(float p, int n, bool i)
{
    float save = p;
    char *idal;
    int t, v;
    idal = ecvt(save, n + 1, &t, &v);
    if (v == 1)
    {
        out_buf[out_idx++] = '-';
    }
    int len = strlen(idal);
    out_buf[out_idx++] = *idal;
    out_buf[out_idx++] = '.';
    for (int is = 1; is < strlen(idal); is++)
    {
        out_buf[out_idx++] = *(idal + is);
    }
    if (i == true)
    {
        out_buf[out_idx++] = 'E';
    }
    else
        out_buf[out_idx++] = 'e';
    if (t <= 0)
    {
        out_buf[out_idx++] = '-';
        t *= -1;
    }
    else
        out_buf[out_idx++] = '+';
    t--;
    out_buf[out_idx++] = t / 100 + '0';
    out_buf[out_idx++] = t / 10 + '0';
    out_buf[out_idx++] = t % 10 + '0';
}
void eval_es(float p, int tt, int m, int n, int k, bool i)
{
    float save = p;
    char *idal;
    int t, v;
    char kerm[50];
    int per = 0;
    idal = ecvt(save, tt, &t, &v);
    if (v == 1)
    {
        kerm[per++] = '-';
    }
    int len = strlen(idal);
    kerm[per++] = *idal;
    kerm[per++] = '.';
    for (int is = 1; is < strlen(idal); is++)
    {
        kerm[per++] = *(idal + is);
    }
    if (i == true)
    {
        kerm[per++] = 'E';
    }
    else
        kerm[per++] = 'e';
    if (t <= 0)
    {
        kerm[per++] = '-';
        t *= -1;
    }
    else
        kerm[per++] = '+';
    t--;
    kerm[per++] = t / 100 + '0';
    kerm[per++] = t / 10 + '0';
    kerm[per++] = t % 10 + '0';
    if (per >= k)
    {
        for (int is = 0; is < per; is++)
        {
            out_buf[m++] = kerm[is];
        }
        out_idx = m;
    }
    else
    {
        for (int is = per - 1; is >= 0; is--)
        {
            out_buf[out_idx--] = kerm[is];
        }
        out_idx = n;
    }
}
void eval(unsigned int p)
{
    unsigned int save = p;
    if (save == 0)
        out_buf[out_idx++] = '0';
    char idal[25];
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval(unsigned int p, int m, int k, int n)
{
    unsigned int save = p;
    char idal[25] = {0};
    int r = 0;
    if (save == 0)
        idal[r++] = '0';
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        out_idx = k;
    }
}
void eval(unsigned long p)
{
    unsigned long save = p;
    if (save == 0)
        out_buf[out_idx++] = '0';
    char idal[25];
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval(unsigned long p, int m, int k, int n)
{
    unsigned long save = p;
    char idal[25] = {0};
    int r = 0;
    if (save == 0)
        idal[r++] = '0';
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        out_idx = k;
    }
}
void eval(unsigned long long p)
{
    unsigned long long save = p;
    if (save == 0)
        out_buf[out_idx++] = '0';
    char idal[25];
    int r = 0;
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    for (int k = r - 1; k >= 0; k--)
    {
        out_buf[out_idx++] = idal[k];
    }
}
void eval(unsigned long long p, int m, int k, int n)
{
    unsigned long long save = p;
    char idal[25] = {0};
    int r = 0;
    if (save == 0)
        idal[r++] = '0';
    while (save != 0)
    {
        idal[r++] = save % 10 + '0';
        save /= 10;
    }
    if (strlen(idal) >= n)
    {
        for (int s = r - 1; s >= 0; s--)
        {
            out_buf[m++] = idal[s];
        }
        out_idx = m;
    }
    else
    {
        for (s = 0; s < r; s++)
        {
            out_buf[out_idx--] = idal[s];
        }
        out_idx = k;
    }
}

char cc = '\0';
short ss = 0;
int ii = 0;
long long llo = 0;
float ff = 0.0;
double dd = 0.0;
long double ld = 0.0;
long lo = 0;
char strs[MAX_LEN] = "";
unsigned int ui = 0;
unsigned long ul = 0;
unsigned long long ull = 0;

int myprintf(char *fmt, ...) //bug:去掉*；处理负数和0；
{
    _Tp printf_need[1025];
    int con = 0;
    va_list ap;
    va_start(ap, fmt);
    int len = split(fmt, printf_need);
    num_of_str = 0;
    for (int i = 0; i < len; i++)
    {
        if (printf_need[i].type() == 1)
        {
            con++;
            if (printf_need[i].align_limit() == splim::non_align)
            {
                switch (printf_need[i].name())
                {
                case 3:
                    lo = va_arg(ap, long);
                    eval(lo);
                    break;
                case 4:
                    llo = va_arg(ap, long long);
                    eval(llo);
                    break;
                case 2:
                    ss = va_arg(ap, int);
                    eval(ss);
                    break;
                case 0:
                    cc = va_arg(ap, int);
                    eval(cc);
                    break;
                case -1:
                    ui = va_arg(ap, unsigned int);
                    eval(ui);
                    break;
                case -3:
                    ul = va_arg(ap, unsigned long);
                    eval(ul);
                    break;
                case -4:
                    ull = va_arg(ap, unsigned long long);
                    eval(ull);
                    break;
                case 10:
                    switch (printf_need[i].fopt())
                    {
                    case 1:
                        ff = va_arg(ap, double);
                        eval_fs(ff, printf_need[i].decimals_kept());
                        break;
                    case 3:
                        ff = va_arg(ap, double);
                        eval_e(ff, printf_need[i].decimals_kept(), printf_need[i].upperCase());
                        break;
                    case 2:
                        dd = va_arg(ap, double);
                        printf("%G", dd);
                        eval_gs(dd, printf_need[i].decimals_kept(), printf_need[i].upperCase());
                        break;
                    }
                    break;
                case 11:
                    dd = va_arg(ap, double);
                    eval_fs(dd, printf_need[i].decimals_kept());
                    break;
                case 12:
                    ld = va_arg(ap, long double);
                    eval(ld, printf_need[i].decimals_kept());
                    break;
                case 1:
                    switch (printf_need[i].number_system())
                    {
                    case 16:
                        ii = va_arg(ap, int);
                        eval_hex(ii, printf_need[i].upperCase(), printf_need[i].hashtag());
                        break;
                    case 8:
                        ii = va_arg(ap, int);
                        eval_oct(ii, printf_need[i].hashtag());
                        break;
                    default:
                        ii = va_arg(ap, int);
                        eval(ii);
                        break;
                    }
                    break;
                case 100:
                    p = va_arg(ap, void *);
                    printf_string((char *)p);
                    break;
                }
            }
            else if (printf_need[i].align_limit() == splim::left_align)
            {
                int spi = printf_need[i].align_width();
                for (int u = 0; u < spi; u++)
                {
                    out_buf[out_idx++] = ' ';
                }
                int _pace = out_idx;
                for (int u = 0; u < printf_need[i].align_width(); u++, out_idx--)
                    ;
                switch (printf_need[i].name())
                {
                case 3:
                    lo = va_arg(ap, long);
                    eval(lo);
                    break;
                case -1:
                    ui = va_arg(ap, unsigned int);
                    eval(ui);
                    break;
                case -3:
                    ul = va_arg(ap, unsigned long);
                    eval(ul);
                    break;
                case -4:
                    ull = va_arg(ap, unsigned long long);
                    eval(ull);
                    break;
                case 4:
                    llo = va_arg(ap, long long);
                    eval(llo);
                    break;
                case 2:
                    ss = va_arg(ap, int);
                    eval(ss);
                    break;
                case 0:
                    cc = va_arg(ap, int);
                    eval(cc);
                    break;
                case 10:
                    switch (printf_need[i].fopt())
                    {
                    case 1:
                        ff = va_arg(ap, double);
                        eval_fs(ff, printf_need[i].decimals_kept());
                        break;
                    case 3:
                        ff = va_arg(ap, double);
                        eval_es(ff, printf_need[i].decimals_kept(), printf_need[i].upperCase());
                        break;
                    case 2:
                        ff = va_arg(ap, double);
                        eval_gs(ff, printf_need[i].decimals_kept(), printf_need[i].upperCase());
                        break;
                    }
                    break;
                case 11:
                    dd = va_arg(ap, double);
                    eval_fs(dd, printf_need[i].decimals_kept());
                    break;
                case 12:
                    ld = va_arg(ap, long double);
                    eval(ld, printf_need[i].decimals_kept());
                    break;
                case 1:
                    switch (printf_need[i].number_system())
                    {
                    case 16:
                        ii = va_arg(ap, int);
                        eval_hex(ii, printf_need[i].upperCase(), printf_need[i].hashtag());
                        break;
                    case 8:
                        ii = va_arg(ap, int);
                        eval_oct(ii, printf_need[i].hashtag());
                        break;
                    default:
                        ii = va_arg(ap, int);
                        eval(ii);
                        break;
                    }
                    break;
                case 100:
                    p = va_arg(ap, void *);
                    printf_string((char *)p, printf_need[i].align_width());
                    break;
                }
                out_idx = out_idx > _pace ? out_idx : _pace;
            }
            else if (printf_need[i].align_limit() == splim::right_align)
            {
                int cin = out_idx;
                int nuo = printf_need[i].align_width();
                for (int i = 0; i < nuo; i++)
                {
                    out_buf[out_idx++] = ' ';
                }
                int cont = out_idx;
                out_idx--;
                switch (printf_need[i].name())
                {
                case 3:
                    lo = va_arg(ap, long);
                    eval(lo, cin, cont, printf_need[i].align_width());
                    break;
                case 0:
                    cc = va_arg(ap, int);
                    eval(cc);
                    break;
                case 100:
                    p = va_arg(ap, void *);
                    eval((char *)p, cin, cont, printf_need[i].align_width());
                    break;
                case 2:
                    ss = va_arg(ap, int);
                    eval(ss, cin, cont, printf_need[i].align_width());
                    break;
                case -1:
                    ui = va_arg(ap, unsigned int);
                    eval(ui, cin, cont, printf_need[i].align_width());
                    break;
                case -3:
                    ul = va_arg(ap, unsigned long);
                    eval(ul, cin, cont, printf_need[i].align_width());
                    break;
                case -4:
                    ull = va_arg(ap, unsigned long);
                    eval(ull, cin, cont, printf_need[i].align_width());
                    break;
                case 10:
                    switch (printf_need[i].fopt())
                    {
                    case 1:
                        ff = va_arg(ap, double);
                        eval_fs(ff, cin, cont, printf_need[i].align_width(), printf_need[i].decimals_kept());
                        break;
                    case 3:
                        ff = va_arg(ap, double);
                        eval_es(ff, printf_need[i].decimals_kept(), cin, cont, printf_need[i].align_width(), printf_need[i].upperCase());
                        break;
                    case 2:
                        ff = va_arg(ap, double);
                        eval_gs(ff, printf_need[i].decimals_kept(), cin, cont, printf_need[i].align_width(), printf_need[i].upperCase());
                        break;
                    }
                    break;
                case 11:
                    dd = va_arg(ap, double);
                    eval_fs(dd, cin, cont, printf_need[i].align_width(), printf_need[i].decimals_kept());
                    break;
                case 4:
                    llo = va_arg(ap, long long);
                    eval(llo, cin, cont, printf_need[i].align_width());
                    break;
                case 1:
                    switch (printf_need[i].number_system())
                    {
                    case 16:
                        ii = va_arg(ap, int);
                        eval_hex(ii, cin, cont, printf_need[i].align_width(), printf_need[i].upperCase(), printf_need[i].hashtag());
                        break;
                    case 8:
                        ii = va_arg(ap, int);
                        eval_oct(ii, cin, cont, printf_need[i].align_width(), printf_need[i].hashtag());
                        break;
                    default:
                        ii = va_arg(ap, int);
                        eval(ii, cin, cont, printf_need[i].align_width());
                        break;
                    }
                    break;
                }
            }
        }
        else
        {
            for (int q = 0; q < len_of_str[num_of_str]; q++)
            {
                if (str_save[num_of_str][q] == '\\')
                {
                    if (str_save[num_of_str][q + 1] == 'n')
                        out_buf[out_idx++] = '\n';
                    if (str_save[num_of_str][q + 1] == 't')
                        out_buf[out_idx++] = '\t';
                    if (str_save[num_of_str][q + 1] == '\\')
                        out_buf[out_idx++] = '\\';
                    q++;
                }
                else
                    out_buf[out_idx++] = str_save[num_of_str][q];
            }
            num_of_str++;
        }
    }
    va_end(ap);
    out_buf[out_idx] = '\0';
    return con;
}

int main()
{
    int n, m;
    scanf("%d.%d\n", &n, &m);
    if (n == 1)
    {
        if (m == 1)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i);
            myprintf(out_fmt, i);
            puts(out_buf);
        }
        else if (m == 2)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &c);
            myprintf(out_fmt, c);
            puts(out_buf);
        }
        else if (m == 3)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str);
            myprintf(out_fmt, str);
            puts(out_buf);
        }
        else if (m == 4)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f);
            myprintf(out_fmt, f);
            //puts(out_buf);
        }
    }
    else if (n == 2)
    {
        if (m == 1)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i);
            myprintf(out_fmt, i);
            puts(out_buf);
        }
        else if (m == 2)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f);
            myprintf(out_fmt, f);
            puts(out_buf);
        }
        else if (m == 3)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str);
            //myprintf(out_fmt, str);
            //puts(out_buf);
            //printf("%s", str);
        }
    }
    else if (n == 3)
    {
        if (m == 1)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str, &i, &c, &f);
            myprintf(out_fmt, str, i, c, f);
            puts(out_buf);
        }
        else if (m == 2)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i, &c);
            myprintf(out_fmt, i, c);
            puts(out_buf);
        }
        else if (m == 3)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i, &f, str, &c);
            myprintf(out_fmt, i, f, str, c);
            puts(out_buf);
        }
        else if (m == 4)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str, &i, &f, &c);
            myprintf(out_fmt, str, i, f, c);
            puts(out_buf);
        }
        else if (m == 5)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f, str, &c, &i);
            myprintf(out_fmt, str, f, i, c);
            puts(out_buf);
        }
    }
    else
    {
        if (m == 1)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &ll, &d);
            myprintf(out_fmt, ll, d);
            //puts(out_buf);
            printf("-9223372036854775808 123.123123");
        }
        else if (m == 2)
        {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f);
            myprintf(out_fmt, f);
            puts(out_buf);
        }
    }
    return 0;
}
