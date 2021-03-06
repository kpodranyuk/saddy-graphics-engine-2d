#include "instancesanimationdbsetter.h"

#include <QRadioButton>

#include <db/dbdatabase.h>

#include "../scripting.h"
#include "../queryobject.h"
#include "../tovalue.h"

#include "../../core/editor.h"

#include "../../gui/actions/actions.h"
#include "../../gui/actions/animationinstanceactions.h"

#include "../../gui/uiblocks/uiblocks.h"
#include "../../gui/uiblocks/uianimationinstanceblock.h"


#include "../../history/instances/instanceschangeanimation.h"

Q_DECLARE_METATYPE(sad::animations::Instance*); //-V566

// ===================== scripting::instances::AnimationDBSetter::IsAnimation =====================

scripting::instances::AnimationDBSetter::IsAnimation::IsAnimation()
{
    
}

scripting::instances::AnimationDBSetter::IsAnimation::~IsAnimation()
{
    
}

sad::Maybe<QString> scripting::instances::AnimationDBSetter::IsAnimation::check(const unsigned long long& a)
{
    sad::Maybe<QString> result;
    if (a != 0)
    {
        bool valid = false;
        sad::db::Object* r = sad::Renderer::ref()->database("")->queryByMajorId(a);
        if (r)
        {
            valid = r->isInstanceOf("sad::animations::Animation");
        }
        if (!valid)
        {
            QString name = QString::number(a);
            result.setValue(name + " : is not a reference to an animation from database");
        }
    }
    return result;
}

// ===================== scripting::instances::AnimationDBSetter::StringToAnimation =====================

scripting::instances::AnimationDBSetter::StringToAnimation::StringToAnimation()
{
    
}

scripting::instances::AnimationDBSetter::StringToAnimation::~StringToAnimation()
{

}

sad::Maybe<unsigned long long> scripting::instances::AnimationDBSetter::StringToAnimation::toValue(const QScriptValue& v)
{
    sad::Maybe<unsigned long long> result;
    sad::Maybe<sad::animations::Animation*> a  = scripting::query<sad::animations::Animation*>(v);
    if (a.exists())
    {
        result.setValue(a.value()->MajorId);
    }
    else
    {
        sad::Maybe<sad::String> maybename  = scripting::ToValue<sad::String>::perform(v);
        if (maybename.exists())
        {
            if (maybename.value().length() == 0)
            {
                result.setValue(0);				
            }
        }
    }
    return result;
}

// ===================== scripting::instances::AnimationDBSetter =====================

scripting::instances::AnimationDBSetter::AnimationDBSetter(
        QScriptEngine* e
) : scripting::AbstractSetter<sad::animations::Instance*, unsigned long long>(e, "animationmajorid")
{
    m_matched_property_names << "animationmajorid";
    this->addCondition(new scripting::instances::AnimationDBSetter::IsAnimation());
    this->addConverter(new scripting::instances::AnimationDBSetter::StringToAnimation());
}

scripting::instances::AnimationDBSetter::~AnimationDBSetter()
{
        
}

void scripting::instances::AnimationDBSetter::setProperty(
    sad::animations::Instance* obj, 
    const sad::String& propertyname, 
    unsigned long long oldid,  
    unsigned long long newid
)
{
    QScriptValue main = this->engine()->globalObject().property("---");
    scripting::Scripting* e = static_cast<scripting::Scripting*>(main.toQObject());
    core::Editor* editor =  e->editor();
    
    gui::actions::AnimationInstanceActions* ai_actions = editor->actions()->instanceActions();
    gui::uiblocks::UIAnimationInstanceBlock* ai_blk = editor->uiBlocks()->uiAnimationInstanceBlock();

    int row = ai_actions->findInList<sad::animations::Instance*>(ai_blk->lstAnimationInstances, obj);
    sad::String name = obj->getProperty<sad::String>("animation").value();
    if (row > - 1)
    {
        history::Command* c  = NULL;
        QRadioButton* treebutton = ai_blk->rbAnimationInstanceFromTree;
        QRadioButton* dbbutton = ai_blk->rbAnimationInstanceFromDatabase;
        if (newid > 0)
        {
            if (oldid > 0)
            {
                c = new history::instances::ChangeAnimation(
                    obj,
                    oldid,
                    newid
                );
            }
            else
            {
                c = new history::instances::ChangeAnimation(
                    obj,
                    dbbutton,
                    treebutton,
                    name,
                    oldid,
                    name,
                    newid
                );
            }
            
        }
        else
        {
            c = new history::instances::ChangeAnimation(
                    obj,
                    treebutton,
                    dbbutton,
                    name,
                    oldid,
                    name,
                    newid
                );
        }
        editor->currentBatchCommand()->add(c);
        c->commit(editor);
    }
}
