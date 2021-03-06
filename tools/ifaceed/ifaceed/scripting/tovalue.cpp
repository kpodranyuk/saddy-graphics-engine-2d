#include "tovalue.h"
#include "queryobject.h" 


#include "point2d.h"
#include "point2i.h"
#include "point3d.h"
#include "point3i.h"
#include "rect2d.h"
#include "rect2i.h"
#include "size2d.h"
#include "size2i.h"
#include "color.h"
#include "acolor.h"

#include "ways/wayspointref.h"

#include "dialogues/dialoguesphraseref.h"

#include <QVariant>
#include <QScriptValueIterator>

#include <scene.h>
#include <label.h>
#include <sprite2d.h>

#include <db/custom/customobject.h>

#include <p2d/app/way.h>

#include <dialogue/dialogue.h>
#include <dialogue/phrase.h>

#include <animations/animationsblinking.h>
#include <animations/animationscamerashaking.h>
#include <animations/animationscamerarotation.h>
#include <animations/animationscolor.h>
#include <animations/animationsfontlist.h>
#include <animations/animationsfontsize.h>
#include <animations/animationsoptionlist.h>
#include <animations/animationsparallel.h>
#include <animations/animationsresize.h>
#include <animations/animationsrotate.h>
#include <animations/animationssimplemovement.h>
#include <animations/animationssequential.h>
#include <animations/animationstexturecoordinateslist.h>
#include <animations/animationstexturecoordinatescontinuous.h>
#include <animations/animationstyping.h>
#include <animations/animationswaymoving.h>

#include <animations/animationsinstance.h>
#include <animations/animationswayinstance.h>

#include <animations/animationsgroup.h>

#include "../qstdstring.h"

Q_DECLARE_METATYPE(scripting::ways::PointRef*) //-V566
Q_DECLARE_METATYPE(sad::Color)
Q_DECLARE_METATYPE(sad::AColor)
Q_DECLARE_METATYPE(sad::Point2D)
Q_DECLARE_METATYPE(sad::Point2I)
Q_DECLARE_METATYPE(sad::Point3D)
Q_DECLARE_METATYPE(sad::Point3I)
Q_DECLARE_METATYPE(sad::Size2D)
Q_DECLARE_METATYPE(sad::Size2I)
Q_DECLARE_METATYPE(sad::Rect2D)
Q_DECLARE_METATYPE(sad::Rect2I)
Q_DECLARE_METATYPE(sad::String)
Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(sad::dialogue::Phrase)

sad::Maybe<QScriptValue>
scripting::ToValue<QScriptValue>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<QScriptValue> result;
    result.setValue(v);
    return result;
}

sad::Maybe<double>
scripting::ToValue<double>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<double> result;
    if (v.isNumber())
    {
        result.setValue(v.toNumber());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<double>())
        {
            result.setValue(var.value<double>());
        }
    }
    return result;
}

sad::Maybe<float>
scripting::ToValue<float>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<float> result;
    if (v.isNumber())
    {
        result.setValue(v.toNumber());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<float>())
        {
            result.setValue(var.value<float>());
        }
    }
    return result;
}

sad::Maybe<int>
scripting::ToValue<int>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<int> result;
    if (v.isNumber())
    {
        result.setValue(v.toInt32());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<int>())
        {
            result.setValue(var.value<int>());
        }
    }
    return result;
}

sad::Maybe<long>
scripting::ToValue<long>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<long> result;
    if (v.isNumber())
    {
        result.setValue(v.toNumber());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<long>())
        {
            result.setValue(var.value<long>());
        }
    }
    return result;
}

sad::Maybe<long long>
scripting::ToValue<long long>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<long long> result;
    if (v.isNumber())
    {
        result.setValue(v.toNumber());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<long long>())
        {
            result.setValue(var.value<long long>());
        }
    }
    return result;
}

sad::Maybe<sad::AColor>
scripting::ToValue<sad::AColor>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::AColor> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Color* oo = qobject_cast<scripting::Color*>(o);
        if (oo)
        {
            sad::Color clr = oo->toColor();
            sad::AColor aclr(clr.r(), clr.g(), clr.b(), 0);
            result.setValue(aclr);
        }
        scripting::AColor* ooo = qobject_cast<scripting::AColor*>(o);
        if (ooo)
        {
            result.setValue(ooo->toColor());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::AColor>())
            {
                result.setValue(var.value<sad::AColor>());
            }
            if (var.canConvert<sad::Color>())
            {
                sad::Color clr = var.value<sad::Color>();
                sad::AColor aclr(clr.r(), clr.g(), clr.b(), 0);
                result.setValue(aclr);
            }
        }
    }
    return result;
}

sad::Maybe<sad::Color>
scripting::ToValue<sad::Color>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Color> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Color* oo = qobject_cast<scripting::Color*>(o);
        if (oo)
        {
            result.setValue(oo->toColor());
        }
        scripting::AColor* ooo = qobject_cast<scripting::AColor*>(o);
        if (ooo)
        {
            result.setValue(ooo->toColor());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Color>())
            {
                result.setValue(var.value<sad::Color>());
            }
            else
            {
                if (var.canConvert<sad::AColor>())
                {
                    sad::AColor color = var.value<sad::AColor>();
                    sad::Color c(color.r(), color.g(), color.b());
                    result.setValue(c);
                }
            }
        }
    }
    return result;
}

sad::Maybe<sad::Point2D>
scripting::ToValue<sad::Point2D>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Point2D> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Point2D* oo = qobject_cast<scripting::Point2D*>(o);
        if (oo)
        {
            result.setValue(oo->toPoint());
        }
        else 
        {
            scripting::ways::PointRef* pr = qobject_cast<scripting::ways::PointRef*>(o);
            if (pr)
            {
                result.setValue(pr->toPoint());
            }
            else
            {
                scripting::Point3D* ooo = qobject_cast<scripting::Point3D*>(o);
                if (ooo)
                {
                    result.setValue(ooo->toPoint());
                }
            }
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Point2D>())
            {
                result.setValue(var.value<sad::Point2D>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::Point2I>
scripting::ToValue<sad::Point2I>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Point2I> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Point2I* oo = qobject_cast<scripting::Point2I*>(o);
        if (oo)
        {
            result.setValue(oo->toPoint());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Point2I>())
            {
                result.setValue(var.value<sad::Point2I>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::Point3D>
scripting::ToValue<sad::Point3D>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Point3D> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Point3D* oo = qobject_cast<scripting::Point3D*>(o);
        if (oo)
        {
            result.setValue(oo->toPoint());
        } 
        else 
        {
            scripting::Point2D* ooo = qobject_cast<scripting::Point2D*>(o);
            if (ooo)
            {
                result.setValue(ooo->toPoint());
            }
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Point3D>())
            {
                result.setValue(var.value<sad::Point3D>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::Point3I>
scripting::ToValue<sad::Point3I>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Point3I> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Point3I* oo = qobject_cast<scripting::Point3I*>(o);
        if (oo)
        {
            result.setValue(oo->toPoint());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Point3I>())
            {
                result.setValue(var.value<sad::Point3I>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::Size2D>
scripting::ToValue<sad::Size2D>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Size2D> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Size2D* oo = qobject_cast<scripting::Size2D*>(o);
        if (oo)
        {
            result.setValue(oo->toSize());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Size2D>())
            {
                result.setValue(var.value<sad::Size2D>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::Size2I>
scripting::ToValue<sad::Size2I>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Size2I> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Size2I* oo = qobject_cast<scripting::Size2I*>(o);
        if (oo)
        {
            result.setValue(oo->toSize());
        }
    } 
    else 
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Size2I>())
            {
                result.setValue(var.value<sad::Size2I>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::Rect2D>
scripting::ToValue<sad::Rect2D>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Rect2D> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Rect2D* oo = qobject_cast<scripting::Rect2D*>(o);
        if (oo)
        {
            result.setValue(oo->toRect());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Rect2D>())
            {
                result.setValue(var.value<sad::Rect2D>());
            }
        }
    }
    return result;
}


sad::Maybe<sad::Rect2I>
scripting::ToValue<sad::Rect2I>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::Rect2I> result;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::Rect2I* oo = qobject_cast<scripting::Rect2I*>(o);
        if (oo)
        {
            result.setValue(oo->toRect());
        }
    } 
    else
    {
        if (v.isVariant())
        {
            QVariant var = v.toVariant();
            if (var.canConvert<sad::Rect2I>())
            {
                result.setValue(var.value<sad::Rect2I>());
            }
        }
    }
    return result;
}

sad::Maybe<sad::String>
scripting::ToValue<sad::String>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::String> result;
    if (v.isString())
    {
        result.setValue(Q2STDSTRING(v.toString()));
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<sad::String>())
        {
            result.setValue(var.value<sad::String>());
        }
    }
    return result;
}

sad::Maybe<std::string>
scripting::ToValue<std::string>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<std::string> result;
    if (v.isString())
    {
        result.setValue(Q2STDSTRING(v.toString()));
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<std::string>())
        {
            result.setValue(var.value<std::string>());
        }
    }
    return result;
}

sad::Maybe<QString>
scripting::ToValue<QString>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<QString> result;
    if (v.isString())
    {
        result.setValue(v.toString());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<QString>())
        {
            result.setValue(var.value<QString>());
        }
    }
    return result;
}

sad::Maybe<short>
scripting::ToValue<short>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<short> result;
    if (v.isNumber())
    {
        result.setValue(v.toInt32());
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<short>())
        {
            result.setValue(var.value<short>());
        }
    }
    return result;
}

sad::Maybe<bool>
scripting::ToValue<bool>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<bool> result;
    if (v.isBool())
    {
        result.setValue(v.toBool());
    }
    if (v.isNumber())
    {
        result.setValue(v.toInt32() != 0);
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<bool>())
        {
            result.setValue(var.value<bool>());
        }
    }
    return result;
}

sad::Maybe<char>
scripting::ToValue<char>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<char> result;
    if (v.isNumber())
    {
        qint32 i = v.toInt32();
        if (i>=-128 && i<=127)
        {
            result.setValue(i);
        }
    }
    if (v.isString())
    {
        QString i = v.toString();
        if (i.length())
        {
            result.setValue(Q2STDSTRING(i)[0]);
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<char>())
        {
            result.setValue(var.value<char>());
        }
    }
    return result;
}

sad::Maybe<signed char>
scripting::ToValue<signed char>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<signed char> result;
    if (v.isNumber())
    {
        qint32 i = v.toInt32();
        if (i>=-128 && i<=127)
        {
            result.setValue(i);
        }
    }
    if (v.isString())
    {
        QString i = v.toString();
        if (i.length())
        {
            result.setValue(Q2STDSTRING(i)[0]);
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<signed char>())
        {
            result.setValue(var.value<signed char>());
        }
    }
    return result;
}

sad::Maybe<unsigned char>
scripting::ToValue<unsigned char>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<unsigned char> result;
    if (v.isNumber())
    {
        qint32 i = v.toInt32();
        if (i>=0 && i<=255)
        {
            result.setValue(i);
        }
    }
    if (v.isString())
    {
        QString i = v.toString();
        if (i.length())
        {
            result.setValue(static_cast<unsigned char>(Q2STDSTRING(i)[0]));
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<unsigned char>())
        {
            result.setValue(var.value<unsigned char>());
        }
    }
    return result;
}

sad::Maybe<unsigned int>
scripting::ToValue<unsigned int>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<unsigned  int> result;
    if (v.isNumber())
    {
        qint32 k = v.toInt32();
        if (k >= 0)
        {
            result.setValue(k);
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<unsigned int>())
        {
            result.setValue(var.value<unsigned int>());
        }
    }
    return result;
}

sad::Maybe<unsigned long>
scripting::ToValue<unsigned long>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<unsigned  long> result;
    if (v.isNumber())
    {
        qint32 k = v.toInt32();
        if (k >= 0)
        {
            result.setValue(k);
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<unsigned long>())
        {
            result.setValue(var.value<unsigned long>());
        }
    }
    return result;
}

sad::Maybe<unsigned long long>
scripting::ToValue<unsigned long long>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<unsigned long long> result;
    if (v.isNumber())
    {
        qint32 k = v.toInt32();
        if (k >= 0)
        {
            result.setValue(k);
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<unsigned long long>())
        {
            result.setValue(var.value<unsigned long long>());
        }
    }
    return result;
}


sad::Maybe<unsigned short>
scripting::ToValue<unsigned short>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<unsigned short> result;
    if (v.isNumber())
    {
        qint32 k = v.toInt32();
        if (k >= 0)
        {
            result.setValue(k);
        }
    }
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<unsigned short>())
        {
            result.setValue(var.value<unsigned short>());
        }
    }
    return result;
}

#define DEFINE_AS_QUERY_OBJECT_FROM_DATABASE( TYPE )   \
sad::Maybe< TYPE >                                          \
scripting::ToValue< TYPE >::perform(                        \
        const QScriptValue& v                               \
)                                                           \
{                                                           \
    return scripting::query< TYPE >(v);                     \
}

DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::db::Object*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::Scene*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::SceneNode*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::Label*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::Sprite2D*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::db::custom::Object*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::p2d::app::Way*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::dialogue::Dialogue*)

DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Animation*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Composite*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Blinking*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::CameraRotation*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::CameraShaking*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Color*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::FontList*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::FontSize*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::OptionList*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Parallel*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Resize*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Rotate*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::SimpleMovement*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Sequential*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::TextureCoordinatesList*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::TextureCoordinatesContinuous*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Typing*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::WayMoving*)

DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Instance*)
DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::WayInstance*)

DEFINE_AS_QUERY_OBJECT_FROM_DATABASE(sad::animations::Group*)

sad::Maybe<sad::dialogue::Phrase>
scripting::ToValue<sad::dialogue::Phrase>::perform(
        const QScriptValue& v
)
{
    sad::Maybe<sad::dialogue::Phrase> result;
    if (v.isVariant())
    {
        QVariant var = v.toVariant();
        if (var.canConvert<sad::dialogue::Phrase>())
        {
            result.setValue(var.value<sad::dialogue::Phrase>());
        }
    }
    else
    {
        if (v.isQObject()) 
        {
            scripting::dialogues::PhraseRef* pr = qobject_cast<scripting::dialogues::PhraseRef*>(v.toQObject());
            if (pr)
            {
                result.setValue(pr->toPhrase());
            }
        }
        else
        {
            if (v.isObject())
            {
                if (v.property("actorName").isValid()
                    && v.property("actorPortrait").isValid()
                    && v.property("text").isValid()
                    && v.property("duration").isValid()
                    && v.property("viewHint").isValid())
                {
                    sad::Maybe<sad::String> maybeActorName = scripting::ToValue<sad::String>::perform(v.property("actorName"));
                    sad::Maybe<sad::String> maybeActorPortrait = scripting::ToValue<sad::String>::perform(v.property("actorPortrait"));
                    sad::Maybe<sad::String> maybeText = scripting::ToValue<sad::String>::perform(v.property("text"));
                    sad::Maybe<double> maybeDuration = scripting::ToValue<double>::perform(v.property("duration"));
                    sad::Maybe<sad::String> maybeViewHint = scripting::ToValue<sad::String>::perform(v.property("viewHint"));
                
                    if (maybeActorName.exists() 
                        && maybeActorPortrait.exists() 
                        && maybeText.exists()
                        && maybeDuration.exists()
                        && maybeViewHint.exists())
                    {
                        sad::dialogue::Phrase phrase;
                        phrase.setActorName(maybeActorName.value());
                        phrase.setActorPortrait(maybeActorPortrait.value());
                        phrase.setPhrase(maybeText.value());
                        phrase.setDuration(maybeDuration.value());
                        phrase.setViewHint(maybeViewHint.value());

                        result.setValue(phrase);
                    }
                }
            }
        }
    }
    return result;
}


sad::Maybe< sad::Vector<sad::p2d::app::WayPoint> >
scripting::ToValue< sad::Vector<sad::p2d::app::WayPoint> >::perform(
        const QScriptValue& v
)
{
    sad::Maybe< sad::Vector<sad::p2d::app::WayPoint> > result;
    if (v.isArray())
    {
        bool valid = true;
        sad::Vector<sad::p2d::app::WayPoint> k;

        QScriptValueIterator it(v);
        while(it.hasNext() && valid)
        {
            it.next();
            bool ok = false;
            it.name().toInt(&ok);
            if (ok) 
            {
                sad::Maybe<sad::Point2D> maybepoint = scripting::ToValue<sad::Point2D>::perform(it.value());
                if (maybepoint.exists())
                {
                    k << maybepoint.value();
                }
                else
                {
                    valid = false;
                }
            }
        }

        if (valid)
        {
            result.setValue(k);
        }		
    }
    
    return result;
}


sad::Maybe< sad::Vector<sad::dialogue::Phrase> >
scripting::ToValue< sad::Vector<sad::dialogue::Phrase> >::perform(
        const QScriptValue& v
)
{
    sad::Maybe< sad::Vector<sad::dialogue::Phrase> > result;
    if (v.isArray())
    {
        bool valid = true;
        sad::Vector<sad::dialogue::Phrase> k;

        QScriptValueIterator it(v);
        while(it.hasNext() && valid)
        {
            it.next();
            bool ok = false;
            it.name().toInt(&ok);
            if (ok) 
            {
                sad::Maybe<sad::dialogue::Phrase> maybepoint = scripting::ToValue<sad::dialogue::Phrase>::perform(it.value());
                if (maybepoint.exists())
                {
                    k << maybepoint.value();
                }
                else
                {
                    valid = false;
                }
            }
        }

        if (valid)
        {
            result.setValue(k);
        }		
    }
    
    return result;
}


sad::Maybe< sad::Vector<sad::String> >
scripting::ToValue< sad::Vector<sad::String> >::perform(
        const QScriptValue& v
)
{
    sad::Maybe< sad::Vector<sad::String> > result;
    if (v.isArray())
    {
        bool valid = true;
        sad::Vector<sad::String> k;

        QScriptValueIterator it(v);
        while(it.hasNext() && valid)
        {
            it.next();
            bool ok = false;
            it.name().toInt(&ok);
            if (ok) 
            {
                sad::Maybe<sad::String> maybepoint = scripting::ToValue<sad::String>::perform(it.value());
                if (maybepoint.exists())
                {
                    k << maybepoint.value();
                }
                else
                {
                    valid = false;
                }
            }
        }

        if (valid)
        {
            result.setValue(k);
        }		
    }
    
    return result;
}

#define DEFINE_BASIC_METHODS_FOR_TYPE(A) \
scripting::ToValue< A >::ToValue()       \
{                                        \
}										 \
scripting::ToValue< A >::~ToValue()      \
{                                        \
}										 \
sad::Maybe< A > scripting::ToValue< A >::toValue(const QScriptValue& v) \
{										 \
     return perform(v);                  \
}

DEFINE_BASIC_METHODS_FOR_TYPE( double )
DEFINE_BASIC_METHODS_FOR_TYPE( float )
DEFINE_BASIC_METHODS_FOR_TYPE( int )
DEFINE_BASIC_METHODS_FOR_TYPE( long )
DEFINE_BASIC_METHODS_FOR_TYPE( long long )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::AColor )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Color )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Point2D )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Point2I )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Point3D )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Point3I )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Size2D )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Size2I )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Rect2D )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Rect2I )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::String )
DEFINE_BASIC_METHODS_FOR_TYPE( std::string )
DEFINE_BASIC_METHODS_FOR_TYPE( QString )
DEFINE_BASIC_METHODS_FOR_TYPE( short )
DEFINE_BASIC_METHODS_FOR_TYPE( bool )
DEFINE_BASIC_METHODS_FOR_TYPE( char )
DEFINE_BASIC_METHODS_FOR_TYPE( signed char )
DEFINE_BASIC_METHODS_FOR_TYPE( unsigned char )
DEFINE_BASIC_METHODS_FOR_TYPE( unsigned int )
DEFINE_BASIC_METHODS_FOR_TYPE( unsigned long )
DEFINE_BASIC_METHODS_FOR_TYPE( unsigned long long )
DEFINE_BASIC_METHODS_FOR_TYPE( unsigned short )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::db::Object* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Scene* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::SceneNode* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Label* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Sprite2D* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::db::custom::Object* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::p2d::app::Way* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::dialogue::Dialogue* )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::dialogue::Phrase )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Vector<sad::p2d::app::WayPoint> )
DEFINE_BASIC_METHODS_FOR_TYPE( sad::Vector<sad::dialogue::Phrase> )
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Animation*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Composite*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Blinking*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::CameraRotation*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::CameraShaking*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Color*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::FontList*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::FontSize*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::OptionList*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Parallel*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Resize*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Rotate*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Sequential*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::TextureCoordinatesList*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::TextureCoordinatesContinuous*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Typing*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::WayMoving*)

DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Instance*)
DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::WayInstance*)

DEFINE_BASIC_METHODS_FOR_TYPE(sad::animations::Group*)

DEFINE_BASIC_METHODS_FOR_TYPE(sad::Vector<sad::String>)
#undef DEFINE_BASIC_METHODS_FOR_TYPE



#define DEFINE_BASIC_ENUM_CAST(T, LASTVAL)                                         \
sad::Maybe<T>                                                                      \
scripting::ToValue<T>::perform(                                                    \
        const QScriptValue& v                                                      \
)                                                                                  \
{                                                                                  \
    sad::Maybe< T > result;                                                        \
    sad::Maybe<unsigned int> mv = scripting::ToValue<unsigned int>::perform(v);    \
    if (mv.exists())                                                               \
    {                                                                              \
        if (mv.value() <= LASTVAL)                                                 \
        {                                                                          \
            result.setValue(static_cast<T>(mv.value()));                           \
        }                                                                          \
    }                                                                              \
                                                                                   \
    return result;                                                                 \
}

DEFINE_BASIC_ENUM_CAST(sad::layouts::Unit, sad::layouts::LU_Percents)
DEFINE_BASIC_ENUM_CAST(sad::layouts::HorizontalAlignment, sad::layouts::LHA_Right)
DEFINE_BASIC_ENUM_CAST(sad::layouts::VerticalAlignment, sad::layouts::LVA_Bottom)
DEFINE_BASIC_ENUM_CAST(sad::layouts::StackingType, sad::layouts::LST_NoStacking)



DECLARE_COMMON_TYPE(QScriptValue)
