/****************************\
| Exceptions relating to SDL |
|                            |
| @author David Saxon        |
\****************************/

#ifndef OMICRON_EXCEPTIONS_SDLEXCEPTION_H_
#   define OMICRON_EXCEPTIONS_SDLEXCEPTION_H_

#include "src/Utilities/exceptions/Exception.hpp"

namespace omiEx {

/*~Base class for SDL related exceptions
^ABC*/
class SDLException : public util::ex::Exception {
};

/*~Warns that SDL initialisation has failed*/
class SDLInitException : public SDLException {
public:

    //CONSTRUCTOR
    /*!Construct a new SDL init Exception
    ^INL
    @errorMessage the error message of the exception*/
    SDLInitException(const std::string& errorMessage) {

        errMsg = errorMessage;
    }

private:

    //PRIVATE MEMBER FUNCTIONS
    /*!^INL
    @return the name of this exception*/
    std::string name() const {

        return "SDL INITIALISATION EXCEPTION";
    }
};

/*~Warns the an SDL window has failed to open*/
class SDLWindowException : public SDLException {
public:

    //CONSTRUCTOR
    /*!Construct a new SDL window exception
    ^INL
    @errorMessage the error message of the exception*/
    SDLWindowException(const std::string& errorMessage) {

        errMsg = errorMessage;
    }

private:

    //PRIVATE MEMBER FUNCTIONS
    /*!^INL
    @return the name of this exception*/
    std::string name() const {

        return "SDL WINDOW EXCEPTION";
    }
};

} //omiEx

#endif