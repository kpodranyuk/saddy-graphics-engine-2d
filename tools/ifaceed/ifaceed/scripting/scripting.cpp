#include "scripting.h"
#include "scriptinghelptext.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "constructorcall.h"
#include "makeconstructor.h"
#include "scriptinglog.h"
#include "multimethod.h"
#include "makescriptingcall.h"
#include "makefunctioncall.h"
#include "abstractgetter.h"
#include "queryresource.h"
#include "isaabb.h"
#include "point2d.h"


#include <animations/animationssimplemovement.h>

#include "../scriptinghelp.h"

#include "../core/editor.h"

#include "../gui/codeedit/codeedit.h"

#include "../gui/uiblocks/uiblocks.h"
#include "../gui/uiblocks/uiconsoleblock.h"
#include "../gui/uiblocks/uianimationblock.h"


#include "../history/scenenodes/scenenodeschangename.h"
#include "../history/scenenodes/scenenodeschangeangle.h"
#include "../history/scenenodes/scenenodeschangecolor.h"
#include "../history/scenenodes/scenenodeschangevisibility.h"

#include "../history/label/changetext.h"
#include "../history/label/changelinespacing.h"
#include "../history/label/changemaximallinewidth.h"
#include "../history/label/changebreaktext.h"
#include "../history/label/changeoverflowstrategy.h"
#include "../history/label/changetextellipsis.h"
#include "../history/label/changemaximallinescount.h"
#include "../history/label/changeoverflowstrategyforlines.h"
#include "../history/label/changetextellipsisforlines.h"
#include "../history/label/changehasformatting.h"

#include "../history/sprite2d/changeflipx.h"
#include "../history/sprite2d/changeflipy.h"

#include "../history/ways/wayschangename.h"
#include "../history/ways/wayschangetotaltime.h"
#include "../history/ways/wayschangeclosed.h"

#include "../history/dialogues/dialogueschangename.h"

#include "../history/animations/animationschangename.h"
#include "../history/animations/animationschangetime.h"
#include "../history/animations/animationschangelooped.h"
#include "../history/animations/animationschangeeasingfunctiontype.h"
#include "../history/animations/animationschangeeasingovershootamplitude.h"
#include "../history/animations/animationschangeeasingperiod.h"
#include "../history/animations/animationschangeblinkingfrequency.h"
#include "../history/animations/animationschangecameraoffset.h"
#include "../history/animations/animationschangeshakingfrequency.h"
#include "../history/animations/animationschangecameraangle.h"
#include "../history/animations/animationschangecamerapivot.h"
#include "../history/animations/animationschangecolorcolor.h"
#include "../history/animations/animationschangefontlistfonts.h"
#include "../history/animations/animationschangefontsizesize.h"
#include "../history/animations/animationschangelist.h"
#include "../history/animations/animationschangeresizestartingsize.h"
#include "../history/animations/animationschangeresizeendingsize.h"
#include "../history/animations/animationschangerotateangle.h"
#include "../history/animations/animationschangerect.h"
#include "../history/animations/animationschangepropertyaspoint2displayedintwospinboxes.h"


#include "database/databasebindings.h"
#include "database/databasepropertysetter.h"
#include "database/databasepropertygetter.h"

#include "scenes/scenesbindings.h"
#include "scenes/scenesnamesetter.h"

#include "scenenodes/scenenodesbindings.h"
#include "scenenodes/scenenodessetter.h"
#include "scenenodes/scenenodesflagsetter.h"
#include "scenenodes/scenenodesareasetter.h"
#include "scenenodes/scenenodesfontsizesetter.h"
#include "scenenodes/scenenodesfontsetter.h"
#include "scenenodes/scenenodesoptionssetter.h"
#include "scenenodes/scenenodesschemasetter.h"
#include "scenenodes/scenenodescustomgetter.h"
#include "scenenodes/scenenodescustomsetter.h"

#include "layouts/gridbindings.h"

#include "ways/waysbindings.h"
#include "ways/wayssetter.h"

#include "dialogues/dialoguesbindings.h"
#include "dialogues/dialoguessetter.h"

#include "animations/animationsbindings.h"
#include "animations/animationspoint2dsetter.h"
#include "animations/animationssetter.h"
#include "animations/animationswidgetsetter.h"
#include "animations/animationswaysetter.h"

#include "instances/instancesbindings.h"
#include "instances/instancesnamesetter.h"
#include "instances/instancesanimationsetter.h"
#include "instances/instancesanimationdbsetter.h"
#include "instances/instancesobjectsetter.h"
#include "instances/instancesstarttimesetter.h"
#include "instances/instanceswaysetter.h"

#include "groups/groupsbindings.h"
#include "groups/groupsnamesetter.h"
#include "groups/groupsloopedsetter.h"
#include "groups/groupssequentialsetter.h"

#include <QFileDialog>
#include <QTextStream>
#include <QScriptValueIterator>

#include <animations/animationsblinking.h>
#include <animations/animationscamerashaking.h>
#include <animations/animationscamerarotation.h>
#include <animations/animationscomposite.h>
#include <animations/animationscolor.h>
#include <animations/animationsfontlist.h>
#include <animations/animationsfontsize.h>
#include <animations/animationsresize.h>
#include <animations/animationsrotate.h>
#include <animations/animationsoptionlist.h>
#include <animations/animationstexturecoordinatescontinuous.h>
#include <animations/animationstexturecoordinateslist.h>
#include <animations/animationswaymoving.h>
#include "animations/easinggetter.h"
#include "animations/easingsetter.h"

Q_DECLARE_METATYPE(QScriptContext*) //-V566

// ================================== PUBLIC METHODS OF scripting::Scripting::Thread ==================================
int scripting::Scripting::Thread::TIMEOUT = 60000;

int scripting::Scripting::Thread::POLLINGTIME = 300;

scripting::Scripting::Thread::Thread(scripting::Scripting* me) : m_should_i_quit(false), m_s(me)
{
    
}

scripting::Scripting::Thread::~Thread()
{
    
}

void scripting::Scripting::Thread::forceQuit()
{
    m_should_i_quit = true;	
}

void scripting::Scripting::Thread::run()
{
    this->msleep(scripting::Scripting::Thread::POLLINGTIME);

    int timeout = 0;
    while (!m_should_i_quit && m_s->engine()->isEvaluating())
    {
        this->msleep(scripting::Scripting::Thread::POLLINGTIME);
        timeout += scripting::Scripting::Thread::POLLINGTIME; 
        m_should_i_quit = timeout >= scripting::Scripting::Thread::TIMEOUT;
    }
    if (m_should_i_quit && timeout >= scripting::Scripting::Thread::TIMEOUT)
    {
        m_s->cancelExecution();
    }
}

// ================================== PUBLIC METHODS OF scripting::Scripting ==================================
scripting::Scripting::Scripting(QObject* parent) : QObject(parent), m_editor(NULL)
{
    m_flags = QScriptValue::ReadOnly|QScriptValue::Undeletable;
    m_engine = new QScriptEngine();
    m_value = m_engine->newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::SkipMethodsInEnumeration);
    m_value.setProperty("log", m_engine->newFunction(scripting::scripting_log), m_flags);  // E.log
    
    QScriptValue globalValue = m_engine->globalObject();
    globalValue.setProperty("console", m_value, m_flags);
    globalValue.setProperty("E",m_value,m_flags);
    globalValue.setProperty("---",m_value,m_flags);
    
    scripting::Callable* oresourcetype = scripting::make_scripting_call(scripting::resource_type, this);
    m_registered_classes << oresourcetype;
    m_value.setProperty("resourceType", m_engine->newObject(oresourcetype), m_flags);

    scripting::Callable* oresourceoptions = scripting::make_scripting_call(scripting::resource_options, this);
    m_registered_classes << oresourceoptions;
    m_value.setProperty("resourceOptions",m_engine->newObject(oresourceoptions), m_flags);

    scripting::Callable* oresourceschema = scripting::make_scripting_call(scripting::resource_schema, this);
    m_registered_classes << oresourceschema;
    m_value.setProperty("resourceSchema", m_engine->newObject(oresourceschema), m_flags);    
}

scripting::Scripting::~Scripting()
{
    m_engine->collectGarbage();
    delete m_engine;
    for(size_t i = 0; i < m_registered_classes.size(); i++)
    {
        delete m_registered_classes[i];
    }
}

void scripting::Scripting::setEditor(core::Editor* editor)
{
    m_editor = editor;
    this->initSadTypeConstructors();
    this->initDatabasePropertyBindings(m_value);
    this->initSceneBindings(m_value);
    this->initSceneNodesBindings(m_value);
    this->initLayoutGridBindings(m_value);
    this->initWaysBindings(m_value);
    this->initDialoguesBindings(m_value);
    this->initAnimationsBindings(m_value);
    this->initAnimationInstanceBindings(m_value);
    this->initAnimationGroupBindings(m_value);
}

core::Editor* scripting::Scripting::editor() const
{
    return m_editor;
}

QScriptEngine* scripting::Scripting::engine() const
{
    return m_engine;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::registerFunction(const QString& name, QScriptValue& v)
{
    v.setProperty("name", name);
    m_engine->globalObject().setProperty(name, v, m_flags);
}

void scripting::Scripting::registerScriptClass(const QString& name, QScriptClass* c)
{
    m_engine->globalObject().setProperty(name, m_engine->newObject(c), m_flags);
    if (m_registered_classes.contains(c) == false) {
        m_registered_classes << c;
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
QSet<QString> scripting::Scripting::commonProperties()
{
    QSet<QString> result;
    const char* firstprops[] = {
        "position",
        "actorName",
        "actorPortrait",
        "text",
        "duration",
        "viewHint",
        "setPoint",
        "point",
        "width",
        "height",
        "x",
        "y",
        "sub",
        "sum",
        "mul",
        "div",
        "mid",
        "movedToPoint",
        NULL
    };
    int i = 0;
    while(firstprops[i] != NULL)
    {
        result.insert(firstprops[i]);
        ++i;
    }
    return result;
}

void scripting::Scripting::propertiesAndFunctions(
    QStringList& properties,
    QStringList& functions
)
{
    QSet<QString> propertiesset = this->commonProperties();
    QSet<QString> functionsset;

    propertiesAndFunctions(propertiesset, functionsset, m_engine->globalObject());

    properties = propertiesset.toList();
    functions = functionsset.toList();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::propertiesAndFunctions(
    QSet<QString>& properties,
    QSet<QString>& functions,
    const QScriptValue& v
)
{
    QScriptValueIterator it(v);
    while(it.hasNext())
    {
        it.next();
        if (it.name() != "prototype" && it.name() != "__prototype__" && it.name() != "constructor")
        {
           if (it.value().isFunction() || it.value().scriptClass() != NULL)
           {
               functions.insert(it.name());
           }
           else
           {
               properties.insert(it.name());
               this->propertiesAndFunctions(properties, functions, it.value());
           }
        }
    }
}


int scripting::Scripting::screenWidth()
{
    return sad::Renderer::ref()->settings().width();
}

int scripting::Scripting::screenHeight()
{
    return sad::Renderer::ref()->settings().height();
}


void scripting::Scripting::runScript()
{
    if (m_engine->isEvaluating())
    {
        return;
    }
    history::BatchCommand* c = new history::BatchCommand();
    m_editor->setCurrentBatchCommand(c);

    gui::uiblocks::UIConsoleBlock* cblk = m_editor->uiBlocks()->uiConsoleBlock();
    cblk->txtConsoleResults->setText("");
    QString text = cblk->txtConsoleCode->toPlainText();
    
    QScriptValue globalValue = m_engine->globalObject();
    globalValue.setProperty("console", m_value, m_flags);
    globalValue.setProperty("E",m_value,m_flags);
    globalValue.setProperty("---",m_value,m_flags);
    
    scripting::Scripting::Thread poller(this);
    poller.start();
    QScriptValue result = m_engine->evaluate(text, "console.js");
    poller.forceQuit();

    if (result.isError())
    {
        cblk->txtConsoleResults->append(QString("<font color=\"red\">")
                                        + result.toString()
                                        + QString("<br/>Backtrace:<br/>")
                                        + m_engine->uncaughtExceptionBacktrace().join("<br/>")
                                        + QString("</font>")
        );
        c->rollback(m_editor);
        delete c;
    }
    else
    {
        if (c->count())
        {
            m_editor->history()->add(c);
        }
        else
        {
            delete c;
        }
    }

    m_editor->setCurrentBatchCommand(NULL);
    poller.wait();
}


// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::showHelp()
{
    ScriptingHelp dlg;
            
    dlg.setText(scripting_help);
    
    dlg.exec();
}


// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::cancelExecution()
{
    if (m_engine->isEvaluating())
    {
        m_engine->abortEvaluation(m_engine->currentContext()->throwError(QScriptContext::SyntaxError, "Aborted due timeout"));
    }
}

void scripting::Scripting::initSadTypeConstructors()
{
    
    // A sad::Point2D constructor	
    scripting::MultiMethod* point2dconstructor = new scripting::MultiMethod(m_engine, "p2d");
    point2dconstructor->add(scripting::make_constructor<sad::Point2D>(this));
    point2dconstructor->add(scripting::make_constructor<sad::Point2D, double, double>(this));
    this->registerScriptClass("p2d", point2dconstructor);

    qScriptRegisterMetaType(m_engine, scripting::Point2D::toValue, scripting::Point2D::fromValue);

    // A sad::Point2I constructor	
    scripting::MultiMethod* point2iconstructor = new scripting::MultiMethod(m_engine, "p2i");
    point2iconstructor->add(scripting::make_constructor<sad::Point2I>(this));
    point2iconstructor->add(scripting::make_constructor<sad::Point2I, int, int>(this));
    this->registerScriptClass("p2i", point2iconstructor);

    // A sad::Point3D constructor	
    scripting::MultiMethod* point3dconstructor = new scripting::MultiMethod(m_engine, "p3d");
    point3dconstructor->add(scripting::make_constructor<sad::Point3D>(this));
    point3dconstructor->add(scripting::make_constructor<sad::Point3D, sad::Point2D>(this));
    point3dconstructor->add(scripting::make_constructor<sad::Point3D, double, double>(this));
    point3dconstructor->add(scripting::make_constructor<sad::Point3D, double, double, double>(this));
    this->registerScriptClass("p3d", point3dconstructor);

    // A sad::Point3I constructor	
    scripting::MultiMethod* point3iconstructor = new scripting::MultiMethod(m_engine, "p3i");
    point3iconstructor->add(scripting::make_constructor<sad::Point3I>(this));
    point3iconstructor->add(scripting::make_constructor<sad::Point3I, sad::Point2I>(this));
    point3iconstructor->add(scripting::make_constructor<sad::Point3I, int, int>(this));
    point3iconstructor->add(scripting::make_constructor<sad::Point3I, int, int, int>(this));
    this->registerScriptClass("p3i", point3iconstructor);

    // A sad::Rect2D constructor
    scripting::MultiMethod* rect2dconstructor = new scripting::MultiMethod(m_engine, "r2d");
    rect2dconstructor->add(scripting::make_constructor<sad::Rect2D>(this));
    rect2dconstructor->add(scripting::make_constructor<sad::Rect2D, sad::Point2D, sad::Point2D>(this));
    rect2dconstructor->add(scripting::make_constructor<sad::Rect2D, double, double, double, double>(this));
    rect2dconstructor->add(scripting::make_constructor<sad::Rect2D, sad::Point2D, sad::Point2D, sad::Point2D, sad::Point2D>(this));
    this->registerScriptClass("r2d", rect2dconstructor);

    // A sad::Rect2I constructor
    scripting::MultiMethod* rect2iconstructor = new scripting::MultiMethod(m_engine, "r2i");
    rect2iconstructor->add(scripting::make_constructor<sad::Rect2I>(this));
    rect2iconstructor->add(scripting::make_constructor<sad::Rect2I, sad::Point2I, sad::Point2I>(this));
    rect2iconstructor->add(scripting::make_constructor<sad::Rect2I, int, int, int, int>(this));
    rect2iconstructor->add(scripting::make_constructor<sad::Rect2I, sad::Point2I, sad::Point2I, sad::Point2I, sad::Point2I>(this));
    this->registerScriptClass("r2i", rect2iconstructor);

    // A sad::Size2D constructor	
    scripting::MultiMethod* size2dconstructor = new scripting::MultiMethod(m_engine, "s2d");
    size2dconstructor->add(scripting::make_constructor<sad::Size2D>(this));
    size2dconstructor->add(scripting::make_constructor<sad::Size2D, double, double>(this));
    this->registerScriptClass("s2d", size2dconstructor);

    // A sad::Size2I constructor	
    scripting::MultiMethod* size2iconstructor = new scripting::MultiMethod(m_engine, "s2i");
    size2iconstructor->add(scripting::make_constructor<sad::Size2I>(this));
    size2iconstructor->add(scripting::make_constructor<sad::Size2I, unsigned int, unsigned int>(this));
    this->registerScriptClass("s2i", size2iconstructor);

    // A sad::Color
    scripting::MultiMethod* clrconstructor = new scripting::MultiMethod(m_engine, "clr");
    clrconstructor->add(scripting::make_constructor<sad::Color>(this));
    clrconstructor->add(scripting::make_constructor<sad::Color, unsigned char, unsigned char, unsigned char>(this));
    this->registerScriptClass("clr", clrconstructor);

    // A sad::AColor
    scripting::MultiMethod* aclrconstructor = new scripting::MultiMethod(m_engine, "aclr");
    aclrconstructor->add(scripting::make_constructor<sad::AColor>(this));
    aclrconstructor->add(scripting::make_constructor<sad::AColor, unsigned char, unsigned char, unsigned char>(this));
    aclrconstructor->add(scripting::make_constructor<sad::AColor, unsigned char, unsigned char, unsigned char, unsigned char>(this));
    this->registerScriptClass("aclr", aclrconstructor);   

    scripting::Callable* screenWidth = scripting::make_function_call(scripting::Scripting::screenWidth, this);
    screenWidth->setName("screenWidth");
    m_registered_classes << screenWidth;
    m_value.setProperty("screenWidth", m_engine->newObject(screenWidth), m_flags); // E.screenWidth

    scripting::Callable* screenHeight = scripting::make_function_call(scripting::Scripting::screenHeight, this);
    screenHeight->setName("screenHeight");
    m_registered_classes << screenHeight;
    m_value.setProperty("screenHeight", m_engine->newObject(screenHeight), m_flags); // E.screenHeight
}

void scripting::Scripting::initDatabasePropertyBindings(QScriptValue& v)
{
    QScriptValue db = m_engine->newObject();
    
    db.setProperty("list", m_engine->newFunction(scripting::database::list), m_flags); // E.db.list
    
    scripting::Callable* tp = scripting::make_scripting_call(scripting::database::type, this);
    m_registered_classes << tp;
    db.setProperty("type", m_engine->newObject(tp), m_flags); // E.db.type

    db.setProperty("readableProperties", m_engine->newFunction(scripting::database::readableProperties), m_flags); // E.db.readableProperties
    db.setProperty("writableProperties", m_engine->newFunction(scripting::database::writableProperties), m_flags); // E.db.writableProperties


    scripting::Callable* add = scripting::make_scripting_call(scripting::database::addProperty, this);
    m_registered_classes << add;
    db.setProperty("add", m_engine->newObject(add), m_flags); // E.db.add
    
    scripting::Callable* remove = scripting::make_scripting_call(scripting::database::removeProperty, this);
    m_registered_classes << remove;
    db.setProperty("remove", m_engine->newObject(remove), m_flags); // E.db.remove

    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
#define PUSH_SETTER(TYPE) set->add(new scripting::database::PropertySetter< TYPE >(m_engine));
    PUSH_SETTER( double )
    PUSH_SETTER( float )
    PUSH_SETTER( int )
    PUSH_SETTER( long )
    PUSH_SETTER( long long )
    PUSH_SETTER( sad::AColor )
    PUSH_SETTER( sad::Color )
    PUSH_SETTER( sad::Point2D )
    PUSH_SETTER( sad::Point2I )
    PUSH_SETTER( sad::Point3D )
    PUSH_SETTER( sad::Point3I )
    PUSH_SETTER( sad::Size2D )
    PUSH_SETTER( sad::Size2I )
    PUSH_SETTER( sad::Rect2D )
    PUSH_SETTER( sad::Rect2I )
    PUSH_SETTER( sad::String )
    PUSH_SETTER( std::string )
    PUSH_SETTER( QString )
    PUSH_SETTER( short )
    PUSH_SETTER( bool )
    PUSH_SETTER( char )
    PUSH_SETTER( signed char )
    PUSH_SETTER( unsigned char )
    PUSH_SETTER( unsigned int )
    PUSH_SETTER( unsigned long )
    PUSH_SETTER( unsigned long long )
    PUSH_SETTER( unsigned short )
#undef PUSH_SETTER
    m_registered_classes << set;
    db.setProperty("set", m_engine->newObject(set), m_flags); // E.db.set

    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
#define PUSH_GETTER(TYPE) get->add(new scripting::database::PropertyGetter< TYPE >(m_engine));
    PUSH_GETTER( double )
    PUSH_GETTER( float )
    PUSH_GETTER( int )
    PUSH_GETTER( long )
    PUSH_GETTER( long long )
    PUSH_GETTER( sad::AColor )
    PUSH_GETTER( sad::Color )
    PUSH_GETTER( sad::Point2D )
    PUSH_GETTER( sad::Point2I )
    PUSH_GETTER( sad::Point3D )
    PUSH_GETTER( sad::Point3I )
    PUSH_GETTER( sad::Size2D )
    PUSH_GETTER( sad::Size2I )
    PUSH_GETTER( sad::Rect2D )
    PUSH_GETTER( sad::Rect2I )
    PUSH_GETTER( sad::String )
    PUSH_GETTER( std::string )
    PUSH_GETTER( QString )
    PUSH_GETTER( short )
    PUSH_GETTER( bool )
    PUSH_GETTER( char )
    PUSH_GETTER( signed char )
    PUSH_GETTER( unsigned char )
    PUSH_GETTER( unsigned int )
    PUSH_GETTER( unsigned long )
    PUSH_GETTER( unsigned long long )
    PUSH_GETTER( unsigned short )
#undef PUSH_GETTER
    m_registered_classes << get;
    db.setProperty("get", m_engine->newObject(get), m_flags); // E.db.get
    
    v.setProperty("db", db, m_flags); // E.db

    m_engine->evaluate(
        "E.db.attr = function() {"  
        "	if (arguments.length == 1)"
        "	{"
        "		return E.db.get(arguments[0]);"
        "	}"
        "	if (arguments.length == 2)"
        "	{"
        "		return E.scenes.set(arguments[0], arguments[1]);"
        "	}"
        "	throw new Error(\"Specify 1 or 2 arguments\");"
        "};"
    );
}

void scripting::Scripting::initSceneBindings(QScriptValue& v)
{
    QScriptValue scenes = m_engine->newObject();


    scenes.setProperty("list", m_engine->newFunction(scripting::scenes::list), m_flags);  // E.scenes.list

    // An add method
    scripting::MultiMethod* add = new scripting::MultiMethod(m_engine, "add");
    add->add(scripting::make_scripting_call(scripting::scenes::add, this));
    add->add(scripting::make_scripting_call(scripting::scenes::addNameless, this));
    m_registered_classes << add;
    
    scenes.setProperty("add", m_engine->newObject(add), m_flags);  // E.scenes.add
    
    scripting::Callable* remove = scripting::make_scripting_call(scripting::scenes::remove, this);
    m_registered_classes << remove;
    scenes.setProperty("remove", m_engine->newObject(remove), m_flags); // E.scenes.remove

    scripting::Callable* moveback = scripting::make_scripting_call(scripting::scenes::moveBack, this);
    m_registered_classes << moveback;
    scenes.setProperty("moveBack", m_engine->newObject(moveback), m_flags); // E.scenes.moveBack

    scripting::Callable* movefront = scripting::make_scripting_call(scripting::scenes::moveFront, this);
    m_registered_classes << movefront;
    scenes.setProperty("moveFront", m_engine->newObject(movefront), m_flags); // E.scenes.moveFront

    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    set->add(new scripting::scenes::NameSetter(m_engine));
    m_registered_classes << set;
    scenes.setProperty("set", m_engine->newObject(set), m_flags); // E.scenes.set

    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    get->add(new scripting::AbstractGetter<sad::Scene*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::Scene*, unsigned int>(m_engine, "layer"));
    get->add(new scripting::AbstractGetter<sad::Scene*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::Scene*, unsigned long long>(m_engine, "minorid"));
    m_registered_classes << get;
    scenes.setProperty("get", m_engine->newObject(get), m_flags); // E.scenes.set

    v.setProperty("scenes", scenes, m_flags); // E.scenes

    m_engine->evaluate(
        "E.scenes.attr = function() {"  
        "	if (arguments.length == 2)"
        "	{"
        "		return E.scenes.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.scenes.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );
}


void scripting::Scripting::initSceneNodesBindings(QScriptValue& v)
{
    QScriptValue scenenodes = m_engine->newObject();

    scenenodes.setProperty("list", m_engine->newFunction(scripting::scenenodes::list), m_flags); // E.scenenodes.list

    scripting::Callable* listscene = scripting::make_scripting_call(scripting::scenenodes::listScene, this);
    m_registered_classes << listscene;
    scenenodes.setProperty("listScene", m_engine->newObject(listscene), m_flags); // E.scenenodes.listScene


    scripting::Callable* _addlabel = scripting::make_scripting_call(scripting::scenenodes::_addLabel, this);
    m_registered_classes << _addlabel;
    scenenodes.setProperty("_addLabel", m_engine->newObject(_addlabel), m_flags); // E.scenenodes._addLabel

    scripting::Callable* _addsprite2d = scripting::make_scripting_call(scripting::scenenodes::_addSprite2D, this);
    m_registered_classes << _addsprite2d;
    scenenodes.setProperty("_addSprite2D", m_engine->newObject(_addsprite2d), m_flags); // E.scenenodes._addSprite2D

    scripting::Callable* _addcustomobject = scripting::make_scripting_call(scripting::scenenodes::_addCustomObject, this);
    m_registered_classes << _addcustomobject;
    scenenodes.setProperty("_addCustomObject", m_engine->newObject(_addcustomobject), m_flags); // E.scenenodes._addCustomObject

    scripting::Callable* makeBackground = scripting::make_scripting_call(scripting::scenenodes::makeBackground, this);
    m_registered_classes << makeBackground;
    scenenodes.setProperty("makeBackground", m_engine->newObject(makeBackground), m_flags); // E.scenenodes.makeBackground

    scripting::Callable* remove = scripting::make_scripting_call(scripting::scenenodes::remove, this);
    m_registered_classes << remove;
    scenenodes.setProperty("remove", m_engine->newObject(remove)); // E.scenenodes.remove

    scripting::Callable* spanBetweenTwoPoints = scripting::make_scripting_call(scripting::scenenodes::spanBetweenTwoPoints, this);
    m_registered_classes << spanBetweenTwoPoints;
    scenenodes.setProperty("spanBetweenTwoPoints", m_engine->newObject(spanBetweenTwoPoints)); // E.scenenodes.spanBetweenTwoPoints


    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    // All props
    set->add(new scripting::scenenodes::FlagSetter(m_editor, m_engine, "visible", history::scenenodes::changeVisibility));
    set->add(new scripting::scenenodes::Setter<sad::String, history::scenenodes::ChangeName>(m_engine, "name"));
    set->add(new scripting::scenenodes::AreaSetter(m_engine));
    set->add(new scripting::scenenodes::Setter<double, history::scenenodes::ChangeAngle>(m_engine, "angle"));
    set->add(new scripting::scenenodes::Setter<sad::AColor, history::scenenodes::ChangeColor>(m_engine, "color"));
    // sad::Label props
    set->add(new scripting::scenenodes::FontSizeSetter(m_engine));
    set->add(new scripting::scenenodes::Setter<sad::String, history::label::ChangeText>(m_engine, "text"));
    set->add(new scripting::scenenodes::Setter<float, history::label::ChangeLineSpacing>(m_engine, "linespacing"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeMaximalLineWidth>(m_engine, "maximallinewidth"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeOverflowStrategy>(m_engine, "overflowstrategy"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeBreakText>(m_engine, "breaktext"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeTextEllipsis>(m_engine, "textellipsisposition"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeMaximalLinesCount>(m_engine, "maximallinescount"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeOverflowStrategyForLines>(m_engine, "overflowstrategyforlines"));
    set->add(new scripting::scenenodes::Setter<unsigned int, history::label::ChangeTextEllipsisForLines>(m_engine, "textellipsispositionforlines"));
    set->add(new scripting::scenenodes::Setter<bool, history::label::ChangeHasFormatting>(m_engine, "hasformatting"));

    set->add(new scripting::scenenodes::FontSetter(m_engine));
    // sad::Sprite2D props
    set->add(new scripting::scenenodes::FlagSetter(m_editor, m_engine, "flipx", history::sprite2d::changeFlipX));
    set->add(new scripting::scenenodes::FlagSetter(m_editor, m_engine, "flipy", history::sprite2d::changeFlipY));
    set->add(new scripting::scenenodes::OptionsSetter(m_engine));
    // sad::db::CustomObject props
    set->add(new scripting::scenenodes::SchemaSetter(m_engine));
#define PUSH_SETTER(TYPE) set->add(new scripting::scenenodes::CustomSetter< TYPE >(m_engine));
    PUSH_SETTER( double )
    PUSH_SETTER( float )
    PUSH_SETTER( int )
    PUSH_SETTER( long )
    PUSH_SETTER( long long )
    PUSH_SETTER( sad::AColor )
    PUSH_SETTER( sad::Color )
    PUSH_SETTER( sad::Point2D )
    PUSH_SETTER( sad::Point2I )
    PUSH_SETTER( sad::Point3D )
    PUSH_SETTER( sad::Point3I )
    PUSH_SETTER( sad::Size2D )
    PUSH_SETTER( sad::Size2I )
    PUSH_SETTER( sad::Rect2D )
    PUSH_SETTER( sad::Rect2I )
    PUSH_SETTER( sad::String )
    PUSH_SETTER( std::string )
    PUSH_SETTER( QString )
    PUSH_SETTER( short )
    PUSH_SETTER( bool )
    PUSH_SETTER( char )
    PUSH_SETTER( signed char )
    PUSH_SETTER( unsigned char )
    PUSH_SETTER( unsigned int )
    PUSH_SETTER( unsigned long )
    PUSH_SETTER( unsigned long long )
    PUSH_SETTER( unsigned short )
#undef PUSH_SETTER
    m_registered_classes << set;
    scenenodes.setProperty("set", m_engine->newObject(set), m_flags); // E.scenes.set
    
    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    // All
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "layer"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned long long>(m_engine, "minorid"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned long long>(m_engine, "scene"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, bool>(m_engine, "visible"));	
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::Rect2D>(m_engine, "area"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, double>(m_engine, "angle"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::AColor>(m_engine, "color"));    
    // sad::Label props
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "fontsize"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::String>(m_engine, "text"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, float>(m_engine, "linespacing"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::String>(m_engine, "font"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "maximallinewidth"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "overflowstrategy"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "breaktext"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "textellipsisposition"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "maximallinescount"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "overflowstrategyforlines"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, unsigned int>(m_engine, "textellipsispositionforlines"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, bool>(m_engine, "hasformatting"));

    // sad::Sprite2D props
    get->add(new scripting::AbstractGetter<sad::SceneNode*, bool>(m_engine, "flipx"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, bool>(m_engine, "flipy"));
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::String>(m_engine, "options"));
    // sad::db::CustomObject props
    get->add(new scripting::AbstractGetter<sad::SceneNode*, sad::String>(m_engine, "schema"));
#define PUSH_GETTER(TYPE) get->add(scripting::scenenodes::custom_getter< TYPE >(m_engine));
    PUSH_GETTER( double )
    PUSH_GETTER( float )
    PUSH_GETTER( int )
    PUSH_GETTER( long )
    PUSH_GETTER( long long )
    PUSH_GETTER( sad::AColor )
    PUSH_GETTER( sad::Color )
    PUSH_GETTER( sad::Point2D )
    PUSH_GETTER( sad::Point2I )
    PUSH_GETTER( sad::Point3D )
    PUSH_GETTER( sad::Point3I )
    PUSH_GETTER( sad::Size2D )
    PUSH_GETTER( sad::Size2I )
    PUSH_GETTER( sad::Rect2D )
    PUSH_GETTER( sad::Rect2I )
    PUSH_GETTER( sad::String )
    PUSH_GETTER( std::string )
    PUSH_GETTER( QString )
    PUSH_GETTER( short )
    PUSH_GETTER( bool )
    PUSH_GETTER( char )
    PUSH_GETTER( signed char )
    PUSH_GETTER( unsigned char )
    PUSH_GETTER( unsigned int )
    PUSH_GETTER( unsigned long )
    PUSH_GETTER( unsigned long long )
    PUSH_GETTER( unsigned short )
#undef PUSH_GETTER
    m_registered_classes << get;
    scenenodes.setProperty("get", m_engine->newObject(get), m_flags); // E.scenes.get

    v.setProperty("scenenodes", scenenodes, m_flags); // E.scenenodes

    m_engine->evaluate(
        "E.OverflowStrategy = { \"Visible\": 0, \"Hidden\": 1, \"Ellipsis\": 2 };"
        "E.BreakText = { \"Normal\": 0, \"BreakWord\": 1};"
        "E.TextEllipsisPosition = { \"Begin\": 0, \"Middle\": 1, \"End\": 2};"
    );

    m_engine->evaluate(
        "E.scenenodes.addLabel = function(o) {"  
        "	if (\"fontsize\" in o == false)"
        "   {                              "
        "     o[\"fontsize\"] = 16;        "
        "   }                              "
        "	if (\"color\" in o == false)   "
        "	{"
        "	   o[\"color\"] = aclr(255, 255, 255, 0);"
        "	}"
        "	if (\"name\" in o == false)   "
        "	{"
        "	   o[\"name\"] = \"\";"
        "	}"
        "	return E.scenenodes._addLabel(o[\"scene\"], o[\"font\"], o[\"fontsize\"], o[\"text\"], o[\"name\"], o[\"point\"], o[\"color\"]);"
        "};"
        "E.scenenodes.addSprite2D = function(o) {"
        "	if (\"color\" in o == false)   "
        "	{"
        "	   o[\"color\"] = aclr(255, 255, 255, 0);"
        "	}"
        "	if (\"name\" in o == false)   "
        "	{"
        "	   o[\"name\"] = \"\";"
        "	}"
        "	return E.scenenodes._addSprite2D(o[\"scene\"], o[\"sprite\"], o[\"name\"], o[\"area\"], o[\"color\"]);"
        "};"
        "E.scenenodes.addCustomObject = function(o) {"
        "	if (\"fontsize\" in o == false)"
        "   {                              "
        "     o[\"fontsize\"] = 16;        "
        "   }                              "
        "	if (\"color\" in o == false)   "
        "	{"
        "	   o[\"color\"] = aclr(255, 255, 255, 0);"
        "	}"
        "	if (\"name\" in o == false)   "
        "	{"
        "	   o[\"name\"] = \"\";"
        "	}"
        "	return E.scenenodes._addCustomObject(o[\"scene\"], o[\"schema\"], o[\"name\"], o[\"fontsize\"], o[\"text\"],  o[\"area\"], o[\"color\"]);"
        "};"
        "E.scenenodes.attr = function() {"  
        "	if (arguments.length == 2)"
        "	{"
        "		return E.scenenodes.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.scenenodes.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::initLayoutGridBindings(QScriptValue& v)
{
    QScriptValue layouts = m_engine->newObject();

    layouts.setProperty("list", m_engine->newFunction(scripting::layouts::list), m_flags); // E.layouts.list
    layouts.setProperty("query", m_engine->newFunction(scripting::layouts::query), m_flags); // E.layouts.query
    layouts.setProperty("add", m_engine->newFunction(scripting::layouts::add), m_flags); // E.layouts.add
    layouts.setProperty("remove", m_engine->newFunction(scripting::layouts::remove), m_flags); // E.layouts.remove
    layouts.setProperty("parent", m_engine->newFunction(scripting::layouts::parent), m_flags); // E.layouts.parent
    layouts.setProperty("LengthValue", m_engine->newFunction(scripting::layouts::length_value), m_flags); // E.layouts.LengthValue

    QScriptValue unit = m_engine->newObject();
    unit.setProperty("LU_Auto", QScriptValue(static_cast<unsigned int>(sad::layouts::LU_Auto)), m_flags);
    unit.setProperty("LU_Pixels", QScriptValue(static_cast<unsigned int>(sad::layouts::LU_Pixels)), m_flags);
    unit.setProperty("LU_Percents", QScriptValue(static_cast<unsigned int>(sad::layouts::LU_Percents)), m_flags);
    layouts.setProperty("Unit", unit); // E.layouts.Unit

    QScriptValue horizontal_alignment = m_engine->newObject();
    horizontal_alignment.setProperty("LHA_Left", QScriptValue(static_cast<unsigned int>(sad::layouts::LHA_Left)), m_flags);
    horizontal_alignment.setProperty("LHA_Middle", QScriptValue(static_cast<unsigned int>(sad::layouts::LHA_Middle)), m_flags);
    horizontal_alignment.setProperty("LHA_Right", QScriptValue(static_cast<unsigned int>(sad::layouts::LHA_Right)), m_flags);
    layouts.setProperty("HorizontalAlignment", horizontal_alignment); // E.layouts.HorizontalAlignment

    QScriptValue vertical_alignment = m_engine->newObject();
    vertical_alignment.setProperty("LVA_Top", QScriptValue(static_cast<unsigned int>(sad::layouts::LVA_Top)), m_flags);
    vertical_alignment.setProperty("LVA_Middle", QScriptValue(static_cast<unsigned int>(sad::layouts::LVA_Middle)), m_flags);
    vertical_alignment.setProperty("LVA_Bottom", QScriptValue(static_cast<unsigned int>(sad::layouts::LVA_Bottom)), m_flags);
    layouts.setProperty("VerticalAlignment", vertical_alignment); // E.layouts.VerticalAlignment

    QScriptValue stacking_type = m_engine->newObject();
    stacking_type.setProperty("LST_Horizontal", QScriptValue(static_cast<unsigned int>(sad::layouts::LST_Horizontal)), m_flags);
    stacking_type.setProperty("LST_Vertical", QScriptValue(static_cast<unsigned int>(sad::layouts::LST_Vertical)), m_flags);
    stacking_type.setProperty("LST_NoStacking", QScriptValue(static_cast<unsigned int>(sad::layouts::LST_NoStacking)), m_flags);
    layouts.setProperty("StackingType", stacking_type); // E.layouts.StackingType

    v.setProperty("layouts", layouts, m_flags); // E.layouts

    m_engine->evaluate(
        "E.layouts.Auto = function() { return E.layouts.LengthValue(E.layouts.Unit.LU_Auto, 0); };"
        "E.layouts.Pixels = function(a) { if (typeof a != \"number\") throw \"E.layouts.Pixels: first argument should be numeric\"; return E.layouts.LengthValue(E.layouts.Unit.LU_Pixels, a); };"
        "E.layouts.Percents = function(a) { if (typeof a != \"number\") throw \"E.layouts.Percents: first argument should be numeric\"; return E.layouts.LengthValue(E.layouts.Unit.LU_Percents, a); };"
    );
}

void scripting::Scripting::initWaysBindings(QScriptValue& v)
{
    QScriptValue ways = m_engine->newObject();

    ways.setProperty("list", m_engine->newFunction(scripting::ways::list), m_flags); // E.ways.list

    scripting::Callable* _add = scripting::make_scripting_call(scripting::ways::_add, this);
    _add->setName("_add");
    m_registered_classes << _add;
    ways.setProperty("_add", m_engine->newObject(_add), m_flags); // E.ways._add

    scripting::Callable* remove = scripting::make_scripting_call(scripting::ways::remove, this);
    remove->setName("remove");
    m_registered_classes << remove;
    ways.setProperty("remove", m_engine->newObject(remove), m_flags); // E.ways.remove

    scripting::Callable* length = scripting::make_scripting_call(scripting::ways::length, this);
    length->setName("length");
    m_registered_classes << length;
    ways.setProperty("length", m_engine->newObject(length), m_flags); // E.ways.length

    scripting::Callable* addPoint = scripting::make_scripting_call(scripting::ways::addPoint, this);
    addPoint->setName("addPoint");
    m_registered_classes << addPoint;
    ways.setProperty("addPoint", m_engine->newObject(addPoint), m_flags); // E.ways.addPoint

    scripting::Callable* removePoint = scripting::make_scripting_call(scripting::ways::removePoint, this);
    removePoint->setName("removePoint");
    m_registered_classes << removePoint;
    ways.setProperty("removePoint", m_engine->newObject(removePoint), m_flags); // E.ways.removePoint

    scripting::Callable* point = scripting::make_scripting_call(scripting::ways::point, this);
    point->setName("point");
    m_registered_classes << point;
    ways.setProperty("point", m_engine->newObject(point), m_flags); // E.ways.point

    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    set->add(new scripting::ways::Setter<sad::String, history::ways::ChangeName>(m_engine, "name"));
    set->add(new scripting::ways::Setter<double, history::ways::ChangeTotalTime>(m_engine, "totaltime"));
    set->add(new scripting::ways::Setter<bool, history::ways::ChangeClosed>(m_engine, "closed"));
    m_registered_classes << set;
    ways.setProperty("set", m_engine->newObject(set), m_flags); // E.ways.set


    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    get->add(new scripting::AbstractGetter<sad::p2d::app::Way*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::p2d::app::Way*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::p2d::app::Way*, unsigned long long>(m_engine, "minorid"));
    get->add(new scripting::AbstractGetter<sad::p2d::app::Way*, double>(m_engine, "totaltime"));
    get->add(new scripting::AbstractGetter<sad::p2d::app::Way*, bool>(m_engine, "closed"));
    m_registered_classes << get;
    ways.setProperty("get", m_engine->newObject(get), m_flags); // E.ways.get

    v.setProperty("ways", ways, m_flags); // E.ways

    m_engine->evaluate(
        "E.ways.add = function(o) {"  
        "   if (typeof o != \"object\")    "
        "   {                              "
        "      o = {};                     "
        "   }                              "
        "	if (\"name\" in o == false)    "
        "   {                              "
        "     o[\"name\"] = \"\";          "
        "   }                              "
        "	if (\"totaltime\" in o == false)   "
        "	{"
        "	   o[\"totaltime\"] = 0;       "
        "	}"
        "	if (\"closed\" in o == false)  "
        "	{"
        "	   o[\"closed\"] = false;      "
        "	}"
        "	if (\"points\" in o == false)  "
        "	{"
        "	   o[\"points\"] = [];         "
        "	}"
        "	return E.ways._add(o[\"name\"], o[\"totaltime\"], o[\"closed\"], o[\"points\"]);"
        "};"
        "E.ways.attr = function() {"  
        "	if (arguments.length == 2)"
        "	{"
        "		return E.ways.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.ways.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );
}


void scripting::Scripting::initDialoguesBindings(QScriptValue& v)
{
    QScriptValue dialogues = m_engine->newObject();

    dialogues.setProperty("list", m_engine->newFunction(scripting::dialogues::list), m_flags); // E.dialogues.list

    scripting::Callable* _add = scripting::make_scripting_call(scripting::dialogues::_add, this);
    _add->setName("_add");
    m_registered_classes << _add;
    dialogues.setProperty("_add", m_engine->newObject(_add), m_flags); // E.dialogues._add

    scripting::Callable* remove = scripting::make_scripting_call(scripting::dialogues::remove, this);
    remove->setName("remove");
    m_registered_classes << remove;
    dialogues.setProperty("remove", m_engine->newObject(remove), m_flags); // E.dialogues.remove

    scripting::Callable* addPhrase = scripting::make_scripting_call(scripting::dialogues::addPhrase, this);
    addPhrase->setName("addPhrase");
    m_registered_classes << addPhrase;
    dialogues.setProperty("addPhrase", m_engine->newObject(addPhrase), m_flags); // E.dialogues.addPhrase

    scripting::Callable* removePhrase = scripting::make_scripting_call(scripting::dialogues::removePhrase, this);
    removePhrase->setName("removePhrase");
    m_registered_classes << removePhrase;
    dialogues.setProperty("removePhrase", m_engine->newObject(removePhrase), m_flags); // E.dialogues.removePhrase

    scripting::Callable* length = scripting::make_scripting_call(scripting::dialogues::length, this);
    length->setName("length");
    m_registered_classes << length;
    dialogues.setProperty("length", m_engine->newObject(length), m_flags); // E.dialogues.length

    scripting::Callable* phrase = scripting::make_scripting_call(scripting::dialogues::phrase, this);
    phrase->setName("phrase");
    m_registered_classes << phrase;
    dialogues.setProperty("phrase", m_engine->newObject(phrase), m_flags); // E.dialogues.point

    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    set->add(new scripting::dialogues::Setter<sad::String, history::dialogues::ChangeName>(m_engine, "name"));
    m_registered_classes << set;
    dialogues.setProperty("set", m_engine->newObject(set), m_flags); // E.dialogues.set


    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    get->add(new scripting::AbstractGetter<sad::dialogue::Dialogue*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::dialogue::Dialogue*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::dialogue::Dialogue*, unsigned long long>(m_engine, "minorid"));
    m_registered_classes << get;
    dialogues.setProperty("get", m_engine->newObject(get), m_flags); // E.dialogues.get


    v.setProperty("dialogues", dialogues, m_flags); // E.dialogues

    m_engine->evaluate(
        "var phrase = function(actorName, actorPortrait, text, duration, viewHint) {"  
        "	return {\"actorName\" : actorName, \"actorPortrait\" : actorPortrait, \"text\": text, \"duration\": duration, \"viewHint\" : viewHint};"
        "};"
        "E.dialogues.add = function(o) {"  
        "   if (typeof o != \"object\")    "
        "   {                              "
        "      o = {};                     "
        "   }                              "
        "	if (\"name\" in o == false)    "
        "   {                              "
        "     o[\"name\"] = \"\";          "
        "   }                              "
        "	if (\"phrases\" in o == false) "
        "	{                              "
        "	   o[\"phrases\"] = [];        "
        "	}                              "
        "	return E.dialogues._add(o[\"name\"], o[\"phrases\"]);"
        "};"
        "E.dialogues.attr = function() {"  
        "	if (arguments.length == 2)"
        "	{"
        "		return E.dialogues.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.dialogues.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );
}


void scripting::Scripting::initAnimationsBindings(QScriptValue& v)
{
    QScriptValue animations = m_engine->newObject();
    
    animations.setProperty("list", m_engine->newFunction(scripting::animations::list), m_flags); // E.animations.list

    scripting::Callable* _add = scripting::make_scripting_call(scripting::animations::_add, this);
    _add->setName("_add");
    m_registered_classes << _add;
    animations.setProperty("_add", m_engine->newObject(_add), m_flags); // E.animations._add

    scripting::Callable* remove = scripting::make_scripting_call(scripting::animations::remove, this);
    remove->setName("remove");
    m_registered_classes << remove;
    animations.setProperty("remove", m_engine->newObject(remove), m_flags); // E.animations.remove

    scripting::Callable* addToComposite = scripting::make_scripting_call(scripting::animations::addToComposite, this);
    addToComposite->setName("addToComposite");
    m_registered_classes << addToComposite;
    animations.setProperty("addToComposite", m_engine->newObject(addToComposite), m_flags); // E.animations.addToComposite

    scripting::Callable* removeFromComposite = scripting::make_scripting_call(scripting::animations::removeFromComposite, this);
    removeFromComposite->setName("removeFromComposite");
    m_registered_classes << removeFromComposite;
    animations.setProperty("removeFromComposite", m_engine->newObject(removeFromComposite), m_flags); // E.animations.removeFromComposite

    scripting::Callable* compositeLength = scripting::make_scripting_call(scripting::animations::compositeLength, this);
    compositeLength->setName("compositeLength");
    m_registered_classes << compositeLength;
    animations.setProperty("compositeLength", m_engine->newObject(compositeLength), m_flags); // E.animations.compositeLength

    scripting::Callable* getAnimation = scripting::make_scripting_call(scripting::animations::getAnimation, this);
    getAnimation->setName("getAnimation");
    m_registered_classes << getAnimation;
    animations.setProperty("getAnimation", m_engine->newObject(getAnimation), m_flags); // E.animations.getAnimation

    scripting::Callable* moveBackInCompositeList = scripting::make_scripting_call(scripting::animations::moveBackInCompositeList, this);
    moveBackInCompositeList->setName("moveBackInCompositeList");
    m_registered_classes << moveBackInCompositeList;
    animations.setProperty("moveBackInCompositeList", m_engine->newObject(moveBackInCompositeList), m_flags); // E.animations.moveBackInCompositeList

    scripting::Callable* moveFrontInCompositeList = scripting::make_scripting_call(scripting::animations::moveFrontInCompositeList, this);
    moveFrontInCompositeList->setName("moveFrontInCompositeList");
    m_registered_classes << moveFrontInCompositeList;
    animations.setProperty("moveFrontInCompositeList", m_engine->newObject(moveFrontInCompositeList), m_flags); // E.animations.moveFrontInCompositeList


    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    set->add(new scripting::animations::Setter<sad::animations::Animation, sad::String, history::animations::ChangeName>(m_engine, "name"));
    set->add(new scripting::animations::Setter<sad::animations::Animation, double, history::animations::ChangeTime>(m_engine, "time"));
    set->add(new scripting::animations::Setter<sad::animations::Animation, bool, history::animations::ChangeLooped>(m_engine, "looped"));
    set->add(new scripting::animations::Setter<sad::animations::Blinking, unsigned int, history::animations::ChangeBlinkingFrequency>(m_engine, "frequency"));
    set->add(new scripting::animations::Setter<sad::animations::CameraShaking, sad::Point2D, history::animations::ChangeCameraOffset>(m_engine, "offset"));
    set->add(new scripting::animations::Setter<sad::animations::CameraShaking, int, history::animations::ChangeShakingFrequency>(m_engine, "frequency"));
    set->add(new scripting::animations::Setter<sad::animations::CameraRotation, sad::Point3D, history::animations::ChangeCameraPivot>(m_engine, "pivot"));

    gui::uiblocks::UIAnimationBlock* ablk = m_editor->uiBlocks()->uiAnimationBlock();
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::CameraRotation, 
                QDoubleSpinBox*,
                double, 
                history::animations::ChangeCameraAngle
            >(m_engine,  ablk->dsbCameraRotationStartingAngle, "min_angle")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::CameraRotation, 
                QDoubleSpinBox*,
                double, 
                history::animations::ChangeCameraAngle
            >(m_engine,  ablk->dsbCameraRotationEndingAngle, "max_angle")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::Color, 
                gui::colorview::ColorView*,
                sad::AColor, 
                history::animations::ChangeColorColor
            >(m_engine, ablk->cwColorStartingColor, "min_color")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::Color, 
                gui::colorview::ColorView*,
                sad::AColor, 
                history::animations::ChangeColorColor
            >(m_engine, ablk->cwColorEndingColor, "max_color")
    );
    set->add(new scripting::animations::Setter<sad::animations::FontList, sad::Vector<sad::String>, history::animations::ChangeFontListFonts>(m_engine, "fonts"));
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::FontSize, 
                QSpinBox*,
                unsigned int, 
                history::animations::ChangeFontSizeSize
            >(m_engine, ablk->sbFontSizeStartingSize, "min_size")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::FontSize, 
                QSpinBox*,
                unsigned int, 
                history::animations::ChangeFontSizeSize
            >(m_engine, ablk->sbFontSizeEndingSize, "max_size")
    );
    set->add(new scripting::animations::Setter<sad::animations::Resize, sad::Point2D, history::animations::ChangeResizeStartingSize>(m_engine, "start_size"));
    set->add(new scripting::animations::Setter<sad::animations::Resize, sad::Point2D, history::animations::ChangeResizeEndingSize>(m_engine, "end_size"));
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::Rotate, 
                QDoubleSpinBox*,
                double, 
                history::animations::ChangeRotateAngle
            >(m_engine, ablk->dsbRotateStartingAngle, "min_angle")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::Rotate, 
                QDoubleSpinBox*,
                double, 
                history::animations::ChangeRotateAngle
            >(m_engine, ablk->dsbRotateEndingAngle, "max_angle")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::OptionList, 
                QTextEdit*,
                sad::Vector<sad::String>, 
                history::animations::ChangeList
            >(m_engine, ablk->txtOptionListList, "list")
    );
    set->add(new scripting::animations::WidgetSetter<
                sad::animations::TextureCoordinatesList, 
                QTextEdit*,
                sad::Vector<sad::String>, 
                history::animations::ChangeList
            >(m_engine, ablk->txtTextureCoordinatesList, "list")
    );
    set->add(new scripting::animations::Point2DSetter<
                sad::animations::SimpleMovement, 
                history::animations::ChangePropertyAsPoint2DDisplayedInTwoSpinboxes
            >(m_engine, "start_point", ablk->dabSimpleMovementStartingPointX,ablk->dabSimpleMovementStartingPointY)
    );
    set->add(new scripting::animations::Point2DSetter<
                sad::animations::SimpleMovement, 
                history::animations::ChangePropertyAsPoint2DDisplayedInTwoSpinboxes
            >(m_engine, "end_point", ablk->dabSimpleMovementEndingPointX,ablk->dabSimpleMovementEndingPointY)
    );
    
    set->add(new scripting::animations::EasingSetter<
                unsigned int, 
                history::animations::ChangeEasingFunctionType
            >(m_engine, "easing_type", &sad::animations::easing::Function::functionTypeAsUnsignedInt)
    );
    set->add(new scripting::animations::EasingSetter<
                double, 
                history::animations::ChangeEasingOvershootAmplitude
            >(m_engine, "easing_overshoot_amplitude", &sad::animations::easing::Function::overshootAmplitude)
    );
    set->add(new scripting::animations::EasingSetter<
                double, 
                history::animations::ChangeEasingPeriod
            >(m_engine, "easing_period", &sad::animations::easing::Function::period)
    );


    scripting::animations::WidgetSetter<
        sad::animations::TextureCoordinatesContinuous,
        gui::rectwidget::RectWidget*,
        sad::Rect2D,
        history::animations::ChangeRect
    >* rect1 = new scripting::animations::WidgetSetter<
        sad::animations::TextureCoordinatesContinuous,
        gui::rectwidget::RectWidget*,
        sad::Rect2D,
        history::animations::ChangeRect
    >(m_engine,  ablk->rctTCCStartingRect, "start_rect");
    rect1->addCondition(new IsAABB());
    set->add(rect1);

    scripting::animations::WidgetSetter<
        sad::animations::TextureCoordinatesContinuous,
        gui::rectwidget::RectWidget*,
        sad::Rect2D,
        history::animations::ChangeRect
    >* rect2 = new scripting::animations::WidgetSetter<
        sad::animations::TextureCoordinatesContinuous,
        gui::rectwidget::RectWidget*,
        sad::Rect2D,
        history::animations::ChangeRect
    >(m_engine,  ablk->rctTCCEndingRect, "end_rect");
    rect2->addCondition(new IsAABB());
    set->add(rect2);

    set->add(new scripting::animations::WaySetter(m_engine));
    m_registered_classes << set;
    animations.setProperty("set", m_engine->newObject(set), m_flags); // E.animations.set

    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    get->add(new scripting::AbstractGetter<sad::animations::Animation*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::animations::Animation*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Animation*, unsigned long long>(m_engine, "minorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Animation*, double>(m_engine, "time"));
    get->add(new scripting::AbstractGetter<sad::animations::Animation*, bool>(m_engine, "looped"));
    get->add(new scripting::animations::EasingGetter<unsigned int>(m_engine, "easing_type", &sad::animations::easing::Function::functionTypeAsUnsignedInt));
    get->add(new scripting::animations::EasingGetter<double>(m_engine, "easing_overshoot_amplitude", &sad::animations::easing::Function::overshootAmplitude));
    get->add(new scripting::animations::EasingGetter<double>(m_engine, "easing_period", &sad::animations::easing::Function::period));
    get->add(new scripting::AbstractGetter<sad::animations::Blinking*, unsigned int>(m_engine, "frequency"));	
    get->add(new scripting::AbstractGetter<sad::animations::CameraShaking*, sad::Point2D>(m_engine, "offset"));
    get->add(new scripting::AbstractGetter<sad::animations::CameraShaking*, int>(m_engine, "frequency"));
    get->add(new scripting::AbstractGetter<sad::animations::CameraRotation*, sad::Point3D>(m_engine, "pivot"));
    get->add(new scripting::AbstractGetter<sad::animations::CameraRotation*, double>(m_engine, "min_angle"));
    get->add(new scripting::AbstractGetter<sad::animations::CameraRotation*, double>(m_engine, "max_angle"));	
    get->add(new scripting::AbstractGetter<sad::animations::Color*, sad::AColor>(m_engine, "min_color"));
    get->add(new scripting::AbstractGetter<sad::animations::Color*, sad::AColor>(m_engine, "max_color"));	
    get->add(new scripting::AbstractGetter<sad::animations::FontList*, sad::Vector<sad::String> >(m_engine, "fonts"));	
    get->add(new scripting::AbstractGetter<sad::animations::FontSize*, unsigned int >(m_engine, "min_size"));	
    get->add(new scripting::AbstractGetter<sad::animations::FontSize*, unsigned int >(m_engine, "max_size"));
    get->add(new scripting::AbstractGetter<sad::animations::Resize*, sad::Point2D >(m_engine, "start_size"));
    get->add(new scripting::AbstractGetter<sad::animations::Resize*, sad::Point2D >(m_engine, "end_size"));	
    get->add(new scripting::AbstractGetter<sad::animations::Rotate*, double >(m_engine, "min_angle"));
    get->add(new scripting::AbstractGetter<sad::animations::Rotate*, double >(m_engine, "max_angle"));	
    get->add(new scripting::AbstractGetter<sad::animations::SimpleMovement*, sad::Point2D>(m_engine, "start_point"));	
    get->add(new scripting::AbstractGetter<sad::animations::SimpleMovement*, sad::Point2D>(m_engine, "end_point"));		
    get->add(new scripting::AbstractGetter<sad::animations::OptionList*, sad::Vector<sad::String> >(m_engine, "list"));
    get->add(new scripting::AbstractGetter<sad::animations::TextureCoordinatesContinuous*, sad::Rect2D >(m_engine, "start_rect"));
    get->add(new scripting::AbstractGetter<sad::animations::TextureCoordinatesContinuous*, sad::Rect2D >(m_engine, "end_rect"));
    get->add(new scripting::AbstractGetter<sad::animations::TextureCoordinatesList*, sad::Vector<sad::String> >(m_engine, "list"));
    get->add(new scripting::AbstractGetter<sad::animations::WayMoving*, unsigned long long >(m_engine, "way"));
    get->add(new scripting::AbstractGetter<sad::animations::Composite*, sad::Vector<unsigned long long> >(m_engine, "list"));
    
    m_registered_classes << get;
    animations.setProperty("get", m_engine->newObject(get), m_flags); // E.animations.set


    v.setProperty("animations", animations, m_flags); // E.animations
    
    QString templateanimationadd(
        "E.animations.add{CLASSNAME} = function(o) {"
        "   if (typeof o != \"object\")    "
        "   {                              "
        "      o = {};                     "
        "   }                              "
        "	if (\"name\" in o == false)    "
        "   {                              "
        "     o[\"name\"] = \"\";          "
        "   }                              "
        "	if (\"time\" in o == false)    "
        "	{                              "
        "	   o[\"time\"] = 0;            "
        "	}                              "
        "	if (\"looped\" in o == false)  "
        "	{                              "
        "	   o[\"looped\"] = false;      "
        "	}                              "
        "	return E.animations._add(\"{CLASSNAME}\", o[\"name\"], o[\"time\"], o[\"looped\"]);"
        "};"
    );

    const char* names[] = {
       "Blinking",
       "CameraRotation",
       "CameraShaking",
       "Color",
       "FontList",
       "FontSize",
       "OptionList",
       "Parallel",
       "Resize",
       "Rotate",
       "SimpleMovement",
       "Sequential",
       "TextureCoordinatesList",
       "TextureCoordinatesContinuous",
       "Typing",
       "WayMoving",
       NULL
    };
    int i =0;
    while(names[i] != 0) {
        QString kadd = templateanimationadd;
        kadd.replace("{CLASSNAME}",names[i]);
        m_engine->evaluate(kadd);
        ++i;
    }
        
    m_engine->evaluate(
        "E.animations.attr = function() {"  
        "	if (arguments.length == 2)"
        "	{"
        "		return E.animations.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.animations.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );

    m_engine->evaluate(
        "E.animations.easingsToNames = ["
        "\"Linear\","
        "\"InSine\","
        "\"OutSine\","
        "\"InOutSine\","
        "\"InQuad\","
        "\"OutQuad\","
        "\"InOutQuad\","
        "\"InCubic\","
        "\"OutCubic\","
        "\"InOutCubic\","
        "\"InQuart\","
        "\"OutQuart\","
        "\"InOutQuart\","
        "\"InQuint\","
        "\"OutQuint\","
        "\"InOutQuint\","
        "\"InExpo\","
        "\"OutExpo\","
        "\"InOutExpo\","
        "\"InCirc\","
        "\"OutCirc\","
        "\"InOutCirc\","
        "\"InElastic\","
        "\"OutElastic\","
        "\"InOutElastic\","
        "\"InBack\","
        "\"OutBack\","
        "\"InOutBack\","
        "\"InBounce\","
        "\"OutBounce\","
        "\"InOutBounce\""
        "];" 
        "E.animations.easing = function(a)"
        "{"
        "  if (typeof(a) == \"string\") return E.animations.easingsToNames.indexOf(a); else return  E.animations.easingsToNames[a]; "
        "};"
    );
}

void scripting::Scripting::initAnimationInstanceBindings(QScriptValue& v)
{
    QScriptValue instances = m_engine->newObject();

    instances.setProperty("list", m_engine->newFunction(scripting::instances::list), m_flags); // E.animations.instances.list

    scripting::Callable* _addInstance = scripting::make_scripting_call(scripting::instances::_addInstance, this);
    _addInstance->setName("_addInstance");
    m_registered_classes << _addInstance;
    instances.setProperty("_addInstance", m_engine->newObject(_addInstance), m_flags); // E.animations.instances._addInstance

    scripting::Callable* _addWayInstance = scripting::make_scripting_call(scripting::instances::_addWayInstance, this);
    _addWayInstance->setName("_addWayInstance");
    m_registered_classes << _addWayInstance;
    instances.setProperty("_addWayInstance", m_engine->newObject(_addWayInstance), m_flags); // E.animations.instances._addWayInstance

    scripting::Callable* remove = scripting::make_scripting_call(scripting::instances::remove, this);
    remove->setName("remove");
    m_registered_classes << remove;
    instances.setProperty("remove", m_engine->newObject(remove), m_flags); // E.animations.instances.remove

    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    set->add(new scripting::instances::NameSetter(m_engine));
    set->add(new scripting::instances::AnimationSetter(m_engine));
    set->add(new scripting::instances::AnimationDBSetter(m_engine));
    set->add(new scripting::instances::ObjectSetter(m_engine));
    set->add(new scripting::instances::StartTimeSetter(m_engine));
    set->add(new scripting::instances::WaySetter(m_engine));
    
    m_registered_classes << set;
    instances.setProperty("set", m_engine->newObject(set), m_flags); // E.animations.instances.set


    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, unsigned long long>(m_engine, "minorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, sad::String>(m_engine, "animation"));
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, unsigned long long>(m_engine, "animationmajorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, unsigned long long>(m_engine, "object"));
    get->add(new scripting::AbstractGetter<sad::animations::Instance*, double>(m_engine, "starttime"));
    get->add(new scripting::AbstractGetter<sad::animations::WayInstance*, unsigned long long>(m_engine, "way"));
    
    m_registered_classes << get;
    instances.setProperty("get", m_engine->newObject(get), m_flags); // E.animations.instances.get

    v.property("animations").setProperty("instances", instances, m_flags);

    m_engine->evaluate(
        "E.animations.instances.addInstance = function(o) {"
        "   if (typeof o != \"object\")    "
        "   {                              "
        "      o = {};                     "
        "   }                              "
        "   if (\"animation\" in o == false)"
        "   {                              "
        "     o[\"animationid\"] = 0; o[\"animationname\"] =\"\"; "
        "   }                              "
        "   else                           "
        "   {                              "
        "        if (typeof o[\"animation\"] == \"string\") "
        "        {                         "
        "             o[\"animationid\"] = 0; o[\"animationname\"] = o[\"animation\"]; "
        "        }                         "
        "        else "
        "        {                         "
        "             o[\"animationid\"] = o[\"animation\"]; o[\"animationname\"] = \"\"; "
        "        }                         "
        "   }"
        "	if (\"name\" in o == false)    "
        "   {                              "
        "     o[\"name\"] = \"\";          "
        "   }                              "
        "	if (\"object\" in o == false)  "
        "	{                              "
        "	   o[\"object\"] = 0;          "
        "	}                              "
        "	if (\"starttime\" in o == false)    "
        "	{                              "
        "	   o[\"starttime\"] = 0;            "
        "	}                              "
        "	return E.animations.instances._addInstance(o[\"name\"], o[\"animationid\"], o[\"animationname\"], o[\"object\"], o[\"starttime\"]);"
        "};"
        "E.animations.instances.addWayInstance = function(o) {"
        "   if (typeof o != \"object\")    "
        "   {                              "
        "      o = {};                     "
        "   }                              "
        "	if (\"name\" in o == false)    "
        "   {                              "
        "     o[\"name\"] = \"\";          "
        "   }                              "
        "	if (\"way\" in o == false)     "
        "	{                              "
        "	   o[\"way\"] = 0;             "
        "	}                              "
        "	if (\"object\" in o == false)  "
        "	{                              "
        "	   o[\"object\"] = 0;          "
        "	}                              "
        "	if (\"starttime\" in o == false)    "
        "	{                              "
        "	   o[\"starttime\"] = 0;            "
        "	}                              "
        "	return E.animations.instances._addWayInstance(o[\"name\"], o[\"way\"], o[\"object\"], o[\"starttime\"]);"
        "};"
        "E.animations.instances.attr = function() {"
        "	if (arguments.length == 2)"
        "	{"
        "		return E.animations.instances.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.animations.instances.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );
}


void scripting::Scripting::initAnimationGroupBindings(QScriptValue& v)
{
    QScriptValue groups = m_engine->newObject();

    groups.setProperty("list", m_engine->newFunction(scripting::groups::list), m_flags); // E.animations.groups.list

    scripting::Callable* _add = scripting::make_scripting_call(scripting::groups::_add, this);
    _add->setName("_add");
    m_registered_classes << _add;
    groups.setProperty("_add", m_engine->newObject(_add), m_flags); // E.animations.groups._add

    scripting::Callable* remove = scripting::make_scripting_call(scripting::groups::remove, this);
    remove->setName("remove");
    m_registered_classes << remove;
    groups.setProperty("remove", m_engine->newObject(remove), m_flags); // E.animations.groups.remove

    scripting::Callable* length = scripting::make_scripting_call(scripting::groups::length, this);
    length->setName("length");
    m_registered_classes << length;
    groups.setProperty("length", m_engine->newObject(length), m_flags); // E.animations.groups.length

    scripting::Callable* entry = scripting::make_scripting_call(scripting::groups::entry, this);
    entry->setName("entry");
    m_registered_classes << entry;
    groups.setProperty("entry", m_engine->newObject(entry), m_flags); // E.animations.groups.entry

    scripting::Callable* addInstance = scripting::make_scripting_call(scripting::groups::addInstance, this);
    addInstance->setName("addInstance");
    m_registered_classes << addInstance;
    groups.setProperty("addInstance", m_engine->newObject(addInstance), m_flags); // E.animations.groups.addInstance

    scripting::Callable* removeInstance = scripting::make_scripting_call(scripting::groups::removeInstance, this);
    removeInstance->setName("removeInstance");
    m_registered_classes << removeInstance;
    groups.setProperty("removeInstance", m_engine->newObject(removeInstance), m_flags); // E.animations.groups.removeInstance


    scripting::MultiMethod* set = new scripting::MultiMethod(m_engine, "set");
    set->add(new scripting::groups::NameSetter(m_engine));
    set->add(new scripting::groups::LoopedSetter(m_engine));
    set->add(new scripting::groups::SequentialSetter(m_engine));
    
    m_registered_classes << set;
    groups.setProperty("set", m_engine->newObject(set), m_flags); // E.animations.groups.set


    scripting::MultiMethod* get = new scripting::MultiMethod(m_engine, "get");
    get->add(new scripting::AbstractGetter<sad::animations::Group*, sad::String>(m_engine, "name"));
    get->add(new scripting::AbstractGetter<sad::animations::Group*, unsigned long long>(m_engine, "majorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Group*, unsigned long long>(m_engine, "minorid"));
    get->add(new scripting::AbstractGetter<sad::animations::Group*, bool>(m_engine, "looped"));
    get->add(new scripting::AbstractGetter<sad::animations::Group*, bool>(m_engine, "sequential"));
    get->add(new scripting::AbstractGetter<sad::animations::Group*, sad::Vector<unsigned long long> >(m_engine, "instances"));
    
    m_registered_classes << get;
    groups.setProperty("get", m_engine->newObject(get), m_flags); // E.scenes.set

    v.property("animations").setProperty("groups", groups, m_flags);


    m_engine->evaluate(
         "E.animations.groups.add = function(o) {"
        "   if (typeof o != \"object\")    "
        "   {                              "
        "      o = {};                     "
        "   }                              "
        "	if (\"name\" in o == false)    "
        "   {                              "
        "     o[\"name\"] = \"\";          "
        "   }                              "
        "	if (\"looped\" in o == false)  "
        "	{                              "
        "	   o[\"looped\"] = false;      "
        "	}                              "
        "	return E.animations.groups._add(o[\"name\"], o[\"looped\"]);"
        "};"
        "E.animations.groups.attr = function() {"
        "	if (arguments.length == 2)"
        "	{"
        "		return E.animations.groups.get(arguments[0], arguments[1]);"
        "	}"
        "	if (arguments.length == 3)"
        "	{"
        "		return E.animations.groups.set(arguments[0], arguments[1], arguments[2]);"
        "	}"
        "	throw new Error(\"Specify 2 or 3 arguments\");"
        "};"
    );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::saveScript()
{
    QString name = QFileDialog::getSaveFileName(this->editor()->panelAsWidget(), "Enter file, where we should store source code", "", "*.js");
    if (name.length() != 0)
    {
        QFile file(name);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            gui::uiblocks::UIConsoleBlock* cblk = m_editor->uiBlocks()->uiConsoleBlock();
            stream << cblk->txtConsoleCode->toPlainText();
        }
        else
        {
            QMessageBox::critical(this->editor()->panelAsWidget(), "Saddy Interface Editor", "Cannot open file " + name);
        }
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void scripting::Scripting::loadScript()
{
    QString name = QFileDialog::getOpenFileName(this->editor()->panelAsWidget(), "Enter file, where code is stored", "", "*.js");
    if (name.length() != 0)
    {
        QFile file(name);
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            QString string;
            string = stream.readAll();
            gui::uiblocks::UIConsoleBlock* cblk = m_editor->uiBlocks()->uiConsoleBlock();
            cblk->txtConsoleCode->setPlainText(string);
        }
        else
        {
            QMessageBox::critical(this->editor()->panelAsWidget(), "Saddy Interface Editor", "Cannot open file " + name);
        }
    }
}

