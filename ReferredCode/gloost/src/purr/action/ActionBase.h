
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

             __ __ __
            |  |__|  |--.-----.--.--.----.----.         )\._.,--....,'``.
            |  |  |  _  |  _  |  |  |   _|   _|        /;   _.. \   _\  (`._ ,.
            |__|__|_____|   __|_____|__| |__|         `----(,_..'--(,_..'`-.;.'
                        |__|
*/


#ifndef H_PURR_ACTION_ACTIONBASE
#define H_PURR_ACTION_ACTIONBASE

// gloost system includes
//#include <gloost/gloostConfig.h>


// cpp includes
#include <string>
#include <memory>
#include <unordered_map>


namespace purr
{

  namespace model { class Node; }

namespace action
{

  // CallOrder type and defaults
  typedef std::string CallOrder;
  const static std::string call(      "purr::action::call");
  const static std::string callUpwards(   "purr::action::callUpwards");
  const static std::string callSubnodes(  "purr::action::callSubnodes");
  const static std::string callSiblings(  "purr::action::callSiblings");


  // base class of all action/traverser

class ActionBase : public std::enable_shared_from_this<ActionBase>
{
	public:

	  enum class TraversalHint : char
	  {
      exit = 0, proceed, repeat, repeatParent, done
	  };

//    /// a std::shared_ptr of an ActionBase instance
//    typedef std::shared_ptr<ActionBase>       shared_ptr;
//    typedef std::shared_ptr<const ActionBase> const_shared_ptr;
//
//    // creator
//    static shared_ptr create();


    // class destructor
    virtual ~ActionBase();


    // returns the type of the action
    virtual const std::string& getType() const;

    // begins the traversal on a specific node
    virtual void begin(const std::shared_ptr<model::Node>& startNode);


	protected:

    // class constructor
    ActionBase(const std::string& type);

    /// map of event name -> std::function
    std::unordered_map<std::string,
                       std::function<void(void)> > _traversOrders;

	private:

    std::string _type;


};


} // namespace action
} // namespace purr


#endif // H_PURR_ACTION_ACTIONBASE


