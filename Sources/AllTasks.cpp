#include "../Headers/AllTasks.h"

#include <limits>
#include <cmath>

inline void AllTasks::checkParam(int paramCount, int expectedParamCount, errorCode_t &flag)
{
    if (paramCount != expectedParamCount)
    {
        flag = WRONG_AMOUNT_PARAM;
    }
    else
    {
        flag = NO_ERR;
    }
}
AllTasks::AllTasks(singleTask &incommingTask) : parameters(incommingTask.parameters), paramCount(incommingTask.paramCount), taskID(incommingTask.taskID)
{
}
errorCode_t AllTasks::executeTask(int &retResult)
{
    errorCode_t retError = NO_ERR;
    switch (taskID)
    {
    case SUM:
        computeSUM(retResult);
        break;
    case MULTIPLICATION:
        computeMULTIPLICATION(retResult);
        break;
    case XOR:
        retError = computeXOR(retResult);
        break;
    case POWER:
        retError = computePOWER(retResult);
        break;
    case FACTORIAL:
        retError = computeFACTORIAL(retResult);
        break;
    case FIBONACCI:
        retError = computeFIBONACCI(retResult);
        break;
    case GCD:
        retError = computeGCD(retResult);
        break;
    case NTH_PRIME_NUMBER:
        retError = computeNTH_PRIME_NUMBER(retResult);
        break;
    case HIGHEST_PRIME_NUMBER_LT_PARAM:
        retError = computeHIGHEST_PRIME_NUMBER_LT_PARAM(retResult);
        break;
    case DISTANCE_AXIS:
        retError = computeDISTANCE_AXIS(retResult);
        break;
    case COUNT_BINARY_ONES:
        retError = computeCOUNT_BINARY_ONES(retResult);
        break;
    case CHECKSUM:
        retError = computeCHECKSUM(retResult);
        break;
    default:
        retError = INVALID_TASK_ID;
        break;
    }
    return retError;
}

void AllTasks::computeSUM(int &retResult)
{
    int sum = 0;
    for (int i = 0; i < paramCount; ++i)
    {
        sum += parameters[i];
    }
    retResult = sum;
}

void AllTasks::computeMULTIPLICATION(int &retResult)
{
    int product = 0;
    if (paramCount > 0)
    {
        product = parameters[0];
        for (int i = 1; i < paramCount; ++i)
        {
            product *= parameters[i];
        }
    }
    retResult = product;
}

errorCode_t AllTasks::computeXOR(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 2, retError);
    if (NO_ERR == retError)
    {
        if ((parameters[0] < 0) || (parameters[1]) < 0)
        {
            retError = INVALID_PARAM;
        }
    }
    if (NO_ERR == retError)
    {
        retResult = static_cast<int>(parameters[0] ^ parameters[1]);
    }
    return retError;
}

errorCode_t AllTasks::computePOWER(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 2, retError);
    if (NO_ERR == retError)
    {
        if ((parameters[0] < 0) || (parameters[1]) < 0)
        {
            retError = INVALID_PARAM;
        }
    }
    if (NO_ERR == retError) //Exponentiation by squaring algorithm
    {
        retResult = 1;
        while (true)
        {
            if (parameters[1] & 1)
            {
                retResult *= parameters[0];
            }
            parameters[1] >>= 1;
            if (!parameters[1])
            {
                break;
            }
            parameters[0] *= parameters[0];
        }
    }
    return retError;
}

errorCode_t AllTasks::computeFACTORIAL(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 1, retError);
    if (NO_ERR == retError)
    {
        if (parameters[0] < 0)
        {
            retError = INVALID_PARAM;
        }
    }
    if (NO_ERR == retError)
    {
        retResult = 1;
        for (int i = 1; i <= parameters[0]; ++i)
        {
            retResult *= i;
        }
    }
    return retError;
}

errorCode_t AllTasks::computeFIBONACCI(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 1, retError);
    if (NO_ERR == retError)
    {
        if (parameters[0] < 0)
        {
            retError = INVALID_PARAM;
        }
    }
    if (NO_ERR == retError)
    {
        if (parameters[0] == 0)
        {
            retResult = 0;
        }
        else
        {
            int val0 = 0;
            int val1 = 1;
            for (int i = 1; i < parameters[0]; ++i)
            {
                int temp = val0;
                val0 = val1;
                val1 = temp + val1;
            }
            retResult = val1;
        }
    }
    return retError;
}

errorCode_t AllTasks::computeGCD(int &retResult)
{
    errorCode_t retError = NO_ERR;
    if (paramCount < 2 || paramCount > 4)
    {
        retError = WRONG_AMOUNT_PARAM;
    }
    else
    {
        for (int i = 0; i < paramCount; ++i)
        {
            if (parameters[i] < 0)
            {
                retError = INVALID_PARAM;
            }
        }
    }
    if (NO_ERR == retError)
    {
        retResult = 0;
        int minVal = parameters[0];
        for (int i = 0; i < paramCount; ++i)
        {
            if (minVal > parameters[i])
            {
                minVal = parameters[i];
            }
        }
        for (int i = 1; i <= minVal; ++i)
        {
            bool isDivisor = true;
            for (int j = 0; j < paramCount; ++j)
            {
                if (parameters[j] % i != 0)
                {
                    isDivisor = false;
                    break;
                }
            }
            if (true == isDivisor)
            {
                retResult = i;
            }
        }
    }
    return retError;
}

errorCode_t AllTasks::computeNTH_PRIME_NUMBER(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 1, retError);
    if (NO_ERR == retError)
    {
        if (parameters[0] < 0)
        {
            retError = INVALID_PARAM;
        }
    }
    if (NO_ERR == retError)
    {
        {
            if (1 == parameters[0])
            {
                retResult = 2;
            }
            else
            {
                int count = 1;                                                  //temp value to count which prime number we are at
                for (int i = 1; i < std::numeric_limits<int>::max(); i = i + 2) //loop till max integer is system is reached
                {
                    if (true == isPrimeNumber(i))
                    {
                        ++count;
                    }
                    if (count == parameters[0]) //if nth prime number is reached return result and break loop
                    {
                        retResult = i;
                        break;
                    }
                }
            }
        }
    }
    return retError;
}

errorCode_t AllTasks::computeHIGHEST_PRIME_NUMBER_LT_PARAM(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 1, retError);
    if (NO_ERR == retError)
    {
        if (parameters[0] <= 2)
        {
            retError = INVALID_PARAM;
        }
        else if (3 == parameters[0])
        {
            retResult = parameters[0];
        }
        else
        {
            for (int i = parameters[0] - 1; i >= 3; --i)
            {
                if (true == isPrimeNumber(i))
                {
                    retResult = i;
                    break;
                }
            }
        }
    }
    return retError;
}

errorCode_t AllTasks::computeDISTANCE_AXIS(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 4, retError);

    if (NO_ERR == retError)
    {
        retResult = abs(parameters[0] - parameters[2]) + abs(parameters[1] - parameters[3]);
    }
    return retError;
}

errorCode_t AllTasks::computeCOUNT_BINARY_ONES(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 1, retError);
    if (NO_ERR == retError)
    {
        if (parameters[0] < 0)
        {
            retError = INVALID_PARAM;
        }
    }
    if (NO_ERR == retError)
    {
        int count = 0;
        for (unsigned int i = 0; i < sizeof(int) * 8; ++i)
        {
            if ((parameters[0] >> i) & 1)
            {
                ++count;
            }
        }
        retResult = count;
    }
    return retError;
}

errorCode_t AllTasks::computeCHECKSUM(int &retResult)
{
    errorCode_t retError = NO_ERR;
    checkParam(paramCount, 1, retError);
    if (parameters[0] < 0 && (NO_ERR == retError))
    {
        retError = INVALID_PARAM;
    }
    if (NO_ERR == retError)
    {
        int mask = 0x555555;
        retResult = parameters[0] ^ mask;
    }
    return retError;
}

bool AllTasks::isPrimeNumber(int &val)
{
    int count = 0;
    for (int i = 1; i <= val; ++i)
    {
        if (val % i == 0)
        {
            count++;
        }
        if (count > 2)
        {
            return false;
        }
    }
    if (count == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}