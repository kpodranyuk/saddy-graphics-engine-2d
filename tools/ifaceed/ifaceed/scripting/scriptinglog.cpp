#include "scriptinglog.h"

#include "scripting.h"

#include "classwrapper.h"

#include "../core/editor.h"

#include "../gui/uiblocks/uiblocks.h"
#include "../gui/uiblocks/uiconsoleblock.h"

#include <QScriptValueIterator>
#include <QTextEdit>

QString  scripting::scripting_log_object(const QScriptValue& v, QScriptEngine *engine)
{
    QString result = "";
    bool handled = false;
    if (v.isQObject())
    {
        QObject* o = v.toQObject();
        scripting::ClassWrapper* wrapper = qobject_cast<scripting::ClassWrapper*>(o);
        if (wrapper)
        {
            handled = true;
            result = (wrapper->toString());
        }
    }
    if (handled == false && v.isArray())
    {
        handled = true;
        QScriptValue o = engine->toObject(v);
        QScriptValueIterator it(o);
        result += "[";
        bool first = true;
        while(it.hasNext())
        {
            it.next();
            bool ok = false;
            it.name().toInt(&ok);
            if (ok) 
            {
                if (first)
                {
                    first = false;
                } 
                else
                {
                    result += ", ";
                }
                result += scripting::scripting_log_object(it.value(), engine);
            }
        }
        result += "]";
    }
    if (handled == false && v.isObject() && !v.isBool() && !v.isDate() && !v.isNumber() && !v.isString() && !v.isVariant())
    {
        handled = true;
        QScriptValue o = engine->toObject(v);

        QScriptValueIterator it(o);
        result += "{";
        bool first = true;
        while(it.hasNext())
        {
            it.next();
            QString name = it.name();
            if (name != "prototype")
            {
                if (first)
                {
                    first = false;
                } 
                else
                {
                    result += ", ";
                }
                result +=  name + ": " + scripting::scripting_log_object(it.value(), engine);
            }
        }
        result += "}";
    }

    if (handled == false)
    {
        result = v.toString();
    }
    return result;
}

QScriptValue scripting::scripting_log(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue main = engine->globalObject().property("---");
    scripting::Scripting* e = static_cast<scripting::Scripting*>(main.toQObject());
    QTextEdit* edit = e->editor()->uiBlocks()->uiConsoleBlock()->txtConsoleResults;
    for(size_t i = 0; i < context->argumentCount(); ++i)
    {
        QScriptValue arg = context->argument(i);

        QString result = scripting::scripting_log_object(arg, engine);

        edit->append(result);
    }
    return QScriptValue();
}
