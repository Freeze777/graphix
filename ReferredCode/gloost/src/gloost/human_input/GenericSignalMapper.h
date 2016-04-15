
/*
                       ___                            __
                      /\_ \                          /\ \__
                   __ \//\ \     ___     ___     ____\ \  _\
                 /'_ `\ \ \ \   / __`\  / __`\  /  __\\ \ \/
                /\ \ \ \ \_\ \_/\ \ \ \/\ \ \ \/\__   \\ \ \_
                \ \____ \/\____\ \____/\ \____/\/\____/ \ \__\
                 \/___/\ \/____/\/___/  \/___/  \/___/   \/__/
                   /\____/
                   \_/__/

                   OpenGL framework for fast demo programming

                             http://www.gloost.org

    This file is part of the gloost framework. You can use it in parts or as
       whole under the terms of the GPL (http://www.gnu.org/licenses/#GPL).
*/



#ifndef H_GLOOST_HUMANINPUT_GENERICSIGNALMAPPER
#define H_GLOOST_HUMANINPUT_GENERICSIGNALMAPPER



// gloost system includes
#include <gloost/gloostConfig.h>
//#include <gloost/gloostMath.h>


// cpp includes
#include <string>
#include <memory>
#include <unordered_map>
#include <set>



namespace gloost
{
namespace human_input
{


  //  Mapps events to another
template <class SourceType, class DestType>
class GenericSignalMapper
{
	public:

    /// a std::shared_ptr of an GenericSignalMapper instance
    typedef std::shared_ptr<GenericSignalMapper<SourceType, DestType> >       shared_ptr;
    typedef std::shared_ptr<const GenericSignalMapper<SourceType, DestType> > const_shared_ptr;

    typedef std::unordered_map<SourceType, DestType> MappingsContainer;
    typedef std::set<DestType>                       OccurentsContainer;


    ////////////////////////////////////////////////////////////////////////////////


    // class factoy
    static shared_ptr create()
    {
      auto instance = new GenericSignalMapper<SourceType, DestType>();
      return std::shared_ptr<GenericSignalMapper<SourceType, DestType> >(instance);
    }


    ////////////////////////////////////////////////////////////////////////////////


    // class destructor
	  virtual ~GenericSignalMapper()
	  {

	  }


    ////////////////////////////////////////////////////////////////////////////////


    // inits the GenericSignalMapper
	  void
	  addMapping(SourceType source, DestType destination)
	  {
	    _mappings[source] = destination;
	  }


    ////////////////////////////////////////////////////////////////////////////////


    // inits the GenericSignalMapper
	  void
	  removeMapping(SourceType source, DestType destination)
	  {
	    _mappings.erase[source];
	  }


    ////////////////////////////////////////////////////////////////////////////////


    // inits the GenericSignalMapper
	  void
	  mappingExistsFor(SourceType source)
	  {
	    return ( _mappings.find(source) != _mappings.end() );
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   must be called if an source event occures
      \param   ...
      \remarks ...
    */

    virtual
	  void
	  frameStep()
	  {
	    _lastFramesSignals = _currentEvents;
	    _currentEvents.clear();
	    _thisFramesNewSignals.clear();
	    _thisFramesExpiredSignals.clear();
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   must be called if an Event happened
      \param   ...
      \remarks ...
    */

	  bool
	  onNotifySignal(SourceType source)
	  {
	    auto it = _mappings.find(source);
	    if (it != _mappings.end())
      {
        const auto& dest = it->second;

        // is it a new signal
        if ( _lastFramesSignals.find(dest) == _lastFramesSignals.end() )
        {
          _thisFramesNewSignals.insert(dest);
        }
        // is it a persisting event
        _currentEvents.insert(dest);
        return true;
      }
      return false;
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   returns true if the signal destTypeEntity had started in this frame
      \param   ...
      \remarks ...
    */

	  bool
	  signalHasStarted(DestType destTypeEntity)
	  {
	    return _thisFramesNewSignals.find(destTypeEntity) != _thisFramesNewSignals.end();
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   returns true if the signal destTypeEntity was notified in this frame
      \param   ...
      \remarks ...
    */

	  bool
	  signalExists(DestType destTypeEntity) const
	  {
	    return _currentEvents.find(destTypeEntity) != _currentEvents.end();
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   returns true if the signal destTypeEntity had started in this frame
      \param   ...
      \remarks ...
    */

	  bool
	  signalEnded(DestType destTypeEntity) const
	  {
	    return     (_currentEvents.find(destTypeEntity) == _currentEvents.end())
	            && (_lastFramesSignals.find(destTypeEntity) != _lastFramesSignals.end());
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   must be called once a "frame" to reset events
      \param   ...
      \remarks ...
    */

	  const MappingsContainer&
	  getMappings() const
	  {
	    return _mappings;
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   must be called once a "frame" to reset events
      \param   ...
      \remarks ...
    */

	  const OccurentsContainer&
	  getCurrentEvents() const
	  {
	    return _currentEvents;
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   must be called once a "frame" to reset events
      \param   ...
      \remarks ...
    */

	  const OccurentsContainer&
	  getThisFramesNewSignals() const
	  {
	    return _thisFramesNewSignals;
	  }


    ////////////////////////////////////////////////////////////////////////////////

    /**
      \brief   must be called once a "frame" to reset events
      \param   ...
      \remarks ...
    */

	  const OccurentsContainer&
	  getThisFramesExpiredSignals() const
	  {
	    return _thisFramesExpiredSignals;
	  }


	protected:

    // class constructor
    GenericSignalMapper():
      _mappings(),
      _currentEvents()
    {

    }

    ////////////////////////////////////////////////////////////////////////////////

    MappingsContainer   _mappings;
    OccurentsContainer  _currentEvents;
    OccurentsContainer  _lastFramesSignals;
    OccurentsContainer  _thisFramesNewSignals;
    OccurentsContainer  _thisFramesExpiredSignals;

	private:

   // ...

};


} // namespace human_input
} // namespace gloost


#endif // H_GLOOST_HUMANINPUT_GENERICSIGNALMAPPER


