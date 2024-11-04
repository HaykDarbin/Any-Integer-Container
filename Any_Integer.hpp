#ifndef ANY_INTEGER_DEF
#define ANY_INTEGER_DEF
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class Any_Integer 
{
public:
    using part_num_t = unsigned long; 
    using offset_t = unsigned long; 
    using dig_count_t = unsigned int; 
private:   
    enum Partition_Cases {P_POSOK, P_WRONG, P_NEGOK};
    struct Partition 
    {
        part_num_t part_val;
        dig_count_t real_dig_count;
        dig_count_t virt_dig_count;
    };
public:
    Any_Integer() = default;
    Any_Integer(const Any_Integer&) = default;
    Any_Integer(Any_Integer&&) = default;
    Any_Integer(const std::string&);
    Any_Integer(const long);
    //const Any_Integer& operator=(Any_Integer&&);
    const Any_Integer& operator=(const Any_Integer&);
    const Any_Integer& operator=(const std::string&);
    const Any_Integer& operator=(const long);
    Any_Integer operator+(const Any_Integer&);
    Any_Integer operator-(const Any_Integer&);
    friend std::ostream& operator<< (std::ostream& out, const Any_Integer& num);
    bool operator<(const Any_Integer&);
    bool operator==(const Any_Integer&);
    bool operator>(const Any_Integer&);

private:
    inline size_t counting_num_offset (const size_t num_dig_c, const size_t iteration);
    Partition_Cases create_cur_partition (const std::string& str_num, size_t cur_off, std::vector<Partition>::iterator);
    inline bool is_digit(std::string::const_iterator character);
    void partitioning (const std::string& str_num);
    std::vector<Partition> absolute_adder (const std::vector<Partition>& first_operand, std::vector<Partition> sec_operand, bool carry);
    part_num_t nine_is_complement (part_num_t num, part_num_t nines);
    const part_num_t base_pow (dig_count_t dig_count);
    const dig_count_t dyn_digit_counter (part_num_t);
    bool second_time_10s_complement ();
    void resizer ();
    bool is_zero () const;
    long compare_sizes(const std::vector<Partition>& sec_operand);
    long compare_signes (const Any_Integer& sec_operand);
    const Any_Integer compare_parts (const Any_Integer& sec_operand);

    std::vector<Partition> num_container;
    bool sign;
};


#endif