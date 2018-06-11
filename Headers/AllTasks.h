#ifndef ALLTASKS_H
#define ALLTASKS_H

#include "Common.h"

class AllTasks
{
public:
  /**
  * @brief Deconstructor
  * */
  ~AllTasks() {}
  /**
   * @brief Overloaded constructor
   * param[in][out] singleTask struct - object to operate on
   */
  explicit AllTasks(singleTask &incommingTask);
  /**
   * @brief function that determines which task to start, based on taskID from singleTask struct
   * param[in][out] reference to value which holds result
   * return Error code specified in Common.h file
  * */
  errorCode_t executeTask(int &retResult); // function executes tasks, used by extractTask(const string&) function

private:
  /**
   * @brief inline function which checks parameters count
   * @param[in] number of parameters to check
   * @param[in] expected number of parameters
   * @param[out] error flag
   * return void
   * */
  inline void checkParam(int paramCount, int expectedParamCount, errorCode_t &flag);
  /**
   * @brief vector of paramaters extracted from single line of txt file
   * */
  std::vector<int> parameters;
  /**
   * @brief number of parameters 
   * */
  int paramCount;
  /**
   * @brief task ID extracted from single line of txt file
   * */
  operations_t taskID;
  /**
   * \see {macro0}
   * */
  DISABLE_UNUSED_CONSTUCTORS(AllTasks);

  /**
   * @brief Computes sum of given parameters. This function should not return any error, unless completely corrupted arguments are used
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeSUM(int &retResult); //this function should not return any error, unless completely corrupted arguments are used
  /**
   * @brief Computes multiplication of given parameters. this function should not return any error, unless completely corrupted arguments are used
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeMULTIPLICATION(int &retResult); //this function should not return any error, unless completely corrupted arguments are used
  /**
   * @brief Computes XOR. Two paramaters expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeXOR(int &retResult);
  /**
   * @brief Computes Power. Two paramaters expected
   * @brief Exponentiation by squaring is used in this function. This algorithm is more effective than function pow() from cmath library
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computePOWER(int &retResult);
  /**
   * @brief Computes Factorial. One paramater expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeFACTORIAL(int &retResult);
  /**
   * @brief Computes NTH Fibonacci number. One paramater expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeFIBONACCI(int &retResult);
  /**
   * @brief Computes Greatest Common Divisor. Two, three or four paramaters expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeGCD(int &retResult);
  /**
   * @brief Computes NTH Prime number. One paramater expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeNTH_PRIME_NUMBER(int &retResult);
  /**
   * @brief Computes The Highest prime number lower than given paramater. One paramater expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeHIGHEST_PRIME_NUMBER_LT_PARAM(int &retResult);
  /**
   * @brief Computes distance between two points at the axis of cartesian coordinate system. Four paramaters expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeDISTANCE_AXIS(int &retResult);
  /**
   * @brief Computes amount of '1' in binary representation of given number. One paramater expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeCOUNT_BINARY_ONES(int &retResult);
  /**
   * @brief Computes Checksum of given number. One paramater expected
   * param[in][out] reference to value which holds result
   * @return Error code specified in Common.h file
   * */
  errorCode_t computeCHECKSUM(int &retResult);

  /**
   * @brief Additional function which checks if given integer is prime number, used by computeNTH_PRIME_NUMBER and computeHIGHEST_PRIME_NUMBER_LT_PARAM functions
   * param[in] value to check
   * @return boolean value - true or false
   * */
  bool isPrimeNumber(int &val);
};

#endif //ALLTASKS_H