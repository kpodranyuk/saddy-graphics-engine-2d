/*! \file scenenodesfontsetter.h
    

    Describes a setter for font property of scene node
 */
#pragma once
#include "scenenodessetter.h"

#include "../../history/label/changefontname.h"

namespace scripting
{

namespace scenenodes
{

/*! A setter for font property
 */
class FontSetter: public scripting::scenenodes::Setter<sad::String, history::label::ChangeFontName>
{
public:
    /*! Creates new setter for specified area
        \param e
     */
    FontSetter(QScriptEngine* e);
    /*! Can be inherited
     */
    virtual ~FontSetter();
    /*! Determines, whether it can be called with this context
        Additionally checks, whether font exists
        \param[in] ctx context
        \return whether it could be called, or error
     */
    virtual scripting::MatchResult canBeCalled(QScriptContext* ctx);
};

}

}
