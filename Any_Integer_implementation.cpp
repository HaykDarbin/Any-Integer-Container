#include "Any_Integer.hpp"
static const unsigned long MAX_INTEGER = -1ul;
static const unsigned int DECIMAL_BASE = 10;
static const unsigned int MIN_PART_COUNT = 2;

template <unsigned long max_num>
static const unsigned int digit_counter ();
const unsigned int PART_DIG_MAXC = digit_counter<static_cast<const Any_Integer::part_num_t>(MAX_INTEGER)>() - 1;

Any_Integer::Any_Integer(const std::string& str_num) : num_container((str_num.length() / PART_DIG_MAXC) + MIN_PART_COUNT)
{
    partitioning(str_num);
}
Any_Integer::Any_Integer(const long num) : num_container(MIN_PART_COUNT), sign (num < 0l)
{
    auto it = num_container.begin();
    it->part_val = sign ? -num : num;
    long tmp = it->part_val;
    while (tmp)
    {
        ++(it->real_dig_count);
        ++(it->virt_dig_count);
        tmp /= DECIMAL_BASE;
    } 
}

inline Any_Integer::offset_t  Any_Integer::counting_num_offset (const Any_Integer::offset_t num_dig_c, const Any_Integer::offset_t iteration)
{
    return (iteration == 0ul) ? 0ul : ((num_dig_c % PART_DIG_MAXC) + PART_DIG_MAXC * (iteration - 1ul));
}
Any_Integer::Partition_Cases Any_Integer::create_cur_partition (const std::string& str_num, Any_Integer::offset_t cur_off, std::vector<Partition>::iterator it)
{
    Any_Integer::offset_t tmp_size = str_num.length() % PART_DIG_MAXC;
    auto str_it = str_num.begin() + cur_off;
    Partition_Cases cur_case = P_POSOK;
    it->virt_dig_count = ((cur_off == 0ul) && (tmp_size != 0ul)) ? tmp_size : PART_DIG_MAXC;
    if (*str_it == '-')
    {
        cur_case = P_NEGOK;
        str_it++;
        it->virt_dig_count--;
        cur_off++;
    } 
    for (; str_it < str_num.begin() + cur_off + it->virt_dig_count; str_it++)
    {
        if (!is_digit(str_it)) { return P_WRONG; }
        it->part_val *= DECIMAL_BASE;
        it->part_val += (*str_it - '0'); 
        if ( it->part_val != 0ul) { it->real_dig_count ++; }
    }
    return cur_case;
}
inline bool Any_Integer::is_digit(std::string::const_iterator character)
{ 
    return ((*character <= '9') && (*character >= '0')); 
}
void Any_Integer::partitioning (const std::string& str_num)
{
    bool is_std_size_part = !static_cast<bool>(str_num.length() % PART_DIG_MAXC);
    auto it = num_container.begin();
    for (long iter = (str_num.length() / PART_DIG_MAXC); iter >= is_std_size_part; iter--)     
    {
        Any_Integer::offset_t current_offset = counting_num_offset (str_num.length(), iter);
        Partition_Cases retval = create_cur_partition(str_num, current_offset, it);
        if (retval != P_POSOK)
        {
            if (retval == P_NEGOK && current_offset == 0ul) 
            {
                sign = true;
                continue;
            }
            throw std::invalid_argument("Passed value cannot be converted to Any_Integer Type");
        } else if (current_offset == 0ul) { sign = false; }
        it++;
    } 
}
const Any_Integer::part_num_t Any_Integer::base_pow (dig_count_t dig_count)
{
    part_num_t ret_val = 1ul;
    while (dig_count--) { ret_val *= DECIMAL_BASE; }
    return ret_val;
}
Any_Integer::part_num_t Any_Integer::nine_is_complement (Any_Integer::part_num_t part_val, Any_Integer::part_num_t nines)
{
    return nines - part_val;
}
std::vector<Any_Integer::Partition> Any_Integer::absolute_adder (const std::vector<Any_Integer::Partition>& first_operand, std::vector<Any_Integer::Partition> sec_operand, bool carry)
{
    Any_Integer::offset_t res_size = first_operand.size() > sec_operand.size() ? first_operand.size() : sec_operand.size();
    std::vector<Partition> result(res_size);
    auto res_it = result.begin();
 

    std::copy(first_operand.begin(), first_operand.end(), res_it);
    res_it = result.begin();
    unsigned int tmp_carry = carry;
    for (auto it2 = sec_operand.begin(); it2 != sec_operand.end(); it2++, res_it++)
    {
        res_it->virt_dig_count = res_it->virt_dig_count > it2->virt_dig_count ? res_it->virt_dig_count : it2->virt_dig_count;
        part_num_t base_dig_exp = base_pow(res_it->virt_dig_count);
        if (carry) {it2->part_val = nine_is_complement (it2->part_val, base_dig_exp - 1);}
        res_it->part_val += (it2->part_val + tmp_carry);
        res_it->real_dig_count = dyn_digit_counter(res_it->part_val);
        if (res_it->real_dig_count == PART_DIG_MAXC + 1 || carry)
        {            
            tmp_carry = res_it->part_val / base_dig_exp;
            res_it->part_val %= base_dig_exp;   
            res_it->real_dig_count = dyn_digit_counter(res_it->part_val);
        }
        else { tmp_carry = 0; }
    }
    
    for (; res_it != result.end(); res_it++)  // նայել carry 
    {
        part_num_t base_dig_exp = base_pow(res_it->virt_dig_count);
        part_num_t sec_compl_val = 0;
        if (carry) { sec_compl_val = nine_is_complement (sec_compl_val, base_dig_exp - 1ul); }
        res_it->part_val += sec_compl_val + tmp_carry;
        res_it->real_dig_count = dyn_digit_counter(res_it->part_val);
        if (res_it->real_dig_count == PART_DIG_MAXC + 1 || carry){ 
            tmp_carry = res_it->part_val / base_dig_exp;
            res_it->part_val %= base_dig_exp;   
            res_it->real_dig_count = dyn_digit_counter(res_it->part_val);
        }    
        else
        { tmp_carry = 0; }
    }
    
    (res_it-1)->part_val = tmp_carry;
    (res_it-1)->virt_dig_count = tmp_carry;
    (res_it-1)->real_dig_count = tmp_carry;
    
    return result;
}

bool Any_Integer::second_time_10s_complement ()
{
    auto it = num_container.end() - 1;
    while (it->part_val == 0ul ) { --it; }
    if ((it)->part_val == 1ul) 
    {
        (it)->part_val = 0ul;
        (it)->real_dig_count = 0;
        (it)->virt_dig_count = 0;
        (it -  1)->virt_dig_count = (it - 1)->real_dig_count;
    }
    else 
    {
        bool tmp_carry = true;
        for (auto tmp_it = num_container.begin() ; tmp_it != num_container.end(); tmp_it++)
        {
            part_num_t tmp_base_exp = base_pow(tmp_it->virt_dig_count);
            tmp_it->part_val = nine_is_complement (tmp_it->part_val, tmp_base_exp - 1ul);
            if(tmp_carry){
                tmp_it->part_val += tmp_carry;
                tmp_carry = tmp_it->part_val / tmp_base_exp;
                tmp_it->part_val %= tmp_base_exp;
            }
            tmp_it->real_dig_count = dyn_digit_counter(tmp_it->part_val);
        }
        return true;
    }
    return false;
}
const Any_Integer::dig_count_t Any_Integer::dyn_digit_counter (Any_Integer::part_num_t integer)
{
    dig_count_t ret_count = 0u;
    while (integer)
    {
        ret_count++;
        integer /= DECIMAL_BASE;
    }
    return ret_count;
}
void Any_Integer::resizer()
{
    offset_t count = 0ul;
    auto it = num_container.end() - 1;
    while (it->part_val == 0 && it >= num_container.begin()) 
    {
        it--;
        count++;
    }
    if (it == num_container.begin() && it->part_val == 0ul)
    {
        it->real_dig_count = 0u;
        it->virt_dig_count = 1u;
    }
    else
    {
        it->real_dig_count = dyn_digit_counter(it->part_val);
        it->virt_dig_count = it->real_dig_count;
    }
    it--;
    for (; it >= num_container.begin(); it--)
    {
        it->virt_dig_count = PART_DIG_MAXC;
        it->real_dig_count = dyn_digit_counter(it->part_val);
    }

    if (count == 0ul){
        num_container.resize(num_container.size() + 1);
    }
    else if (count >= MIN_PART_COUNT)
    {
        num_container.resize(num_container.size() + 1 - count);
        num_container.shrink_to_fit();
    }
}
long Any_Integer::compare_sizes(const std::vector<Any_Integer::Partition>& sec_operand)
{
    dig_count_t virtual_size1 = 0u;
    dig_count_t virtual_size2 = 0u;
    if (num_container.size() > sec_operand.size()) {return 1l;}
    else if (num_container.size() < sec_operand.size()) {return -1l;}
    for (auto it = num_container.begin(); it != num_container.end(); it++)
    {
        virtual_size1 += it->virt_dig_count;
    }
    for (auto it = sec_operand.begin(); it != sec_operand.end(); it++)
    {
        virtual_size2 += it->virt_dig_count;
    }
    long tmp = virtual_size1 - virtual_size2;
    if (tmp < 0) { return -1l; }
    else if (tmp > 0) {return 1l;}
    return tmp;
}
long Any_Integer::compare_signes (const Any_Integer& sec_operand)
{
    if (sign == sec_operand.sign) {return 0l;}
    else if (sign == false && sec_operand.sign == true) {return 1l;}
    else { return -1l; }
}
const Any_Integer Any_Integer::compare_parts (const Any_Integer& sec_operand)
{
    return *this - sec_operand;
}
bool Any_Integer::is_zero () const
{
    for (auto it = num_container.begin(); it != num_container.end(); it++)
    {
        if (it->part_val != 0ul) { return false; }
    }
    return true;
}

Any_Integer Any_Integer::operator-(const Any_Integer& op2)
{
    bool operation = !(sign ^ op2.sign);
    bool ret_sign = ((sign || op2.sign) && !(!sign && op2.sign));
    Any_Integer res_obj;
    res_obj.num_container = absolute_adder(num_container, op2.num_container, operation);
    if (operation)
    {
        ret_sign ^= res_obj.second_time_10s_complement();
    }
    res_obj.sign = ret_sign;
    res_obj.resizer();
    return res_obj;
}
Any_Integer Any_Integer::operator+(const Any_Integer& op2)
{
    bool ret_sign = ((sign || op2.sign) && !(!sign && op2.sign));
    bool operation = sign ^ op2.sign;
    Any_Integer res_obj;
    res_obj.num_container = absolute_adder(num_container, op2.num_container, operation);
    if (operation)
    {
        ret_sign ^= res_obj.second_time_10s_complement();
    }
    res_obj.sign = ret_sign;
    res_obj.resizer();
    return res_obj;
}
std::ostream& operator<< (std::ostream& out, const Any_Integer& num)
{
    if (num.is_zero())
    {        
        out << 0;
        return out;
    }
    if (num.sign) {out << '-';}
    for (auto it = num.num_container.end() - 1; it != num.num_container.begin() - 1; it-- )
    {
        Any_Integer::dig_count_t tmp_count = it->virt_dig_count - it->real_dig_count;
        while (tmp_count != 0u)
        {
            out << '0';
            --tmp_count;
        }
        if (it->part_val != 0ul){ out << it->part_val; }
    }
    return out;
}
bool Any_Integer::operator<(const Any_Integer& sec_operand) 
{

    return !((*this == sec_operand) || (*this > sec_operand));
    
}
bool Any_Integer::operator==(const Any_Integer& sec_operand) 
{
    switch (compare_signes(sec_operand))
    {
        case -1l:
        case 1l: return false;
    }
    switch (compare_sizes (sec_operand.num_container))
    {
        case -1l:
        case 1l: return false;
    }
    return compare_parts(sec_operand).is_zero();
}
bool Any_Integer::operator>(const Any_Integer& sec_operand) 
{
    if (*this == sec_operand)
    {
        return false;
    }
    
    switch (compare_signes(sec_operand))
    {
        case -1l: return false;
        case 1l: return true;
    }
    switch (compare_sizes (sec_operand.num_container))
    {
        case -1l: return false;
        case 1l: return true;
    }
    Any_Integer tmp = compare_parts(sec_operand);
    return tmp.is_zero() ? false : !tmp.sign;
}
const Any_Integer& Any_Integer::operator=(const std::string& str_num)
{
    num_container.clear();
    num_container.resize((str_num.length() / PART_DIG_MAXC) + MIN_PART_COUNT);
    num_container.shrink_to_fit();
    partitioning(str_num);
    return *this;
}
const Any_Integer& Any_Integer::operator=(const long num)
{
    num_container.clear();
    num_container.resize(MIN_PART_COUNT);
    num_container.shrink_to_fit();
    sign = (num < 0);
    auto it = num_container.begin();
    it->part_val = sign ? -num : num;
    long tmp = it->part_val;
    while (tmp)
    {
        ++it->real_dig_count;
        ++it->virt_dig_count;
        tmp /= DECIMAL_BASE;
    }
    return *this;
}
const Any_Integer& Any_Integer::operator=(const Any_Integer& other)
{
    if (this == &other) {return other;}
    num_container = other.num_container;
    sign = other.sign;   
    return *this; 
}


template <unsigned long max_num>
static const unsigned int digit_counter ()
{
    return digit_counter <max_num/DECIMAL_BASE>() + 1;
}
template <>
const unsigned int digit_counter<0> ()
{
    return 0;
}



