#ifndef COMMON_H
#define COMMON_H
/**
 * @brief Default config file path 
 */
#define CONFIG_FILE_PATH "./Configuration/config.txt"

#include <vector>

/**
 * @brief Macro that disallows to create unused construtors
 */
#define DISABLE_UNUSED_CONSTUCTORS(className)         \
    className(const className &) = delete;            \
    className &operator=(const className &) = delete; \
    className(className &&) = delete;                 \
    className &operator=(className &&) = delete

/**
 * @brief Enum describing all possible operations
 * */
enum operations_t
{
    START = 0,
    SUM,                           //any number of input args
    MULTIPLICATION,                //any number of input args
    XOR,                           //2 parameters
    POWER,                         //2 param[in], param1 ^ param2
    FACTORIAL,                     //1 param
    FIBONACCI,                     //1 param
    GCD,                           //the greatest common divisor
    NTH_PRIME_NUMBER,              //1 param, find first prime number
    HIGHEST_PRIME_NUMBER_LT_PARAM, //the highest pm lower than given parameter
    DISTANCE_AXIS,                 //distance between two points on coordinate axis, 4 param in (x1, y1, x2, y2)
    COUNT_BINARY_ONES,             //count ones in binary representation of given parameter
    CHECKSUM                       //checksum of given parameter
};

/**
 * @brief Enum with error codes
 * */
enum errorCode_t
{
    NO_ERR = 0,          //no error occured
    INVALID_PARAM,       //invalid parameter
    INVALID_TASK_ID,     //there is no task with given ID
    WRONG_AMOUNT_PARAM,  //wrong amount of parameters
    FILE_READ_ERR,       //error while opening file
    FILE_SAVE_ERR,       //error while saving file
    CONFIG_FILE_READ_ERR //error while opening config file
};

/**
 * struct holding all data which are used to compute and print task results
 * */
struct singleTask // struct containing everything that is needed by task, and its result after computing
{
    operations_t taskID;
    std::vector<int> parameters;
    int paramCount;
    int result;
    double timeMS;
    bool errorFlag;
};

#endif //COMMON_H