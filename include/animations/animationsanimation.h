/*! \file animationsanimation.h
    \author HiddenSeeker

    Defines a basic class for all kind of animation as a resource in project
 */
#pragma once

#include "../resource/resource.h"


namespace sad
{

namespace animations
{

class Instance;

class Animation: public sad::resource::Resource
{
SAD_OBJECT
public:
    /*! Creates new empty animation
     */
    Animation();
    /*! Must be inherited
     */
    virtual ~Animation();
    /*! Tries to load animation from value
        \param[in] v value
        \return whether it was successfull
     */
    virtual bool loadFromValue(const picojson::value& v);
    /*! Sets, whether animation is looped
        \param[in] looped whether animation is looped
     */
    void setLooped(bool looped);
    /*! Returs, whether animation is looped
        \return whether animation is looped
     */
    bool looped() const;
    /*! Sets playback time for animation
        \param time a playback time for animation
     */
    void setTime(double time);
    /*! Returns playback time for animation
        \return playback time for animation
     */
    double time() const;
    /*! Sets state of object from animation
        \param[in] o object
        \param[in] time a time of playing of animation
     */
    virtual void setState(sad::db::Object* o, double time) = 0;
    /*! Saves states of object in animation instance
        \param[in] i an animation instance
     */
    virtual void saveState(sad::animations::Instance* i) = 0;
    /*! Resets state of object in animation instance, when animation ended
        \param[in] i an animation instance
     */
    virtual void resetState(sad::animations::Instance* i) = 0;
protected:
    /*! Loads an animation from specified file, using specified renderer for resolving some
        properties.
        \param[in] file a file, via which a resource should be loaded
        \param[in] r  a renderer, which resource should be linked to (NULL if global renderer)
        \param[in] options  an options for loading a resource
        \return whether loading was successfull
     */
    virtual bool load(
        const sad::resource::PhysicalFile & file,
        sad::Renderer * r,
        const picojson::value& options
    );
    /*! Whether animation is looped
     */
    bool m_looped;
    /*! A total time of animation playback
     */
    double m_time;
};

}

}

DECLARE_TYPE_AS_SAD_OBJECT_ENUM(sad::animations::Animation)