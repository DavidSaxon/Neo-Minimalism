/**********************************************\
| Execptions relating to Omicron's main engine |
|                                              |
| @author David Saxon                          |
\**********************************************/

#ifndef OMICRON_EXCEPTIONS_ENGINEEXCEPTION_H_
#   define OMICRON_EXCEPTIONS_ENGINEEXCEPTION_H_

#include "src/Utilities/exceptions/Exception.hpp"

namespace omiEx {

/*~Base class for Engine related excepetions
^ABC*/
class EngineException : public util::ex::Exception {
};

/*~Warns that the engine has not yet been initialised*/
class UnInitEngineException : public EngineException {
public:

    //CONSTRUCTOR
    /*!Construct a new un-initialised engine exception
    ^INL
    @errorMessage the error message of the exception*/
    UnInitEngineException(const std::string& errorMessage) {

        errMsg = errorMessage;
    }

private:

    //PRIVATE MEMBER FUNCTIONS
    /*!^INL
    @return the name of this exception*/
    std::string name() const {

        return "UN-INITIALISED ENGINE EXCEPTION";
    }
};

} //omiEx

#endif